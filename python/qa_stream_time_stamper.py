#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2020 Johannes Demel.
#
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import latency_swig as latency


class qa_stream_time_stamper(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):
        packet_len = 76
        num_samples = 10000

        tagger = latency.stream_time_stamper(4, "time", packet_len)
        src = blocks.vector_source_f([1., ] * num_samples)
        snk = blocks.vector_sink_f()
        self.tb.connect(src, tagger, snk)
        # set up fg
        self.tb.run()
        # check data
        tags = snk.tags()
        self.assertEqual(len(tags), 1 + num_samples // packet_len)
        for t in tags:
            self.assertEqual(t.offset % packet_len, 0)


if __name__ == '__main__':
    gr_unittest.run(qa_stream_time_stamper)
