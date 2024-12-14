#include <cstdio>
#include <iostream>
using namespace std;
// #include "shared_ptr.h"
#include "unique_ptr.hpp"
#include "weak_ptr.hpp"
bool TEST() {
    // Test weak_ptr assignment and lock
    SharedPtr<std::string> sp1{new std::string{"Hello"}};
    WeakPtr<std::string> wp1(sp1);
    WeakPtr<std::string> wp2 = wp1;
    SharedPtr<std::string> sp2 = wp1.lock();
    if (!sp2 || *sp2 != "Hello" || wp1.use_count() != 2) {
        return false;
    }

    sp1.reset();
    sp2.reset();
    // cout << wp1.expired() << "\n";
    if (!wp1.expired() || !wp2.expired()) {
        return false;
    }
    wp1.reset();
    wp2.reset();
    return true;
}

int main() {
    // cout << TEST() << "\n";

    SharedPtr<int> c(new int{100});
    SharedPtr<int> b = c;
    SharedPtr<int> a = b;
    cout << *a;
    return 0;
}