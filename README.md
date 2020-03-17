# HLS Projects

Projects with benchmark code for Xilinx SDSoC and Vivado HLS

Repository organization:

* **benchmark_chstone** - kernels from the CHStone benchmark suite, flattened into a single folder
* **benchmark_hiflipvx** - image processing kernels from the [HiFlipVX](https://github.com/TUD-ADS/HiFlipVX/tree/master/Source) benchmark suite
* **benchmark_misc** - kernels from Afonso Ferreira's master thesis
* **benchmark_utdsp_apps** - apps from the UTDSP benchmark suite, flattened into a single folder
* **benchmark_utdsp_kernels** - kernels from the UTDSP benchmark suite, flattened into a single folder
* **instrumented_code** - instrumented version of Afonso's code
* **lara_math_analysis** - LARA/Clava code restructuring strategies to manipulate math.h function calls
* **sdsoc_legup_fft** - Xilinx SDSoC project with a hardware + software implementation of the FFT kernel from the LegUp benchmark suite
* **vivado_hls_examples** - Vivado HLS project with some kernels as example inputs, plus performance metrics for experimentation

See also [this repository](https://github.com/tiagolascasas/Vivado-HLS-Report-Parser) for a simple parser for Vivado HLS synthesis reports