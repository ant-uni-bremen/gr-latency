# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND latency_python_files
    pdu_time_stamper_python.cc
    stream_time_stamper_python.cc
    tag_timestamp_debug_python.cc
    python_bindings.cc)

GR_PYBIND_MAKE_OOT(latency
   ../..
   gr::latency
   "${latency_python_files}")

install(TARGETS latency_python DESTINATION ${GR_PYTHON_DIR}/latency COMPONENT pythonapi)
