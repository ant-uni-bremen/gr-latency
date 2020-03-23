![Check Formatting](https://github.com/ant-uni-bremen/gr-latency/workflows/Check%20Formatting/badge.svg)

# Latency measurements

Sometimes we need to measure latency in a flowgraph. 

* Which blocks delay processing?
* How long does it take a packet to propagate through the DSP chain?

## The idea

We add a timestamp to a packet. Either in a PDU or with other means. The trick is a<br>
`const auto ticks = std::chrono::high_resolution_clock::now().time_since_epoch()`<br>
which represents our timestamp. Further down the processing chain, we can pick up this tag and analyze the time difference. This might give us a pretty consistent idea where we spend most of our latency.

### Inspiration

This module was inspired by [a comment in gr-sched](https://github.com/bastibl/gr-sched#metrics).

## Issues

* All data is printed to `stdout`. Instead, we should use GNU Radio's logging capabilities.
* Debug data should contain a common identifier, preferably the timestamp itself to identify different propagation stages of the same packet.

## Code formatting
This is the current way to format everything:<br>
`find . -regex '.*\.\(c\|cc\|cpp\|cxx\|h\|hh\)' -not -path "*build*" -exec clang-format -style=file -i {} \;`
