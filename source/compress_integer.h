/*
	COMPRESS_INTEGER.H
	------------------
	Copyright (c) 2016 Andrew Trotman
	Released under the 2-clause BSD license (See:https://en.wikipedia.org/wiki/BSD_licenses)
*/
/*!
	@file
	@brief Compression codexes for integer sequences.
	@author Andrew Trotman
	@copyright 2016 Andrew Trotman
*/
#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <vector>

namespace JASS
	{
	/*
		CLASS COMPRESS_INTEGER
		----------------------
	*/
	/*!
		@brief Compression codexes for integer sequences
		@details To implement a codex you need to subclass this virtual base class and implement two
		methods, encode() and decode().  As those methods are virtual, an object of the given subclass
		is needed in order to encode or decode integer sequences.
	*/
	class compress_integer
		{
		public:
			typedef uint32_t integer;									///< This class and descendants will work on integers of this size.  Do not change without also changing JASS_COMPRESS_INTEGER_BITS_PER_INTEGER
			#define JASS_COMPRESS_INTEGER_BITS_PER_INTEGER 32	///< The number of bits in compress_integer::integer (either 32 or 64). This must remain in sync with compress_integer::integer (and a hard coded value to be used in \#if statements)

		public:
			/*
				COMPRESS_INTEGER::COMPRESS_INTEGER()
				------------------------------------
			*/
			/*!
				@brief Constructor.
			*/
			compress_integer()
				{
				/* Nothing */
				}
			/*
				COMPRESS_INTEGER::COMPRESS_INTEGER()
				------------------------------------
			*/
			/*!
				@brief Destructor.
			*/
			virtual ~compress_integer()
				{
				/* Nothing */
				}

			/*
				COMPRESS_INTEGER::D1_ENCODE()
				-----------------------------
			*/
			/*!
				@brief Convert an array of integers into an array of D1 (delta, d-gap) encoded integers.
				@param encoded [out] The d1-encoded result.
				@parm source [in] The integers to be D1 encoded.
				@param source_integers [in] The number of integers in the list.
				@return The number of integers encoded.
			*/
			static size_t d1_encode(integer *encoded, const integer *source, size_t source_integers)
				{
				integer prior = 0;
				const integer *end = source + source_integers;

				for (const integer *current = source; current < end; current++)
					{
					/*
						This is done in this order so that the encoded and source buffers can be the same array.
					*/
					integer d1 = *current - prior;
					prior = *current;
					*encoded++ = d1;
					}
				return source_integers;
				}

			/*
				COMPRESS_INTEGER::D1_DECODE()
				-----------------------------
			*/
			/*!
				@brief Convert a D1 encoded array of integers into an array of integers.
				@param encoded [out] The decoded integers.
				@parm source [in] The D1 encoded integers.
				@param source_integers [in] The number of integers in the list.
				@return The number of integers encoded.
			*/
			static size_t d1_decode(integer *decoded, const integer *source, size_t source_integers)
				{
				integer sum = 0;
				const integer *end = source + source_integers;

				for (const integer *current = source; current < end; current++)
					{
					sum += *current;
					*decoded++ = sum;
					}
				return source_integers;
				}

			/*
				COMPRESS_INTEGER::ENCODE()
				--------------------------
			*/
			/*!
				@brief Encode a sequence of integers returning the number of bytes used for the encoding, or 0 if the encoded sequence doesn't fit in the buffer.
				@param encoded [out] The sequence of bytes that is the encoded sequence.
				@param encoded_buffer_length [in] The length (in bytes) of the output buffer, encoded.
				@param source [in] The sequence of integers to encode.
				@param source_integers [in] The length (in integers) of the source buffer.
				@return The number of bytes used to encode the integer sequence, or 0 on error (i.e. overflow).
			*/
			virtual size_t encode(void *encoded, size_t encoded_buffer_length, const integer *source, size_t source_integers) = 0;
			
			/*
				COMPRESS_INTEGER::DECODE()
				--------------------------
			*/
			/*!
				@brief Decode a sequence of integers encoded with this codex.
				@param decoded [out] The sequence of decoded integers.
				@param integers_to_decode [in] The minimum number of integers to decode (it may decode more).
				@param source [in] The encoded integers.
				@param source_length [in] The length (in bytes) of the source buffer.
			*/
			virtual void decode(integer *decoded, size_t integers_to_decode, const void *source, size_t source_length) = 0;

			/*
				COMPRESS_INTEGER::UNITTEST_ONE()
				--------------------------------
			*/
			/*!
				@brief Test one sequence to make sure it encodes and decodes to the same thing.  Assert if not.
				@param encoder [in] The integer encoded being tested.
				@param sequence [in] the sequernce to encode.
			*/
			static void unittest_one(compress_integer &encoder, const std::vector<uint32_t> &sequence);

			/*
				COMPRESS_INTEGER::UNITTEST()
				----------------------------
			*/
			/*!
				@brief Unit test this class, assert on failure.
				@param compressor [in] a compressor
				@param staring_from [in] normally 0.  The bitness to start testing from (some schemes cannot encode a 0 (e.g. Elias gama) so use 1 in those cases).
			*/
			static void unittest(compress_integer &&compressor, uint32_t staring_from = 0);
		} ;
	}
