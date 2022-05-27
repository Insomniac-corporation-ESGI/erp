#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list_pokemon.h"

int main(int argc, char** argv) {
	(void) argc;
	(void) argv;

	head_list_pokemon* list = NULL;
	list_add(&list, (struct pokemon_info){
		.name = "Bulbizarre",
		.type = GRASS,
		.count_owned = 15,
		.first_seen = time(NULL),
		.last_seen = time(NULL),
	});
	list_add(&list, (struct pokemon_info){
		.name = "Dardagnan",
		.count_owned = 5,
		.type = FLYING,
		.first_seen = time(NULL),
		.last_seen = time(NULL),
	});
	list_add(&list, (struct pokemon_info){
		.name = "Abo",
		.count_owned = 0,
		.type = GRASS,
		.first_seen = time(NULL),
		.last_seen = time(NULL),
	});
	printf("Searching for 'bulbizzare' : %p\n", (void*)list_search_by_name(list, "Bulbizarre"));
	printf("Searching for 'not found' : %p\n", (void*)list_search_by_name(list, "not found"));
	for(int i = 0; !list_is_empty(list); i++) {
		printf("size: %lu\n", list_length(list));
		printf("is empty: %hhu\n", list_is_empty(list));
		printf("(element 0)->name: %s\n",  list_get(list, 0)->name);
		printf("popping: %s\n", list_pop(&list, 0)->name);
		list_print(list);
	}
	printf("size: %lu\n", list_length(list));
	printf("is empty: %hhu\n", list_is_empty(list));
	list_print(list);

    return 0;
}
