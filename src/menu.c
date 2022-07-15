#include "list_pokemon.h"
#include "menu.h"


int menu(head_list_pokemon **linked_list){
	printf("========== Welcome to your Pokedex ! ========== \n");
	printf("What do you want to do today ? \n");
	printf("1 - Add a pokemon seen ? \n2 - Add a pokemon captured ? \n3 - Display all pokemon ?\n4 - Display one pokemon ?\n5 - Display pokemon captured ?\n6 - Modify a pokemon ?\n7 - Delete a pokemon ?\n8 - Save the Pokedex ?\n");
	printf("Your choice : \n");
	int index = 0;
	scanf("%d", &index);
	if (index < 1 || index > 8){
		printf("Bad number !");
		return -1;
	}
	index -= 1;
	select_action(index, linked_list);
	return 0;
}

char* get_now_as_str() {
  time_t current_time;
  char* timeString = calloc(8, sizeof (char));

  time(&current_time);
  struct tm* time_info = localtime(&current_time);

  strftime(timeString, 8, "%d/%m/%Y", time_info);
  return timeString;
}

int add_pokemon_seen(head_list_pokemon **linked_list){
	char *name = NULL;
	char *type_one = NULL;
	char *type_two = NULL;	
	char *first_capacity = NULL;
	printf("Well done ! \nWhich pokemon do you want to add ?\n");
	printf("Name : \n");
	scanf("%s", name);
	while(name == NULL){
		printf("Name can not be null\n");
			printf("Name : \n");
			scanf("%s", name);
	}
	printf("First type : \n");
	scanf("%s", type_one);
	while(type_one == NULL){
		printf("First type can not be null\n");
		printf("First type : \n");
		scanf("%s", type_one);
	}	
	printf("Second type (can be empty): \n");
	scanf("%s", type_two);
	printf("Capacity : \n");
	scanf("%s", first_capacity);	
	while(first_capacity == NULL){
		printf("Capacity can not be null\n");
		printf("Capacity : \n");
		scanf("%s", first_capacity);
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
	return 0;
	
}

void select_action(int index, head_list_pokemon **linked_list){
	int(*array_fptr[POINTER_ARRAY_SIZE_MENU])(head_list_pokemon **);
	array_fptr[0] = add_pokemon_seen;
	/*array_fptr[1] = &add_pokemon_captured;
	array_fptr[2] = &display_all_pokemon;
	array_fptr[3] = &display_pokemon_by_name;
	array_fptr[4] = &display_pokemon_captured;
	array_fptr[5] = &modify_pokemon_name_by_name;
	array_fptr[6] = &delete_pokemon;
	array_fptr[7] = &save; */

	array_fptr[index](linked_list);
}
