#include "menu.h"
#include "list_pokemon.h"
#include "sqlite_functions.h"


void menu(head_list_pokemon **linked_list){
	printf("========== Welcome to your Pokedex ! ========== \n");
	printf("What do you want to do today ? \n");
	while(1) {
		printf("1 - Add a pokemon seen ? \n2 - Add a pokemon captured ? \n3 - Display all pokemon ?\n4 - Display one pokemon ?\n5 - Display pokemon captured ?\n6 - Modify a pokemon's name ?\n7 - Delete a pokemon ?\n8 - Save the Pokedex ?\n");
		printf("Your choice : \n");
		int index = 0;
		scanf("%d", &index);
		if (index < 1 || index > 8){
			printf("Bad number !\n");
			continue;
		}
		index -= 1;
		select_action(index, linked_list);
	}
}

char* get_now_as_str() {
  time_t current_time;
  char* timeString = calloc(11, sizeof (char));

  time(&current_time);
  struct tm* time_info = localtime(&current_time);

  strftime(timeString, 11, "%d/%m/%Y", time_info);
  return timeString;
}

int add_pokemon_seen(head_list_pokemon **linked_list){
	char *name = calloc(21, sizeof (char));
	char *type_one = calloc(21, sizeof (char));
	char *type_two = calloc(21, sizeof (char));	
	char *first_capacity = calloc(21, sizeof (char));
	printf("Well done ! \nWhich pokemon do you want to add ?\n");
	printf("Name : ");
	scanf(" %20s", name);
	while(name == NULL){
		printf("Name can not be null\n");
			printf("Name : ");
			scanf(" %20s", name);
	}
	printf("First type : ");
	scanf(" %20s", type_one);
	while(type_one == NULL){
		printf("First type can not be null\n");
		printf("First type : ");
		scanf(" %20s", type_one);
	}	
	printf("Second type (can be empty): ");
	scanf(" %20s", type_two);
	printf("Capacity : ");
	scanf(" %20s", first_capacity);	
	while(first_capacity == NULL){
		printf("Capacity can not be null\n");
		printf("Capacity : ");
		scanf(" %20s", first_capacity);
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
	puts("List saved!");
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
		printf("Name ('quit' to quit): ");
		scanf(" %20s", name);
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
		printf("Name ('quit' to quit): ");
		scanf(" %20s", name);
		if(strcmp(name, "quit") == 0) {
			return 0;
		}
	} while ((res = list_search_by_name(*list, name)) == NULL);
	free(name);

	char *new_name = calloc(21, sizeof (char));
	printf("New name: ");
	scanf(" %20s", new_name);

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
		printf("Name ('quit' to quit): ");
		scanf(" %20s", name);
		if(strcmp(name, "quit") == 0) {
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
		printf("Name ('quit' to quit): ");
		scanf(" %20s", name);
		if(strcmp(name, "quit") == 0) {
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
			scanf(" %d", &choice);
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
			scanf(" %d", &choice);
		} while(choice < 1 || choice > 4);
		switch (choice) {
			case 1:
				res->count_owned -= 1;
				break;
			case 2: {
				unsigned int count = -1;
				printf("How many: ");
				scanf(" %u", &count);
				// TODO: check if count_owned is not negative
				res->count_owned -= count;
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
