#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list_pokemon.h"
#include "sqlite_functions.h"
#include "menu.h"


int main(int argc, char** argv) {
	(void) argc;
	(void) argv;
	INIT_LISTS;

	create_db();

	struct pokemon_crud pkm_crud;

	pkm_crud.pkm_info = (struct pokemon_info){
		.name = "Bulbizarre",
		.type_one = "some_type",
		.type_two = "some_other_type",
		.first_capacity = "some_capacity",
		.first_seen = "yesterday",
		.first_capture = "today",
		.count_owned = 15,
	};

	head_list_pokemon* list = NULL;
	list_functions[ADD](&list, pkm_crud);

	pkm_crud.pkm_info = (struct pokemon_info){
		.name = "Dardagnan",
		.type_one = "some_type",
		.type_two = "some_other_type",
		.first_capacity = "some_capacity",
		.first_seen = "yesterday",
		.first_capture = "today",
		.count_owned = 5,
	};
	list_functions[ADD](&list, pkm_crud);

	pkm_crud.pkm_info = (struct pokemon_info){
		.name = "Abo",
		.type_one = "some_type",
		.type_two = "some_other_type",
		.first_capacity = "some_capacity",
		.first_seen = "yesterday",
		.first_capture = "today",
		.count_owned = 0,
	};
	list_functions[ADD](&list, pkm_crud);

	ll_to_db(list);

	list = NULL;
	db_to_ll(&list);

	list_print(list);
	list_sort(&list);
	list_print(list);
	menu(&list);

    return 0;
}
