#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list_pokemon.h"
#include "signal_handler.h"
#include "sqlite_functions.h"
#include "menu.h"

head_list_pokemon* list_pokemon = NULL;

int main(int argc, char** argv) {
	(void) argc;
	(void) argv;
	INIT_LISTS;

//	Signal handling statring
	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sigtstp_handler);
	signal(SIGUSR1, sigusr1_handler);
	signal(SIGUSR2, sigusr2_handler);

	check_if_db_exists();
	db_to_ll(&list_pokemon);
	list_sort(&list_pokemon);

	menu(&list_pokemon);

    return 0;
}
