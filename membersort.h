#ifndef MEMBERSORT_H
/* TODO:
 * - parallel execution
 *   - threads
 *   - SIMD
 * - sorting parallel arrays
 * - reverse
 */

int ms_cmp_int(void *a, void *b)
{ return *(int *)a - *(int *)b; }

int ms_cmp_unsigned(void *a, void *b)
{ return *(unsigned *)a - *(unsigned *)b; }

int ms_cmp_double(void *a, void *b)
{ return (int)(*(double *)a - *(double *)b); }
int ms_cmp_float(void *a, void *b)
{ return (int)(*(float *)a - *(float *)b); }

int ms_cmp_str(void *a, void *b)
{ return strcmp((char *)a, (char *)b); }

int
ms_sort(void *array, void *first_member, size_t len, size_t member_size, enum ms_direction dir, int (* cmp_fn)(void *, void *))
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
