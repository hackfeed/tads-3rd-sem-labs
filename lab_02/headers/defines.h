/*
Return codes, integer constants and 
boolean constants definition.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

#define OK 0
#define IN_BETWEEN_ERROR 1
#define FILENAME_ERROR 2
#define FILE_NOT_EXIST_ERROR 3
#define EMPTY_FILE_ERROR 4
#define INVALID_STRING_INPUT_ERROR 5
#define INVALID_INT_INPUT_ERROR 6
#define NON_POSITIVE_INPUT_ERROR 7
#define WRONG_BOOK_TYPE_ERROR 8
#define WRONG_SIGN_ERROR 9
#define WRONG_YEAR_ERROR 10
#define MULTIPLE_GENRES_ERROR 11

/*
Macroreplacements.
*/
#define MAX_FILENAME_LEN 256
#define MAX_STRING_FIELD_SIZE 256

#define GOT_ARG 1

/*
Colored printf ouptut.
*/
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"

#endif