#ifndef WEAK_PTR
#define WEAK_PTR
#include <cstddef>
#include <utility>
#include "shared_ptr.hpp"  // Include SharedPtr definition
// When submitting to ACMOJ, please replace this with the content inside shared_ptr.h

template <typename T>
class WeakPtr {
   public:
    WeakPtr();  // 默认构造函数

    WeakPtr(const WeakPtr& other);  // 拷贝构造Copy constructor

    WeakPtr(WeakPtr&& other) noexcept;  // 移动构造Move constructor

    WeakPtr(const SharedPtr<T>& other) noexcept;  // 从shared构造

    ~WeakPtr();

    WeakPtr& operator=(const WeakPtr& other) noexcept;  // Copy assignment

    WeakPtr& operator=(WeakPtr&& other) noexcept;  // Move assignment

    WeakPtr& operator=(const SharedPtr<T>& other) noexcept;  // SharedPtr assignment

    void reset();  // Reset to empty state

    size_t use_count() const;  // 得到多少共享

    bool expired() const;  // 检查是否失效

    SharedPtr<T> lock() const noexcept;  // 得到一个shareptr 此时计数器加一

    // Utility functions
    void swap(WeakPtr& other) noexcept;

   private:
    T* ptr;
    size_t* weak_cnt;
    size_t* shared_cnt;
    friend class SharedPtr<T>;  // 允许SharePtr对weak进行修改和访问
};

template <typename T>
WeakPtr<T>::WeakPtr()
    : ptr(nullptr), weak_cnt(nullptr), shared_cnt(nullptr) {}

template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr& other)
    : ptr(other.ptr), weak_cnt(other.weak_cnt), shared_cnt(other.shared_cnt) {
    if (weak_cnt) {
        (*weak_cnt)++;
    }
}

template <typename T>
WeakPtr<T>::WeakPtr(WeakPtr&& other) noexcept
    : ptr(other.ptr), weak_cnt(other.weak_cnt), shared_cnt(other.shared_cnt) {
    other.ptr = nullptr;
    other.weak_cnt = nullptr;
    other.shared_cnt = nullptr;
}

template <typename T>
WeakPtr<T>::WeakPtr(const SharedPtr<T>& other) noexcept
    : ptr(other.ptr), weak_cnt(other.weak_cnt), shared_cnt(other.shared_cnt) {
    if (weak_cnt) {
        (*weak_cnt)++;
    }
}

// Destructor
template <typename T>
WeakPtr<T>::~WeakPtr() {
    reset();
}

// Assignment operators
template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr& other) noexcept {
    if (this == &other) {
        return *this;
    }
    reset();
    ptr = other.ptr;
    weak_cnt = other.weak_cnt;
    shared_cnt = other.shared_cnt;
    if (weak_cnt) {
        (*weak_cnt)++;
    }
    return *this;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    reset();
    ptr = other.ptr;
    weak_cnt = other.weak_cnt;
    shared_cnt = other.shared_cnt;
    other.ptr = nullptr;
    other.weak_cnt = nullptr;
    other.shared_cnt = nullptr;
    return *this;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const SharedPtr<T>& other) noexcept {
    if ((weak_cnt != other.weak_cnt) && (shared_cnt != other.shared_cnt)) {
        reset();
        ptr = other.ptr;
        weak_cnt = other.weak_cnt;
        shared_cnt = other.shared_cnt;
        if (weak_cnt) {
            (*weak_cnt)++;
        }
    }
    return *this;
}

// Basic operations
template <typename T>
void WeakPtr<T>::reset() {
    if (weak_cnt && (*weak_cnt)) {
        (*weak_cnt)--;
        if (((*weak_cnt) == 0) && shared_cnt && ((*shared_cnt) == 0)) {
            delete weak_cnt;
            delete shared_cnt;
        }
    }
    ptr = nullptr;
    weak_cnt = nullptr;
    shared_cnt = nullptr;
}

template <typename T>
size_t WeakPtr<T>::use_count() const {
    return shared_cnt ? (*shared_cnt) : 0;
}

template <typename T>
bool WeakPtr<T>::expired() const {
    return (use_count() == 0);
}

template <typename T>
SharedPtr<T> WeakPtr<T>::lock() const noexcept {
    if (shared_cnt && (*shared_cnt > 0)) {
        return SharedPtr<T>(*this);
    }
    return SharedPtr<T>();
}

template <typename T>
void WeakPtr<T>::swap(WeakPtr<T>& other) noexcept {
    std::swap(ptr, other.ptr);
    std::swap(shared_cnt, other.shared_cnt);
    std::swap(weak_cnt, other.weak_cnt);
};  // Swap with another WeakPtr

template <typename T>
void swap(WeakPtr<T>& lhs, WeakPtr<T>& rhs) noexcept {
    lhs.swap(rhs);
}

#endif  // WEAK_PTR