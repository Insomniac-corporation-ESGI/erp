// Coded by KD the 21/06 - Example of linked list
#include "struct.h"
#include "functions.h"

int main(void)
{
	pokemon_t carapuce;
	carapuce.id = 1;
	carapuce.name = "Carapuce";
	carapuce.first_capacity = "Bulle d'eau";
	carapuce.type_one= "Eau";
	carapuce.type_two = "Sol";
	carapuce.count_owned = 5;
	carapuce.first_seen = "07-05-2022";
	carapuce.first_capture = "07-05-2022";
	carapuce.next = NULL;
	
	printf("\n========== Linked_list part ==========\n");
	//printf("Displaying first ID pokemon address and name : \n");
	//printf("%p\n%s\n",&carapuce, carapuce.name);

	pokemon_t *linked_list = &carapuce;
	insert_node_at_end(&linked_list, 2, "Salameche", "Souflle feu", "Feu", "", 2, "07-11-2022", "07-05-2022");
	
	//printf("Displaying second ID pokemon address and name : \n");
	//printf("%p\n%s\n",&carapuce.next, carapuce.next->name);	
	
	printf("Displaying all linked list content : \n");
	display_linked_list(linked_list);

	printf("\n========== Linked list to DB ==========\n");
	create_db();
	ll_to_db(linked_list);
	//retrieve_one_db("Salameche");
	retrieve_all_db();

	printf("\n========== DB to Linked List ==========\n");
	pokemon_t *linked_list_bis = NULL;
	db_to_ll(&linked_list_bis);
	display_linked_list(linked_list_bis);
	return 0;
}

