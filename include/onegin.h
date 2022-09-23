#pragma once

/*! \file onegin.h
 * Lexicographic sort. */

//! const for describing input parameters
static const char* USAGE = "Usage: ./onegin flag_file filename option_sort_type option_sort_direction flag_algoritm algoritm\n \
        flag_file - option '-f' notifying about filename.\n \
        filename  - name of file with text.\n \
                                          \n \
        option_sort_type - option to sort from the beginning or from the end of the string.\n \
        type '-b' to sort from the beginning of the string.\n \
        type '-e' to sort from the end of the string.\n \
                                          \n \
        option_sort_direction - sorting in descending and ascending order.\n \
        type '-r' to enable reverse sort. \n \
        type '-d' to enable directly sort.\n \
                                          \n \
        flag_algoritm - option '-a' notifying about type of algorithm.\n \
        algorithm - proposed sorting algorithm. \n \
        type '--sort=qsort' or '--sort=insertion' to enable it.\n";

//! \enum algorithm
/*! An enum of possible algorithms. */
enum algorithm
{
    QSORT     = -7,
    INSERTION = -6
};
//! \enum error_names
/*! An enum of possible errors. */
enum error_names
{
    ERR_INC_INPUT = -5,
    ERR_BAD_FILE  = -4,
    ERR_BAD_READ  = -3,
    ERR_BAD_PTR   = -2
};

//! \enum option_sort_type
/*! An enum of possible sorts type. */
enum option_sort_type
{
    BEGIN = 0,
    END   = 1
};

//! \enum option_sort_direction
/*! An enum of possible sorts direction. */
enum option_sort_direction
{
    DIRECTLY =  1,
    REVERSE  = -1
};


//! \struct args_t
/*! Сommand line args structure, including the args and their number. */
struct args_t
{
    char* filename; /*!< The name of the text file to sort. */
    int option_sort_type; /*!< options '-b' and '-e' for sorting. */
    int option_sort_direction; /*!< options '-d' and '-r' for directly and reverse sort. */
    int option_sort_algorithm; /*!< options for type of algorithm. */
    char* algorithm; /*!< algorithm of sorting. */

};

//! \struct string_t
/*! A structure describing the string. */
struct string_t
{

    char* begin_string; /*!< Pointer to the beginning of the string. */
    char* end_string; /*!< Pointer to the end of the string. */
    int len_string; /*!< Length of the string. */

};

//! Macros HANDLE_ERROR
/*! macros to describe the error. */
/*! \param retval - return value to be tested.
/*! \param errcode - const describing a possible error. 
/*! \param msg - error message. */
#define HANDLE_ERROR(retval, errcode, msg) \
    if (retval == errcode)                 \
    {                                      \
        printf(msg);                       \
        exit(errcode);                     \
    };

//! Function that parses the input arguments.
/*! \param &args - pointer to the struct args_t.
    \param argc - count of the argumets.
    \param argv[] - array of the strings - input data.
 *  \returns result - ERR_INC_INPUT or 0. */
int parse_args(struct args_t* args, int argc, char** argv);

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

//! Function that skips unnecessary symbols, moves forward lines.
/*! \param &current_position - pointer to current position in string. */
void should_skip_forward(char** ptr_current_position);

//! Function that skips unnecessary symbols, moves back lines.
/*! \param &current_position - pointer to current position in string. */
void should_skip_back(char** ptr_current_position);

//! Function that compares two objects from the beginning.
/*! \param lhs - pointer to the struct of the first string.
/*! \param rhs - pointer to the struct of the second string.
 *  \returns one of the possible results:
                when sorted in ascending order:
                -1 - when lhs < rhs. 
                 1 - when lhs > rhs.
                 0 - when lhs = rhs. 
    differently when sorted in descending order. */
int string_comparator(const void* lhs, const void* rhs);

//! Function that compares two objects from the end.
/*! \param lhs - pointer to the struct of the first string.
/*! \param rhs - pointer to the struct of the second string.
 *  \returns one of the possible results:
                when sorted in ascending order:
                -1 - when lhs < rhs. 
                 1 - when lhs > rhs.
                 0 - when lhs = rhs. 
    differently when sorted in descending order. */
int string_comparator_reverse(const void* lhs, const void* rhs);

//! Function that prints array of the strings.
/*! \param strings - pointer to the array of the strings.
/*! \param number_strings - number of strings in the file. */
void print_strings(struct string_t* strings, long number_strings);

//! Function that creates output file and prints there array of the sorted strings.
/*! \param strings - pointer to the array of the strings.
/*! \param number_strings - number of strings in the file. */
void make_output_file(struct string_t* strings, long number_strings);

//! Function that sorts strings by qsot algorithm.
/*! \param strings - pointer to the array of the strings.
/*! \param number_strings - number of strings in the file. */
void qsort_sort(struct args_t* args, struct string_t* strings, long number_strings);

//! Function that sorts strings.
/*! \param strings - pointer to the array of the strings.
/*! \param number_strings - number of strings in the file. */
void sort(struct args_t* args, struct string_t* strings, long number_strings);
