#include "signal_handler.h"
#include "sqlite_functions.h"
#include "list_pokemon.h"
#include "utils.h"
#include <unistd.h>

extern head_list_pokemon* list_pokemon;

// When the user hits CTRL^C
// Checks if he done it once, if yes, close no save
// then asks to save exit, if yes, save and exits
void sigint_handler(int sig){

	uint8_t flagActi = 0; // flag 

	int8_t c; // choice init

	signal(sig, SIG_IGN);
	signal(SIGINT, sigint_handler);

	if (flagActi == 1)
		exit(1);
 	else
		flagActi = 1;
	
	printf("Do you want to:\nSave and Exit the program ? (x)\nSave without Exit ?(q)\nDoing Nothing (n)\n>>> ");
	
	c = getchar(); // get char
	getchar(); // flush buffer

	if (c == 'x' || c == 'x'){
	
		printf("Saving...\n");
		ll_to_db(list_pokemon);
		exit(1);
	} else if (c == 'q' || c == 'Q'){
			
	} else {
		raise(SIGINT);
		flagActi = 0;
	}
}

//when the user hits CTRL^Z
// Basically Saves
void sigtstp_handler(int sig){
	(void)sig;

	printf("Saving..\n");
	ll_to_db(list_pokemon);
	
	printf("Save done.\n");
}

// when kill -sigusr1 
// Basically Saves
void sigusr1_handler(int sig){
	(void)sig;	

	printf("Saving command recieved...\nSaving...\n");
	ll_to_db(list_pokemon);
}

//When kill -sigusr2
void sigusr2_handler(int sig){
	(void)sig;

	write(STDOUT_FILENO, "Congrats, you activated an easter egg !", 39);

	struct pokemon_crud crud = { 0 };
	crud.pkm_info.count_owned = 1;
	crud.pkm_info.name = strdup("Mew");
	crud.pkm_info.first_capacity = strdup("Mental schok");
	crud.pkm_info.type_one = strdup("Psy");
	crud.pkm_info.first_seen = get_now_as_str();

	list_functions[ADD](&list_pokemon, crud);
}

