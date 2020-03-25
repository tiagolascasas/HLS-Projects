# HLS Projects

Projects with benchmark code for Xilinx SDSoC and Vivado HLS, as well as LARA/Clava aspects to restructure code in order to improve their compilation for FPGAs.

Repository organization:

* **Benchmarks** - code from multiple benchmark suites, modified so that they compile and possibly with an added main and input data
    * **CHStone** - modified CHStone benchmarks. All compilable
    * **HiFlipVX** - see [official repository](https://github.com/TUD-ADS/HiFlipVX/tree/master/Source). Compilable
    * **Misc** - assorted programs from multiple sources, as well as custom code. All compilable
    * **SNU_RealTime** - 3 programs from the SNU Real Time benchmark suite. All compilable
    * **UTDSP_apps** - modified UTDSP apps. Some compilable
    * **UTDSP_kernels** - modified UTDSP kernels. All compilable
* **Data** - Data gathered from the benchmarks, restructured code and experimentation
* **LARA** - [LARA/Clava](http://specs.fe.up.pt/tools/clava/) aspects to analyse and restructure code for FPGA compilation
    * **DataflowGraph** - LARA/Clava aspect to insert instrumentation prints in order to produce a dataflow graph
    * **MathAnalysis** - LARA/Clava aspects to manipulate math.h function calls
* **SDSoC** - Xilinx SDSoC projects with hardware + software implementations of a kernel/app, targeting a Xilinx Virtex-7
    * **legup_fft** - FFT kernel from the LegUp benchmark suite
* **Vivado HLS** - Vivado HLS project with some kernels as example inputs, plus performance metrics for experimentation

See also [this repository](https://github.com/tiagolascasas/Vivado-HLS-Report-Parser) for a simple parser for Vivado HLS synthesis reports