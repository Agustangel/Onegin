#pragma once

/*! \file onegin.h
 * Lexicographic sort. */

//! const for describing input parameters
static const char* USAGE = "Usage: ./onegin filename option\n \
        filename - name of file with text\n \
        option - reverse sort option;\n \
        type '-r' to enable it.\n";

//! \enum error_names
/*! An enum of possible errors. */
enum error_names
{
    ERR_INC_INPUT = -5,
    ERR_BAD_FILE  = -4,
    ERR_BAD_READ  = -3,
    ERR_BAD_PTR   = -2
};

//! \enum options
/*! An enum of possible sorts. */
enum options
{
    DIRECTLY = 0,
    BACK     = 1
};

//! \struct args_t
/*! Сommand line args structure, including the args and their number. */
struct args_t
{

    char* filename; /*!< The name of the text file to sort. */
    char* option; /*!< option '-r' for reverse sort. */

};

//! \struct string_t
/*! A structure describing the string. */
struct string_t
{

    char* begin_string; /*!< Pointer to the beginning of the string. */
    int len_string; /*!< Length of the string. */

};

//! Marker HANDLE_ERROR
/*! marker to describe the error. */
/*! \param retval - return value to be tested.
/*! \param errcode - const describing a possible error. 
/*! \param msg - error message. */
#define HANDLE_ERROR(retval, errcode, msg) \
    if (retval == errcode)                 \
    {                                      \
        printf(msg);                       \
        exit(errcode);                     \
    }

//! Function that parses the input arguments.
/*! \param &args - pointer to the struct args_t.
    \param argc - count of the argumets.
    \param argv[] - array of the strings - input data.
    \param &flag - pointer to a variable describing possible sorting.
 *  \returns result - ERR_INC_INPUT or 0. */
int parse_args(struct args_t* args, int argc, char** argv, int* flag);

//! Function that opens file.
/*! \param filename - string contains the filename.
 *  \returns result - pointer to the opened file. */
FILE* open_file(char* filename);

//! Function that counts symbols in the file.
/*! \param text - pointer to the file.
 *  \returns result - number of symbols in the file. */
long count_symbols(FILE* text);

//! Function that reads the file into a buffer.
/*! \param text - pointer to the file.
/*! \param count - number of symbols in the file.
/*! \param buffer - pointer to the beginning of buffer.
 *  \returns result - error in case of incorrect filling. */
int fill_buffer(FILE* text, char* buffer, long count);

//! Function that counts strings in the file.
/*! \param buffer - pointer to the beginning of buffer.
/*! \param count - number of symbols in the file.
 *  \returns result - number of strings in the file. */
long count_strings(char* buffer, long count);

//! Function that receives array of strings.
/*! \param buffer - pointer to the beginning of buffer.
/*! \param count - number of symbols in the file.
/*! \param number_strings - number of strings in the file.
 *  \returns result - pointer to the array of strings. */
struct string_t* get_strings(char* buffer, long count, long number_strings);

//! Function that skips unnecessary symbols.
/*! \param current_position - pointer to the current position in string. */
void should_skip(char* current_position);

int string_comparator(const void* lhs, const void* rhs);
void print_strings(struct string_t* strings, long number_strings);