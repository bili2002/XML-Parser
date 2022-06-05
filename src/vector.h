#pragma once

template <typename Type>
class MyVector {
private:
    Type* arr = nullptr;
    int maxSize = 0;
    int currSize = 0;

    void expandVector() {
        int newSize = maxSize != 0 ? maxSize*2 : 1;
        Type* temp = new Type[newSize];
        for (int i=0; i<currSize; i++) {
            temp[i] = arr[i];
        }

        delete[] arr;
        arr = temp;
        maxSize = newSize;
    }

    void shrinkVector() {
        Type* temp = new Type[maxSize/2];
        for (int i=0; i<currSize; i++) {
            temp[i] = arr[i];
        }

        delete[] arr;
        arr = temp;
        maxSize /= 2;
    }

    static void swap(Type& left, Type& right) {
        Type temp = left;
        left = right;
        right = temp;
    }

public:
    MyVector() {
        arr = nullptr;
        maxSize = 0;
        currSize = 0;
    }

    MyVector(int size) {
        int newSize = 1;
        while (newSize < size) {
            newSize *= 2;
        }

        arr = new Type[newSize];
        maxSize = newSize;
        currSize = size;
    } 

    MyVector(int size, Type var) : MyVector(size) {
        for (int i=0; i<size; i++) {
            arr[i] = var;
        }
    }

    MyVector(const MyVector& oth) {
        maxSize = oth.maxSize;
        currSize = oth.currSize;

        arr = new Type[maxSize];
        for (int i=0; i<currSize; i++) {
            arr[i] = oth.arr[i];
        }
    }

    ~MyVector() {
        delete[] arr;
    }
    
    MyVector& operator=(const MyVector& oth) {
        maxSize = oth.maxSize;
        currSize = oth.currSize;

        delete[] arr;
        arr = new Type[maxSize];
        for (int i=0; i<currSize; i++) {
            arr[i] = oth.arr[i];
        }

        return *this;
    }

    bool operator==(const MyVector& oth) {
        if (currSize != oth.currSize) {
            return false;
        }

        for (int i=0; i<currSize; i++) {
            if (arr[i] != oth.arr[i]) {
                return false;
            }
        }
        return true;
    }

    void operator+=(const Type& el) {
        arr.push_back(el);
    }

    Type& operator[](int i) {
        return arr[i];
    }

    const Type& operator[](int i) const {
        return arr[i];
    }

    void push_back(const Type& var) {
        if (currSize == maxSize) {
            expandVector();
        }
        arr[currSize++] = var;
    }

    Type& pop_back() {
        Type& temp = arr[currSize - 1];
        if (currSize == maxSize/2) {
            shrinkVector();
        }
        currSize--;

        return temp;
    }

    void erase(int pos) {
        for (int i=pos; i<currSize-1; i++) {
            swap(arr[i], arr[i+1]);
        }
        pop_back();
    }

    int size() const {
        return currSize;
    }

    void resize(int n) {
        int newSize = 1;
        while (newSize < n) {
            newSize *= 2;
        }

        delete[] arr;
        arr = new Type[newSize];
        maxSize = newSize;
        currSize = n;
    }

    bool empty() {
        return currSize == 0;
    }

    Type* begin() {
        return arr;
    }
    
    Type* end() {
        return arr + currSize;
    }

    const Type* begin() const {
        return arr;
    }
    
    const Type* end() const{
        return arr + currSize;
    }

    void swap(MyVector& oth) {
        swap(maxSize, oth.maxSize);
        swap(currSize, oth.currSize);
        swap(arr, oth.arr);
    }
};
