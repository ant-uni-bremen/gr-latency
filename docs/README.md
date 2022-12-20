[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.6338010.svg)](https://doi.org/10.5281/zenodo.6338010) ![Check Formatting](https://github.com/ant-uni-bremen/gr-latency/workflows/Check%20Formatting/badge.svg)

# Latency measurements

The *gr-latency* GNU Radio Out-of-Tree module is a Free Software Package that aims to provide tools to measure flowgraph latency. The module provides features to measure GNU Radio flowgraph latency, e.g.:
* Which blocks delay processing?
* How long does it take a packet to propagate through the DSP chain?

## The idea

We add a timestamp to a packet. Either in a PDU or with other means. The trick is a<br>
`const auto ticks = std::chrono::high_resolution_clock::now().time_since_epoch()`<br>
which represents our timestamp. Further down the processing chain, we can pick up this tag and analyze the time difference. This might give us a pretty consistent idea where we spend most of our latency.

### Inspiration

* This module was inspired by [a comment in gr-sched](https://github.com/bastibl/gr-sched#metrics).

* Bloessl, Müller, Hollick: ["Benchmarking and Profiling the GNU Radio Scheduler"](https://pubs.gnuradio.org/index.php/grcon/article/view/64), GNU Radio Conference (GRCon), September 2019, Huntsville, AL, USA

## Issues

* All data is printed to `stdout`. Instead, we should use GNU Radio's logging capabilities.
* Debug data should contain a common identifier, preferably the timestamp itself to identify different propagation stages of the same packet.

## Code formatting
This is the current way to format everything:<br>
`find . -regex '.*\.\(c\|cc\|cpp\|cxx\|h\|hh\)' -not -path "*build*" -exec clang-format -style=file -i {} \;`


## Example usage
This is a short example how to generate latency reports. It uses [Pandas](https://pandas.pydata.org/)

1. Use a flowgraph in `examples`.
2. Generate this flowgraph in GRC, e.g. `tag_timestamp_demo.grc`
3. Run flowgraph with `GR_CONF_LOG_LOG_FILE=log.txt ./tag_timestamp_demo.py`. This does create a new file `examples/log.txt`
4. Plot results with `python/latency_analysis.py`