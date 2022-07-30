
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "onegin.h"

#define DEBUG 0

static int flag = DIRECTLY;


void sort(struct string_t* strings, long number_strings, int flag_sort_type, int flag_sort_direction)
{
    if((flag_sort_type == BEGIN) && (flag_sort_direction == DIRECTLY))
    {
        qsort(strings, number_strings, sizeof(struct string_t), string_comparator);
    }

    if((flag_sort_type == BEGIN) && (flag_sort_direction == BACK))
    {
        qsort(strings, number_strings, sizeof(struct string_t), string_comparator);
    }

    if((flag_sort_type == END) && (flag_sort_direction == DIRECTLY))
    {
        qsort(strings, number_strings, sizeof(struct string_t), string_comparator_reverse);
    }

    if((flag_sort_type == END) && (flag_sort_direction == BACK))
    {
        qsort(strings, number_strings, sizeof(struct string_t), string_comparator_reverse);
    }
}


void should_skip_forward(char** ptr_current_position)
{
    assert(ptr_current_position != NULL);

    while(isalpha(**ptr_current_position) == 0)
    {
        ++(*ptr_current_position);
    }
}

void should_skip_back(char** ptr_current_position)
{
    assert(ptr_current_position != NULL);

    while(isalpha(**ptr_current_position) == 0)
    {
        --(*ptr_current_position);
    }
}


int string_comparator(const void* lhs, const void* rhs)
{
    assert(lhs != NULL);
    assert(rhs != NULL);

    struct string_t* str_1 = (struct string_t*) lhs;
    struct string_t* str_2 = (struct string_t*) rhs;

    char* current_position_1 = str_1->begin_string;
    char* current_position_2 = str_2->begin_string;

    while((*current_position_1 != '\0') && (*current_position_2 != '\0'))
    {
        #ifdef DEBUG
            printf("current_position_1: %s\n", current_position_1);
            printf("current_position_2: %s\n", current_position_2);
        #endif

        should_skip_forward(&current_position_1);
        should_skip_forward(&current_position_2);

        #ifdef DEBUG
            printf("current_position_1: %s\n", current_position_1);
            printf("current_position_2: %s\n", current_position_2);
        #endif

        while(*current_position_1 == *current_position_2)
        {
            ++current_position_1;
            ++current_position_2;

            if((*current_position_1 == '\0') && (*current_position_2 == '\0'))
            {
                #ifdef DEBUG
                    printf("str_1 = str_2: %s = %s\n", str_1->begin_string, str_2->begin_string);
                    printf("current_position_1: %s\n", current_position_1);
                    printf("current_position_2: %s\n", current_position_2);
                #endif

                return 0;
            }
        }

        if(*current_position_1 == '\0') 
        {
            #ifdef DEBUG
                printf("str_1 < str_2: %s = %s\n", str_1->begin_string, str_2->begin_string);
                printf("current_position_1: %s\n", current_position_1);
                printf("current_position_2: %s\n", current_position_2);
            #endif

            if(flag == DIRECTLY)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }

        if(*current_position_2 == '\0') 
        {
            #ifdef DEBUG
                printf("str_1 > str_2: %s = %s\n", str_1->begin_string, str_2->begin_string);
                printf("current_position_1: %s\n", current_position_1);
                printf("current_position_2: %s\n", current_position_2);
            #endif

            if(flag == DIRECTLY)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }

        if(tolower((*current_position_1) < tolower(*current_position_2)) && \
          (isalpha(*current_position_1) != 0) && (isalpha(*current_position_2) != 0))
        {
            #ifdef DEBUG
                printf("str_1 < str_2: %s = %s\n", str_1->begin_string, str_2->begin_string);
                printf("current_position_1: %s\n", current_position_1);
                printf("current_position_2: %s\n", current_position_2);
            #endif

            if(flag == DIRECTLY)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }

        if((tolower(*current_position_1) > tolower(*current_position_2)) && \
          (isalpha(*current_position_1) != 0) && (isalpha(*current_position_2) != 0))
        {
            #ifdef DEBUG
                printf("str_1 > str_2: %s = %s\n", str_1->begin_string, str_2->begin_string);
                printf("current_position_1: %s\n", current_position_1);
                printf("current_position_2: %s\n", current_position_2);
            #endif

            if(flag == DIRECTLY)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
    }

    return 0;
}


int string_comparator_reverse(const void* lhs, const void* rhs)
{
    assert(lhs != NULL);
    assert(rhs != NULL);

    struct string_t* str_1 = (struct string_t*) lhs;
    struct string_t* str_2 = (struct string_t*) rhs;

    char* current_position_1 = str_1->end_string;
    char* current_position_2 = str_2->end_string;

    #ifdef DEBUG
        printf("current_position_1: %s\n", current_position_1);
        printf("current_position_2: %s\n", current_position_2);
    #endif

    do
    {
        should_skip_back(&current_position_1);
        should_skip_back(&current_position_2);

        while(*current_position_1 == *current_position_2)
        {
            --current_position_1;
            --current_position_2;

            if((current_position_1 == str_1->begin_string) && (current_position_2 == str_2->begin_string))
            {
                #ifdef DEBUG
                    printf("str_1 = str_2: %s = %s\n", str_1->begin_string, str_2->begin_string);
                    printf("current_position_1: %s\n", current_position_1);
                    printf("current_position_2: %s\n", current_position_2);
                #endif

                return 0;
            }

            if((current_position_1 == str_1->begin_string) && (current_position_2 != str_2->begin_string))
            {
                #ifdef DEBUG
                    printf("str_1 < str_2: %s = %s\n", str_1->begin_string, str_2->begin_string);
                    printf("current_position_1: %s\n", current_position_1);
                    printf("current_position_2: %s\n", current_position_2);
                #endif

                if(flag == DIRECTLY)
                {
                    return -1;
                }
                else
                {
                    return 1;
                }
            }

            if((current_position_1 != str_1->begin_string) && (current_position_2 == str_2->begin_string)) 
            {
                #ifdef DEBUG
                    printf("str_1 > str_2: %s = %s\n", str_1->begin_string, str_2->begin_string);
                    printf("current_position_1: %s\n", current_position_1);
                    printf("current_position_2: %s\n", current_position_2);
                #endif

                if(flag == DIRECTLY)
                {
                    return 1;
                }
                else
                {
                    return -1;
                }
            }
        }

        if(tolower((*current_position_1) < tolower(*current_position_2)) && \
          (isalpha(*current_position_1) != 0) && (isalpha(*current_position_2) != 0))
        {
            #ifdef DEBUG
                printf("str_1 < str_2: %s > %s\n", str_1->begin_string, str_2->begin_string);
                printf("current_position_1: %s\n", current_position_1);
                printf("current_position_2: %s\n", current_position_2);
            #endif

            if(flag == DIRECTLY)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }

        if((tolower(*current_position_1) > tolower(*current_position_2)) && \
          (isalpha(*current_position_1) != 0) && (isalpha(*current_position_2) != 0))
        {
            #ifdef DEBUG
                printf("str_1 > str_2: %s < %s\n", str_1->begin_string, str_2->begin_string);
                printf("current_position_1: %s\n", current_position_1);
                printf("current_position_2: %s\n", current_position_2);
            #endif

            if(flag == DIRECTLY)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
    }
    while((current_position_1 != str_1->begin_string) && (current_position_2 != str_2->begin_string));

    return 0;
}


void print_strings(struct string_t* strings, long number_strings)
{
    assert(strings != NULL);

    printf("number_strings = %ld\n", number_strings);

    for (int idx = 0; idx < number_strings; ++idx)
    {
        printf("%d: %s\n", idx, strings[idx].begin_string);
    }
}


struct string_t* get_strings(char* buffer, long count, long number_strings)
{
    assert(buffer != NULL);

    struct string_t* strings = (struct string_t*) calloc(number_strings, sizeof(struct string_t));

    struct string_t* current_string = strings;
    char* current_position = buffer;
    char* subsidiary_possition = buffer;

    long string_idx = 1L;

    current_string->begin_string = current_position;

    while((current_position = strchr(current_position, '\n')) != NULL)
    {
        current_string->end_string = current_position - 1;
        current_string->len_string = (current_position - subsidiary_possition) / sizeof(char);

        #ifdef DEBUG
            printf("%ld: len_string: %d\n", string_idx, current_string->len_string);
            printf("%ld: begin_string: %s\n", string_idx, current_string->begin_string);
            printf("%ld: end_string: %s\n", string_idx, current_string->end_string);
        #endif

        *current_position = '\0';

        ++current_position;
        ++string_idx;
        
        subsidiary_possition = strchr(subsidiary_possition, '\0');
        ++subsidiary_possition;
        
        ++current_string;

        if(string_idx <= number_strings)
        {
            current_string->begin_string = current_position;
        }
    }

    return strings;
}


long count_strings(char* buffer, long count)
{
    assert(buffer != NULL);

    long number_strings= 0L;

    char* current_position = buffer;

    while((current_position = strchr(current_position, '\n')) != NULL)
    {
        ++number_strings;
        ++current_position;
    }

    #ifdef DEBUG
        printf("number_strings = %ld\n", number_strings);
    #endif

    return number_strings;
}


int fill_buffer(FILE* text, char* buffer, long count)
{
    assert(text != NULL);
    assert(buffer != NULL);

    rewind(text);

    long get_count = fread(buffer, sizeof(char), count, text);

    #ifdef DEBUG
        printf("get_count = %ld\n", get_count);
    #endif

    if(get_count != count)
    {
        return ERR_BAD_READ;
    }
}


long count_symbols(FILE* text)
{
    assert(text != NULL);

    long begin_position = ftell(text);

    if(fseek(text, 0, SEEK_END) == 0)
    {
        long end_position = ftell(text);

        if(end_position == -1L)
        {
            exit(ERR_BAD_PTR);
        }

        long count_symbols = (end_position - begin_position) / sizeof(char);

        #ifdef DEBUG
            printf("count_symbols: %ld\n", count_symbols);
        #endif

        return count_symbols;
    }
    else
    {
        return ERR_BAD_PTR;
    }
}

void make_output_file(struct string_t* strings, long number_strings)
{
    FILE* output_text = fopen("output.txt", "w");

    for (long idx = 0L; idx < number_strings; ++idx)
    {
        fprintf(output_text, "%s\n", strings[idx].begin_string);
    }
}


FILE* open_file(char* filename)
{
    assert(filename != NULL);

    FILE* text = fopen(filename, "r");

    #ifdef DEBUG
        printf("text: %p\n", text);
    #endif

    if(text != NULL)
    {
        return text;
    }
    else
    {
        return NULL;
    }
}


int parse_args(struct args_t* args, int argc, char** argv, int* flag_sort_type, int* flag_sort_direction)
{
    #ifdef DEBUG
        printf("argc: %d\n", argc);
        printf("filename: %s\n", argv[1]);
        printf("flag_sort_type: %d\n", *flag_sort_type);
        printf("flag_sort_direction: %d\n", *flag_sort_direction);
    #endif

    if ((argc < 3) || (argc > 4))
    {
        printf("%s\n", USAGE);
        return ERR_INC_INPUT;
    }

    if(argv[1] == "--help")
    {
        printf("%s\n", USAGE);
        exit(0);
    }

    args->filename = argv[1];
    args->option_sort_type = argv[2];

    #ifdef DEBUG
        printf("args->filename: %s\n", args->filename);
        printf("option_sort_type: %s\n", args->option_sort_type);
    #endif

    if(args->option_sort_type[0] == '-' && args->option_sort_type[1] == 'b')
    {
        *flag_sort_type = BEGIN;
    }
    else if (args->option_sort_type[0] == '-' && args->option_sort_type[1] == 'e')
    {
        *flag_sort_type = END;
    }
    else
    {
        printf("%s\n", USAGE);
        return ERR_INC_INPUT;
    }

    if (argc == 4)
    {
        args->option_sort_direction = argv[3];

        #ifdef DEBUG
            printf("args->option_sort_direction: %s\n", args->option_sort_direction);
        #endif

        if(args->option_sort_direction[0] == '-' && args->option_sort_direction[1] == 'r')
        {
            *flag_sort_direction = BACK;
            flag = BACK;
        }
        else
        {
            printf("%s\n", USAGE);
            return ERR_INC_INPUT;
        }
    }
    else
    {
        args->option_sort_direction = NULL;
    }
}
