#include <cassert>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using std::cout;

template<typename T>
struct vector {
    T* data;
    int size;
    int capacity;

    vector() : data(nullptr), size(0), capacity(0) {}

    vector(int count, const T& value) : data(nullptr), size(0), capacity(0) {
        reserve(count);
        for (int i = 0; i < count; ++i) {
            push_back(value);
        }
    }

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

    T& operator[](int index) {
        return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
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

    void pop_back() {
        if (size > 0) {
            --size;
        }
    }

    void swap(vector& other) {
        std::swap(data, other.data);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
    }
};

double power(double x, int n) {
    if (n == 0) {
        return 1.0;
    }

    return x * power(x, n - 1);
}

int digit_sum(int n) {
    if (n < 10) {
        return n;
    }

    return n % 10 + digit_sum(n / 10);
}

int digit_count(int n) {
    if (n < 10) {
        return 1;
    }

    return 1 + digit_count(n / 10);
}

void print_binary(int n) {
    if (n < 2) {
        cout << n;
        return;
    }

    print_binary(n / 2);
    cout << n % 2;
}

template<typename T>
T recursive_max(vector<T>& v, int index) {
    if (index == v.size - 1) {
        return v[index];
    }

    T max_in_tail = recursive_max(v, index + 1);
    return (max_in_tail < v[index]) ? v[index] : max_in_tail;
}

template<typename T>
int recursive_count(vector<T>& v, T value, int index) {
    if (index == v.size) {
        return 0;
    }

    int current = (v[index] == value) ? 1 : 0;
    return current + recursive_count(v, value, index + 1);
}

template<typename T>
void recursive_reverse(vector<T>& v, int left, int right) {
    if (left >= right) {
        return;
    }

    std::swap(v[left], v[right]);
    recursive_reverse(v, left + 1, right - 1);
}

template<typename T>
bool recursive_is_sorted(vector<T>& v, int index) {
    if (index >= v.size - 1) {
        return true;
    }

    return v[index] <= v[index + 1] && recursive_is_sorted(v, index + 1);
}

bool is_palindrome(vector<char>& v, int left, int right) {
    if (left >= right) {
        return true;
    }

    return v[left] == v[right] && is_palindrome(v, left + 1, right - 1);
}

double fast_power(double x, int n) {
    if (n == 0) {
        return 1.0;
    }

    if (n % 2 == 0) {
        double half = fast_power(x, n / 2);
        return half * half;
    }

    return x * fast_power(x, n - 1);
}

int gcd(int a, int b) {
    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    if (b == 0) {
        return a;
    }

    return gcd(b, a % b);
}

void hanoi(int n, char from, char to, char aux) {
    if (n == 0) {
        return;
    }

    hanoi(n - 1, from, aux, to);
    cout << from << " -> " << to << '\n';
    hanoi(n - 1, aux, to, from);
}

long long fib_memo(int n, vector<long long>& cache) {
    if (cache[n] != -1) {
        return cache[n];
    }

    if (n <= 1) {
        cache[n] = n;
    } else {
        cache[n] = fib_memo(n - 1, cache) + fib_memo(n - 2, cache);
    }

    return cache[n];
}

int count_paths_memo(int m, int n, vector<vector<int>>& cache) {
    if (m == 1 || n == 1) {
        return 1;
    }

    if (cache[m][n] != -1) {
        return cache[m][n];
    }

    cache[m][n] = count_paths_memo(m - 1, n, cache) + count_paths_memo(m, n - 1, cache);
    return cache[m][n];
}

int count_paths(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }

    vector<vector<int>> cache;
    for (int i = 0; i <= m; ++i) {
        cache.push_back(vector<int>(n + 1, -1));
    }

    return count_paths_memo(m, n, cache);
}

int climb_stairs_memo(int n, vector<int>& cache) {
    if (n <= 1) {
        return 1;
    }

    if (cache[n] != -1) {
        return cache[n];
    }

    cache[n] = climb_stairs_memo(n - 1, cache) + climb_stairs_memo(n - 2, cache);
    return cache[n];
}

int climb_stairs(int n) {
    if (n < 0) {
        return 0;
    }

    vector<int> cache(n + 1, -1);
    return climb_stairs_memo(n, cache);
}

void print_subset(vector<int>& current) {
    cout << '{';
    for (int i = 0; i < current.size; ++i) {
        if (i > 0) {
            cout << ',';
        }
        cout << current[i];
    }
    cout << "}\n";
}

void subsets(vector<int>& v, vector<int>& current, int index) {
    if (index == v.size) {
        print_subset(current);
        return;
    }

    subsets(v, current, index + 1);
    current.push_back(v[index]);
    subsets(v, current, index + 1);
    current.pop_back();
}

template<typename T>
int recursive_min_index(vector<T>& v, int current, int best) {
    if (current == v.size) {
        return best;
    }

    if (v[current] < v[best]) {
        best = current;
    }

    return recursive_min_index(v, current + 1, best);
}

template<typename T>
void recursive_selection_sort(vector<T>& v, int start) {
    if (start >= v.size - 1) {
        return;
    }

    int min_index = recursive_min_index(v, start + 1, start);
    std::swap(v[start], v[min_index]);
    recursive_selection_sort(v, start + 1);
}

bool check_brackets(const char* str, int index, int open_count) {
    if (open_count < 0) {
        return false;
    }

    if (str[index] == '\0') {
        return open_count == 0;
    }

    if (str[index] == '(') {
        return check_brackets(str, index + 1, open_count + 1);
    }

    if (str[index] == ')') {
        return check_brackets(str, index + 1, open_count - 1);
    }

    return check_brackets(str, index + 1, open_count);
}

std::string capture_output(void (*function)()) {
    std::ostringstream output;
    std::streambuf* old_buffer = std::cout.rdbuf(output.rdbuf());
    function();
    std::cout.rdbuf(old_buffer);
    return output.str();
}

void print_binary_13() {
    print_binary(13);
}

void hanoi_3() {
    hanoi(3, 'A', 'C', 'B');
}

void subsets_123() {
    vector<int> values = {1, 2, 3};
    vector<int> current;
    subsets(values, current, 0);
}

int main() {
    assert(power(2.0, 10) == 1024.0);
    assert(digit_sum(1234) == 10);
    assert(digit_count(1234) == 4);
    assert(digit_count(7) == 1);
    assert(capture_output(print_binary_13) == "1101");

    vector<int> numbers = {3, 7, 2, 9, 4};
    assert(recursive_max(numbers, 0) == 9);

    vector<int> counted = {1, 3, 2, 3, 3};
    assert(recursive_count(counted, 3, 0) == 3);

    vector<int> reversed = {1, 2, 3, 4, 5};
    recursive_reverse(reversed, 0, reversed.size - 1);
    assert(reversed[0] == 5 && reversed[1] == 4 && reversed[2] == 3);
    assert(reversed[3] == 2 && reversed[4] == 1);

    vector<int> sorted = {1, 3, 5, 7};
    vector<int> not_sorted = {1, 5, 3, 7};
    assert(recursive_is_sorted(sorted, 0));
    assert(!recursive_is_sorted(not_sorted, 0));

    vector<char> palindrome = {'a', 'b', 'b', 'a'};
    vector<char> not_palindrome = {'a', 'b', 'c'};
    assert(is_palindrome(palindrome, 0, palindrome.size - 1));
    assert(!is_palindrome(not_palindrome, 0, not_palindrome.size - 1));

    assert(fast_power(2.0, 10) == 1024.0);
    assert(gcd(48, 18) == 6);
    assert(capture_output(hanoi_3) == "A -> C\nA -> B\nC -> B\nA -> C\nB -> A\nB -> C\nA -> C\n");

    vector<long long> fib_cache(11, -1);
    assert(fib_memo(10, fib_cache) == 55);
    assert(count_paths(3, 3) == 6);
    assert(climb_stairs(5) == 8);

    assert(capture_output(subsets_123) == "{}\n{3}\n{2}\n{2,3}\n{1}\n{1,3}\n{1,2}\n{1,2,3}\n");

    vector<int> selection_sorted = {5, 1, 4, 2, 3};
    recursive_selection_sort(selection_sorted, 0);
    assert(selection_sorted[0] == 1 && selection_sorted[1] == 2 && selection_sorted[2] == 3);
    assert(selection_sorted[3] == 4 && selection_sorted[4] == 5);

    assert(check_brackets("(()())", 0, 0));
    assert(!check_brackets("(()", 0, 0));
    assert(!check_brackets("())(", 0, 0));

    return 0;
}
