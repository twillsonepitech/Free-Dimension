/**
 * @file free.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Free lib that deallocate all type of pointer in every dimension(s).
 * @version 0.1
 * @date 2022-09-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef FREE_H_
# define FREE_H_

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Tips, d = dimension. */

/* Initialization of variables used to free ptr. */
#define __INIT_DIMENSION    (0)
#define __INIT_INTEGER      (0)
#define __INIT_STRUCT       (0)

/* Check if the ptr passed through is 1d, 2d or 3d (no case of 4d or more...) */
#define __S_IFSPL           (2)
#define __S_IFDBL           (4)
#define __S_IFTPL           (8)

/* Set the ptr passed through as 1d, 2d or 3d before getting fread. */
#define __S_ISSPL           (1)
#define __S_ISDBL           (2)
#define __S_ISTPL           (3)

/* __nmemb_fn_t struct take care the size of the 1d (in case of 2d ptr)
        // 1d and 2d (in case of 3d ptr). */
typedef struct { size_t __nmemb1d; size_t __nmemb2d; } __nmemb_fn_t;
/* __next_dimension_fn_t function ptr return the value of the data for each
        nmemb in ptr. */
typedef void *(*__next_dimension_fn_t) (const void *);

extern void *__get_next_dimension_ptr(const void * __restrict__ __data)
    __THROW __nonnull((1)) __attribute_warn_unused_result__;

extern void __get_dimension_nmemb_ptr(const void * __restrict__ __data, unsigned int __dimension,
            __nmemb_fn_t * __restrict__ __nmemb)
    __THROW __nonnull((1, 3));

extern void __free_ptr(void * __restrict__ __data, unsigned int __dimension, unsigned int __current,
            size_t * __restrict__ __nmemb, __next_dimension_fn_t __next_dim)
    __THROW __nonnull((1, 4, 5));

extern int __free(void * __restrict__ __data, unsigned int __flags)
    __THROW __nonnull((1)) __attribute_warn_unused_result__;

#endif /* !FREE_H_ */
