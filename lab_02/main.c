#include <stdio.h>
#include "headers/io.h"
#include "headers/func_table.h"

int main()
{
    welcome_print();

    book_t main_table[350];
    book_key_t key_table[350];

    aio_table_t table;
    table.main_table = main_table;
    table.key_table = key_table;
    table.size_of_table = 300;

    parse_table("data/data.txt", &table);
    output_main_table(&table);
    output_key_table(&table);

    add_record(&table);
    output_main_table(&table);
    output_key_table(&table);

    return 0;
}