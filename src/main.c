#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list_pokemon.h"
#include "signal_handler.h"
#include "sqlite_functions.h"
#include "menu.h"


int main(int argc, char** argv) {
	(void) argc;
	(void) argv;
	INIT_LISTS;

	head_list_pokemon* list_pokemon = NULL;

	create_db();
	db_to_ll(&list_pokemon);

	menu(&list_pokemon);

    return 0;
}
