/**
 * @file free.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief File that contains __free functions.
 * @version 0.1
 * @date 2022-09-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "free.h"

void __get_dimension_nmemb_ptr(const void * __restrict__ __data, unsigned int __dimension, __nmemb_fn_t * __restrict__ __nmemb)
{
    if (__dimension >= __S_ISDBL)
    {
        char **__dbl_dataptr = (char **)__data;
        while (__dbl_dataptr[++__nmemb->__nmemb1d] != NULL);
    }
    if (__dimension >= __S_ISTPL)
    {
        char ***__trpl_dataptr = (char ***)__data;
        while (__trpl_dataptr[__nmemb->__nmemb1d - 1][++__nmemb->__nmemb2d] != NULL);
    }
}

void *__get_next_dimension_ptr(const void * __restrict__ __data)
{
    return *((char **)__data);
}

void __free_ptr(void * __restrict__ __data, unsigned int __dimension, unsigned int __current, size_t * __restrict__ __nmemb, __next_dimension_fn_t __next_dim)
{
    size_t __i;

    if (__dimension == __current + 1)
    {
        free((char **)__data);
        return;
    }
    __i = __INIT_INTEGER;
    while (__i < __nmemb[__current])
    {
        __free_ptr(__next_dim((char **)__data + __i), __dimension, __current + 1, __nmemb, __next_dim);
        __i++;
    }
    free((char **)__data);
}

int __free(void * __restrict__ __data, unsigned int __flags)
{
    __nmemb_fn_t __nmemb;
    size_t __i;
    unsigned int __dimension;

    if (__flags < (__S_IFSPL) || __flags > (__S_IFSPL | __S_IFDBL | __S_IFTPL)    \
        || NULL == memset(&__nmemb, __INIT_STRUCT, sizeof(__nmemb_fn_t)))
    {
        return EXIT_FAILURE;
    }
    const struct {
        unsigned int __minimum;
        unsigned int __maximum;
        unsigned int __dimension;
    } __get_dimension[] = {
        { .__minimum = (__S_IFSPL), .__maximum = (__S_IFSPL),                         .__dimension = __S_ISSPL },
        { .__minimum = (__S_IFDBL), .__maximum = (__S_IFSPL | __S_IFDBL),             .__dimension = __S_ISDBL },
        { .__minimum = (__S_IFTPL), .__maximum = (__S_IFSPL | __S_IFDBL | __S_IFTPL), .__dimension = __S_ISTPL },
    };
    __i = __INIT_INTEGER;
    while (__i < sizeof(__get_dimension) / sizeof(__get_dimension[0]))
    {
        if (__flags >= __get_dimension[__i].__minimum && __flags <= __get_dimension[__i].__maximum)
        {
            __dimension = __get_dimension[__i].__dimension;
        }
        __i++;
    }
    __get_dimension_nmemb_ptr(__data, __dimension, &__nmemb);
    __free_ptr(__data, __dimension, __INIT_DIMENSION, (size_t[2]){__nmemb.__nmemb1d, __nmemb.__nmemb2d}, &__get_next_dimension_ptr);
    return EXIT_SUCCESS;
}
