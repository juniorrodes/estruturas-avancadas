class Node {
private:
    int data;
    Node *next;
    Node *previous;
    void insert(Node next, Node previous);
public:
    Node();
    Node(int *arr, int size);
    ~Node();

    void display();
    void insertAt(int position, int value);
    void insertOrdered(int value);
    int deleteAt(int position);
    int length();
    int min();
    int max();
    int sum();

};
