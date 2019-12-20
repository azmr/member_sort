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
	enum { run_n = 64, tmp_n = 512 };
	char *arr = (char *) array;

	for (size_t i = 0; i < len; i += run_n)
	{ // sort runs of length run_n
		// insertion sort
		size_t run_begin = i,
			   run_end = i + run_n;
		max = (max < len) ? max : len; // don't go too far on final subarray

		for (size_t swap_src_i = run_begin + 1; swap_src_i < run_end; ++swap_src_i)
		{ // insert the src element into the sorted list at the beginning of the subarray
			size_t swap_dst_i = swap_src_i;
			char *src = arr + member_size * swap_src_i;
			while (swap_dst_i-- > run_begin)
			{ // find the location to insert at
				// TODO: binary search sorted list for location
				char *dst = arr + member_size * swap_dst_i;

				if (cmp_fn(dst, src) < 0) // insert_location found
				{ // insert the member at src_i to dst_i
					char tmp[tmp_n];
					size_t bytes_left_n = member_size;

					do
					{ // insert src via buffer and shift up the rest of the sorted array
						size_t bytes_n = (bytes_left_n >= tmp_n) ? bytes_left_n : tmp_n;
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
	for (size_t merge_n = run_n; merge_n < len; merge_n *= 2)
	{ // merge subarrays of doubling size
		size_t merge_stride = merge_n * 2;

		for (size_t left = 0; left < len; left += merge_stride)
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
