#include <cassert>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <initializer_list>
#include <random>
#include <utility>

using std::cout;
using std::endl;

// Simple template vector<T> compatible with the lecture examples.
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

    void swap(vector& other) {
        std::swap(data, other.data);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
    }
};

// Task 1
template<typename T>
void bubble_sort_desc(vector<T>& v) {
    for (int i = 0; i < v.size - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < v.size - 1 - i; ++j) {
            if (v[j] < v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            return;
        }
    }
}

// Task 2
template<typename T>
int bubble_sort_count(vector<T>& v) {
    int swaps = 0;
    for (int i = 0; i < v.size - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < v.size - 1 - i; ++j) {
            if (v[j + 1] < v[j]) {
                std::swap(v[j], v[j + 1]);
                ++swaps;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
    return swaps;
}

// Task 3
template<typename T>
void bubble_sort_range(vector<T>& v, int left, int right) {
    if (left < 0) {
        left = 0;
    }
    if (right >= v.size) {
        right = v.size - 1;
    }
    if (left >= right) {
        return;
    }

    for (int end = right; end > left; --end) {
        bool swapped = false;
        for (int j = left; j < end; ++j) {
            if (v[j + 1] < v[j]) {
                std::swap(v[j], v[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            return;
        }
    }
}

// Task 4
template<typename T>
bool is_sorted(vector<T>& v) {
    for (int i = 1; i < v.size; ++i) {
        if (v[i] < v[i - 1]) {
            return false;
        }
    }
    return true;
}

// Task 5
template<typename T>
void insert_sorted(vector<T>& v, T value) {
    v.push_back(value);
    int i = v.size - 2;
    while (i >= 0 && value < v[i]) {
        v[i + 1] = v[i];
        --i;
    }
    v[i + 1] = value;
}

// Task 6
template<typename T>
void insertion_sort_desc(vector<T>& v) {
    for (int i = 1; i < v.size; ++i) {
        T key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] < key) {
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = key;
    }
}

// Task 7
template<typename T>
int insertion_sort_count(vector<T>& v) {
    int shifts = 0;
    for (int i = 1; i < v.size; ++i) {
        T key = v[i];
        int j = i - 1;
        while (j >= 0 && key < v[j]) {
            v[j + 1] = v[j];
            ++shifts;
            --j;
        }
        v[j + 1] = key;
    }
    return shifts;
}

// Task 8
template<typename T>
void binary_insertion_sort(vector<T>& v) {
    for (int i = 1; i < v.size; ++i) {
        T key = v[i];
        int left = 0;
        int right = i;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (key < v[mid]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        for (int j = i; j > left; --j) {
            v[j] = v[j - 1];
        }
        v[left] = key;
    }
}

template<typename T>
int partition_last(vector<T>& v, int low, int high) {
    T pivot = v[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (!(pivot < v[j])) {
            ++i;
            std::swap(v[i], v[j]);
        }
    }
    std::swap(v[i + 1], v[high]);
    return i + 1;
}

// Task 9
template<typename T>
int partition_first(vector<T>& v, int low, int high) {
    T pivot = v[low];
    int i = low + 1;
    int j = high;

    while (true) {
        while (i <= high && !(pivot < v[i])) {
            ++i;
        }
        while (j >= low + 1 && pivot < v[j]) {
            --j;
        }
        if (i >= j) {
            break;
        }
        std::swap(v[i], v[j]);
        ++i;
        --j;
    }

    std::swap(v[low], v[j]);
    return j;
}

template<typename T>
void quick_sort(vector<T>& v, int low, int high) {
    if (low >= high) {
        return;
    }

    int pi = partition_last(v, low, high);
    quick_sort(v, low, pi - 1);
    quick_sort(v, pi + 1, high);
}

template<typename T>
void quick_sort(vector<T>& v) {
    if (v.size > 1) {
        quick_sort(v, 0, v.size - 1);
    }
}

template<typename T>
void quick_sort_count_impl(vector<T>& v, int low, int high, int& calls) {
    ++calls;
    if (low >= high) {
        return;
    }

    int pi = partition_last(v, low, high);
    quick_sort_count_impl(v, low, pi - 1, calls);
    quick_sort_count_impl(v, pi + 1, high, calls);
}

// Task 10
template<typename T>
int quick_sort_count(vector<T>& v) {
    if (v.size == 0) {
        return 0;
    }

    int calls = 0;
    quick_sort_count_impl(v, 0, v.size - 1, calls);
    return calls;
}

// Task 11: k is one-based: k == 1 returns the smallest element.
template<typename T>
T quick_select(vector<T>& v, int k) {
    int target = k - 1;
    int low = 0;
    int high = v.size - 1;

    while (low <= high) {
        int pi = partition_last(v, low, high);
        if (pi == target) {
            return v[pi];
        }
        if (target < pi) {
            high = pi - 1;
        } else {
            low = pi + 1;
        }
    }

    return v[0];
}

// Task 12
template<typename T>
void partition_3way(vector<T>& v, int low, int high, int& lt, int& gt) {
    T pivot = v[low];
    lt = low;
    gt = high;
    int i = low;

    while (i <= gt) {
        if (v[i] < pivot) {
            std::swap(v[lt], v[i]);
            ++lt;
            ++i;
        } else if (pivot < v[i]) {
            std::swap(v[i], v[gt]);
            --gt;
        } else {
            ++i;
        }
    }
}

// Task 13
template<typename T>
vector<T> merge_vectors(vector<T>& a, vector<T>& b) {
    vector<T> result;
    result.reserve(a.size + b.size);
    int i = 0;
    int j = 0;

    while (i < a.size && j < b.size) {
        if (!(b[j] < a[i])) {
            result.push_back(a[i]);
            ++i;
        } else {
            result.push_back(b[j]);
            ++j;
        }
    }
    while (i < a.size) {
        result.push_back(a[i]);
        ++i;
    }
    while (j < b.size) {
        result.push_back(b[j]);
        ++j;
    }

    return result;
}

template<typename T>
int merge_count(vector<T>& v, vector<T>& temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    int inversions = 0;

    while (i <= mid && j <= right) {
        if (!(v[j] < v[i])) {
            temp[k] = v[i];
            ++i;
        } else {
            temp[k] = v[j];
            ++j;
            inversions += mid - i + 1;
        }
        ++k;
    }
    while (i <= mid) {
        temp[k] = v[i];
        ++i;
        ++k;
    }
    while (j <= right) {
        temp[k] = v[j];
        ++j;
        ++k;
    }
    for (int p = left; p <= right; ++p) {
        v[p] = temp[p];
    }

    return inversions;
}

template<typename T>
int count_inversions_impl(vector<T>& v, vector<T>& temp, int left, int right) {
    if (left >= right) {
        return 0;
    }

    int mid = left + (right - left) / 2;
    int result = count_inversions_impl(v, temp, left, mid);
    result += count_inversions_impl(v, temp, mid + 1, right);
    result += merge_count(v, temp, left, mid, right);
    return result;
}

// Task 14
template<typename T>
int count_inversions(vector<T>& v) {
    if (v.size < 2) {
        return 0;
    }

    vector<T> temp(v.size, T{});
    return count_inversions_impl(v, temp, 0, v.size - 1);
}

template<typename T>
void merge_range(vector<T>& v, vector<T>& temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (!(v[j] < v[i])) {
            temp[k] = v[i];
            ++i;
        } else {
            temp[k] = v[j];
            ++j;
        }
        ++k;
    }
    while (i <= mid) {
        temp[k] = v[i];
        ++i;
        ++k;
    }
    while (j <= right) {
        temp[k] = v[j];
        ++j;
        ++k;
    }
    for (int p = left; p <= right; ++p) {
        v[p] = temp[p];
    }
}

// Task 15
template<typename T>
void merge_sort_iterative(vector<T>& v) {
    if (v.size < 2) {
        return;
    }

    vector<T> temp(v.size, T{});
    for (int width = 1; width < v.size; width *= 2) {
        for (int left = 0; left < v.size - width; left += 2 * width) {
            int mid = left + width - 1;
            int right = left + 2 * width - 1;
            if (right >= v.size) {
                right = v.size - 1;
            }
            merge_range(v, temp, left, mid, right);
        }
    }
}

// Task 16
template<typename T>
void natural_merge_sort(vector<T>& v) {
    if (v.size < 2) {
        return;
    }

    vector<T> temp(v.size, T{});
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        int left = 0;

        while (left < v.size) {
            int mid = left;
            while (mid + 1 < v.size && !(v[mid + 1] < v[mid])) {
                ++mid;
            }
            if (mid == v.size - 1) {
                break;
            }

            int right = mid + 1;
            while (right + 1 < v.size && !(v[right + 1] < v[right])) {
                ++right;
            }

            merge_range(v, temp, left, mid, right);
            sorted = false;
            left = right + 1;
        }
    }
}

void insertion_sort(vector<int>& v) {
    for (int i = 1; i < v.size; ++i) {
        int key = v[i];
        int j = i - 1;
        while (j >= 0 && key < v[j]) {
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = key;
    }
}

void bubble_sort(vector<int>& v) {
    bubble_sort_count(v);
}

// Task 17
void empirical_comparison(int n) {
    vector<int> original;
    original.reserve(n);

    std::mt19937 generator(42);
    std::uniform_int_distribution<int> distribution(0, 1000000);
    for (int i = 0; i < n; ++i) {
        original.push_back(distribution(generator));
    }

    auto measure = [](const char* name, vector<int> values, void (*sort_function)(vector<int>&)) {
        auto start = std::chrono::high_resolution_clock::now();
        sort_function(values);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        cout << name << ": " << duration.count() << " us" << endl;
    };

    cout << "n = " << n << endl;
    measure("bubble sort", original, bubble_sort);
    measure("insertion sort", original, insertion_sort);
    measure("quick sort", original, quick_sort<int>);
    measure("bottom-up merge sort", original, merge_sort_iterative<int>);
}

// Task 18
vector<int> make_quick_sort_worst_case(int n) {
    vector<int> result;
    result.reserve(n);
    for (int i = 1; i <= n; ++i) {
        result.push_back(i);
    }
    return result;
}

// With pivot = last element, an already sorted ascending array is worst-case:
// partition always places the pivot at the end and leaves a subproblem of size n - 1.
void quick_sort_worst_case_demo() {
    vector<int> values = make_quick_sort_worst_case(10);
    quick_sort(values);
}

// Task 19
struct student {
    int id;
    int age;
    double grade;
};

bool compare_by_grade_desc(const student& a, const student& b) {
    return a.grade > b.grade;
}

bool compare_by_age(const student& a, const student& b) {
    return a.age < b.age;
}

// Task 20
struct point {
    int x;
    int y;
};

int distance_squared(const point& p) {
    return p.x * p.x + p.y * p.y;
}

bool compare_by_distance(const point& a, const point& b) {
    return distance_squared(a) < distance_squared(b);
}

template<typename T, typename Compare>
void insertion_sort_by(vector<T>& v, Compare compare) {
    for (int i = 1; i < v.size; ++i) {
        T key = v[i];
        int j = i - 1;
        while (j >= 0 && compare(key, v[j])) {
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = key;
    }
}

int main() {
    vector<int> task1 = {5, 3, 8, 4, 2};
    bubble_sort_desc(task1);
    assert((task1[0] == 8 && task1[1] == 5 && task1[2] == 4 && task1[3] == 3 && task1[4] == 2));

    vector<int> task2 = {5, 3, 8, 4, 2};
    assert(bubble_sort_count(task2) == 7);
    assert(is_sorted(task2));

    vector<int> task3 = {9, 5, 3, 8, 4, 2, 7};
    bubble_sort_range(task3, 2, 5);
    assert((task3[0] == 9 && task3[1] == 5 && task3[2] == 2 && task3[3] == 3 && task3[4] == 4 && task3[5] == 8 && task3[6] == 7));

    vector<int> task4a = {1, 2, 3, 5};
    vector<int> task4b = {1, 3, 2};
    assert(is_sorted(task4a));
    assert(!is_sorted(task4b));

    vector<int> task5 = {2, 4, 6, 8};
    insert_sorted(task5, 5);
    assert((task5[0] == 2 && task5[1] == 4 && task5[2] == 5 && task5[3] == 6 && task5[4] == 8));

    vector<int> task6 = {5, 3, 8, 4, 2};
    insertion_sort_desc(task6);
    assert((task6[0] == 8 && task6[1] == 5 && task6[2] == 4 && task6[3] == 3 && task6[4] == 2));

    vector<int> task7 = {5, 3, 8, 4, 2};
    assert(insertion_sort_count(task7) == 7);
    assert(is_sorted(task7));

    vector<int> task8 = {5, 3, 8, 4, 2};
    binary_insertion_sort(task8);
    assert(is_sorted(task8));

    vector<int> task9 = {5, 3, 8, 4, 2};
    int first_pivot_index = partition_first(task9, 0, task9.size - 1);
    for (int i = 0; i < first_pivot_index; ++i) {
        assert(!(task9[first_pivot_index] < task9[i]));
    }
    for (int i = first_pivot_index + 1; i < task9.size; ++i) {
        assert(!(task9[i] < task9[first_pivot_index]));
    }

    vector<int> task10 = {5, 3, 8, 4, 2};
    assert(quick_sort_count(task10) > 0);
    assert(is_sorted(task10));

    vector<int> task11 = {5, 3, 8, 4, 2};
    assert(quick_select(task11, 2) == 3);

    vector<int> task12 = {4, 2, 4, 1, 4, 3};
    int lt = 0;
    int gt = 0;
    partition_3way(task12, 0, task12.size - 1, lt, gt);
    for (int i = 0; i < lt; ++i) {
        assert(task12[i] < 4);
    }
    for (int i = lt; i <= gt; ++i) {
        assert(task12[i] == 4);
    }
    for (int i = gt + 1; i < task12.size; ++i) {
        assert(4 < task12[i]);
    }

    vector<int> task13a = {1, 3, 5};
    vector<int> task13b = {2, 4, 6};
    vector<int> task13 = merge_vectors(task13a, task13b);
    assert((task13[0] == 1 && task13[1] == 2 && task13[2] == 3 && task13[3] == 4 && task13[4] == 5 && task13[5] == 6));

    vector<int> task14 = {5, 3, 8, 4, 2};
    assert(count_inversions(task14) == 7);
    assert(is_sorted(task14));

    vector<int> task15 = {5, 3, 8, 4, 2};
    merge_sort_iterative(task15);
    assert(is_sorted(task15));

    vector<int> task16 = {1, 3, 5, 2, 4, 6};
    natural_merge_sort(task16);
    assert(is_sorted(task16));

    vector<int> task18 = make_quick_sort_worst_case(5);
    assert((task18[0] == 1 && task18[1] == 2 && task18[2] == 3 && task18[3] == 4 && task18[4] == 5));

    vector<student> students = {{1, 20, 91.5}, {2, 18, 95.0}, {3, 19, 88.0}};
    insertion_sort_by(students, compare_by_grade_desc);
    assert(students[0].id == 2);
    insertion_sort_by(students, compare_by_age);
    assert(students[0].id == 2);

    vector<point> points = {{3, 4}, {1, 1}, {2, 0}};
    insertion_sort_by(points, compare_by_distance);
    assert(points[0].x == 1 && points[0].y == 1);

    cout << "All sorting task checks passed." << endl;
    return 0;
}
