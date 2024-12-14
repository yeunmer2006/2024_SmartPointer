#include <iostream>
#include <thread>
#include <vector>
#include "./SmartPointer/weak_ptr.hpp"

struct TestStruct {
    int data;
    TestStruct(int d)
        : data(d) {
        std::cout << "Constructing TestStruct with data: " << data << std::endl;
    }
    ~TestStruct() {
        std::cout << "Destructing TestStruct with data: " << data << std::endl;
    }
};

void test_basic() {
    std::cout << "\n=== Test Basic SharedPtr and WeakPtr ===\n";
    SharedPtr<TestStruct> sp1(new TestStruct(10));
    {
        SharedPtr<TestStruct> sp2 = sp1;  // Copy construction
        WeakPtr<TestStruct> wp = sp1;     // Create a WeakPtr
        std::cout << "Shared count: " << sp1.use_count() << "\n";
        std::cout << "Weak count: " << wp.use_count() << "\n";

        SharedPtr<TestStruct> sp3 = wp.lock();  // Lock the WeakPtr
        std::cout << "Locked WeakPtr. Shared count: " << sp3.use_count() << "\n";
    }
    std::cout << "Out of scope. Shared count: " << sp1.use_count() << "\n";
}

void test_nested_pointers() {
    std::cout << "\n=== Test Nested Pointers ===\n";
    struct Node {
        SharedPtr<Node> next;
        WeakPtr<Node> prev;
        int value;
        Node(int val)
            : value(val) {
            std::cout << "Constructing Node with value: " << value << std::endl;
        }
        ~Node() {
            std::cout << "Destructing Node with value: " << value << std::endl;
        }
    };

    SharedPtr<Node> node1(new Node(1));
    SharedPtr<Node> node2(new Node(2));

    node1->next = node2;
    node2->prev = node1;

    std::cout << "Node1 use count: " << node1.use_count() << "\n";
    std::cout << "Node2 use count: " << node2.use_count() << "\n";

    node1.reset();
    std::cout << "After resetting Node1. Node2 use count: " << node2.use_count() << "\n";
    node2.reset();
    std::cout << "After resetting Node2.\n";
}

void test_multithreaded() {
    std::cout << "\n=== Test Multithreaded Use ===\n";

    SharedPtr<TestStruct> sp(new TestStruct(42));
    auto thread_func = [](SharedPtr<TestStruct> local_sp) {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Thread ID: " << std::this_thread::get_id() << ", data: " << local_sp->data << "\n";
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(thread_func, sp);
    }
    for (auto& th : threads) {
        th.join();
    }
    std::cout << "Multithreaded test complete. Shared count: " << sp.use_count() << "\n";
}

void test_complex_reset_and_assignment() {
    std::cout << "\n=== Test Complex Reset and Assignment ===\n";

    SharedPtr<TestStruct> sp1(new TestStruct(1));
    SharedPtr<TestStruct> sp2(new TestStruct(2));
    WeakPtr<TestStruct> wp = sp1;

    std::cout << "Before reset:\n";
    std::cout << "sp1 use count: " << sp1.use_count() << "\n";
    std::cout << "sp2 use count: " << sp2.use_count() << "\n";

    sp1.reset(new TestStruct(3));  // Reset sp1
    std::cout << "After sp1 reset:\n";
    std::cout << "sp1 use count: " << sp1.use_count() << "\n";

    sp2 = sp1;  // Assign sp1 to sp2
    std::cout << "After sp2 assignment:\n";
    std::cout << "sp2 use count: " << sp2.use_count() << "\n";

    wp = sp2;                               // Assign sp2 to wp
    SharedPtr<TestStruct> sp3 = wp.lock();  // Lock wp
    std::cout << "After locking wp:\n";
    std::cout << "sp3 use count: " << sp3.use_count() << "\n";

    sp1.reset();  // Reset sp1
    std::cout << "After resetting sp1:\n";
    std::cout << "sp2 use count: " << sp2.use_count() << "\n";
}

int main() {
    test_basic();
    test_nested_pointers();
    test_multithreaded();
    test_complex_reset_and_assignment();

    return 0;
}
