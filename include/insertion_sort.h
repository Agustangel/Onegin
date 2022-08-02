#pragma once

#include <stdio.h>


//! Marker SORTING
/*! marker to sort with different comparators. */
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
/*! \param number_strings - number of strings in the file.
/*! \param flag_sort_type - flag value to sort from the beginning or end of lines.
/*! \param flag_sort_direction - flag value to sort in ascending or descending order. */
void insertion_sort(struct string_t* strings, long number_strings, int flag_sort_type, int flag_sort_direction);