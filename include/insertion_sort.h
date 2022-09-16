#pragma once

#include <stdio.h>


//! Macros SORTING
/*! macros to sort with different comparators. */
/*! \param comparator - sort comparator version. */
#define SORTING(comparator)                                                                    \
{                                                                                              \
    while((support_idx > 0) && (comparator(&strings[support_idx - 1], &current_string) == 1))  \
    {                                                                                          \
        strings[support_idx] = strings[support_idx - 1];                                       \
                                                                                               \
        --support_idx;                                                                         \
                                                                                               \
        strings[support_idx] = current_string;                                                 \
    }                                                                                          \
};

//! Function for insertion sort
/*! \param strings - pointer to the array of strings.
/*! \param number_strings - number of strings in the file. */
void insertion_sort(struct args_t* args, struct string_t* strings, long number_strings);
