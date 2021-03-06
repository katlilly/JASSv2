#
# CMAKELISTS.TXT
# --------------
#
# Build file for JASS
# Copyright (c) 2016 - 2017 Andrew Trotman
#
# Released under the 2-clause BSD license (See:https://en.wikipedia.org/wiki/BSD_licenses)
#

set(JASSlib_FILES
	accumulator_2d.h
	allocator.h
	allocator_cpp.h
	allocator_memory.h
	allocator_memory.cpp
	allocator_pool.h
	allocator_pool.cpp
	ascii.h
	ascii.cpp
	asserts.h
	asserts.cpp
	binary_tree.h
	bitstream.h
	bitstring.h
	bitstring.cpp
	channel.h
	channel_file.h
	channel_file.cpp
	checksum.h
	checksum.cpp
	commandline.h
	compress_general.h
	compress_general_zlib.h
	compress_general_zlib.cpp
	compress_general_zstd.h
	compress_general_zstd.cpp
	compress_integer.h
	compress_integer.cpp
	compress_integer_all.h
	compress_integer_all.cpp
	compress_integer_bitpack.h
	compress_integer_bitpack.cpp
	compress_integer_bitpack_32_reduced.h
	compress_integer_bitpack_32_reduced.cpp
	compress_integer_bitpack_64.h
	compress_integer_bitpack_64.cpp
	compress_integer_bitpack_128.h
	compress_integer_bitpack_128.cpp
	compress_integer_bitpack_256.h
	compress_integer_bitpack_256.cpp
	compress_integer_carry_8b.h
	compress_integer_carry_8b.cpp
	compress_integer_carryover_12.h
	compress_integer_carryover_12.cpp
	compress_integer_elias_delta.h
	compress_integer_elias_delta.cpp
	compress_integer_elias_delta_bitwise.h
	compress_integer_elias_delta_simd.h
	compress_integer_elias_delta_simd.cpp
	compress_integer_elias_gamma.h
	compress_integer_elias_gamma.cpp
	compress_integer_elias_gamma_bitwise.h
	compress_integer_elias_gamma_simd.h
	compress_integer_elias_gamma_simd.cpp
	compress_integer_lyck_16.h
	compress_integer_lyck_16.cpp
	compress_integer_none.h
	compress_integer_none.cpp
	compress_integer_nybble_8.h
	compress_integer_nybble_8.cpp
	compress_integer_qmx_improved.h
	compress_integer_qmx_improved.cpp
	compress_integer_qmx_jass_v1.h
	compress_integer_qmx_jass_v1.cpp
	compress_integer_qmx_original.h
	compress_integer_qmx_original.cpp
	compress_integer_relative_10.h
	compress_integer_relative_10.cpp
	compress_integer_simple_16.h
	compress_integer_simple_16.cpp
	compress_integer_simple_16_packed.h
	compress_integer_simple_16_packed.cpp
	compress_integer_simple_8b.h
	compress_integer_simple_8b.cpp
	compress_integer_simple_8b_packed.h
	compress_integer_simple_8b_packed.cpp
	compress_integer_simple_9.h
	compress_integer_simple_9.cpp
	compress_integer_simple_9_packed.h
	compress_integer_simple_9_packed.cpp
	compress_integer_stream_vbyte.h
	compress_integer_stream_vbyte.cpp
	compress_integer_variable_byte.h
	compress_integer_variable_byte.cpp
	decode_d0.h
	decode_d1.h
	deserialised_jass_v1.h
	deserialised_jass_v1.cpp
	document.h
	dynamic_array.h
	file.h
	file.cpp
	forceinline.h
	global_new_delete.h
	hardware_support.h
	hash_table.h
	hash_pearson.h
	hash_pearson.cpp
	heap.h
	index_manager.h
	index_manager_sequential.h
	index_postings.h
	index_postings_impact.h
	instream.h
	instream_document_trec.h
	instream_document_trec.cpp
	instream_file.h
	instream_file.cpp
	instream_file_star.h
	instream_memory.h
	instream_memory.cpp
	maths.h
	maths.cpp
	parser.h
	parser.cpp
	parser_query.h
	parser_query.cpp
	pointer_box.h
	quantize.h
	query.h
	query_term.h
	query_term_list.h
	ranking_function.h
	ranking_function_atire_bm25.h
	reverse.h
	run_export.h
	run_export_trec.h
	serialise_ci.cpp
	serialise_ci.h
	serialise_integers.cpp
	serialise_integers.h
	serialise_jass_v1.cpp
	serialise_jass_v1.h
	slice.h
	string_cpp.h
	threads.h
	threads.cpp
	timer.h
	top_k_heap.h
	top_k_qsort.h
	top_k_qsort.cpp
	unicode.h
	unicode.cpp
	unittest_data.h
	unittest_data.cpp
	version.h
	)

add_library(JASSlib ${JASSlib_FILES})
add_dependencies(JASSlib zstd zlib)

include_directories(.)

#
# Tell cmake about the source code files that are generated by other parts of the build process.
#
set_source_files_properties(unicode.cpp PROPERTIES GENERATED 1)
add_dependencies(JASSlib generate_unicode_cpp)

set_source_files_properties(ascii.cpp PROPERTIES GENERATED 1)
add_dependencies(JASSlib generate_ascii_cpp)

source_group ("Source Files" FILES ${JASSlib_FILES})
