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

#ifndef INCLUDED_LATENCY_PDU_TIME_STAMPER_H
#define INCLUDED_LATENCY_PDU_TIME_STAMPER_H

#include <gnuradio/sync_block.h>
#include <latency/api.h>

namespace gr {
namespace latency {

/*!
 * \brief Add a timestamp to each PDU
 * \ingroup latency
 *
 */
class LATENCY_API pdu_time_stamper : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<pdu_time_stamper> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of latency::pdu_time_stamper.
     *
     * To avoid accidental use of raw pointers, latency::pdu_time_stamper's
     * constructor is in a private implementation
     * class. latency::pdu_time_stamper::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::string& key_string);
};

} // namespace latency
} // namespace gr

#endif /* INCLUDED_LATENCY_PDU_TIME_STAMPER_H */
