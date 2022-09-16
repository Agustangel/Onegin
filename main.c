
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "onegin.h"
#include "insertion_sort.h"


int main(int argc, char* argv[])
{
    struct args_t args;

    int ret = parse_args(&args, argc, argv);
    HANDLE_ERROR(ret, ERR_INC_INPUT, "ERROR: incorrect input.\n");
    HANDLE_ERROR(ret, ERR_NO_ARG, "ERROR: missing file or algorithm name.\n");

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

    fclose(text);

    long number_strings = count_strings(buffer, count);
    struct string_t* strings = get_strings(buffer, count, number_strings);

    sort(&args, strings, number_strings);

    make_output_file(strings, number_strings);

    free(buffer);

    return 0;
}
