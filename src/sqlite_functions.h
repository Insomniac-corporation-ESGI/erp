#ifndef SQLITE_FUNCTION_H
#define SQLITE_FUNCTION_H
#include <sqlite3.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "list_pokemon.h"
int create_db(void);
int retrieve_one_db(char *name);
int callback(void *not_used, int argc, char **argv, char **col_name);
int retrieve_all_db(void);
int ll_to_db(head_list_pokemon* linked_list);
int db_to_ll(head_list_pokemon **linked_list);
#endif
