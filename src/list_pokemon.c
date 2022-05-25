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
    node_pokemon* tmp = malloc(sizeof (node_pokemon));
    (*list)->next = *list;
    (*list)->pokemon = malloc(sizeof(pokemon_info));
    *list = tmp;
    return tmp->pokemon;
}

void list_remove(head_list_pokemon** list, size_t index) {
    node_pokemon* tmp = *list;
    if(tmp == NULL) {
        return ;
    }
    for(size_t i = 0; i < index-1; i++) {
        if(tmp == NULL) {
            return ;
        }
        tmp = tmp->next;
    }
    if(tmp == NULL) {
        return ;
    }

    tmp->next = tmp->next->next;
}

pokemon_info* list_pop(head_list_pokemon** list, size_t index) {
    node_pokemon* tmp = *list;
    if(tmp == NULL) {
        return NULL;
    }
    for(size_t i = 0; i < index-1; i++) {
        if(tmp == NULL) {
            return NULL;
        }
        tmp = tmp->next;
    }
    if(tmp == NULL) {
        return NULL;
    }

    pokemon_info* res = tmp->next->pokemon;
    free(tmp->next);
    tmp->next = tmp->next->next;
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
    for(tmp = list; tmp; tmp = tmp->next) {
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