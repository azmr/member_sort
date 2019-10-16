#ifndef MEMBERSORT_H
/* TODO:
 * - parallel execution
 *   - threads
 *   - SIMD
 * - sorting parallel arrays
 * - reverse
 */
#include <stdint.h>
#include <string.h>

int ms_cmp_int(void *a, void *b)
{ return *(int *)a - *(int *)b; }

int ms_cmp_unsigned(void *a, void *b)
{ return *(unsigned *)a - *(unsigned *)b; }

int ms_cmp_double(void *a, void *b)
{ return (int)(*(double *)a - *(double *)b); }
int ms_cmp_float(void *a, void *b)
{ return (int)(*(float *)a - *(float *)b); }

int (*ms_cmp_str)(void *a, void *b) = (int (*)(void*, void*)) strcmp;

int
ms_sort(void *array, void *first_member, size_t len, size_t member_size, int (* cmp_fn)(void *, void *))
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
