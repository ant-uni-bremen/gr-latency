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

#ifndef INCLUDED_LATENCY_PDU_TIME_STAMPER_IMPL_H
#define INCLUDED_LATENCY_PDU_TIME_STAMPER_IMPL_H

#include <latency/pdu_time_stamper.h>

namespace gr {
namespace latency {

class pdu_time_stamper_impl : public pdu_time_stamper
{
private:
    pmt::pmt_t d_timestamp_key;
    std::string d_timestamp_str;
    std::string d_log_name;

public:
    pdu_time_stamper_impl(const std::string& key_string, const std::string& name);
    ~pdu_time_stamper_impl();

    // Where all the action really happens
    void handle_msg(pmt::pmt_t pdu);

    // A dummy
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace latency
} // namespace gr

#endif /* INCLUDED_LATENCY_PDU_TIME_STAMPER_IMPL_H */
