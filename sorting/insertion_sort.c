
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "onegin.h"
#include "insertion_sort.h"


void insertion_sort(struct string_t* strings, long number_strings, int flag_sort_type, int flag_sort_direction)
{
    unsigned long idx = 1L;

    for(idx = 1L; idx < number_strings; ++idx )
    {
        struct string_t current_string = strings[idx];

        unsigned long support_idx = idx;

        if(flag_sort_type == BEGIN)
        {
            SORTING(string_comparator);
        }

        if(flag_sort_type == END)
        {
            SORTING(string_comparator_reverse);
        }       
    }
}
