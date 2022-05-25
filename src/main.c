#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); \
				} while (0)

void cleanupRoutine(int signal_number);


volatile sig_atomic_t shutdown_flag = 1;


int main(void){

	int wstatus;

	pid_t c_pid = fork();
	if(c_pid == -1)
		errExit("forkErr");

	if (c_pid == 0 ){
		printf("printed from a functionnal child process - %d\n", getpid());

		int count = 0;
		struct sigaction sigterm_action;
		memset(&sigterm_action, 0, sizeof(sigterm_action));
		sigterm_action.sa_handler = &cleanupRoutine;
		sigterm_action.sa_flags = 0;

		if (sigfillset(&sigterm_action.sa_mask) != 0)
			errExit("sigfillset");

		if (sigaction(SIGINT, &sigterm_action, NULL) != 0)
			errExit("sigaction");

		while(shutdown_flag){
			getpid();
		}
		printf("pid: %d exited\n", getpid());

		exit(EXIT_SUCCESS);
	} else {

		printf("printed from parent process - %d\n", getpid());

		if(waitpid(c_pid, &wstatus, WUNTRACED ) == -1)
			errExit("waitpid");
	}


	exit(EXIT_SUCCESS);
}

void cleanupRoutine(int sinagl_number){
	shutdown_flag = 0;
}
