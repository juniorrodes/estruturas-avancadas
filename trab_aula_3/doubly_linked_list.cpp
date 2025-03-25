#include "List.h"
#include <iostream>
#include <ostream>

using namespace std;

int main(void) {
    int arr[] = { 5, 8, 10, 14, 19 };
    Node *list = new Node(arr, sizeof(arr)/sizeof(int));

    list->display();
    cout << "List length is: " << list->length() << endl;

    list->insertOrdered(18);
    list->insertOrdered(2);
    list->insertAt(3, 2);
    list->insertAt(0, 32);
    list->display();
    cout << "List length is: " << list->length() << endl;
    list->deleteAt(4);
    list->display();
    cout << "List length is: " << list->length() << endl;
    list->deleteAt(1);
    list->display();
    cout << "List length is: " << list->length() << endl;

    cout << "min value of list is: " << list->min() << endl;
    cout << "max value of list is: " << list->max() << endl;
    cout << "sum of the list is: " << list->sum() << endl;
    delete list;
}
