/*
	UNITTEST.CPP
	------------
	Copyright (c) 2016 Andrew Trotman
	Released under the 2-clause BSD license (See:https://en.wikipedia.org/wiki/BSD_licenses)
*/
#include "file.h"
#include "ascii.h"
#include "maths.h"
#include "query.h"
#include "slice.h"
#include "parser.h"
#include "unicode.h"
#include "version.h"
#include "checksum.h"
#include "bitstring.h"
#include "hash_table.h"
#include "top_k_heap.h"
#include "binary_tree.h"
#include "pointer_box.h"
#include "serialise_ci.h"
#include "hash_pearson.h"
#include "parser_query.h"
#include "channel_file.h"
#include "dynamic_array.h"
#include "allocator_cpp.h"
#include "instream_file.h"
#include "index_manager.h"
#include "allocator_pool.h"
#include "index_postings.h"
#include "accumulator_2d.h"
#include "instream_memory.h"
#include "allocator_memory.h"
#include "serialise_jass_v1.h"
#include "instream_file_star.h"
#include "index_postings_impact.h"
#include "instream_document_trec.h"
#include "index_manager_sequential.h"
#include "compress_integer_variable_byte.h"

/*
	MAIN()
	------
*/
int main(void)
	{
	int failed = true;			// main() returns 0 on success

	/*
		Output basic statistics about JASS as it stands
	*/
	puts(JASS::version::credits().c_str());

	/*
		Test the JASS classes
	*/
	puts("PERFORM ALL UNIT TESTS");

	try
		{
		//	JASS::string is a typedef so nothing to test.
		
		puts("checksum");
		JASS::checksum::unittest();

		puts("file");
		JASS::file::unittest();
		
		puts("bitstring");
		JASS::bitstring::unittest();

		puts("unicode");
		JASS::unicode::unittest();
		
		puts("ascii");
		JASS::ascii::unittest();
		
		puts("maths");
		JASS::maths::unittest();
		
		// JASS::allocator does not have a unittest because it is a virtual base class
		
		puts("allocator_pool");
		JASS::allocator_pool::unittest();
		
		puts("allocator_memory");
		JASS::allocator_memory::unittest();

		puts("document");
		JASS::document::unittest();
		
		puts("allocator_cpp");
		JASS::allocator_cpp<size_t>::unittest();
		
		puts("slice");
		JASS::slice::unittest();
		
		// instream does not have a unittest because it is a virtual base class
		
		puts("instream_file");
		JASS::instream_file::unittest();

		puts("instream_file_star");
		JASS::instream_file_star::unittest();

		puts("instream_memory");
		JASS::instream_memory::unittest();

		puts("instream_document_trec");
		JASS::instream_document_trec::unittest();

		// JASS::channel does not have a unittest because it is a virtual base class

		puts("channel_file");
		JASS::channel_file::unittest();

		puts("parser");
		JASS::parser::unittest();

		puts("query_term");
		JASS::query_term::unittest();
		
		puts("parser_query");
		JASS::parser_query::unittest();
		
		puts("hash_pearson");
		JASS::hash_pearson::unittest();

		puts("binary_tree");
		JASS::binary_tree<size_t, size_t>::unittest();
		
		puts("hash_table");
		JASS::hash_table<JASS::slice, JASS::slice>::unittest();
		
		puts("dynamic_array");
		JASS::dynamic_array<JASS::slice>::unittest();

		puts("index_postings");
		JASS::index_postings::unittest();

		puts("impact_postings_impact");
		JASS::index_postings_impact::unittest();


		puts("index_manager");
		JASS::index_manager::unittest();

		puts("index_manager_sequential");
		JASS::index_manager_sequential::unittest();

		puts("serialise_jass_ci");
		JASS::serialise_jass_v1::unittest();

		puts("serialise_ci");
		JASS::serialise_ci::unittest();

		puts("compress_integer_variable_byte");
		JASS::compress_integer_variable_byte::unittest();

		puts("accumulator_2d");
		JASS::accumulator_2d<uint32_t>::unittest();

		puts("pointer_box");
		JASS::pointer_box<int>::unittest();

		puts("top_k_heap");
		JASS::top_k_heap<int>::unittest();

		puts("query");
		JASS::query<uint16_t>::unittest();

		puts("ALL UNIT TESTS HAVE PASSED");
		failed = false;
		}
	// LCOV_EXCL_START
	catch (std::bad_array_new_length &error)
		{
		printf("CAUGHT AN EXCEPTION OF TYPE std::bad_array_new_length (%s)\n", error.what());
		}
	catch (std::exception &error)
		{
		printf("CAUGHT AN EXCEPTION OF TYPE std::exception (%s)\n", error.what());
		}
	catch (...)
		{
		printf("CAUGHT AN EXCEPTION OF UNKNOEN TYPE)\n");
		}
	// LCOV_EXCL_STOP

	return failed;
	}
