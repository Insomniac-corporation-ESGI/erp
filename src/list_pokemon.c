#include "list_pokemon.h"
#include <string.h>

pokemon_info* (*list_functions[3])(head_list_pokemon**, struct pokemon_crud) = { 0 };

// here "pkm_crud->pkm_info->name" should be allocated in the heap, as it will be freed if using the list_remove function
pokemon_info* _list_add(head_list_pokemon** list, struct pokemon_crud pkm_crud) {
    struct pokemon_info pkm_info = pkm_crud.pkm_info;
    if(*list == NULL) {
        *list = malloc(sizeof (node_pokemon));
        (*list)->next = NULL;
        (*list)->pokemon = malloc(sizeof (pokemon_info));
        memcpy((*list)->pokemon, &pkm_info, sizeof (pokemon_info));
        return (*list)->pokemon;
    }
    node_pokemon* res = malloc(sizeof (node_pokemon));
    res->pokemon = malloc(sizeof (pokemon_info));
    memcpy(res->pokemon, &pkm_info, sizeof (pokemon_info));
    res->next = NULL;

    node_pokemon* last_el;
    for(last_el = *list; last_el->next != NULL; last_el = last_el->next) { }
    last_el->next = res;
    return res->pokemon;
}

pokemon_info* _list_pop(head_list_pokemon** list, struct pokemon_crud pkm_crud) {
    node_pokemon* curr = *list;
    if(curr == NULL) {
        return NULL;
    }
    if(pkm_crud.index == 0) { // special case here because 0-1 would overflow as size_t is unsigned
        pokemon_info* res = (*list)->pokemon;
        node_pokemon* tmp = *list;
        *list = (*list)->next;
        free(tmp);
        return res;
    }
    for(size_t i = 0; i < pkm_crud.index-1 && curr != NULL; i++) {
        curr = curr->next;
    }
    if(curr == NULL) {
        return NULL;
    }

    pokemon_info* res = curr->next->pokemon;
    node_pokemon* tmp = curr->next;
    curr->next = curr->next->next;
    free(tmp);
    return res;
}

pokemon_info* _list_update(head_list_pokemon** list, struct pokemon_crud pkm_crud) {
    node_pokemon* tmp = *list;
    for(size_t i = 0; i < pkm_crud.index && tmp != NULL; i++) {
        tmp = tmp->next;
    }
    if(tmp == NULL) {
        return NULL;
    }

    memcpy(tmp->pokemon, &pkm_crud.pkm_info, sizeof (struct pokemon_info));
    return tmp->pokemon;
}

pokemon_info* _list_get(head_list_pokemon** list, struct pokemon_crud pkm_crud) {
    node_pokemon* tmp = *list;
    for(size_t i = 0; i < pkm_crud.index && tmp != NULL; i++) {
        tmp = tmp->next;
    }
    if(tmp == NULL) {
        return NULL;
    }
    return tmp->pokemon;
}

int list_is_empty(head_list_pokemon* list) {
    return list == NULL;
}

size_t list_length(head_list_pokemon* list) {
    node_pokemon* tmp = list;
    if(tmp == NULL) {
        return 0;
    }
    size_t size = 0;
    for(tmp = list; tmp != NULL; tmp = tmp->next) {
        size++;
    }
    return size;
}

void list_print(head_list_pokemon* list) {
    node_pokemon* tmp = list;
    if(tmp == NULL) {
        puts("<empty>");
    }
    unsigned int index = 0;
    for(tmp = list; tmp != NULL; tmp = tmp->next) {
    	struct pokemon_info *val = tmp->pokemon;
        printf("ID : %d\nName: %s\nCapacity : %s\nType one : %s\nType two :%s\nCapture : %d\nFirst seen : %s\nFirst capture : %s\n", val->id, val->name, val->first_capacity, val->type_one, val->type_two, val->count_owned, val->first_seen, val->first_capture);
        index++;
    }
}

pokemon_info* list_search_by_name(head_list_pokemon* list, char* name) {
    for(node_pokemon* tmp = list; tmp != NULL; tmp = tmp->next) {
        if(strcmp(tmp->pokemon->name, name) == 0) {
            return tmp->pokemon;
        }
    }
    return NULL;
}

// bubble sort
void swap(node_pokemon* a, node_pokemon* b) {
    struct pokemon_info* tmp = a->pokemon;
    a->pokemon = b->pokemon;
    b->pokemon = tmp;
}
void list_sort(head_list_pokemon** list) {
    if(*list == NULL) {
        return ;
    }

    int swapped;
    node_pokemon* curr = NULL;
    node_pokemon* last_sorted = NULL;
  
    do { 
        swapped = 0; 
        curr = *list; 
  
        while (curr->next != last_sorted) { 
            // if current pokemon's name is greater than the next one, swap them
            if (strcmp(curr->pokemon->name, curr->next->pokemon->name) > 0) {
                swap(curr, curr->next); 
                swapped = 1; 
            } 
            curr = curr->next; 
        } 
        last_sorted = curr; 
    } while (swapped); 
}