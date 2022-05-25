#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list_pokemon.h"

int main(int argc, char** argv) {
	INIT_LISTS
	(void) argc;
	(void) argv;

	head_list_pokemon* list = NULL;
	list_add(&list, 1, "bulbizarre");
	list_add(&list, 15, "dardagnan");
	list_add(&list, 23, "abo");
	list_add(&list, 24, "arbok");
	list_add(&list, 25, "pikachu");
	for(int i = 0; !list_is_empty(list); i++) {
		printf("size: %lu\n", list_length(list));
		printf("is empty: %hhu\n", list_is_empty(list));
		printf("(element 1)->name: %s\n", list_get(list, 0)->name);
		printf("popping: %s\n", list_pop(&list, 0)->name);
		list_print(list);
	}
	printf("size: %lu\n", list_length(list));
	printf("is empty: %hhu\n", list_is_empty(list));
	list_print(list);
    return 0;
}
