############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project VivadoHLS
set_top make_symmetrical
add_files VivadoHLS/fast_math.h
add_files VivadoHLS/math_testing.c
open_solution "solution1"
set_part {xc7z020-clg484-1} -tool vivado
create_clock -period 10 -name default
source "./VivadoHLS/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -format ip_catalog
