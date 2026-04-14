#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

/* ===================== 1.7 VECTOR3D ===================== */

class Vector3D {
private:
    double x, y, z;
    int State;
    static int count;

public:
    // constructors
    Vector3D() : x(0), y(0), z(0), State(0) { count++; }

    Vector3D(double v) : x(v), y(v), z(v), State(0) { count++; }

    Vector3D(double* arr) {
        if (!arr) {
            State = -1;
            x = y = z = 0;
        }
        else {
            x = arr[0]; y = arr[1]; z = arr[2];
            State = 0;
        }
        count++;
    }

    Vector3D(double x, double y, double z) : x(x), y(y), z(z), State(0) { count++; }

    ~Vector3D() {
        cout << "Destructor called, state = " << State << endl;
        count--;
    }

    static int getCount() { return count; }

    // ++ --
    Vector3D& operator++() { x++; y++; z++; return *this; }
    Vector3D operator++(int) { Vector3D t = *this; ++(*this); return t; }

    Vector3D& operator--() { x--; y--; z--; return *this; }
    Vector3D operator--(int) { Vector3D t = *this; --(*this); return t; }

    // !
    bool operator!() const { return !(x != 0 && y != 0 && z != 0); }

    // ~ (simple perpendicular)
    Vector3D operator~() { return Vector3D(-y, x, z); }

    // unary -
    Vector3D operator-() { return Vector3D(-x, -y, -z); }

    // =
    Vector3D& operator=(const Vector3D& v) {
        x = v.x; y = v.y; z = v.z; State = v.State;
        return *this;
    }

    // += -= *= /=
    Vector3D& operator+=(const Vector3D& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3D& operator-=(const Vector3D& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }

    Vector3D& operator*=(double k) { x *= k; y *= k; z *= k; return *this; }

    Vector3D& operator/=(double k) {
        if (k == 0) { State = -2; return *this; }
        x /= k; y /= k; z /= k;
        return *this;
    }

    // binary
    Vector3D operator+(const Vector3D& v) { return Vector3D(x + v.x, y + v.y, z + v.z); }
    Vector3D operator-(const Vector3D& v) { return Vector3D(x - v.x, y - v.y, z - v.z); }
    Vector3D operator*(double k) { return Vector3D(x * k, y * k, z * k); }
    Vector3D operator/(double k) { return k == 0 ? *this : Vector3D(x / k, y / k, z / k); }

    // ==
    bool operator==(const Vector3D& v) {
        return x == v.x && y == v.y && z == v.z;
    }

    bool operator!=(const Vector3D& v) {
        return !(*this == v);
    }

    // []
    double& operator[](int i) {
        if (i == 0) return x;
        if (i == 1) return y;
        if (i == 2) return z;
        State = -3;
        return z;
    }

    // ()
    void operator()() {
        cout << "(" << x << "," << y << "," << z << ")" << endl;
    }

    // compare
    double len() const { return x * x + y * y + z * z; }

    bool operator>(const Vector3D& v) { return len() > v.len(); }
    bool operator>=(const Vector3D& v) { return len() >= v.len(); }
    bool operator<(const Vector3D& v) { return len() < v.len(); }
    bool operator<=(const Vector3D& v) { return len() <= v.len(); }

    // I/O
    friend istream& operator>>(istream& in, Vector3D& v) {
        in >> v.x >> v.y >> v.z;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Vector3D& v) {
        out << "(" << v.x << "," << v.y << "," << v.z << ")";
        return out;
    }
};

int Vector3D::count = 0;

/* ===================== 2.7 ASSOCIATIVE ===================== */

class Assoc {
private:
    vector<int> num;
    vector<string> name;
    int CodeError;

public:
    Assoc() : CodeError(0) {}

    void add(int n, string s) {
        num.push_back(n);
        name.push_back(s);
    }

    string operator[](int n) {
        for (int i = 0; i < num.size(); i++)
            if (num[i] == n) return name[i];
        CodeError = 1;
        return "Not found";
    }

    int operator()(string s) {
        for (int i = 0; i < name.size(); i++)
            if (name[i] == s) return num[i];
        CodeError = 1;
        return -1;
    }

    friend ostream& operator<<(ostream& out, Assoc& a) {
        for (int i = 0; i < a.num.size(); i++)
            out << a.num[i] << " -> " << a.name[i] << endl;
        [14.04.2026 16:06] Vadim🦴: return out;
    }
};

/* ===================== 3.7 MATRIX ===================== */

class MatrixLong {
private:
    vector<vector<long>> m;
    int n;
    int codeError;
    static int count;

public:
    MatrixLong() : n(0), codeError(0) { count++; }

    MatrixLong(int size) {
        n = size;
        m.resize(n, vector<long>(n, 0));
        for (int i = 0; i < n; i++) m[i][i] = 1;
        count++;
    }

    MatrixLong(int n, int val) {
        this->n = n;
        m.resize(n, vector<long>(n, val));
        count++;
    }

    ~MatrixLong() { count--; }

    // +
    MatrixLong operator+(MatrixLong& b) {
        MatrixLong r(n, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                r.m[i][j] = m[i][j] + b.m[i][j];
        return r;
    }

    // *
    MatrixLong operator*(long k) {
        MatrixLong r(n, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                r.m[i][j] = m[i][j] * k;
        return r;
    }

    void randomFill() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                m[i][j] = rand() % 10;
    }

    void print() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << m[i][j] << " ";
            cout << endl;
        }
    }
};

int MatrixLong::count = 0;

/* ===================== TEST ===================== */

void test1() {
    Vector3D a(1, 2, 3), b(3, 2, 1);
    Vector3D r = (a + b) * 2 - a + b * 3;
    cout << "Result: " << r << endl;
}

void test2() {
    Assoc a;
    a.add(1, "Ivan");
    a.add(2, "Petro");
    cout << a;
    cout << "Search 2: " << a[2] << endl;
}

void test3() {
    MatrixLong A(3), B(3);
    A.randomFill();
    B.randomFill();
    cout << "A:\n"; A.print();
    cout << "B:\n"; B.print();
    MatrixLong C = A + B;
    cout << "A+B:\n"; C.print();
}

/* ===================== MAIN ===================== */

int main() {
    srand(time(0));

    int c;
    do {
        cout << "\n1-Task1\n2-Task2\n3-Task3\n0-Exit\n";
        cin >> c;

        if (c == 1) test1();
        if (c == 2) test2();
        if (c == 3) test3();

    } while (c != 0);

    return 0;
}