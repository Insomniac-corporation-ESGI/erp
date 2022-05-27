#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

enum pokemon_type {
  NORMAL,
  FIRE,
  WATER,
  ELECTRIC,
  GRASS,
  ICE,
  FIGHTING,
  POISON,
  GROUND,
  FLYING,
  PSYCHIC,
  BUG,
  ROCK,
  GHOST,
  DRAGON,
  DARK,
  STEEL,
  FAIRY
};

struct pokemon_info {
	char* name;
	enum pokemon_type type;
	unsigned int count_owned;
	time_t first_seen;
	time_t last_seen;

};

struct node_pokemon {
	struct node_pokemon* next;
	struct pokemon_info* pokemon;
};

typedef struct node_pokemon head_list_pokemon;
typedef struct node_pokemon node_pokemon;
typedef struct pokemon_info pokemon_info;

// a copy of pokemon_info will be made in the function
pokemon_info* list_add(head_list_pokemon** list, struct pokemon_info pkm_info);

void list_remove(head_list_pokemon** list, size_t index);
pokemon_info* list_pop(head_list_pokemon** list, size_t index);
pokemon_info* list_get(head_list_pokemon* list, size_t index);
pokemon_info* list_search_by_name(head_list_pokemon* list, char* name);
int list_is_empty(head_list_pokemon* list);
size_t list_length(head_list_pokemon* list);
void list_print(head_list_pokemon* list);

#endif