#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "test.h"

RESULT
test_array_index ()
{
	GArray *array = g_array_new (FALSE, FALSE, sizeof (int));
	int v;

	v = 27;
	g_array_append_val (array, v);

	if (27 != g_array_index (array, int, 0))
		return FAILED ("");

	g_array_free (array, TRUE);

	return NULL;
}

RESULT
test_array_append_zero_terminated ()
{
	GArray *array = g_array_new (TRUE, FALSE, sizeof (int));
	int v;

	v = 27;
	g_array_append_val (array, v);

	if (27 != g_array_index (array, int, 0))
		return FAILED ("g_array_append_val failed");

	if (0 != g_array_index (array, int, 1))
		return FAILED ("zero_terminated didn't append a zero element");

	g_array_free (array, TRUE);

	return NULL;
}

RESULT
test_array_append ()
{
	GArray *array = g_array_new (FALSE, FALSE, sizeof (int));
	int v;

	if (0 != array->len)
		return FAILED ("initial array length not zero");

	v = 27;

	g_array_append_val (array, v);

	if (1 != array->len)
		return FAILED ("array append failed");

	g_array_free (array, TRUE);

	return NULL;
}

RESULT
test_array_remove ()
{
	GArray *array = g_array_new (FALSE, FALSE, sizeof (int));
	int v[] = {30, 29, 28, 27, 26, 25};

	g_array_append_vals (array, v, 6);

	if (6 != array->len)
		return FAILED ("append_vals fail");

	g_array_remove_index (array, 3);

	if (5 != array->len)
		return FAILED ("remove_index failed to update length");

	if (26 != g_array_index (array, int, 3))
		return FAILED ("remove_index failed to update the array");

	g_array_free (array, TRUE);

	return NULL;
}

static Test array_tests [] = {
	{"array_append", test_array_append},
	{"array_index", test_array_index},
	{"array_remove", test_array_remove},
	{"array_append_zero_terminated", test_array_append_zero_terminated},
	{NULL, NULL}
};

DEFINE_TEST_GROUP_INIT(array_tests_init, array_tests)
