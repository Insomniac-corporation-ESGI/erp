#include <stdint.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define POINTER_ARRAY_SIZE_SIGHANDLER 4


void sigint_handler(int signal);
void sigtstp_hanlder(int signal);
void sigusr1_handler(int signal);
void sigusr2_handler(int signal);

