#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "free.h"

char **dbl_pointer_generator(size_t size, const char *s)
{
    char **dbl_ptr = malloc(sizeof(char *) * (size + 1));
    size_t i = 0;

    for (i = 0; i < size; i += 1) {
        dbl_ptr[i] = strdup(s);
    }
    dbl_ptr[i] = NULL;
    return dbl_ptr;
}

Test(simple_ptr_free, tests)
{
    int return_from_function;
    char *spl_ptr = (char *)malloc(sizeof(char) * 100);

    for (int i = 0; i < 100; i++) {
        spl_ptr[i] = (char)i;
    }
    return_from_function = __free(spl_ptr, __S_IFSPL);
    if (EXIT_FAILURE == return_from_function) {
        cr_log_error("Error in __free()");
    }
    cr_log_warn("tests_simple_ptr_free : [SUCCESS]");
    cr_assert_eq(return_from_function, EXIT_SUCCESS);
}

Test(double_ptr_free, tests_character)
{
    int return_from_function;
    char **dbl_ptr = dbl_pointer_generator(200, "DOUBLE PTR TEST");

    return_from_function = __free(dbl_ptr, __S_IFDBL);
    if (EXIT_FAILURE == return_from_function) {
        cr_log_error("Error in __free()");
    }
    cr_log_warn("tests_double_char_ptr_free : [SUCCESS]");
    cr_assert_eq(return_from_function, EXIT_SUCCESS);
}

Test(double_ptr_free, tests_integer)
{
    int return_from_function;
    int **dbl_int_ptr = malloc(sizeof(int *) * (100 + 1));
    int _i;

    for (_i = 0; _i < 100; _i += 1) {
        dbl_int_ptr[_i] = malloc(sizeof(int) * 50);
        for (int j = 0; j < 50; j += 1) {
            dbl_int_ptr[_i][j] = (_i + 1) * (j + 1);
        }
    }
    dbl_int_ptr[_i] = NULL;
    return_from_function = __free(dbl_int_ptr, __S_IFDBL);
    if (EXIT_FAILURE == return_from_function) {
        cr_log_error("Error in __free()");
    }
    cr_log_warn("tests_double_int_ptr_free : [SUCCESS]");
    cr_assert_eq(return_from_function, EXIT_SUCCESS);
}

Test(triple_ptr_free, tests_character)
{
    int return_from_function;
    char ***trpl_ptr = malloc(sizeof(char **) * (850 + 1));
    int _i;

    for (_i = 0; _i < 850; _i += 1) {
        trpl_ptr[_i] = dbl_pointer_generator(1000, "TRIPLE PTR TEST");
    }
    trpl_ptr[_i] = NULL;
    return_from_function = __free(trpl_ptr, __S_IFTPL);
    if (EXIT_FAILURE == return_from_function) {
        cr_log_error("Error in __free()");
    }
    cr_assert_eq(return_from_function, EXIT_SUCCESS);
    cr_log_warn("tests_triple_ptr_free : [SUCCESS]");
}

Test(tests_free_failure, test_flags)
{
    int return_from_function;
    char *ptr = "FAILURE TEST";

    return_from_function = __free(ptr, UINT16_MAX);
    cr_assert_eq(return_from_function, EXIT_FAILURE);
    cr_log_warn("tests_flags_failure : [SUCCESS]");
}
