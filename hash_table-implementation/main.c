#include <stdlib.h>
#include <stdio.h>

#define TABLE_SIZE 8

typedef struct {
    int matricula;
    char nome[30];
    float n1, n2, n3;
} Aluno;

typedef struct {
    int quantity;
    int table_size;
    Aluno **items;
} Hash;

Hash *criaHash(int table_size) {
    Hash *t = (Hash*) malloc(sizeof(Hash));

    if (!t) {
        return NULL;
    }

    t->table_size = table_size;
    t->quantity = 0;
    t->items = (Aluno**) malloc(table_size * sizeof(Aluno*));
    if (!t->items) {
        free(t);
        return NULL;
    }

    for(int i = 0; i < table_size; i++) {
        t->items[i] = NULL;
    }

    return t;
}

void destroyHash(Hash *t) {
    if (!t) {
        return;
    }

    for(int i = 0; i < t->table_size; i++) {
        if (!t->items[i]) {
            continue;
        }
        free(t->items[i]);
    }
    free(t->items);

    free(t);
}

int main(void) {

    Hash *t = criaHash(TABLE_SIZE);

    destroyHash(t);

    return 0;
}
