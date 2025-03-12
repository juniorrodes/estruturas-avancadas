#include <iostream>
#include <string>
using namespace std;

template<typename T>

class Grades {
private:
    string name;
    T grade;
public:
    Grades(string name, T grade) {
        this->name = name;
        this->grade = grade;
    }

    void print() {
        cout << "O estudante " << this->name << " obteve a nota " << this->grade << endl;
    }
};

int main(void) {
    Grades student1 = Grades<float>("Mauro", 3.5);
    student1.print();

    Grades student2 = Grades<int>("Mauricio", 5);
    student2.print();
    return 0;
}
