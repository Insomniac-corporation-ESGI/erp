#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include <stddef.h>

typedef struct pokemon
{
	int id;
       	char *name;
	char *type_one;
	char *type_two;
	char *first_capacity;
	int count_owned;
	char *first_seen;
	char *first_capture;
	struct pokemon *next;	
} pokemon_t;

#endif /* __LINKED_LIST__ */
