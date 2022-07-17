#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// POKEMON DATA
struct pokemon_info
{
	int id;
	char *name;
	char *type_one;
	char *type_two;
	char *first_capacity;
	int count_owned;
	char *first_seen;
	char *first_capture;
};

struct node_pokemon {
	struct node_pokemon* next;
	struct pokemon_info* pokemon;
};

typedef struct node_pokemon head_list_pokemon;
typedef struct node_pokemon node_pokemon;
typedef struct pokemon_info pokemon_info;

// FUNCTIONS LIST

struct pokemon_crud {
  unsigned int index;
  struct pokemon_info pkm_info;
};

// a copy of pokemon_info will be made in the function
pokemon_info* _list_add(head_list_pokemon** list, struct pokemon_crud pkm_crud);
pokemon_info* _list_pop(head_list_pokemon** list, struct pokemon_crud pkm_crud);
pokemon_info* _list_get(head_list_pokemon** list, struct pokemon_crud pkm_crud);
pokemon_info* _list_update(head_list_pokemon** list, struct pokemon_crud pkm_crud);
int list_is_empty(head_list_pokemon* list);
size_t list_length(head_list_pokemon* list);
void list_print(head_list_pokemon* list);
pokemon_info* list_search_by_name(head_list_pokemon* list, char* name);
void list_sort(head_list_pokemon** list); // bubble sort
size_t list_get_index(head_list_pokemon* list, pokemon_info* pokemon);
void list_free(head_list_pokemon* list);

void print_pokemon(pokemon_info pokemon);

#define ADD 0
#define POP 1
#define GET 2
#define UPDATE 3

extern pokemon_info* (*list_functions[4])(head_list_pokemon**, struct pokemon_crud);

#define INIT_LISTS \
        list_functions[ADD] = _list_add; \
        list_functions[POP] = _list_pop; \
        list_functions[GET] = _list_get; \
        list_functions[UPDATE] = _list_update; 

#endif
