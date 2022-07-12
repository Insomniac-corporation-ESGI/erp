#include <sqlite3.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int insert_node_at_end(pokemon_t **linked_list, int id, char *name, char *first_capacity, char *type_one, char *type_two, int count_owned, char *first_seen, char *first_capture){
        pokemon_t *new_pokemon = malloc(sizeof(*new_pokemon));
        new_pokemon->id = id;
        new_pokemon->name = name;
        new_pokemon->first_capacity = first_capacity;
        new_pokemon->type_one = type_one;
	new_pokemon->type_two = type_two;
        new_pokemon->count_owned = count_owned;
        new_pokemon->first_seen = first_seen;
        new_pokemon->first_capture = first_capture;
        new_pokemon->next = NULL;

	if(*linked_list == NULL){
		*linked_list = new_pokemon; 
		return 1;
	}

        pokemon_t *tmp = *linked_list;

        while (tmp != NULL)
        {
                if (tmp->next == NULL)
                {
                        tmp->next = new_pokemon;
                        return 0;
                }
                tmp = tmp->next;
        }
        return 0;
}

int display_linked_list(pokemon_t* linked_list){
        pokemon_t *tmp = linked_list;
        while(tmp != NULL)
        {
		printf("%s\n",tmp->name);
                //printf("ID : %d\nName: %s\nCapacity : %s\nType one : %s\nType two : %s\nNext : %p\nCapture : %d\nFirst seen : %s\nFirst capture : %s\n", tmp->id, tmp->name, tmp->first_capacity, tmp->type_one, tmp->type_two,  tmp->next, tmp->count_owned, tmp->first_seen, tmp->first_capture);
                tmp = tmp->next;
        }
        return 0;
}

int create_db(void){
	sqlite3 *db;
	char *err_msg = 0;
	int rc = sqlite3_open("pokemon.db", &db);
	
	if(rc != SQLITE_OK){
		fprintf(stderr, "Cannot open database : %s \n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	char *sql = "DROP TABLE IF EXISTS POKEMON;"
		    "CREATE TABLE POKEMON(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, type_one TEXT NOT NULL, type_two TEXT, first_capacity TEXT NOT NULL, count_owned INT, first_seen DATETIME, first_capture DATETIME);";
	 
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);	

	if(rc != SQLITE_OK){
		fprintf(stderr, "SQL error : %s \n", err_msg);
		sqlite3_free(err_msg);
		sqlite3_close(db);
		return 1;
	}

	sqlite3_close(db);
	printf("Table created \n");

	return 0;
}

int retrieve_one_db(char *name){
	sqlite3 *db;
	sqlite3_stmt *res;
	int rc = sqlite3_open("pokemon.db", &db);
	size_t poke_length = strlen(name);
	int number_of_columns = 8;
	int counter = 0;
	
	if(rc != SQLITE_OK){
		fprintf(stderr, "Cannot open database : %s \n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	
	char *sql = "SELECT id, name, type_one, type_two, first_capacity, count_owned, first_seen, first_capture FROM POKEMON WHERE name = ?";
	 
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
	if(rc == SQLITE_OK){
		sqlite3_bind_text(res, 1, name, poke_length, SQLITE_STATIC);
	} else {
		fprintf(stderr, "Failed to execute statement : %s\n", sqlite3_errmsg(db));
	}
	
	int step = sqlite3_step(res);

	if(step == SQLITE_ROW){
		for(counter = 0; counter < number_of_columns; counter++){
			printf("| %s ", sqlite3_column_text(res, counter));
		}
	}

	sqlite3_finalize(res);
	sqlite3_close(db);

	return 0;
	
}

// Function to display all our DB datas. Argc is the number of cols, **argv is the number of row's data, and **col_name the columns name - not_used is required for using the callback function
int callback(void *not_used, int argc, char **argv, char **col_name){
	fprintf(stderr, "%p", not_used);
	for(int i = 0; i < argc; i++){
		printf("%s = %s \n", col_name[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int retrieve_all_db(void){
	sqlite3 *db;
	char *err_msg = 0;
	int rc = sqlite3_open("pokemon.db", &db);
	
	if(rc != SQLITE_OK){
		fprintf(stderr, "Cannot open database : %s \n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	
	char *sql = "SELECT id, name, type_one, type_two, first_capacity, count_owned, first_seen, first_capture FROM POKEMON";
	 
	rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
	if(rc != SQLITE_OK){
		fprintf(stderr, "Failed to execute statement : %s\n", sqlite3_errmsg(db));
		sqlite3_free(err_msg);
		return 1;
	}
	
	sqlite3_close(db);

	return 0;
	
}
int ll_to_db(pokemon_t* linked_list){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;
	int rc = sqlite3_open("pokemon.db", &db);

	if(rc != SQLITE_OK){
		fprintf(stderr, "Cannot open database : %s \n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	} else {
		printf("Database opened \n");
	}
	
	pokemon_t *tmp = linked_list;

	while(tmp != NULL)
	{
		const char *sql = "INSERT INTO POKEMON VALUES(?,?,?,?,?,?,?,?);";
	 	
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_null(res, 1);
			char *name= tmp->name;
			int name_length = strlen(name);
			sqlite3_bind_text(res, 2, name, name_length, SQLITE_STATIC);
			char *type_one = tmp->type_one;
			int type_one_length = strlen(type_one);
			sqlite3_bind_text(res, 3, type_one, type_one_length, SQLITE_STATIC);
			char *type_two = tmp->type_two;
			int type_two_length = strlen(type_two);
			sqlite3_bind_text(res, 4, type_two, type_two_length, SQLITE_STATIC);
			char *first_capacity = tmp->first_capacity;
			int first_capacity_length = strlen(first_capacity);
			sqlite3_bind_text(res, 5, first_capacity, first_capacity_length, SQLITE_STATIC);
			int count_owned = tmp->count_owned;
			sqlite3_bind_int(res, 6, count_owned);
			char *first_seen = tmp->first_seen;
			int first_seen_length = strlen(first_seen);
			sqlite3_bind_text(res, 7, first_seen, first_seen_length, SQLITE_STATIC);
			char *first_capture = tmp->first_capture;
			int first_capture_length = strlen(first_capture);
			sqlite3_bind_text(res, 8, first_capture, first_capture_length, SQLITE_STATIC);
		} else {
			fprintf(stderr, "Failed to execute statement : %s\n", sqlite3_errmsg(db));
		}
		rc = sqlite3_step(res);
		if(rc != SQLITE_DONE){
			fprintf(stderr, "Execution failed : %s \n", err_msg);
			sqlite3_finalize(res);
			return 1;
		}
		sqlite3_finalize(res);
		tmp = tmp->next;
	}
	sqlite3_close(db);
	return 0;
}	

int callback_to_ll(void *linked_list, int argc, char **argv, char **col_name){
	
	for(int i = 0; i < argc; i++){
		insert_node_at_end((pokemon_t **)linked_list, *argv[0], argv[1], argv[2], argv[3], argv[4], *argv[5], argv[6], argv[8]);
	}
	
	printf("Row %s done \n", col_name[0]);
	printf("Row %s done \n", argv[1]);
	display_linked_list(linked_list);
	(void)col_name;
	return 0;	
}

int db_to_ll(pokemon_t **linked_list){
	
	sqlite3 *db;
	char *err_msg = 0;
	int rc = sqlite3_open("pokemon.db", &db);

	if(rc != SQLITE_OK){
		fprintf(stderr, "Cannot open database : %s \n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	} else {
		printf("Database opened \n");
	}

	char *sql = "SELECT id, name, type_one, type_two, first_capacity, count_owned, first_seen, first_capture FROM POKEMON";
	
	rc = sqlite3_exec(db, sql, callback_to_ll, (void *)linked_list, &err_msg);
	if(rc != SQLITE_OK){
		fprintf(stderr, "Failed to execute statement : %s\n", sqlite3_errmsg(db));
		sqlite3_free(err_msg);
		return 1;
	}
	
	sqlite3_close(db);

	return 0;
}
