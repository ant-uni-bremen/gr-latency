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

#ifndef INCLUDED_LATENCY_STREAM_TIME_STAMPER_IMPL_H
#define INCLUDED_LATENCY_STREAM_TIME_STAMPER_IMPL_H

#include <latency/stream_time_stamper.h>

namespace gr {
namespace latency {

class stream_time_stamper_impl : public stream_time_stamper
{
private:
    size_t d_sizeof_stream_item;
    std::string d_key_string;
    pmt::pmt_t d_key;
    int d_packet_len;

public:
    stream_time_stamper_impl(size_t sizeof_stream_item,
                             const std::string& key_string,
                             int packet_len);
    ~stream_time_stamper_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace latency
} // namespace gr

#endif /* INCLUDED_LATENCY_STREAM_TIME_STAMPER_IMPL_H */
