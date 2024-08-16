﻿#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
class Array {
private:
    T* data;
    int size;
    int capacity;
    int grow;

public:
    Array() : data(nullptr), size(0), capacity(0), grow(1) {}

    Array(const Array& other) {
        size = other.size;
        capacity = other.capacity;
        grow = other.grow;
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    ~Array() {
        delete[] data;
    }

    int GetSize() const {
        return size;
    }

    void SetSize(int newSize, int grow = 1) {
        this->grow = grow;
        if (newSize > capacity) {
            T* newData = new T[newSize];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newSize;
        }
        else if (newSize < size) {
            T* newData = new T[newSize];
            for (int i = 0; i < newSize; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            size = newSize;
            capacity = newSize;
        }
    }

    int GetUpperBound() const {
        return size - 1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
        if (size < capacity) {
            T* newData = new T[size];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = size;
        }
    }

    void RemoveAll() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    T GetAt(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Array index out of range");
        }
        return data[index];
    }

    void SetAt(T value, int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Array index out of range");
        }
        data[index] = value;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Array index out of range");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Array index out of range");
        }
        return data[index];
    }

    void Add(T value) {
        if (size == capacity) {
            SetSize(size + grow, grow);
        }
        data[size++] = value;
    }

    void Append(const Array& other) {
        for (int i = 0; i < other.size; ++i) {
            Add(other.data[i]);
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            grow = other.grow;
            data = new T[capacity];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    T* GetData() {
        return data;
    }

    void InsertAt(T value, int index) {
        if (index < 0 || index > size) {
            throw out_of_range("Array index out of range");
        }
        if (size == capacity) {
            SetSize(size + grow, grow);
        }
        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++size;
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Array index out of range");
        }
        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
        if (size < capacity - grow) {
            FreeExtra();
        }
    }

    template<typename U>
    friend ostream& operator<<(ostream& os, const Array<U>& arr);
};

template<typename T>
ostream& operator<<(ostream& os, const Array<T>& arr) {
    for (int i = 0; i < arr.size; ++i) {
        os << arr.data[i] << " ";
    }
    return os;
}

double average(const Array<double>& arr) {
    double sum = 0.0;
    for (int i = 0; i < arr.GetSize(); ++i) {
        sum += arr[i];
    }
    return sum / arr.GetSize();
}

int main() {
    srand(time(0));

    Array<double> arr;
    arr.Add(5.6);
    arr.Add(3.14);
    arr.Add(9.24);
    arr.Add(10.24);
    arr.Add(124.43);

    cout << "Array elements: " << arr << endl;
    cout << "Average: " << average(arr) << endl;
}