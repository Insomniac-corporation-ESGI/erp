#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list_pokemon.h"
#include "signal_handler.h"


int main(int argc, char** argv) {
	(void) argc;
	(void) argv;
	INIT_LISTS;

	struct pokemon_crud pkm_crud;

	pkm_crud.pkm_info = (struct pokemon_info){
		.name = "Bulbizarre",
		.type = GRASS,
		.count_owned = 15,
		.first_seen = time(NULL),
		.last_seen = time(NULL),
	};

	head_list_pokemon* list = NULL;
	list_functions[ADD](&list, pkm_crud);

	pkm_crud.pkm_info = (struct pokemon_info){
		.name = "Dardagnan",
		.count_owned = 5,
		.type = FLYING,
		.first_seen = time(NULL),
		.last_seen = time(NULL),
	};
	list_functions[ADD](&list, pkm_crud);

	pkm_crud.pkm_info = (struct pokemon_info){
		.name = "Abo",
		.count_owned = 0,
		.type = GRASS,
		.first_seen = time(NULL),
		.last_seen = time(NULL),
	};
	list_functions[ADD](&list, pkm_crud);

	printf("Searching for 'bulbizzare' : %p\n", (void*)list_search_by_name(list, "Bulbizarre"));
	printf("Searching for 'not found' : %p\n", (void*)list_search_by_name(list, "not found"));

	list_print(list);
	pkm_crud.index = 0;
	printf("(element 0)->name: %s\n", list_functions[GET](&list, pkm_crud)->name);
	list_functions[UPDATE](&list, pkm_crud);

	for(int i = 0; !list_is_empty(list); i++) {
		printf("size: %lu\n", list_length(list));
		printf("is empty: %i\n", list_is_empty(list));

		pkm_crud.index = 0;
		pkm_crud.pkm_info = (struct pokemon_info) { 0 };

		printf("(element 0)->name: %s\n", list_functions[GET](&list, pkm_crud)->name);
		printf("popping: %s\n", list_functions[POP](&list, pkm_crud)->name);
		list_print(list);
	}
	printf("size: %lu\n", list_length(list));
	printf("is empty: %i\n", list_is_empty(list));
	list_print(list);

    return 0;
}
