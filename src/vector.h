#pragma once

template <typename Type>
class MyVector {
private:
protected:
    Type* arr = nullptr;
    size_t maxSize = 0;
    size_t currSize = 0;

    void expandVector() {
        int newSize = maxSize != 0 ? maxSize*2 : 1;
        Type* temp = new Type[newSize];
        for (size_t i=0; i<currSize; i++) {
            temp[i] = std::move(arr[i]);
        }

        delete[] arr;
        arr = temp;
        maxSize = newSize;
    }

    void shrinkVector() {
        Type* temp = new Type[maxSize/2];
        for (size_t i=0; i<currSize; i++) {
            temp[i] = std::move(arr[i]);
        }

        delete[] arr;
        arr = temp;
        maxSize /= 2;
    }

    static void swap(Type& left, Type& right) {
        Type temp = std::move(left);
        left = std::move(right);
        right = std::move(temp);
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

    MyVector(int size, const Type& var) : MyVector(size) {
        for (size_t i=0; i<size; i++) {
            arr[i] = var;
        }
    }

    MyVector(const MyVector& oth) {
        maxSize = oth.maxSize;
        currSize = oth.currSize;

        arr = new Type[maxSize];
        for (size_t i=0; i<currSize; i++) {
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
        for (size_t i=0; i<currSize; i++) {
            arr[i] = oth.arr[i];
        }

        return *this;
    }

    bool operator==(const MyVector& oth) const {
        if (currSize != oth.currSize) {
            return false;
        }

        for (size_t i=0; i<currSize; i++) {
            if (arr[i] != oth.arr[i]) {
                return false;
            }
        }
        return true;
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

    void push_back(Type&& var) {
        if (currSize == maxSize) {
            expandVector();
        }
        arr[currSize++] = std::move(var);
    }

    void append(const MyVector& oth) {
        for (size_t i=0; i<oth.size(); i++) {
            push_back(oth[i]);
        }
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
        for (size_t i=pos; i<currSize-1; i++) {
            swap(arr[i], arr[i+1]);
        }
        pop_back();
    }

    void clear() {
        while (!empty()) {
            pop_back();
        }
    }

    size_t size() const {
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

    bool empty() const {
        return currSize == 0;
    }

    Type& back() {
        return arr[currSize-1];
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
