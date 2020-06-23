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
import pmt
import time
import latency_python as latency


class qa_tag_timestamp_debug(gr_unittest.TestCase):
    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):
        tags = []
        # ref = []
        nt = int(time.time() * 1e9)
        for i in range(5):
            d = [i * 500, pmt.intern('time'), pmt.from_long(nt),
                 pmt.intern('testsource')]
            t = gr.tag_utils.python_to_tag(d)
            tags.append(t)

        debugger = latency.tag_timestamp_debug(8, "time", "tester")
        src = blocks.vector_source_c([0.j] * 10000, False, 1, tags)
        self.tb.connect(src, debugger)
        # set up fg
        self.tb.run()
        # check data


if __name__ == '__main__':
    gr_unittest.run(qa_tag_timestamp_debug)
