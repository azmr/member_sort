#ifndef MEMBERSORT_H
/* TODO:
 * - parallel execution
 *   - threads
 *   - SIMD
 * - sorting parallel arrays
 * - reverse
 * - generic & templated versions
 */
#include <stdint.h>
#include <string.h>

#if 1  // COMPARISON FUNCTIONS
typedef int MSFnCmp(void const *a, void const *b, void *user_data);

int ms_cmp_int8(void const *a, void const *b, void *user_data) { (void)user_data;
	int8_t A = *(int8_t const *)a,
	       B = *(int8_t const *)b;
	return (a > b) - (a < b);
}
int ms_cmp_uint8(void const *a, void const *b, void *user_data) { (void)user_data;
	uint8_t A = *(uint8_t const *)a,
	        B = *(uint8_t const *)b;
	return (a > b) - (a < b);
}

int ms_cmp_int16(void const *a, void const *b, void *user_data) { (void)user_data;
	int16_t A = *(int16_t const *)a,
	        B = *(int16_t const *)b;
	return (a > b) - (a < b);
}
int ms_cmp_uint16(void const *a, void const *b, void *user_data) { (void)user_data;
	uint16_t A = *(uint16_t const *)a,
	         B = *(uint16_t const *)b;
	return (a > b) - (a < b);
}

int ms_cmp_int32(void const *a, void const *b, void *user_data) { (void)user_data;
	int32_t A = *(int32_t const *)a,
	        B = *(int32_t const *)b;
	return (a > b) - (a < b);
}
int ms_cmp_uint32(void const *a, void const *b, void *user_data) { (void)user_data;
	uint32_t A = *(uint32_t const *)a,
	         B = *(uint32_t const *)b;
	return (a > b) - (a < b);
}

int ms_cmp_int64(void const *a, void const *b, void *user_data) { (void)user_data;
	int64_t A = *(int64_t const *)a,
	        B = *(int64_t const *)b;
	return (a > b) - (a < b);
}
int ms_cmp_uint64(void const *a, void const *b, void *user_data) { (void)user_data;
	uint64_t A = *(uint64_t const *)a,
	         B = *(uint64_t const *)b;
	return (a > b) - (a < b);
}

int ms_cmp_float(void const *a, void const *b, void *user_data) { (void)user_data;
	float A = *(float const *)a,
	      B = *(float const *)b;
	return (a > b) - (a < b);
}
int ms_cmp_double(void const *a, void const *b, void *user_data) { (void)user_data;
	double A = *(double const *)a,
	       B = *(double const *)b;
	return (a > b) - (a < b);
}

int ms_cmp_str(void const *a, void const *b, void *user_data) { (void)user_data;
	return strcmp((char const *a), (char const *b));
}

#endif // COMPARISON FUNCTIONS

int
ms_sort(void *array, void *first_comparand, size_t array_n, size_t member_size, MSFnCmp* cmp_fn, void *user_data)
{
	enum {
		First_6_Bits = (1 << 6) - 1,
		run_n = 64, Tmp_N = 512,
		Runs_N = 3,
	};
	char   tmp[Tmp_N];
	char  *arr               = (char *) array;

	size_t run_is[Runs_N]    = {0};
	size_t is_longer_than_64 = !!(array_n & ~(size_t)First_6_Bits);
	size_t min_run_n         = (array_n & First_6_Bits) + is_longer_than_64;
	assert(32 <= min_run_n && min_run_n <= 65);

	for (size_t arr_i = 1; arr_i < array_n;)// arr_i += run_n)
	{ // find (or force) runs of at least length min_run_n
		// insertion sort the remaining
		size_t run_begin_i = arr_i - 1;
		size_t arr_i_p     = run_begin_i;
			   /* run_end   = arr_i + run_n; */
		/* run_end = (run_end < array_n) ? run_end : array_n; // don't go too far on final subarray */

		size_t run_n = 1;
		if (cmp_fn(arr + member_size * run_begin, arr + member_size * arr_i) <= 0) do
		{ // find non-decreasing run
			arr_i_p = arr_i++;
			++run_n;
		} while (cmp_fn(arr + member_size * arr_i_p, arr + member_size * arr_i) <= 0);

		else
		{ // find strictly decreasing run and reverse it
			do
			{
				arr_i_p = arr_i++;
				++run_n;
			} while (cmp_fn(arr + member_size * arr_i_p, arr + member_size * arr_i) > 0);

			{ // reverse by swapping either end until hitting the middle
				size_t run_end_i = run_begin_i + run_n - 1;
				char *swaps[2]; {
					swaps[0] = arr + member_size * run_begin_i;
					swaps[1] = arr + member_size * run_end_i;
				}
				for (size_t swaps_i = 0, swaps_n = run_n / 2; // NOTE: this may miss out the middle if odd - this is correct behaviour
						swaps_i < swaps_n;
						++swaps_i, swaps[0] += member_size, swaps[1] -= member_size)
				{ // swap ends outside in
					assert(swaps[0] != swaps[1]);

					for (size_t bytes_left_n = member_size; bytes_left_n > 0;)
					{ // swap 2 ends
						size_t bytes_n = (bytes_left_n <= Tmp_N) ? bytes_left_n : Tmp_N;
						memcpy(tmp,	  swaps[0], bytes_n);
						memcpy(swaps[0], swaps[1], bytes_n);
						memcpy(swaps[1], tmp,	  bytes_n);
						swaps[0] += bytes_n;
						swaps[1] += bytes_n;
						bytes_left_n -= bytes_n;
					}
				}
			}
		}

		assert (run_n >= 2);
		// We now have a non-decreasing run of length run_n,
		// but we want to make sure that the run is at least min_run_n.
		// Insertion sort any new elements until we get to min_run_n
		for (size_t swap_src_i = run_end + 1;
			 run_n      < min_run_n &&
			 swap_src_i < array_n;
			 ++swap_src_i)
		{ // insert the src element into the sorted list at the beginning of the subarray
			size_t  swap_dst_i = swap_src_i;
			char   *src        = arr + member_size * swap_src_i;

			while (swap_dst_i-- > run_begin)
			{ // find the location to insert at
				// TODO: binary search sorted list for location
				char *dst = arr + member_size * swap_dst_i;

				if (cmp_fn(dst, src) < 0) // insert_location found
				{ // insert the member at src_i to dst_i
					size_t bytes_left_n = member_size;

					do
					{ // insert src via buffer and shift up the rest of the sorted array
						size_t bytes_n = (bytes_left_n <= Tmp_N) ? bytes_left_n : Tmp_N;
						memcpy(tmp, src, bytes_n);
						memmove(dst + bytes_n, dst, bytes_n);
						memcpy(dst, tmp, bytes_n);
						src += bytes_n;
						dst += bytes_n;
						bytes_left_n -= bytes_n;
					} while (bytes_left_n > 0);

					break;
				}
			}
		}
	}


	// merge sorted runs
	for (size_t merge_n = run_n; merge_n < array_n; merge_n *= 2)
	{ // merge subarrays of doubling size
		size_t merge_stride = merge_n * 2;

		for (size_t left = 0; left < array_n; left += merge_stride)
		{
			size_t mid = left + merge_n - 1;
		}
	}
}

int
ms_sortr(void *array, void *first_member, size_t len, size_t member_size, int (* cmp_fn)(void *, void *))
{

}

int
ms_sortp(void **arrays, size_t num_arrays, void *first_member, size_t len, size_t member_size, int (* cmp_fn)(void *, void *))
{

}

size_t
ms_search(void *array, void *first_member, size_t len, size_t member_size, int (* cmp_fn)(void *, void *))
{

}

#define MEMBERSORT_H
#endif//MEMBERSORT_H
