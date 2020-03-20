#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2017 Johannes Demel.
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
from __future__ import print_function, division
import pmt
import numpy as np


def generate_tacnet_header(target_idx, request_or_sender_idx, frame_idx,
                           downlink_direction=False):
    f = np.unpackbits(np.array([frame_idx, ], dtype=np.uint8))[3:]
    d = np.array([downlink_direction, ], dtype=f.dtype)
    rs = np.unpackbits(np.array([request_or_sender_idx, ], dtype=np.uint8))[3:]
    t = np.unpackbits(np.array([target_idx, ], dtype=np.uint8))[3:]
    bits = np.concatenate((t, rs, d, f))
    return np.packbits(bits)[::-1]


def parse_tacnet_header(header):
    bits = np.unpackbits(header[::-1])
    frame_idx = int(np.packbits(np.concatenate((np.zeros(3,
                                                         dtype=bits.dtype),
                                                bits[-5:])))[0])
    target_idx = int(np.packbits(np.concatenate((np.zeros(3,
                                                          dtype=bits.dtype),
                                                 bits[0:5])))[0])
    sender_idx = int(np.packbits(np.concatenate((np.zeros(3,
                                                          dtype=bits.dtype),
                                                 bits[5:10])))[0])
    direction = bool(bits[10])
    return target_idx, sender_idx, frame_idx, direction


def scramble_tacnet_frame(frame):
    return frame + np.arange(frame.size, dtype=frame.dtype)


def descramble_tacnet_frame(frame):
    return frame - np.arange(frame.size, dtype=frame.dtype)


def get_pdu(dest_id, src_id, frame_num, message, checksum=None):
    meta = get_pdu_header(dest_id, src_id, frame_num)
    payload = get_pdu_payload(message)
    return pmt.cons(meta, payload)


def get_pdu_header(dest_id, src_id, frame_num, checksum=None):
    d = pmt.make_dict()
    d = set_pdu_header_checksum(d, checksum)
    d = pmt.dict_add(d, pmt.intern("frame_num"), pmt.from_long(frame_num))
    d = pmt.dict_add(d, pmt.intern("src_id"), pmt.from_long(src_id))
    d = pmt.dict_add(d, pmt.intern("dest_id"), pmt.from_long(dest_id))
    return d


def extract_pdu_header(header):
    d = pmt.to_long(pmt.dict_ref(header, pmt.intern('dest_id'), pmt.PMT_NIL))
    s = pmt.to_long(pmt.dict_ref(header, pmt.intern('src_id'), pmt.PMT_NIL))
    f = pmt.to_long(pmt.dict_ref(header, pmt.intern('frame_num'), pmt.PMT_NIL))
    c = pmt.dict_ref(header, pmt.intern('checksum'), pmt.PMT_NIL)
    if pmt.is_u8vector(c):
        c = pmt_u8vector_to_ndarray(c)
    elif pmt.eq(c, pmt.PMT_T):
        c = True
    else:
        c = False
    return d, s, f, c


def set_pdu_header_checksum(meta, checksum=None):
    if checksum is None:
        meta = pmt.dict_add(meta, pmt.intern("checksum"), pmt.PMT_NIL)
    else:
        c = ndarray_to_pmt_u8vector(checksum)
        meta = pmt.dict_add(meta, pmt.intern("checksum"), c)
    return meta


def get_pdu_payload(payload):
    return pmt.init_u8vector(len(payload), payload)


def ndarray_to_pmt_u8vector(d):
    return pmt.init_u8vector(len(d),
                             np.array(d).astype(dtype=np.uint8).tolist())


def pmt_u8vector_to_ndarray(msg):
    return np.array(pmt.u8vector_elements(msg)).astype(dtype=np.uint8)


def get_hex_char_string(char_vec):
    return ' '.join('{:02x}'.format(i) for i in char_vec)


def string_to_int_list(s):
    lmsg = list(s)
    cmsg = [ord(c) for c in lmsg]
    return cmsg


def hex_string_to_int_list(s):
    s = s.replace(" ", "")
    l = map(''.join, zip(*[iter(s)]*2))
    h = [''.join(['0x', i, ]) for i in l]
    il = [int(i, 16) for i in h]
    return il


def main():
    src_id = 42
    dest_id = 84
    frame_num = 4711
    checksum = range(16)
    raw_payload = range(16)
    payload = get_pdu_payload(raw_payload)
    print(payload, pmt.length(payload))
    meta = get_pdu_header(dest_id, src_id, frame_num)
    # pl = pmt.u
    print(meta)
    print(pmt.dict_keys(meta))
    print(pmt.dict_values(meta))
    meta = set_pdu_header_checksum(meta, checksum)
    print(meta)

    K = "00010203 04050607 08090A0B 0C0D0E0F 10111213 14151617 18191A1B 1C1D1E1F"
    print(K)
    vals = hex_string_to_int_list(K)
    print(get_hex_char_string(vals))


if __name__ == '__main__':
    main()
