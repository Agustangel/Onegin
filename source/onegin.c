
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>

#include "onegin.h"
#include "insertion_sort.h"

//#define DEBUG 0

static int flag = DIRECTLY;


void sort(struct args_t* args, struct string_t* strings, long number_strings)
{
    if(args->option_sort_algorithm == QSORT)
    {
        qsort_sort(args, strings, number_strings);
    }
    if(args->option_sort_algorithm == INSERTION)
    {
        insertion_sort(args, strings, number_strings);
    } 
}

void qsort_sort(struct args_t* args, struct string_t* strings, long number_strings)
{
    if(args->option_sort_type == BEGIN)
    {
        qsort(strings, number_strings, sizeof(struct string_t), string_comparator);
    }
    if(args->option_sort_type == END)
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

        should_skip_forward(&current_position_1);
        should_skip_forward(&current_position_2);

        while((tolower(*current_position_1) == tolower(*current_position_2)) && (isalnum(*current_position_1) != 0) && (isalnum(*current_position_2) != 0))
        {
            ++current_position_1;
            ++current_position_2;

            if((*current_position_1 == '\0') && (*current_position_2 == '\0'))
            {
                #ifdef DEBUG
                    printf("%s\n", str_1->begin_string);
                    printf(" =\n");
                    printf("%s\n", str_2->begin_string);
                    printf("current_position_1: %s\n", current_position_1);
                    printf("current_position_2: %s\n", current_position_2);
                #endif

                return 0;
            }
        }

        if(*current_position_1 == '\0') 
        {
            #ifdef DEBUG
                printf("%s\n", str_1->begin_string);
                printf(" <\n");
                printf("%s\n", str_2->begin_string);
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
                printf("%s\n", str_1->begin_string);
                printf(" >\n");
                printf("%s\n", str_2->begin_string);
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

        if((tolower(*current_position_1) < tolower(*current_position_2)) && \
          (isalnum(*current_position_1) != 0) && (isalnum(*current_position_2) != 0))
        {
            #ifdef DEBUG
                printf("%s < %s\n", str_1->begin_string, str_2->begin_string);
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

        if ((tolower(*current_position_1) > tolower(*current_position_2)) && \
          (isalnum(*current_position_1) != 0) && (isalnum(*current_position_2) != 0))
        {
            #ifdef DEBUG
                printf("%s\n", str_1->begin_string);
                printf(" >\n");
                printf("%s\n", str_2->begin_string);
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

    char* current_position_1 = &(str_1->begin_string[str_1->len_string]);
    char* current_position_2 = &(str_2->begin_string[str_2->len_string]);

    #ifdef DEBUG
        printf("current_position_1: %s\n", current_position_1);
        printf("current_position_2: %s\n", current_position_2);
    #endif

     while((current_position_1 != str_1->begin_string) && (current_position_2 != str_2->begin_string))
    {
        should_skip_back(&current_position_1);
        should_skip_back(&current_position_2);

        while(tolower(*current_position_1) == tolower(*current_position_2))
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

        if((tolower(*current_position_1) < tolower(*current_position_2)) && \
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

    char* current_position = buffer;
    char* subsidiary_possition = buffer;

    unsigned long string_idx = 0L;

    while((current_position = strchr(current_position, '\n')) != NULL)
    {
        strings[string_idx].len_string = (current_position - subsidiary_possition) / sizeof(char);

        *current_position = '\0';
        ++current_position;
        
        strings[string_idx].begin_string = subsidiary_possition;

        subsidiary_possition = strchr(subsidiary_possition, '\0');
        ++subsidiary_possition;

        int test_len = strlen(strings[string_idx].begin_string);

        #ifdef DEBUG
            printf("%ld: len_string: %d\n", string_idx, strings[string_idx].len_string);
            printf("%ld: begin_string: %s\n", string_idx, strings[string_idx].begin_string);
        #endif
        
        ++string_idx;
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

    long get_count = fread(buffer, sizeof(char), count, text);
    #ifdef DEBUG
        printf("get_count = %ld\n", get_count);
    #endif

    if(get_count != (count - 1))
    {
        return ERR_BAD_READ;
    }

    return 0;
}


long count_symbols(FILE* text)
{
    assert(text != NULL);

    long begin_position = ftell(text);

    if(fseek(text, 0, SEEK_END) != 0)
    {
        return ERR_BAD_PTR;
    }

    long end_position = ftell(text);
    if(end_position == -1L)
    {
        exit(ERR_BAD_PTR);
    }

    long count_symbols = (end_position - begin_position) / sizeof(char);

    #ifdef DEBUG
        printf("count_symbols: %ld\n", count_symbols);
    #endif

    rewind(text);

    return count_symbols + 1;
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

    return text;
}


int parse_args(struct args_t* args, int argc, char** argv)
{
    #ifdef DEBUG
        printf("argc: %d\n", argc);
        printf("filename: %s\n", argv[1]);
        printf("flag_sort_type: %d\n", *flag_sort_type);
        printf("flag_sort_direction: %d\n", *flag_sort_direction);
    #endif

    if(strcmp(argv[1], "--help") == 0)
    {
        printf("%s\n", USAGE);
        exit(0);
    }

    if (argc != 6)
    {
        printf("%s\n", USAGE);
        return ERR_INC_INPUT;
    }

    static struct option longopts[] =
    {
        {"qsort", 0, NULL, QSORT},
        {"insertion", 0, NULL, INSERTION},
    };
    static const char opts[] = "bedrf:";

    int ret = 0;
    while((ret = getopt_long(argc, argv, opts, longopts, &optind)) != -1)
    {
        switch (ret)
        {
        case 'b':
            args->option_sort_type = BEGIN;
            break;
        case 'e':
            args->option_sort_type = END;
            break;
        case 'd':
            args->option_sort_direction = DIRECTLY;
            flag = DIRECTLY;
            break; 
        case 'r':
            args->option_sort_direction = REVERSE;
            flag = REVERSE;
            break;
        case 'f':
            args->filename = optarg;
            break;
        case QSORT:
            args->option_sort_algorithm = QSORT;
            break;
        case INSERTION:
            args->option_sort_algorithm = INSERTION;
            break;
        default:
            printf("ERROR: invalied option.\n");
            exit(ERR_INC_INPUT);              
        }
    }

    #ifdef DEBUG
        printf("args->filename: %s\n", args->filename);
        printf("option_sort_type: %s\n", args->option_sort_type);
        printf("args->option_sort_direction: %s\n", args->option_sort_direction);
        printf("LINE %d: option_sort_algorithm: %d\n", __LINE__, args->option_sort_algorithm);
    #endif
}
