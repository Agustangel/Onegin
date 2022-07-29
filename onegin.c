
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "onegin.h"


void should_skip(char* current_position)
{
    while(isalpha(*current_position) == 0)
    {
        ++current_position;
    }
}

int string_comparator(const void* lhs, const void* rhs)
{

    struct string_t* str_1 = (struct string_t*) lhs;
    struct string_t* str_2 = (struct string_t*) rhs;

    char* current_position_1 = str_1->begin_string;
    char* current_position_2 = str_2->begin_string;

    while((*current_position_1 != '\0') && (*current_position_2 != '\0'))
    {
        should_skip(current_position_1);
        should_skip(current_position_2);

        while(*current_position_1 == *current_position_2)
        {
            ++current_position_1;
            ++current_position_2;
        }

        if((*current_position_1 == '\0') && (*current_position_2 == '\0'))
        {
            return 0;
        }

        if(*current_position_1 == '\0') 
        {
            return -1;
        }

        if(*current_position_2 == '\0') 
        {
            return 1;
        }

        if(tolower((*current_position_1) < tolower(*current_position_2)) && \
          (isalpha(*current_position_1) != 0) && (isalpha(*current_position_2) != 0))
        {
            return -1;
        }

        if((tolower(*current_position_1) > tolower(*current_position_2)) && \
          (isalpha(*current_position_1) != 0) && (isalpha(*current_position_2) != 0))
        {
            return 1;
        }
    };

}

void print_strings(struct string_t* strings, long number_strings)
{
    printf("number_strings = %ld\n", number_strings);
    for (int idx = 0; idx < number_strings; ++idx)
    {
        printf("%d: %s\n", idx, strings[idx].begin_string);
    }
}


struct string_t* get_strings(char* buffer, long count, long number_strings)
{
    struct string_t* strings = (struct string_t*) calloc(number_strings, sizeof(struct string_t));

    struct string_t* current_string = strings;
    char* current_position = buffer;
    char* subsidiary_possition = buffer;

    long string_idx = 1L;

    current_string->begin_string = current_position;
    printf("In function get_strings \n");
    printf("%s", current_string->begin_string);

    while((current_position = strchr(current_position, '\n')) != NULL)
    {
        printf("%ld: %s", string_idx, current_string->begin_string);

        current_string->len_string = (current_position - subsidiary_possition) / sizeof(char);

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
    long number_strings= 0L;

    char* current_position = buffer;

    while((current_position = strchr(current_position, '\n')) != NULL)
    {
        ++number_strings;
        ++current_position;
    }

    return number_strings;
}


int fill_buffer(FILE* text, char* buffer, long count)
{
    rewind(text);

    long get_count = fread(buffer, sizeof(char), count, text);

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

        return count_symbols;
    }

    else
    {
        return ERR_BAD_PTR;
    }
}


FILE* open_file(char* filename)
{
    assert(filename != NULL);

    FILE* text = fopen(filename, "r");

    if(text != NULL)
    {
        return text;
    }
    
    else
    {
        return NULL;
    }
}


int parse_args(struct args_t* args, int argc, char** argv, int* flag)
{
    if ((argc < 2) || (argc > 3))
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

    if (argc == 3)
    {
        args->option = argv[2];

        printf("%s\n", args->option);
        fflush(stdout);

        if(args->option[0] == '-' && args->option[1] == 'r')
        {
            *flag = BACK;
        }

        else
        {
            printf("%s\n", USAGE);
            return ERR_INC_INPUT;
        }
    }

    else
    {
        args->option = NULL;
    }
}
