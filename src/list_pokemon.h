#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "stdint.h"
#include "stddef.h"

#define SORT_BY_ID 0
#define SORT_BY_NAME 1

struct pokemon_info {
	uint8_t id;
	char* name;
};

struct node_pokemon {
	struct node_pokemon* next;
	struct pokemon_info* pokemon;
};

typedef struct node_pokemon head_list_pokemon;
typedef struct node_pokemon node_pokemon;
typedef struct pokemon_info pokemon_info;

void list_add(head_list_pokemon** list, uint8_t id, char* name);
void list_remove(head_list_pokemon** list, size_t index);
pokemon_info* list_pop(head_list_pokemon** list, size_t index);
pokemon_info* list_get(head_list_pokemon* list, size_t index);
int list_is_empty(head_list_pokemon* list);
size_t list_length(head_list_pokemon* list);
void list_print(head_list_pokemon* list);

// sort
void _list_sort_id(head_list_pokemon** list);
void _list_sort_name(head_list_pokemon** list);

void (*list_sort[2])(head_list_pokemon**);

#define INIT_LISTS \
			list_sort[SORT_BY_ID] = _list_sort_id; \
			list_sort[SORT_BY_NAME] = _list_sort_name;
#endif