#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr {
   public:
    UniquePtr()
        : ptr(nullptr) {};

    explicit UniquePtr(T* pointer) {
        ptr = pointer;
    };
    // explicit 关键字用于防止编译器进行隐式类型转换
    ~UniquePtr() {
        delete ptr;
        ptr = nullptr;
    }

    // 拷贝构造函数不能使用
    UniquePtr(UniquePtr& other) = delete;
    UniquePtr& operator=(UniquePtr& other) = delete;

    // 右值引用 并将原先ptr进入可析构但不可用状态
    UniquePtr(UniquePtr&& other);

    UniquePtr& operator=(UniquePtr&& other) noexcept;

    operator bool() const;
    T* get() const;
    T& operator*() const;
    T* operator->() const;
    void reset();
    void reset(T* new_pointer);
    T* release();

   private:
    T* ptr;
    // Add whatever you want to add.
};

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& other) {
    ptr = other.ptr;
    other.ptr = nullptr;
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept {
    if (this != &other) {
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    return *this;
}

template <typename T>
UniquePtr<T>::operator bool() const {
    return (ptr != nullptr);
}

template <typename T>
T* UniquePtr<T>::get() const {
    return ptr;
};

template <typename T>
T& UniquePtr<T>::operator*() const {
    return *ptr;
};

template <typename T>
T* UniquePtr<T>::operator->() const {
    return ptr;
};

template <typename T>
void UniquePtr<T>::reset() {
    delete ptr;
    ptr = nullptr;
}

template <typename T>
void UniquePtr<T>::reset(T* new_pointer) {
    delete ptr;
    ptr = new_pointer;
}

template <typename T>
T* UniquePtr<T>::release() {
    T* temp = ptr;
    ptr = nullptr;
    return temp;
}

template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    // Args&&通用引用是一个模板语法特性，而非具体的引用类型,可以传入左值或者右值
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
// A tricky question: to implement the make_unique function
// template <?>
//? make_unique(?);

#endif  // UNIQUE_PTR