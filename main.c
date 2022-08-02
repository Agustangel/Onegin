
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "onegin.h"
#include "insertion_sort.h"


int main(int argc, char* argv[])
{
    int flag_sort_type = BEGIN;
    int flag_sort_direction = DIRECTLY;
    int flag_algorithm = QSORT;

    struct args_t args;

    int ret = parse_args(&args, argc, argv, &flag_sort_type, &flag_sort_direction, &flag_algorithm);
    HANDLE_ERROR(ret, ERR_INC_INPUT, "ERROR: incorrect input.\n");

    FILE* text = open_file(args.filename);
    if (text == NULL)
    {
        printf("ERROR: bad file read.\n");
        exit(ERR_BAD_FILE);
    }

    long count = count_symbols(text);
    HANDLE_ERROR(count, ERR_BAD_PTR, "ERROR: pointer outside file.\n");

    char* buffer = (char*) calloc(count, sizeof(char));

    ret = fill_buffer(text, buffer, count);
    HANDLE_ERROR(ret, ERR_BAD_READ, "ERROR: file read error.\n");

    long number_strings = count_strings(buffer, count);

    struct string_t* strings = get_strings(buffer, count, number_strings);

    sort(strings, number_strings, flag_sort_type, flag_sort_direction, flag_algorithm);

    make_output_file(strings, number_strings);

    free(buffer);

    return 0;
}
