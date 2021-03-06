/*
	HEAP.H
	------
	Copyright (c) 2017 Andrew Trotman
	Released under the 2-clause BSD license (See:https://en.wikipedia.org/wiki/BSD_licenses)

	Originally from the ATIRE code base where it was written by Xiang-Fei Jia and Andrew Trotman
*/
/*!
	@file
	@brief A bare-bones implementaiton of a min-heap.
	@author iang-Fei Jia and Andrew Trotman
	@copyright 2017 Andrew Trotman
*/
#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <chrono>
#include <random>
#include <sstream>
#include <algorithm>

#include "asserts.h"
#include "forceinline.h"

namespace JASS
	{
	/*
		CLASS HEAP
		----------
	*/
	/*!
		@brief A bare-bones implementaiton of a min-heap over an array passed by the caller.
		@tparam TYPE The type to build the heap over (normall a pointer type).
		@tparam COMPARE Function returning -1=ve on smaller, 0 on same, or +ve on larger.
	*/
	template <typename TYPE, typename COMPARE>
	class heap
		{
		private:
			TYPE *array;					///< The array to build the heap over
			size_t size;					///< The maximum size of of the heap
			COMPARE compare;				///< The comparison functor

		private:
			/*
				HEAP::LEFT_OF()
				---------------
			*/
			/*!
				@brief Return the index of the left element of the heap given the current position in the heap.
				@param position [in] current position in the heap.
				@return index of left of position.
			*/
			forceinline size_t left_of(size_t position)
				{
				return (position << 1) + 1;
				}

			/*
				HEAP::RIGHT_OF()
				----------------
			*/
			/*!
				@brief Return the index of the right element of the heap given the current position in the heap.
				@param position [in] current position in the heap.
				@return index of right of position.
			*/
			forceinline size_t right_of(size_t position)
				{
				return (position << 1) + 2;
				}

			/*
				HEAP::HEAPIFY()
				---------------
			*/
			/*!
				@brief Recurively build the heap.
				@param position [in] where, in the array, to build the heap
			*/
			void heapify(size_t position)
				{
				size_t smallest;

				size_t left = left_of(position);
				size_t right = right_of(position);

				if ((left < size) && (compare(array[left], array[position]) < 0))
					smallest = left;
				else
					smallest = position;

				if ((right < size) && (compare(array[right], array[smallest]) < 0))
					smallest = right;

				if (smallest != position)
					{
					std::swap(array[position], array[smallest]);
					heapify(smallest);
					}
				}

			/*
				HEAP::INSERT_FROM()
				-------------------
			*/
			/*!
				@brief Add and element to the heap after the given position
				@param key [in] The element to add to the heap
				@param position [in] The element to start looking from.
				@details This method does not check to see if the element is already in the heap or that
				the element should be in the heap (i.e. > smallest).
			*/
			void insert_from(TYPE key, size_t position = 0)
				{
				while (position < size)
					{
					size_t left = left_of(position);
					size_t right = right_of(position);

					// check array out of bound, it's also the stopping condition
					if (left < size && right < size)
						{
						if (compare(key, array[left]) <= 0 && compare(key, array[right]) <= 0)
							break;			// we're smaller then the left and the right so we're done
						else if (compare(array[left], array[right]) < 0)
							{
							array[position] = array[left];
							position = left;
							}
						else
							{
							array[position] = array[right];
							position = right;
							}
						}
					else if (left < size)			// and right > size (because this is an else)
						{
						if (compare(key, array[left]) > 0)
							{
							array[position] = array[left];
							position = left;
							}
						else
							break;
						}
					else
						break;			// both right and left exceed end of array
					}

				array[position] = key;
				}

		public:
			/*
				HEAP::HEAP()
				------------
			*/
			/*!
				@brief Constructor
				@param array [in] The array to maintain the heap over
				@param size [in] The maximum number of elements in te array (the size of the heap)
				@param compare [in] The comparison functor
			*/
			heap(TYPE &array, size_t size, const COMPARE &compare = COMPARE()) :
				array(&array),
				size(size),
				compare(compare)
				{
				/* Nothing */
				}

			/*
				HEAP::MAKE_HEAP()
				-----------------
			*/
			/*!
				@brief build the heap
			*/
			forceinline void make_heap(void)
				{
				for (int64_t position = size / 2 - 1; position >= 0; position--)
					heapify(position);
				}

			/*
				HEAP::PUSH_BACK()
				-----------------
			*/
			/*!
				@brief Add and element to the heap.
				@param key [in] The element to add to the heap
				@details This method does not check to see if the element is already in the heap or that
				the element should be in the heap (i.e. > smallest).
			*/
			forceinline void push_back(TYPE key)
				{
				insert_from(key, 0);
				}

			/*
				HEAP::PROMOTE()
				--------------
			*/
			/*!
				@brief Key has changed its value so re-build the heap from that point onwards
				@param key [in] The element that has changed
			*/
			forceinline void promote(TYPE key)
				{
				size_t position;

				for (position = 0; position < size; position++)
					if (array[position] == key)
						break;

				insert_from(key, position);
				}

			/*
				HEAP::UNITTEST()
				----------------
			*/
			/*!
				@brief Unit test this class
			*/
			static void unittest(void)
				{
				/*
					Start with an ordered sequence of numbers
				*/
				int sequence[] =  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
				
				/*
					Seed the random number generator
				*/
				auto seed = std::chrono::system_clock::now().time_since_epoch().count();
				std::default_random_engine random((unsigned int)seed);
				
				/*
					Some relatively small number of times, we're going to shuffle the sequence then add elements to the heap
					then sort the heap then make sure we got the right answer
				*/
				for (auto iteration = 0; iteration < 5; iteration++)
					{
					/*
						Shuffle the sequence of numbers
					*/
					std::shuffle(&sequence[0], &sequence[10], random);

					/*
						Add them to a heap that keeps a top-k of less than the number of elements in the sequence
					*/
					class unittest_compare
						{
						public:
							int operator()(int a, int b)
								{
								return a < b ? -1 : a == b ? 0 : 1;
								}
						};

					std::vector<int> buffer(5);
					heap<int, unittest_compare> heap(buffer[0], buffer.size());

					for (const auto &element : sequence)
						{
						/*
							NOTE:  This code maintains the heap, it does not determine which values should be in it.
						*/
						if (element > buffer[0])
							heap.push_back(element);
						}

					/*
						Sort the contents of the heap
					*/
					std::sort(buffer.begin(), buffer.end(), std::greater<int>());
		
					/*
						Serialise and compare to the known correct result
					*/
					std::ostringstream result;
					for (const auto &value : buffer)
						result << value << " ";
					JASS_assert(result.str() == "9 8 7 6 5 ");
					}

				/*
					We passed!
				*/
				puts("heap::PASSED");
				}
		};
	}

