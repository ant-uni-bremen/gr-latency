# Latency measurements

Sometimes we need to measure latency in a flowgraph. 

* Which blocks delay processing?
* How long does it take a packet to propagate through the DSP chain?

## The idea

We add a timestamp to a packet. Either in a PDU or with other means. The trick is a<br>
`const auto ticks = std::chrono::high_resolution_clock::now().time_since_epoch()`<br>
which represents our timestamp. Further down the processing chain, we can pick up this tag and analyze the time difference. This might give us a pretty consistent idea where we spend most of our latency.
