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
import latency_swig as latency
from utils import string_to_int_list, get_pdu_payload


class qa_pdu_time_stamper(gr_unittest.TestCase):
    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):
        src_id = 21
        dst_id = 10
        direction = True  # Downlink
        msg = u"Sample message for frame formatter Yihhaaa"
        message = string_to_int_list(msg)
        payload = get_pdu_payload(message)

        meta = pmt.make_dict()

        pdu = pmt.cons(meta, payload)

        formatter = latency.pdu_time_stamper("time")
        dbg = blocks.message_debug()

        self.tb.msg_connect(formatter, "PDUout", dbg, "store")
        self.tb.msg_connect(formatter, "PDUout", dbg, "print_pdu")

        self.tb.start()
        formatter.to_basic_block()._post(pmt.intern("PDUin"), pdu)  # eww, what's that smell?
        while dbg.num_messages() < 1:
            pass
        self.tb.stop()
        self.tb.wait()
        result_msg = dbg.get_message(0)
        # print(result_msg)
        print('finished test')
        # print(result_msg)
        meta = pmt.car(result_msg)
        bits = pmt.cdr(result_msg)
        print(meta)


if __name__ == '__main__':
    gr_unittest.run(qa_pdu_time_stamper)
