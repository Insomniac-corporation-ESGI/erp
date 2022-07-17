#include <stdint.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sigint_handler(int signal);
void sigtstp_handler(int signal);
void sigusr1_handler(int signal);
void sigusr2_handler(int signal);

