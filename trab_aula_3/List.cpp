#include "List.h"
#include <iostream>
#include <ostream>

using namespace std;

Node::Node(){}

Node::~Node() {
    delete this->next;
}

Node::Node(int *arr, int size) {
    this->data = arr[0];
    this->previous = nullptr;
    this->next = nullptr;
    if (size <= 1) {
        return;
    }

    this->next = new Node(arr + 1, size - 1);
    this->next->previous = this;
}

void Node::display() {
    cout << this->data << " ";
    if (!this->next) {
        cout << endl;
        return;
    }
    this->next->display();
    return;
}

void Node::insertOrdered(int value) {
    if (!this->next) {
        Node *node = new Node();
        if (value >= this->data) {
            node->data = value;
            node->previous = this;
            node->next = nullptr;
            this->next = node;
            return;
        }
    } 
    if (value < this->data) {
        Node *node = new Node();
        if(this->previous == nullptr) {
           node->previous = this;
           node->data = this->data;
           node->next = this->next;
           this->next->previous = node;
           this->next = node;
           this->data = value;
           return;
        }
        node->data = value;
        node->previous = this->previous;
        node->next = this;
        this->previous->next = node;
        this->previous = node; 
        return;
    }
    this->next->insertOrdered(value);
}

void Node::insertAt(int position, int value) {
    if (position > this->length() || position < 0) {
        return;
    }
    if (position == 0) {
        Node *node = new Node();
        node->data = this->data;
        node->next = this->next;
        node->previous = this;
        this->next = node;
        this->data = value;
        return;
    }
    if (position <= 1) {
        Node *node = new Node();
        node->data = value;
        node->next = this;
        node->previous = this->previous;
        this->previous->next = node;
        this->previous = node;
        return;
    }
    this->next->insertAt(position - 1, value);
}

int Node::deleteAt(int position) {
    if (position < 1 || position > this->length()) {
        return -1;
    }
    Node *toBeDelete = this->next;
    if (position == 1) {
        this->data = toBeDelete->data;
        this->next = toBeDelete->next;
        this->next->previous = this;
        toBeDelete = nullptr;
        delete toBeDelete;
    }
    if (position < 1) {
        Node *toBeDelete = this->next;
        this->next = toBeDelete->next;
        this->next->previous = this;
        int value = toBeDelete->data;
        toBeDelete->next = nullptr;
        delete toBeDelete;
        return value;
    }
    return this->next->deleteAt(position - 1);
}

int Node::length() {
    if (!this->next) {
        return 1;
    }

    return this->next->length() + 1;
}

int Node::min() {
    if (!this->next) {
        return this->data;
    }
    int v = this->next->min();
    return this->data < v ? this->data : v;
}

int Node::max() {
    if (!this->next) {
        return this->data;
    }
    int v = this->next->max();
    return this->data > v ? this->data : v;
}

int Node::sum() {
    return this->next ? this->data + this->next->sum() : this->data;
}
