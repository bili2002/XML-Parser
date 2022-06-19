#pragma once

template <typename Type>
class MyPointer {
private:
    Type* ptr = nullptr;

public:
    ~MyPointer() {
        if (ptr != nullptr) {
            delete ptr;
        }
    }
    
    MyPointer() : ptr(nullptr) {}
    MyPointer(Type* ptr) : ptr(ptr) {}
    MyPointer(const MyPointer& oth) = delete;
    MyPointer& operator=(const MyPointer& oth) = delete;

    MyPointer(MyPointer&& oth) {
		this->ptr = oth.ptr;
		oth.ptr = nullptr; 
	}

    MyPointer& operator=(MyPointer&& oth) {
        this->~MyPointer();
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

    static void swap(MyPointer& a, MyPointer& b) {
        MyPointer temp;
        temp.ptr = a.ptr;
        a.ptr = b.ptr;
        b.ptr = temp.ptr;
    }

    Type& get() {
        return *ptr;
    }

    Type* getPtr() {
        return &get();
    }
};
