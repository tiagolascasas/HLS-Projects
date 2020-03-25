cmake_minimum_required(VERSION 2.8.9)
project (chstone_adpcm)
set(SOURCES adpcm.c)
add_executable(adpcm ${SOURCES})

find_package(Clava REQUIRED)
clava_weave(adpcm "../../lara_math_analysis/MathAnalysis.lara")  