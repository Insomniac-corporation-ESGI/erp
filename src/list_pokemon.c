#include "list_pokemon.h"
#include <string.h>

// here "name" should be allocated in the heap, as it will be freed if using the list_remove function
pokemon_info* list_add(head_list_pokemon** list, struct pokemon_info pkm_info) {
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

void list_remove(head_list_pokemon** list, size_t index) {
    free(list_pop(list, index)); // pop element and free pokemon_info struct
}

pokemon_info* list_pop(head_list_pokemon** list, size_t index) {
    node_pokemon* curr = *list;
    if(curr == NULL) {
        return NULL;
    }
    if(index == 0) { // special case here because 0-1 would overflow as size_t is unsigned
        pokemon_info* res = (*list)->pokemon;
        node_pokemon* tmp = *list;
        *list = (*list)->next;
        free(tmp);
        return res;
    }
    for(size_t i = 0; i < index-1 && curr != NULL; i++) {
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

pokemon_info* list_get(head_list_pokemon* list, size_t index) {
    node_pokemon* tmp = list;
    for(size_t i = 0; i < index && tmp != NULL; i++) {
        tmp = tmp->next;
    }
    if(tmp == NULL) {
        return NULL;
    }
    return tmp->pokemon;
}

pokemon_info* list_search_by_name(head_list_pokemon* list, char* name) {
    for(node_pokemon* tmp = list; tmp != NULL; tmp = tmp->next) {
        if(strcmp(tmp->pokemon->name, name) == 0) {
            return tmp->pokemon;
        }
    }
    return NULL;
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
    for(tmp = list; tmp; tmp = tmp->next) {
        size++;
    }
    return size;
}

void list_print(head_list_pokemon* list) {
    node_pokemon* tmp = list;
    if(tmp == NULL) {
        puts("<empty>");
    }
    for(tmp = list; tmp != NULL; tmp = tmp->next) {
        printf("%s: type: %d, count owned: %u, first seen: %lu, last seen: %lu\n", tmp->pokemon->name, tmp->pokemon->type, tmp->pokemon->count_owned, tmp->pokemon->first_seen, tmp->pokemon->last_seen);
    }
}