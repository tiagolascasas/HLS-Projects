cmake_minimum_required(VERSION 3.7)

	#message(STATUS "Aspect: C:/Users/Tiago/Dev/HLS-Projects/benchmark_chstone/adpcm/../../lara_math_analysis/MathAnalysis.lara")
	#message(STATUS "Aspect args flags: ")
	#message(STATUS "Working dir: C:/Users/Tiago/Dev/HLS-Projects/benchmark_chstone/adpcm/adpcm_clava_weave")
	#message(STATUS "Woven dir name: woven")

	set(WEAVER_DEPENDENCIES C:/Users/Tiago/Dev/HLS-Projects/benchmark_chstone/adpcm/adpcm.c C:/Users/Tiago/Dev/HLS-Projects/benchmark_chstone/adpcm/../../lara_math_analysis/MathAnalysis.lara)	
	# to skip parsing header files: -sih 
	add_custom_command(
		OUTPUT "C:/Users/Tiago/Dev/HLS-Projects/benchmark_chstone/adpcm/adpcm_clava_weave/woven/clava_generated_files.txt"
		COMMAND java  -jar "C:/Users/Tiago/Dev/HLS-Projects/benchmark_chstone/adpcm/clava.jar" "C:/Users/Tiago/Dev/HLS-Projects/benchmark_chstone/adpcm/../../lara_math_analysis/MathAnalysis.lara"   --cmake -s -b 2 -p  "C:/Users/Tiago/Dev/HLS-Projects/benchmark_chstone/adpcm/adpcm.c" -o "C:/Users/Tiago/Dev/HLS-Projects/benchmark_chstone/adpcm/adpcm_clava_weave" -of "woven"  "" 
		WORKING_DIRECTORY "C:/Users/Tiago/Dev/HLS-Projects/benchmark_chstone/adpcm" 
		DEPENDS 
		COMMENT "Applying LARA strategy 'C:/Users/Tiago/Dev/HLS-Projects/benchmark_chstone/adpcm/../../lara_math_analysis/MathAnalysis.lara' to target 'adpcm'"
		VERBATIM
	)
	
	add_custom_target("adpcm_weaving" ALL
		DEPENDS "C:/Users/Tiago/Dev/HLS-Projects/benchmark_chstone/adpcm/adpcm_clava_weave/woven/clava_generated_files.txt" 
	)
