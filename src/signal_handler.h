#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <stdint.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void sigint_handler(int signal);
void sigtstp_handler(int signal);
void sigusr1_handler(int signal);
void sigusr2_handler(int signal);

#endif