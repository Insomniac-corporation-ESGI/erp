#ifndef MENU_H
#define MENU_H

#include "list_pokemon.h"

#define POINTER_ARRAY_SIZE_MENU 8

int add_pokemon_seen(head_list_pokemon **linked_list);
void menu(head_list_pokemon **linked_list);
void select_action(int index, head_list_pokemon **linked_list);

#endif
