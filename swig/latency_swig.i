/* -*- c++ -*- */

#define LATENCY_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "latency_swig_doc.i"

%{
#include "latency/pdu_time_stamper.h"
%}

%include "latency/pdu_time_stamper.h"
GR_SWIG_BLOCK_MAGIC2(latency, pdu_time_stamper);