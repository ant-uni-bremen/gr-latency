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

#include "tag_timestamp_debug_impl.h"
#include <gnuradio/io_signature.h>
#include <chrono>

namespace gr {
namespace latency {

tag_timestamp_debug::sptr tag_timestamp_debug::make(size_t sizeof_stream_item,
                                                    const std::string& key_name,
                                                    const std::string& name)
{
    return gnuradio::get_initial_sptr(
        new tag_timestamp_debug_impl(sizeof_stream_item, key_name, name));
}


/*
 * The private constructor
 */
tag_timestamp_debug_impl::tag_timestamp_debug_impl(size_t sizeof_stream_item,
                                                   const std::string& key_name,
                                                   const std::string& name)
    : gr::sync_block("tag_timestamp_debug",
                     gr::io_signature::make(1, -1, sizeof_stream_item),
                     gr::io_signature::make(0, 0, 0)),
      d_name(name),
      d_key_name(key_name),
      d_key(pmt::string_to_symbol(key_name))
{
}

/*
 * Our virtual destructor.
 */
tag_timestamp_debug_impl::~tag_timestamp_debug_impl() {}

int tag_timestamp_debug_impl::work(int noutput_items,
                                   gr_vector_const_void_star& input_items,
                                   gr_vector_void_star& output_items)
{
    for (size_t i = 0; i < input_items.size(); i++) {
        const size_t abs_N = nitems_read(i);
        const size_t end_N = abs_N + (size_t)(noutput_items);

        std::vector<tag_t> tags;
        get_tags_in_range(tags, i, abs_N, end_N);
        for (auto t : tags) {
            // std::cout << d_name << " ";
            // pmt::print(t.value);
            std::chrono::nanoseconds s;
            if (t.key == d_key) {
                s = std::chrono::nanoseconds(pmt::to_long(t.value));
            } else if (pmt::is_dict(t.value) && dict_has_key(t.value, d_key)) {
                s = std::chrono::nanoseconds(
                    pmt::to_long(pmt::dict_ref(t.value, d_key, pmt::PMT_NIL)));
            } else {
                continue;
            }
            auto cn = std::chrono::high_resolution_clock::now().time_since_epoch();
            auto d = std::chrono::duration_cast<std::chrono::nanoseconds>(cn - s);
            // FIXME: Add timestamp for correct clustering!
            // FIXME: Use GR Logger for thread safety fanciness!
            std::cout << d_name << " duration: " << d.count() << "ns" << std::endl;
        }
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace latency */
} /* namespace gr */
