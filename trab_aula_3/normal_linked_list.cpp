#include <climits>
#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *next;
};

class LinkedList {
private:
    Node *head;
public:
    // Class prototype
    LinkedList(){head = NULL;}  // Construtor padrão
    LinkedList(int A[], int size); // Construtor inicializado com array
    ~LinkedList();              // Destrutor

    void display();
    void insertAt(int position, int value);
    int deleteAt(int position);
    int length();
    int min();
    int max();
    int sum();
};

LinkedList::LinkedList(int A[], int size) {
    Node *tail;
    Node *temp;
    this->head = new Node;
    this->head->data = A[0];
    this->head->next = NULL;
    tail = head;

    for (int i = 1; i < size; i++) {
        temp = new Node;
        temp->data = A[i];
        temp->next = NULL;  // O nodo atual criado não possui nenhum next ainda
        tail->next = temp;  // Atualizamos o next do ponteiro anterior para o novo nodo
        tail = temp;        // tail agora aponta para o novo nodo criado.
    }
}

LinkedList::~LinkedList() {
    Node *p = head;
    while (head != NULL) {
        this->head = this->head->next;
        delete p;
        p = this->head;
    }
}

void LinkedList::display() {
    Node *p = this->head;
    while(p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int LinkedList::length() {
    Node *p = this->head;
    int lenght = 0;
    while (p != NULL) {
        lenght++;
        p = p->next;
    }
    return lenght;
}

void LinkedList::insertAt(int position, int value) {
    Node *temp = NULL;
    Node *p = this->head;
    if (position < 0 || position > length()){
        return;
    }
    
    temp = new Node;
    temp->data = value;
    temp->next = NULL;

    if (position == 0) {
        temp->next = this->head;
        head = temp;
    } else {
        // Itera pela nossa lista até a posição anterior a desejada
        for (int i = 0; i < position - 1; i++)
            p = p->next;
    
        temp->next = p->next;
        p->next = temp;
    }
}

int LinkedList::deleteAt(int position) {
    if (position < 1 || position > length()) {
        return -1;
    }

    Node *p = NULL;
    Node *q = NULL;
    int val = -1;

    if (position == 1) {
        p = this->head;
        this->head = this->head->next;
        val = p->data;
        delete p;
    } else {
        p = this->head;
        for (int i = 0; i < position - 1; i++) {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        val = p->data;
        delete p;
    }
    return val;
}

int LinkedList::min() {
    Node *node = this->head;
    if (node->next == NULL) {
        return node->data;
    }

    int min = INT_MAX;
    while(node != NULL) {
        if (node->data < min) {
            min = node->data;
        }
        node = node->next;
    }

    return min;
}

int LinkedList::max() {
    Node *node = this->head;
    if (node->next == NULL) {
        return node->data;
    }

    int max = INT_MIN;
    while(node != NULL) {
        if (node->data > max) {
            max = node->data;
        }
        node = node->next;
    }

    return max;
}

int LinkedList::sum() {
    Node *node = this->head;
    if (node->next == NULL) {
        return node->data;
    }

    int sum = 0;
    while(node != NULL) {
        sum += node->data;
        node = node->next;
    }

    return sum;
}

int main() {

    int A[] = {20, 30, 40, 50, 10};
    LinkedList lista(A, 5);
    
    lista.display();
    cout << "A lista possui: " << lista.length() << " elementos" << endl;

    lista.insertAt(4, 99);
    cout << "Após a inserção, a lista está assim: ";
    lista.display();

    cout << "O elemento de valor " << lista.deleteAt(3) << " foi deletado" << endl;
    lista.display();

    cout << "O elemento de menor valor da lista é: " << lista.min() << endl;
    cout << "O elemento de maior valor da lista é: " << lista.max() << endl;
    cout << "A soma de todos elementos da lista é: " << lista.sum() << endl;

    return 0;
}
