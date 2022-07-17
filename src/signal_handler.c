#include "signal_handler.h"
#include "sqlite_functions.h"
#include "list_pokemon.h"

// When the user hits CTRL^C
// Checks if he done it once, if yes, close no save
// then asks to save exit, if yes, save and exits
void sigint_handler(int signal){

	uint8_t flagActi; // flag 

	int8_t c; // choice init

	signal(signal, SIG_IGN);
	signal(SIGINT, sigint_handler);

	if (flagActi == 1)
		exit(1);
 	else
		flagActi = 1;
	
	printf("Do you want to:\nSave and Exit the program ? (x)\nSave without Exit ?(q)\nDoing Nothing (n)\n>>> ");
	
	c = getchar(); // get char
	getchar(); // flush buffer

	if (c == 'x' || c == 'x'){
	
		ll_to_db(/*linked list pointer*/);
		exit(1);
	} else if (c == 'q' || c == 'Q'){
			
	} else {
		raise(SIGINT);
		flagActi = 0;
	}

}

//when the user hits CTRL^Z
// Basically Saves
void sigtstp_handler(int signal){

	signal(signal, SIG_IGN);
	signal(SIGTSTP, sigtstp_handler);

	printf("Saving..\n");

	ll_to_db(/*linked list pointer */);
	
	printf("Save done.\n");
	raise(SIGTSTP);
}
// when kill -sigusr1 
// Basically Saves
void sigusr1_handler(int signal){
	
	signal(signal, SIG_IGN);
	signal(SIGUSR1, sigusr1_handler);

	print("Saving command recieved...\nSaving...\n");
	
	ll_to_db(/*linked list pointer*/);
	raise(SIGUSR1);
}

//When kill -sigusr2
// Basically do nothing
void sigusr2_handler(int signal){
	// Traitement usr2
	signal(signal, SIG_IGN);
	signal(SIGUSR1, sigusr2_handler);
	
	printf("Congrats, you activated an easter egg");

	raise(SIGUSR2);
}

