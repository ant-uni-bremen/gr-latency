#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright 2019 Johannes Demel.
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

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def load_pandas_data(filepath):
    d = pd.read_csv(filepath, header=None)
    print(d[~d[0].str.contains('timestamp')])
    d = d[d[0].str.contains('timestamp')]

    d = d[[0, 1, 2]]
    s = d[0].str.split(expand=True)
    d[0] = s[4]
    d[0] = d[0].transform(int)
    d[1] = d[1].str.strip()
    return d


def main():
    pd.set_option('display.width', 0)
    filepath = '../examples/log.txt'
    d = load_pandas_data(filepath)
    d = d.sort_values(0)
    grouped = d.groupby(1)

    print(grouped.groups.keys())

    for gk in grouped.groups.keys():
        g = grouped.get_group(gk)
        t = g[0]
        v = g[2] * 1e-3
        plt.plot(t, v, label=gk)

    plt.ylabel('latency [us]')
    plt.legend()
    plt.show()


if __name__ == '__main__':
    main()
