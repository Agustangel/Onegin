
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "onegin.h"


int main(int argc, char* argv[])
{
    int flag = DIRECTLY;

    struct args_t args;

    int ret = parse_args(&args, argc, argv, &flag);
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

    free(buffer);

    //print_strings(strings, number_strings);
    //fflush(stdout);

    if(flag == BACK);
        // sort_back();
    if(flag == DIRECTLY);
        // sort_directly();

    qsort(strings, number_strings, sizeof(struct string_t), string_comparator);

    return 0;
}
