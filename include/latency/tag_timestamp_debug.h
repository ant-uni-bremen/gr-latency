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

#ifndef INCLUDED_LATENCY_TAG_TIMESTAMP_DEBUG_H
#define INCLUDED_LATENCY_TAG_TIMESTAMP_DEBUG_H

#include <gnuradio/sync_block.h>
#include <latency/api.h>

namespace gr {
namespace latency {

/*!
 * \brief Pick up timestamp and print time difference
 * \ingroup latency
 *
 */
class LATENCY_API tag_timestamp_debug : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<tag_timestamp_debug> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of latency::tag_timestamp_debug.
     *
     * To avoid accidental use of raw pointers, latency::tag_timestamp_debug's
     * constructor is in a private implementation
     * class. latency::tag_timestamp_debug::make is the public interface for
     * creating new instances.
     */
    static sptr
    make(size_t sizeof_stream_item, const std::string& key_name, const std::string& name);
};

} // namespace latency
} // namespace gr

#endif /* INCLUDED_LATENCY_TAG_TIMESTAMP_DEBUG_H */
