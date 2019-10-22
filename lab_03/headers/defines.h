#ifndef __DEFINES_H__
#define __DEFINES_H__

/*
Return codes and macroreplacements.
*/

/*
Global return codes.
*/
#define OK 0

/*
ds_matrix module's return codes.
*/
#define MEMORY_ALLOC_ERROR 1
#define MATRIX_INPUT_ERROR 2

/*
func_io module's return codes.
*/
#define INVALID_INTERVAL_ERROR 11
#define INVALID_INT_INPUT_ERROR 12

/*
Macroreplacements.
*/
#define GOT_ARG 1
#define FALSE 0
#define TRUE 1
#define A_LESS 1
#define B_LESS 2
#define EQUAL 3
#define UB 4

/*
Colored printf ouptut.
*/
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"

#endif