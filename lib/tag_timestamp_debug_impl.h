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

#ifndef INCLUDED_LATENCY_TAG_TIMESTAMP_DEBUG_IMPL_H
#define INCLUDED_LATENCY_TAG_TIMESTAMP_DEBUG_IMPL_H

#include <latency/tag_timestamp_debug.h>

namespace gr {
namespace latency {

class tag_timestamp_debug_impl : public tag_timestamp_debug
{
private:
    std::string d_name;
    std::string d_key_name;
    pmt::pmt_t d_key;

public:
    tag_timestamp_debug_impl(size_t sizeof_stream_item,
                             const std::string& key_name,
                             const std::string& name);
    ~tag_timestamp_debug_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace latency
} // namespace gr

#endif /* INCLUDED_LATENCY_TAG_TIMESTAMP_DEBUG_IMPL_H */
