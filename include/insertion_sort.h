#pragma once

#include <stdio.h>


//! Function for insertion sort
/*! \param strings - pointer to the array of strings.
/*! \param args - pointer to the struct of entering arguments.
/*! \param number_strings - number of strings in the file. */
void insertion_sort(struct args_t* args, struct string_t* strings, long number_strings);
