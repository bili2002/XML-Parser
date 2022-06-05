#pragma once

template <typename Type>
class MyPointer {
private:
    Type* ptr = nullptr;

public:
    ~MyPointer() {
        if (ptr != nullptr) 
            delete ptr;
    }
    
    MyPointer() : ptr(nullptr) {};

    MyPointer(Type* ptr) : ptr(ptr) {}; 

    MyPointer(const MyPointer& oth) = delete;

    MyPointer& operator=(const MyPointer& oth) = delete;

    MyPointer& operator=(MyPointer&& oth) {
        delete ptr;
        ptr = oth.ptr;
        oth.ptr = nullptr;

        return *this;
    }

    Type& operator*() const {
        return *ptr;
    }

    Type* operator->() const {
        return ptr;
    }
};
