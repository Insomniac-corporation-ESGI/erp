#include "menu.h"
#include "list_pokemon.h"
#include "sqlite_functions.h"


void menu(head_list_pokemon **linked_list){
	printf("========== Welcome to your Pokedex ! ========== \n");
	printf("What do you want to do today ? \n");
	while(1) {
		printf("1 - Add a pokemon seen ? \n2 - Add a pokemon captured ? \n3 - Display all pokemon ?\n4 - Display one pokemon ?\n5 - Display pokemon captured ?\n6 - Modify a pokemon's name ?\n7 - Delete a pokemon ?\n8 - Save the Pokedex ?\n98 - Quit without saving\n99 - Save and quit\n");
		printf("Your choice : ");
		int index = 0;
		int flag = scanf("%d", &index);
		if(flag == EOF) {
			continue;
		}
		if(index == 99) { // quit
			ll_to_db(*linked_list);
			break;
		} else if (index == 98) {
			break;
		} else if (index < 1 || index > 8){
			printf("Bad number !\n");
			continue;
		}
		index -= 1;
		printf("\n");
		select_action(index, linked_list);
		printf("\n");
		list_sort(linked_list); // sort after modifications
	}
}


int add_pokemon_seen(head_list_pokemon **linked_list){
	char *name = calloc(21, sizeof (char));
	char *type_one = calloc(21, sizeof (char));
	char *type_two = calloc(21, sizeof (char));	
	char *first_capacity = calloc(21, sizeof (char));
	printf("Well done ! \nWhich pokemon do you want to add ?\n");
	printf("Name : ");
	if(scanf(" %20s", name) == EOF) {
		return 0;
	}
	while(name == NULL){
		printf("Name can not be null\n");
			printf("Name : ");
			if(scanf(" %20s", name) == EOF) {
				free(name);
				free(type_one);
				free(type_two);
				free(first_capacity);
				return 0;
			}
	}
	printf("First type : ");
	if(scanf(" %20s", type_one) == EOF) {
		free(name);
		free(type_one);
		free(type_two);
		free(first_capacity);
		return 0;
	}
	while(type_one == NULL){
		printf("First type can not be null\n");
		printf("First type : ");
		if(scanf(" %20s", type_one) == EOF) {
			free(name);
			free(type_one);
			free(type_two);
			free(first_capacity);
			return 0;
		}
	}
	printf("Second type (can be empty): ");
	if(scanf(" %20s", type_two) == EOF) {
		free(name);
		free(type_one);
		free(type_two);
		free(first_capacity);
		return 0;
	}
	// remove last '\n'
	printf("Capacity : ");
	if(scanf(" %20s", first_capacity) == EOF) {
		free(name);
		free(type_one);
		free(type_two);
		free(first_capacity);
		return 0;
	}
	while(first_capacity == NULL){
		printf("Capacity can not be null\n");
		printf("Capacity : ");
		if(scanf(" %20s", first_capacity) == EOF) {
			free(name);
			free(type_one);
			free(type_two);
			free(first_capacity);
			return 0;
		}
	}
	
	struct pokemon_crud new_poke;
	new_poke.pkm_info.name = name;
	new_poke.pkm_info.type_one = type_one;
	new_poke.pkm_info.type_two = type_two;
	new_poke.pkm_info.first_capacity = first_capacity;
	new_poke.pkm_info.count_owned = 0;
	new_poke.pkm_info.first_seen = get_now_as_str();
	new_poke.pkm_info.first_capture = NULL;
		
	list_functions[ADD](linked_list, new_poke);

	puts("Pokemon added!");
	return 0;
}


int save(head_list_pokemon** list) {
	ll_to_db(*list);
	puts("Pokedex saved!");
	return 0;
}

int display_all_pokemon(head_list_pokemon** list) {
	list_print(*list);
	return 0;
}

int display_pokemon_by_name(head_list_pokemon** list) {
	char *name = calloc(21, sizeof (char));
	pokemon_info* res = NULL;

	do {
		puts("Pokemon owned:");
		for(node_pokemon* tmp = *list; tmp != NULL; tmp = tmp->next) { printf("'%s' ", tmp->pokemon->name); }
		printf("\nName ('quit' to quit): ");
		if(scanf(" %20s", name) == EOF) {
			free(name);
			return 0;
		}
		if(strcmp(name, "quit") == 0) {
			return 0;
		}
	} while ((res = list_search_by_name(*list, name)) == NULL);
	free(name);

	print_pokemon(*res);
	return 0;
}

int modify_pokemon_name_by_name(head_list_pokemon** list) {
	char *name = calloc(21, sizeof (char));
	pokemon_info* res = NULL;

	do {
		puts("Pokemon owned:");
		for(node_pokemon* tmp = *list; tmp != NULL; tmp = tmp->next) { printf("'%s' ", tmp->pokemon->name); }
		printf("\nName ('quit' to quit): ");
		if(scanf(" %20s", name) == EOF) {
			free(name);
			return 0;
		}
		if(strcmp(name, "quit") == 0) {
			free(name);
			return 0;
		}
	} while ((res = list_search_by_name(*list, name)) == NULL);
	free(name);

	char *new_name = calloc(21, sizeof (char));
	printf("New name: ");
	if(scanf(" %20s", new_name) == EOF) {
		free(new_name);
		return 0;
	}

	free(res->name);
	res->name = new_name;

	return 0;
}

int display_pokemon_captured(head_list_pokemon** list) {
	if(list == NULL) {
		puts("<no pokemon>");
	}

	size_t count_owned = 0;
	for(node_pokemon* curr = *list; curr != NULL; curr = curr->next) {
		if(curr->pokemon->count_owned > 0) {
			count_owned++;
			print_pokemon(*(curr->pokemon));
		}
	}

	if(count_owned == 0) {
		puts("<no pokemon>");
	}
	return 0;
}

int add_pokemon_captured(head_list_pokemon** list) {
	char *name = calloc(21, sizeof (char));
	pokemon_info* res = NULL;

	do {
		puts("Pokemon owned:");
		for(node_pokemon* tmp = *list; tmp != NULL; tmp = tmp->next) { printf("'%s' ", tmp->pokemon->name); }
		printf("\nName ('quit' to quit): ");
		if(scanf(" %20s", name) == EOF) {
			free(name);
			return 0;
		}
		if(strcmp(name, "quit") == 0) {
			free(name);
			return 0;
		}
	} while ((res = list_search_by_name(*list, name)) == NULL);
	free(name);

	if(res->first_capture == NULL) {
		res->first_capture = get_now_as_str();
	}
	res->count_owned++;

	return 0;
}

int delete_pokemon(head_list_pokemon** list) {
	char *name = calloc(21, sizeof (char));
	pokemon_info* res = NULL;

	do {
		puts("Pokemon owned:");
		for(node_pokemon* tmp = *list; tmp != NULL; tmp = tmp->next) { printf("'%s' ", tmp->pokemon->name); }
		printf("\nName ('quit' to quit): ");
		if(scanf(" %20s", name) == EOF) {
			free(name);
			return 0;
		}
		if(strcmp(name, "quit") == 0) {
			free(name);
			return 0;
		}
	} while ((res = list_search_by_name(*list, name)) == NULL);
	free(name);

	if(res->count_owned == 0 && res->first_capture == 0) { // forget
		struct pokemon_crud crud = { 0 };
		crud.index = list_get_index(*list, res);
		list_functions[POP](list, crud);
	} else if(res->count_owned == 1) {
		int choice = -1;
		do {
			printf("Release (1) or delete (2): ");
			if(scanf(" %d", &choice) == EOF) {
				return 0;
			}
		} while(choice != 1 && choice != 2);
		switch (choice) {
			case 1:
				res->count_owned = 0;
				free(res->first_capture);
				res->first_capture = NULL;
				break;
			case 2: {
				struct pokemon_crud crud = { 0 };
				crud.index = list_get_index(*list, res);
				list_functions[POP](list, crud);
				break;
			}
		}
	} else if(res->count_owned > 1) {
		int choice = -1;
		do {
			printf("Release one (1), release multiple (2), release all (3), delete (4): ");
			if(scanf(" %d", &choice) == EOF) {
				return 0;
			}
		} while(choice < 1 || choice > 4);
		switch (choice) {
			case 1:
				res->count_owned -= 1;
				break;
			case 2: {
				unsigned int count = -1;
				printf("How many: ");
				if(scanf(" %u", &count) == EOF) {
					return 0;
				}
				if (res->count_owned < 0){
					printf("Error, you cannot erase more pokemons than you have.\n");
				} else {
					res->count_owned -= count;
				}
				break;
			}
			case 3: {
				res->count_owned = 0;
				free(res->first_capture);
				res->first_capture = NULL;
				break;
			}
			case 4: {
				struct pokemon_crud crud = { 0 };
				crud.index = list_get_index(*list, res);
				list_functions[POP](list, crud);
				break;
			}
		}
	}

	return 0;
}

void select_action(int index, head_list_pokemon **linked_list){
	int(*array_fptr[POINTER_ARRAY_SIZE_MENU])(head_list_pokemon **);
	array_fptr[0] = &add_pokemon_seen;
	array_fptr[1] = &add_pokemon_captured;
	array_fptr[2] = &display_all_pokemon;
	array_fptr[3] = &display_pokemon_by_name;
	array_fptr[4] = &display_pokemon_captured;
	array_fptr[5] = &modify_pokemon_name_by_name;
	array_fptr[6] = &delete_pokemon;
	array_fptr[7] = &save;

	array_fptr[index](linked_list);
}
