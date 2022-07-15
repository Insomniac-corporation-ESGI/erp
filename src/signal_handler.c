#include "signal_handler.h"

void sigint_handler(int signal){

	uint8_t flagActi; // flag 

	int8_t c; // choice init

	signal(signal, SIG_IGN);
	signal(SIGINT, sigint_handler);

	if (flagActi == 1)
		exit(1);
 	else
		flagActi = 1;
	
	printf("Voulez-vous:\nsauvegarder et quitter ? (x)\nsauvegarder sans quitter ?(q)\nne pas quitter(n)\n>>> ");
	
	c = getchar(); // get char
	getchar(); // flush buffer

	if (c == 'x' || c == 'x'){
		// fonction sauvegarde
		exit(1);
	} else if (c == 'q' || c == 'Q'){
	
	} else {
		raise(SIGINT);
		flagActi = 0;
	}

}

void sigtstp_handler(int signal){

	signal(signal, SIG_IGN);
	signal(SIGTSTP, sigtstp_handler);

	printf("Sauvegarde...\n");

	// fonction sauvegarde
	
	// wait
	
	printf("Sauvegarde faite.\n");
	raise(SIGTSTP);
}

void sigusr1_handler(int signal){
	
	signal(signal, SIG_IGN);
	signal(SIGUSR, sigusr1_handler);

	print("Commande de sauvegarde recue...\nSauvegarde en cours.\n");
	// fonction Sauvegarde
}

void sigusr2_handler(int signal){
	// Traitement usr2
}

