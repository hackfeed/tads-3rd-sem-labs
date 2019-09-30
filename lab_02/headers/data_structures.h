/*
Data structures for table.
*/

#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

#define MAX_STRING_FIELD_SIZE 256

/*
Bool enum.
*/
typedef enum boolean
{
    FALSE,
    TRUE
} boolean_t;

/*
Literature type enum.
*/
typedef enum literature
{
    technical = 1,
    fiction,
    kids
} literature_t;

/*
Unique fields for techical literature.
*/
typedef struct
{
    char field[MAX_STRING_FIELD_SIZE];
    boolean_t is_national;
    boolean_t is_translated;
    int release_year;
} technical_t;

/*
Unique fields for fiction.
*/
typedef struct
{
    boolean_t is_novel;
    boolean_t is_play;
    boolean_t is_poetry;
} fiction_t;

/*
Unique fields for kids literature.
*/
typedef struct
{
    boolean_t is_fairytale;
    boolean_t is_poetry;
} kids_t;

/*
Variative part for book structure.
*/
typedef union 
{
    technical_t technical_book;
    fiction_t fiction_book;
    kids_t kids_book;
} variative_t;

/*
Book representing data structure.
*/
typedef struct
{
    char author_last_name[MAX_STRING_FIELD_SIZE];
    char book_name[MAX_STRING_FIELD_SIZE];
    char publisher[MAX_STRING_FIELD_SIZE];
    int page_count;
    literature_t book_type;
    variative_t variative_part;
} book_t;

#endif