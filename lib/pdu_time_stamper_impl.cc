/* -*- c++ -*- */
/*
 * Copyright 2020 Johannes Demel.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "pdu_time_stamper_impl.h"
#include <chrono>

namespace gr {
  namespace latency {

    pdu_time_stamper::sptr
    pdu_time_stamper::make(const std::string& key_string)
    {
      return gnuradio::get_initial_sptr
        (new pdu_time_stamper_impl(key_string));
    }


    /*
     * The private constructor
     */
    pdu_time_stamper_impl::pdu_time_stamper_impl(const std::string& key_string)
      : gr::sync_block("pdu_time_stamper",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        d_timestamp_str(key_string),
        d_timestamp_key(pmt::string_to_symbol(key_string))
    {
      message_port_register_out(pmt::string_to_symbol("PDUout"));
      message_port_register_in(pmt::string_to_symbol("PDUin"));
      set_msg_handler(pmt::string_to_symbol("PDUin"), 
                      boost::bind(&pdu_time_stamper_impl::handle_msg, this, _1));
    }

    /*
     * Our virtual destructor.
     */
    pdu_time_stamper_impl::~pdu_time_stamper_impl()
    {
    }

    void pdu_time_stamper_impl::handle_msg(pmt::pmt_t pdu)
    {
      // add the field and publish
      pmt::pmt_t meta = pmt::car(pdu);
      if (pmt::is_null(meta)) {
          meta = pmt::make_dict();
      } else if (!pmt::is_dict(meta)) {
          throw std::runtime_error("pdu_set received non PDU input");
      }
      const auto ticks = std::chrono::high_resolution_clock::now().time_since_epoch();
      meta = pmt::dict_add(meta, d_timestamp_key, pmt::from_long(ticks.count()));
      message_port_pub(pmt::string_to_symbol("PDUout"), pmt::cons(meta, pmt::cdr(pdu)));
    }

    int
    pdu_time_stamper_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace latency */
} /* namespace gr */

