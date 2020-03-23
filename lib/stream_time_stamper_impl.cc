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

#include "stream_time_stamper_impl.h"
#include <gnuradio/io_signature.h>
#include <chrono>
#include <cstring>

namespace gr {
namespace latency {

stream_time_stamper::sptr stream_time_stamper::make(size_t sizeof_stream_item,
                                                    const std::string& key_string,
                                                    int packet_len)
{
    return gnuradio::get_initial_sptr(
        new stream_time_stamper_impl(sizeof_stream_item, key_string, packet_len));
}


/*
 * The private constructor
 */
stream_time_stamper_impl::stream_time_stamper_impl(size_t sizeof_stream_item,
                                                   const std::string& key_string,
                                                   int packet_len)
    : gr::sync_block("stream_time_stamper",
                     gr::io_signature::make(1, 1, sizeof_stream_item),
                     gr::io_signature::make(1, 1, sizeof_stream_item)),
      d_sizeof_stream_item(sizeof_stream_item),
      d_key_string(key_string),
      d_key(pmt::mp(key_string)),
      d_packet_len(packet_len)
{
}

/*
 * Our virtual destructor.
 */
stream_time_stamper_impl::~stream_time_stamper_impl() {}

int stream_time_stamper_impl::work(int noutput_items,
                                   gr_vector_const_void_star& input_items,
                                   gr_vector_void_star& output_items)
{
    const void* in = (const void*)input_items[0];
    void* out = (void*)output_items[0];
    memcpy(out, in, noutput_items * d_sizeof_stream_item);

    const auto nitems = nitems_read(0);
    for (int i = 0; i < noutput_items; ++i) {
        if ((nitems + i) % d_packet_len == 0) {
            const auto ticks =
                std::chrono::high_resolution_clock::now().time_since_epoch();
            add_item_tag(0, nitems + i, d_key, pmt::from_long(ticks.count()));
        }
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace latency */
} /* namespace gr */
