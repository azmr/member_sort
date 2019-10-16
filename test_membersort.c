#include "membersort.h"
#include "stdio.h"

typedef struct TestType {
	unsigned int u;
	int i;
	double d;
	char *str;
} TestType;

#define countof(a) (sizeof(a)/sizeof(*a))

void
print_vals(TestType vals[], size_t vals_n)
{
	for (size_t i = 0; i < vals_n; ++i)
	{
		TestType val = vals[i];
		printf("u: %u,\ti: %d,\td: %lf,\tstr: %s\n",
				val.u, val.i, val.d, val.str);
	}
}

int main()
{
	TestType vals[] = {
		{0,  1, 1.1, "ars"},
		{1, -1, 1.4, "rs"},
		{2,  3, 2.3, "arst"},
		{4,  2, 2.0, "cars"},
	};
	print_vals(vals, countof(vals));

	ms_sort(vals, &vals[0].u, countof(vals), sizeof(vals[0]), ms_cmp_unsigned);
	print_vals(vals, countof(vals));

	ms_sort(vals, &vals[0].i, countof(vals), sizeof(vals[0]), ms_cmp_int);
	print_vals(vals, countof(vals));

	ms_sort(vals, &vals[0].d, countof(vals), sizeof(vals[0]), ms_cmp_double);
	print_vals(vals, countof(vals));

	ms_sort(vals, &vals[0].str, countof(vals), sizeof(vals[0]), ms_cmp_str);
	print_vals(vals, countof(vals));

	return 0;
}
