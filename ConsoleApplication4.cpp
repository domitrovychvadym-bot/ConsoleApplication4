#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

/* ===================== VECTOR3D ===================== */

class Vector3D {
private:
    double x, y, z;
    int State;
    static int objectCount;

public:
    Vector3D() : x(0), y(0), z(0), State(0) { objectCount++; }
    Vector3D(double xx, double yy, double zz) : x(xx), y(yy), z(zz), State(0) { objectCount++; }

    ~Vector3D() {
        cout << "[Destructor Vector3D] State = " << State << endl;
        objectCount--;
    }

    static int getObjectCount() { return objectCount; }

    Vector3D operator+(const Vector3D& b) const {
        return Vector3D(x + b.x, y + b.y, z + b.z);
    }

    Vector3D operator-(const Vector3D& b) const {
        return Vector3D(x - b.x, y - b.y, z - b.z);
    }

    Vector3D operator*(double k) const {
        return Vector3D(x * k, y * k, z * k);
    }

    Vector3D operator/(double k) const {
        if (k == 0) return *this;
        return Vector3D(x / k, y / k, z / k);
    }

    bool operator==(const Vector3D& b) const {
        return x == b.x && y == b.y && z == b.z;
    }

    double& operator[](int i) {
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    friend ostream& operator<<(ostream& os, const Vector3D& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

    friend istream& operator>>(istream& is, Vector3D& v) {
        is >> v.x >> v.y >> v.z;
        return is;
    }
};

int Vector3D::objectCount = 0;

/* ===================== ASSOCIATIVE CLASS ===================== */

class StudentRecord {
private:
    string surname, name, patronymic;

public:
    StudentRecord(string s = "", string n = "", string p = "")
        : surname(s), name(n), patronymic(p) {
    }

    string getFullName() const {
        return surname + " " + name + " " + patronymic;
    }

    bool operator==(const StudentRecord& other) const {
        return getFullName() == other.getFullName();
    }

    friend ostream& operator<<(ostream& os, const StudentRecord& st) {
        os << st.getFullName();
        return os;
    }
};

class AssocGroupList {
private:
    int numbers[10];
    StudentRecord students[10];
    int count;

public:
    AssocGroupList() : count(0) {}

    void add(int number, const StudentRecord& st) {
        numbers[count] = number;
        students[count] = st;
        count++;
    }

    void createSample() {
        add(1, { "Ivanenko","Petro","Oleksandrovych" });
        add(2, { "Petrenko","Iryna","Vasylivna" });
        add(3, { "Sydorenko","Oleh","Mykolaiovych" });
        add(4, { "Kovalenko","Maria","Ivanivna" });
        add(5, { "Bondar","Andrii","Serhiiovych" });
    }

    void printAll() const {
        cout << "\nGroup list:\n";
        for (int i = 0; i < count; i++) {
            cout << numbers[i] << " -> " << students[i] << endl;
        }
    }

    StudentRecord operator[](int number) {
        for (int i = 0; i < count; i++) {
            if (numbers[i] == number)
                return students[i];
        }
        return StudentRecord();
    }

    int operator()(const StudentRecord& st) {
        for (int i = 0; i < count; i++) {
            if (students[i] == st)
                return numbers[i];
        }
        return -1;
    }
};

/* ===================== MATRIX ===================== */

class MatrixLong {
private:
    long a[3][3];

public:
    MatrixLong(long val = 0) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                a[i][j] = val;
    }

    MatrixLong operator+(const MatrixLong& b) const {
        MatrixLong r;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                r.a[i][j] = a[i][j] + b.a[i][j];
        return r;
    }

    MatrixLong operator*(long k) const {
        MatrixLong r;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                r.a[i][j] = a[i][j] * k;
        return r;
    }

    void input() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                cin >> a[i][j];
    }

    void print() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                cout << a[i][j] << " ";
            cout << endl;
        }
    }
};

/* ===================== TESTS ===================== */

void testTask17() {
    cout << "\n========== TASK 1.7 ==========\n";
    Vector3D a(1, 2, 3), b(3, 2, 1);
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a + b = " << a + b << endl;
}

void testTask27() {
    cout << "\n========== TASK 2.7 ==========\n";
    AssocGroupList grp;
    grp.createSample();
    grp.printAll();

    cout << "\nSearch number 3: " << grp[3] << endl;
}

void testTask37() {
    cout << "\n========== TASK 3.7 ==========\n";
    MatrixLong A, B;

    cout << "Enter matrix A:\n";
    A.input();

    cout << "Enter matrix B:\n";
    B.input();

    MatrixLong C = A + B;

    cout << "\nA + B:\n";
    C.print();
}

/* ===================== MAIN ===================== */

int main() {

    system("chcp 1251");

    int choice;

    do {
        cout << "\n========== LAB 4 MENU ==========\n";
        cout << "1 - Task 1.7\n";
        cout << "2 - Task 2.7\n";
        cout << "3 - Task 3.7\n";
        cout << "0 - Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
        case 1: testTask17(); break;
        case 2: testTask27(); break;
        case 3: testTask37(); break;
        }

    } while (choice != 0);

    return 0;
}