#include "list_pokemon.h"

pokemon_info* list_add(head_list_pokemon** list, uint8_t id, char* name) {
    if(*list == NULL) {
        *list = malloc(sizeof (node_pokemon));
        (*list)->next = NULL;
        (*list)->pokemon = malloc(sizeof (pokemon_info));
        (*list)->pokemon->id = id;
        (*list)->pokemon->name = name;
        return (*list)->pokemon;
    }
    node_pokemon* res = malloc(sizeof (node_pokemon));
    res->pokemon = malloc(sizeof (pokemon_info));
    res->pokemon->id = id;
    res->pokemon->name = name;
    res->next = NULL;

    node_pokemon* last_el;
    for(last_el = *list; last_el->next != NULL; last_el = last_el->next) { }
    last_el->next = res;
    return res->pokemon;
}

void list_remove(head_list_pokemon** list, size_t index) {
    pokemon_info* pi = list_pop(list, index);
    free(pi->name);
    free(pi);
}

pokemon_info* list_pop(head_list_pokemon** list, size_t index) {
    node_pokemon* curr = *list;
    if(curr == NULL) {
        return NULL;
    }
    if(index == 0) {
        pokemon_info* res = (*list)->pokemon;
        node_pokemon* tmp = *list;
        *list = (*list)->next;
        free(tmp);
        return res;
    }
    for(size_t i = 0; i < index-1; i++) {
        if(curr == NULL) {
            return NULL;
        }
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
    if(tmp == NULL) {
        return NULL;
    }
    for(size_t i = 0; i < index; i++) {
        if(tmp == NULL) {
            return NULL;
        }
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
        printf("(%hhu) %s\n", tmp->pokemon->id, tmp->pokemon->name);
    }
}

// sort
void _list_sort_id(head_list_pokemon** list) {
    (void)list;
}

void _list_sort_name(head_list_pokemon** list) {
    (void)list;
}