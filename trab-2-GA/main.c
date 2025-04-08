#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int TABLE_SIZE = 8;

typedef struct {
    int matricula;
    char nome[30];
    float n1, n2, n3;
}Aluno;

typedef struct hashNode {
    Aluno data;
    struct hashNode *next;
} HashNode;

typedef struct hash {
    int TABLE_SIZE;
    int qtd;
    HashNode **itens;
} Hash;

Hash *createHash() {
    Hash* ha = (Hash *) malloc(sizeof(Hash));
    if (!ha) {
        return NULL;
    }
    ha->TABLE_SIZE = TABLE_SIZE;
    ha->itens = (HashNode **) malloc(TABLE_SIZE * sizeof(HashNode *));

    if (ha->itens == NULL) {
        free(ha);
        return NULL;
    }

    ha->qtd = 0;
    for (int i = 0; i < ha->TABLE_SIZE; i++) {
        ha->itens[i] = NULL;
    }

    return ha;
}

void deleteNode(HashNode *n) {
    if (!n) {
        return;
    }
    deleteNode(n->next);
    free(n);
}

void deleteHash(Hash *ha) {
    if (ha == NULL) return;

    for (int i = 0; i < ha->TABLE_SIZE; i++) {
        deleteNode(ha->itens[i]);
    }

    free(ha->itens);
    free(ha);
}

int divisionMethod(int chave) {
    return chave % TABLE_SIZE;
}

int insertIntoTable(Hash *h, Aluno item) {
    int hash = divisionMethod(item.matricula);
    HashNode *newNode = (HashNode*)malloc(sizeof(HashNode));
    if (!newNode) {
        deleteHash(h);
        return -1;
    }

    newNode->data = item;
    newNode->next = h->itens[hash] ? h->itens[hash] : NULL;
    h->itens[hash] = newNode;
    return 0;
}

Hash *createHashFull(Aluno *items, int size) {
    Hash* h = (Hash *) malloc(sizeof(Hash));
    if (!h) {
        return NULL;
    }
    h->TABLE_SIZE = TABLE_SIZE;
    h->itens = (HashNode **) malloc(TABLE_SIZE * sizeof(HashNode *));
    for(int i = 0; i < TABLE_SIZE; i++) {
        h->itens[i] = NULL;
    }
    
    for(int i = 0; i < size; i++) {
        if (insertIntoTable(h, items[i]) != 0) {
            deleteHash(h);
            return NULL;
        }
    }

    return h;
}

void insertMultiple_SeparateChaining(Hash *h, Aluno *items, int size) {
    for(int i = 0; i < size; i++) {
        if (insertIntoTable(h, items[i]) != 0) {
            return;
        }
    } 
}

// Insere um aluno
int insert_SeparateChaining(Hash *ha, Aluno al) {
    if (ha == NULL) return 0;

    int pos = divisionMethod(al.matricula);

    // Cria um novo nodo para o alunot
    HashNode *newNode = (HashNode *) malloc(sizeof(HashNode));
    if (newNode == NULL) return 0;

    newNode->data = al;
    newNode->next = ha->itens[pos];  // Insere no início da lista encadeada
    ha->itens[pos] = newNode;
    ha->qtd++;

    return 1;
}

// Função para procurar por um aluno a partir de sua matrícula
int search_SeparateChaining(Hash *ha, int mat, Aluno *al) {
    if (ha == NULL) return 0;

    int pos = divisionMethod(mat);
    HashNode *current = ha->itens[pos];

    // Percorre a lista encadeada do índice específico
    while (current != NULL) {
        if (current->data.matricula == mat) {
            *al = current->data;
            return 1;
        }
        current = current->next;
    }

    return 0;
}

// Imprime nossa HashTable
void printHash(Hash *ha) {
    printf("HASH TABLE:\n");
    if (ha == NULL) return;

    for (int i = 0; i < ha->TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        HashNode *current = ha->itens[i];
        while (current != NULL) {
            printf("-> [%d, %s] ", current->data.matricula, current->data.nome);
            current = current->next;
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    //Hash* h = createHash();

    // Cria um aluno e o insere
    //Aluno aluno1 = {};
    //insert_SeparateChaining(h, aluno1);

    //printf("Imprimindo o HashTable depois da primeira insercao...");
    //printHash(h);

    //// Cria um aluno e o insere forçando uma colisão no índice 3
    //Aluno aluno2 = {11, "Humberto", 3, 2, 1};
    //insert_SeparateChaining(h, aluno2);
    Aluno alunos[2] = {
        {123, "Dio", 10, 9, 8},
        {11, "Humberto", 3, 2, 1}
    };

    Hash *h = createHashFull(alunos, 2);
    printf("\nImprimindo o HashTable depois da segunda insercao...");
    printHash(h);

    Aluno new_alunos[3] = {
        {153, "Marcelo", 10, 9, 8},
        {18, "Marcio", 3, 2, 1},
        {1900, "Kleber", 7, 6, 2}
    };
    insertMultiple_SeparateChaining(h, new_alunos, 3);
    printHash(h);

    Aluno resultado;
    // Verifica a existência de um aluno com matrícula 123
    if (search_SeparateChaining(h, 123, &resultado))
        printf("\nEncontrado: %s, Notas: %.1f, %.1f, %.1f\n", resultado.nome, resultado.n1, resultado.n2, resultado.n3);
    else
        printf("\nAluno nao encontrado....\n");

    // Verifica a existência de um aluno com matrícula 11
    if (search_SeparateChaining(h, 11, &resultado))
        printf("Encontrado: %s, Notas: %.1f, %.1f, %.1f\n", resultado.nome, resultado.n1, resultado.n2, resultado.n3);
    else
        printf("Student not found.\n");

    // Procura por matrícula inexistente
    if (search_SeparateChaining(h, 40, &resultado))
        printf("Encontrado: %s, Notas: %.1f, %.1f, %.1f\n", resultado.nome, resultado.n1, resultado.n2, resultado.n3);
    else
        printf("Aluno nao encontrado....\n");

    // Libera a memória
    deleteHash(h);

    return 0;
}
