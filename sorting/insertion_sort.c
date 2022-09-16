
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "onegin.h"
#include "insertion_sort.h"



void insertion_sort(struct args_t* args, struct string_t* strings, long number_strings)
{
    unsigned long idx = 1L;

    for(idx = 1L; idx < number_strings; ++idx )
    {
        struct string_t current_string = strings[idx];

        unsigned long support_idx = idx;

        if(args->option_sort_type == BEGIN)
        {
            while((support_idx > 0) && (string_comparator(&strings[support_idx - 1], &current_string) == 1))
            {
                strings[support_idx] = strings[support_idx - 1];    

                --support_idx;

                strings[support_idx] = current_string;
            }
        }
        if(args->option_sort_type == END)
        {
            while((support_idx > 0) && (string_comparator_reverse(&strings[support_idx - 1], &current_string) == 1))
            {
                strings[support_idx] = strings[support_idx - 1];    

                --support_idx;

                strings[support_idx] = current_string;
            }
        }       
    }
}
