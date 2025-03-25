#include <iostream>

using namespace std;

struct Node
{
    int data;
    struct Node *next;
}*first = NULL; // Já criamos um ponteiro global que pode ser referenciado em qlqr lugar

void create(int A[], int n)
{
    int i;
    struct Node *t;     // Ponteiro temporário
    struct Node *last;  // Ponteiro p/ o último nodo, p/ auxiliar na inclusão de nodos no fim
    first = (struct Node *) malloc(sizeof(struct Node)); // Alocamos memória no heap

    first->data = A[0]; // O valor contido no primeiro nodo é igual ao primeiro elemento do array do parâmetro
    first->next = NULL; // Como é o primeiro nodo, não possui next
    last = first;       // O last e o first apontam para o mesmo local, quando temos apenas 1 nodo

    for (i = 1; i < n; i++)
    {
        t = (struct Node *) malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = NULL; // O nodo atual criado não possui nenhum next ainda
        last->next = t; // Atualizamos o next do ponteiro anterior para o novo nodo
        last = t;       // last agora aponta para o novo nodo criado.
    }
}

void display(struct Node *p)
{
    while (p != NULL) // Para quando o ponteiro estiver apontando para NULL
    {
        cout << p->data << " ";
        p = p->next; // O ponteiro p agora recebe o valor do seu next
    }
    cout << endl;
}

void recursiveDisplay(struct Node *p) 
{
    if (p != NULL)
    {
        cout << p->data << " ";
        recursiveDisplay(p->next);
    }
    cout << endl;
}

int count(struct Node *p) 
{
    int length = 0;
    while (p != NULL)
    {
        length++;
        p = p->next;
    }

    return length;
}

/* int sum(struct Node *p)
{
    int sum = 0;
    while (p!= NULL)
    {
        sum += p->data;
        p = p->next;
    }
    
    return sum;
} */

int max(struct Node* p)
{
    int max = INT_MIN;
    while (p != NULL)
    {
        if (p->data > max)
            max = p->data;
        
        p = p->next;
    }

    return max;
}

struct Node * linearSearch(struct Node *p, int key) {
    while (p != NULL)
    {
        if (key == p->data)
            return p; // Retorna o nodo
        p = p->next;
    }
    return NULL;
}

struct Node * linearSearchMoveToFront(struct Node *p, int key) {
    struct Node *q;
    
    while (p != NULL)
    {
        if (key == p->data) { // Quando achar a chave
            q->next = p->next;
            p->next = first;
            first = p;

            return p; // Retorna o nodo
        }

        q = p;
        p = p->next;
    }
    return NULL;
}

void insertAtPos(struct Node *p, int position, int val)
{
    struct Node* temp;
    if (position < 0 || position > count(p))
        return;
    
    temp = (struct Node*) malloc(sizeof(struct Node)); // Cria um novo nodo
    temp->data = val;

    if (position == 0)
    {
        temp->next = first;
        first = temp;
    } else 
    {
        for (int i = 0; i < position - 1; i++) // Itera até a posição desejada
            p = p->next; 
        
        temp->next = p->next;
        p->next = temp;
    }
}

void insertSorted(struct Node *p, int val)
{
    struct Node *temp= (struct Node*) malloc(sizeof(struct Node));
    temp->data = val;
    temp->next = NULL;

    struct Node *q = NULL;

    if (first == NULL) // Caso a lista esteja vazia
        first = temp;
    else 
    {
        while (p != NULL && p->data < val) // Itera enquanto o valor do nodo atual for menor que o val
        {
            q = p;
            p = p->next;
        }

        if (p == first) // Caso o elemento precise ser adicionado antes do first
        {
            temp->next = first;
            first = temp;
        } else
        {
            temp->next = q->next;
            q->next = temp;
        }
    }
}

int deleteAt(struct Node *p, int pos)
{
    struct Node *q;
    int val = -1;

    if (pos < 1 || pos > count(p)) // Posição inválida
        return val;
    
    if (pos == 1)            // Se é o primeiro nodo
    {
        q = first;           // Nodo q aponta para o primeiro nodo
        val = first->data;   // Val pega o valor do nodo a ser deletado
        first = first->next; // Move o ponteiro do first para o nodo seguinte.
        free(q);             // Deleta o antigo primeiro Nodo
        return val;          
    } else
    {
        for(int i = 0; i < pos - 1; i++) // Movimenta p até o nodo a ser deletado, e q para no anterior
        {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        val = p->data;
        free(p);
        return val;
    }
}

int main()
{
    int A[] = {3, 5, 7, 12, 9};
    create(A, 5);
    display(first);

    cout << "A lista tem " << count(first) << " elementos" << endl;
    cout << "O maior elemento na lista é o " << max(first) << endl;

    // LinearSearch
    struct Node *temp; // Crio um nodo temporário para receber o retorno da search
    temp = linearSearch(first, 7);
    if (temp != NULL)
        cout << "Chave encontrada na lista!" << endl;
    else
        cout << "Chave não encontrada na lista..." << endl;
    
    // LinearSearchMoveToFront
    temp = linearSearchMoveToFront(first, 7);
    if (temp != NULL)
        cout << "Chave encontrada na lista!" << endl;
    else
        cout << "Chave não encontrada na lista..." << endl;

    display(first);

    // InsertAtPos (mostraque dá pra criar uma LL só com insertAtPost, mas precisa lembrar dos índices)
    insertAtPos(first, 0, 10);
    display(first);
    insertAtPos(first, 3, 62);
    display(first);

    // insertSorted (shift + alt + a)
    int B[] = {10, 20, 30, 40, 50};
    create(B, 5);
    insertSorted(first, 35);
    insertSorted(first, 5);
    display(first); 

    // DeleteAt
    deleteAt(first, 4);
    display(first);

    return 0;
}