#include <cassert>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace task1 {

template<typename T>
T my_min(T a, T b) {
    return (b < a) ? b : a;
}

} // namespace task1

namespace task2 {

void print_info(int x) {
    std::cout << "Number: " << x;
}

void print_info(const char* text) {
    std::cout << "Text: " << text;
}

void print_info(char c) {
    std::cout << "Character: " << c;
}

} // namespace task2

namespace tasks3_and_4 {

struct point {
    int x;
    int y;
};

std::ostream& operator<<(std::ostream& out, const point& p) {
    out << '(' << p.x << ", " << p.y << ')';
    return out;
}

std::istream& operator>>(std::istream& in, point& p) {
    in >> p.x >> p.y;
    return in;
}

} // namespace tasks3_and_4

namespace task5 {

struct student {
    int id;
    int age;
    double grade;
};

std::ostream& operator<<(std::ostream& out, const student& s) {
    out << "Student #" << s.id << " (age: " << s.age << ", grade: " << s.grade << ')';
    return out;
}

} // namespace task5

namespace task6 {

template<typename T, typename U>
struct pair {
    T first;
    U second;

    pair(T a, U b) : first(a), second(b) {}
};

} // namespace task6

namespace task7 {

template<typename T>
struct vector {
    T* data;
    int size;
    int capacity;

    vector() : data(nullptr), size(0), capacity(0) {}

    vector(std::initializer_list<T> values) : data(nullptr), size(0), capacity(0) {
        reserve(static_cast<int>(values.size()));
        for (const T& value : values) {
            push_back(value);
        }
    }

    vector(const vector& other) : data(nullptr), size(0), capacity(0) {
        reserve(other.size);
        for (int i = 0; i < other.size; ++i) {
            push_back(other.data[i]);
        }
    }

    vector& operator=(const vector& other) {
        if (this == &other) {
            return *this;
        }

        vector copy(other);
        swap(copy);
        return *this;
    }

    ~vector() {
        delete[] data;
    }

    void reserve(int new_capacity) {
        if (new_capacity <= capacity) {
            return;
        }

        T* new_data = new T[new_capacity];
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    void push_back(const T& value) {
        if (size == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }

        data[size] = value;
        ++size;
    }

    void swap(vector& other) {
        std::swap(data, other.data);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
    }

    void print() const {
        std::cout << '[';
        for (int i = 0; i < size; ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << data[i];
        }
        std::cout << ']';
    }
};

} // namespace task7

namespace task8 {

struct point {
    int x;
    int y;
    int z;
};

std::ostream& operator<<(std::ostream& out, const point& p) {
    out << '(' << p.x << ", " << p.y << ", " << p.z << ')';
    return out;
}

std::istream& operator>>(std::istream& in, point& p) {
    in >> p.x >> p.y >> p.z;
    return in;
}

} // namespace task8

namespace task9 {

using task7::vector;
using task8::point;
using task8::operator<<;
using task8::operator>>;

void add_point_from_input(vector<point>& points, std::istream& in) {
    point new_point{};
    in >> new_point;
    points.push_back(new_point);
}

void demo(std::istream& in) {
    vector<point> points = {{0, 0, 0}, {1, 1, 1}, {-5, 3, 2}};

    points.print();
    std::cout << '\n';

    add_point_from_input(points, in);

    points.print();
    std::cout << '\n';
}

} // namespace task9

namespace task10 {

template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

} // namespace task10

namespace {

std::string capture_output(void (*function)()) {
    std::ostringstream output;
    std::streambuf* old_buffer = std::cout.rdbuf(output.rdbuf());
    function();
    std::cout.rdbuf(old_buffer);
    return output.str();
}

void test_task2_int() {
    task2::print_info(42);
}

void test_task2_text() {
    task2::print_info("hello");
}

void test_task2_char() {
    task2::print_info('A');
}

} // namespace

int main() {
    assert(task1::my_min(5, 3) == 3);
    assert(task1::my_min(2.5, 8.1) == 2.5);
    assert(task1::my_min('a', 'z') == 'a');

    assert(capture_output(test_task2_int) == "Number: 42");
    assert(capture_output(test_task2_text) == "Text: hello");
    assert(capture_output(test_task2_char) == "Character: A");

    tasks3_and_4::point point2d{};
    std::istringstream point2d_input("5 10");
    point2d_input >> point2d;
    std::ostringstream point2d_output;
    point2d_output << point2d;
    assert(point2d_output.str() == "(5, 10)");

    task5::student student{7, 19, 91.5};
    std::ostringstream student_output;
    student_output << student;
    assert(student_output.str() == "Student #7 (age: 19, grade: 91.5)");

    task6::pair<int, double> pair1(5, 3.14);
    task6::pair<char, int> pair2('A', 42);
    assert(pair1.first == 5 && pair1.second == 3.14);
    assert(pair2.first == 'A' && pair2.second == 42);

    task8::point point3d{};
    std::istringstream point3d_input("1 2 3");
    point3d_input >> point3d;
    std::ostringstream point3d_output;
    point3d_output << point3d;
    assert(point3d_output.str() == "(1, 2, 3)");

    int x = 5;
    int y = 10;
    task10::swap(x, y);
    assert(x == 10 && y == 5);

    double a = 3.14;
    double b = 2.71;
    task10::swap(a, b);
    assert(a == 2.71 && b == 3.14);

    std::istringstream point_list_input("9 8 7");
    task9::demo(point_list_input);

    return 0;
}
