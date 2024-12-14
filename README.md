# 2024_SmartPointer
Big Homework 3rd in SJTU 2024

### 作业说明
依照C++ STL 中 智能指针的实现 仿写实现了 unique_ptr shared_ptr weak_ptr

> Thanks to wty500 and JohnClass2023 who provides a framework for project ideas

## 下面是具体使用方法
</br>

# UniquePtr Class
Define a template class named `UniquePtr` and add the following functions to the class.

This class should use a member variable called `T* _p` (T is a template argument) to store a given pointer.

- **Constructor**
Implement a constructor for your class so the below code would work. Your constructor should be able to store the given dynamic pointer properly inside the class using `_p` variable.

	```cpp
	UniquePtr<int> ptr{new int{10}};
	```

- **make_unique** (outside the class)
The prefered way to construct a  std::unique_ptr is to use a function called `std::make_unique`. implement a similar function and make this code work:

	```cpp
	UniquePtr<int> ptr{make_unique<int>(10)};
 	UniquePtr<std::vector<int>> ptr2{make_unique<std::vector<int>>(2,3)};
	```
	**Be careful: Both l_values and r_values can be passed into this function.**

- **Default Constructor**
Implement a default constructor for your class so the below code works and assign `nullptr` to `_p`.

	```cpp
	UniquePtr<int> ptr;
	```
- **Destructor**
As you know when dealing a with dynamic pointer in a class, implementing destructor is a neccessaty so implement a proper destructor and delete your dynamic pointer (*hint:* assign `nullptr` after deletion).

	```cpp
	~UniquePtr()
	```
- **Copy Constructor**
As you already know you cannot copy a UniquePtr, make arrangements so the following code would cause a compile error.

	```cpp
	UniquePtr<int> ptr1{new int{10}};
	UniquePtr<int> ptr2{ptr1};
	```

- **Operator=**
Exactly like the previous section we should not be able to write the following code as well. Make the compiler to produce an error for this code.

	```cpp
	UniquePtr<int> ptr1{new int{10}};
	UniquePtr<int> ptr2{new int{11}};
	ptr2 = ptr1;
	```
- **get**
The get() function should return the raw pointer stored in the class.

	```cpp
	UniquePtr<int> ptr{new int{10}};
	std::cout << ptr.get() << std::endl; // output: raw pointer stored in the class
	```
- **Operator***
Smart pointers should be able to be dereferenced exactly like raw pointers. make this code work:

	```cpp
	UniquePtr<int> ptr{new int{10}};
	std::cout << *ptr << std::endl; // output: 10
	```
- **Operator->**
Smart pointers can use the arrow operator like normal pointers. make this code work as well:

	```cpp
	UniquePtr<std::string> ptr{new std::string{"hello"}};
	std::cout << ptr->length() << std::endl; // output: 5
	```

- **reset**
The reset() function will delete the pointer and assign `nullptr` to it:

	```cpp
	void reset();
	```

- **reset**
The reset() function can have a input and make a new pointer with it after deleting the old pointer:

	```cpp
	UniquePtr<std::string> ptr{new std::string{"hello"}};
    ptr.reset(new std::string{"nice"});
	std::cout << *ptr << std::endl; // output: nice
	```
- **release**
The release() function returns the stored pointer in the class (like get) with two differences: The UniquePtr class won't store  the pointer anymore and also deleting the pointer should **not** be done by UniquePtr class after calling release().

	```cpp
	UniquePtr<double> ptr{new double{1.567}};
    double *tmp{ptr.release()};
	std::cout << *tmp << std::endl; // output: 1.567
    delete tmp; // manual deletion
	```


</br>

# SharedPtr Class
Define a template class named `SharedPtr` and add the following functions to the class.

This class should use a member variable called `T* _p` (T is a template argument) to store a given pointer.


- **Constructor**
Implement a constructor for your class so the below code would work. Your constructor should be able to store the given dynamic pointer properly inside the class using `_p` variable.

	```cpp
	SharedPtr<int> ptr{new int{10}};
	```

- **make_shared** (outside the class)
The prefered way to construct a  std::shared_ptr is to use a function called `std::make_shared`. implement a similar function and make the code below work.

	```cpp
	SharedPtr<int> ptr{make_shared<int>(10)};
	```
 	**Be careful: Both l_values and r_values can be passed into this function.**

- **Default Constructor**
Implement a default constructor for your class so the below code works and assign nullptr to `_p`.

	```cpp
	SharedPtr<int> ptr;
	```
- **Destructor**
As you know when dealing with dynamic pointers inside a class implementing destructor is a neccessaty so implement a proper destructor and delete your dynamic pointers (do not forget to assign `nullptr` after deletion).

	```cpp
	~SharedPtr()
	```

- **Copy Constructor**
As you already know A key difference between `SharedPtr` and `UniquePtr` classes is that we can use copy constrctor and make a copy of `SharedPtr`s. so the code below should run smoothly.

	```cpp
	SharedPtr<int> ptr1{new int{10}};
	SharedPtr<int> ptr2{ptr1};
	```

- **Operator=**
Exactly like the previous section we can have operator= for `SharedPtr`s. again the code below should run without any errors.

	```cpp
	SharedPtr<int> ptr1{new int{10}};
	SharedPtr<int> ptr2{new int{11}};
	ptr2 = ptr1;
	```

- **use_count**
In `SharedPtr`s we should have the ability to count the number of instances pointing to a same place. to do this you have to define another member variabel for your `SharedPtr` class and keep track of this number.

	**note.** you may have to make some adjusments in the previous functions (such as constructor and ...) to do this.

	```cpp
	SharedPtr<int> ptr1{make_shared<int>(10)};
	std::cout << ptr1.use_count() << std::endl; // output: 1
    SharedPtr<int> ptr2{ptr1};
	std::cout << ptr1.use_count() << std::endl; // output: 2
	std::cout << ptr2.use_count() << std::endl; // output: 2
	```

- **get**
The get() function should return the raw pointer stored in the class.

	```cpp
	SharedPtr<int> ptr{new int{10}};
	std::cout << ptr.get() << std::endl; // output: raw pointer of the class
	```
- **Operator***
Smart pointers should be able to be dereferenced exactly like raw pointers. make this code work:

	```cpp
	SharedPtr<int> ptr{new int{10}};
	std::cout << *ptr << std::endl; // output: 10
	```
- **Operator->**
Smart pointers can use the arrow operator like raw pointers. make this code work:

	```cpp
	SharedPtr<std::string> ptr{new std::string{"hello"}};
	std::cout << ptr->length() << std::endl; // output: 5
	```

- **reset**
The reset() function will delete the pointer and assigns `nullptr` to it:

	```cpp
	void reset();
	```

- **reset**
The reset() function can have a input and make a new pointer with it after deleting the old pointer:

	```cpp
	SharedPtr<std::string> ptr{new std::string{"hello"}};
    ptr.reset(new std::string{"nice"});
	std::cout << *ptr << std::endl; // output: nice
	```

</br> 

# WeakPtr Class

Define a template class named `WeakPtr` and add the following functions to the class.

This class works in conjunction with the `SharedPtr` class to help break potential circular references. Unlike `SharedPtr`, a `WeakPtr` does not own the object it points to - it tracks an object owned by one or more `SharedPtr` instances.

## Required Functions

- **Constructor**
  Implement a constructor that takes a `SharedPtr` as its argument. The `WeakPtr` will track the object owned by the `SharedPtr` without increasing its reference count.

    ```cpp
  SharedPtr<int> sp{new int{10}};
  WeakPtr<int> wp{sp};
    ```

- **Default Constructor**
  Implement a default constructor that creates an empty `WeakPtr`.

    ```cpp
  WeakPtr<int> wp;
    ```

- **Copy Constructor**
  Implement a copy constructor that creates a `WeakPtr` from another `WeakPtr`.

    ```cpp
  WeakPtr<int> wp1{sp};
  WeakPtr<int> wp2{wp1};
    ```

- **Move Constructor**
  Implement a move constructor that transfers ownership from another `WeakPtr`.

    ```cpp
  WeakPtr<int> wp1{sp};
  WeakPtr<int> wp2{std::move(wp1)};
    ```

- **Copy Assignment Operator**
  Allow assigning from another `WeakPtr` or from a `SharedPtr`.

    ```cpp
  WeakPtr<int> wp1, wp2;
  SharedPtr<int> sp{new int{10}};
  wp1 = sp;
  wp2 = wp1;
    ```

- **Move Assignment Operator**
  Implement move assignment that transfers ownership from another `WeakPtr`.

    ```cpp
  WeakPtr<int> wp1{sp}, wp2;
  wp2 = std::move(wp1);
    ```

- **Destructor**
  Implement a destructor that properly cleans up the weak reference.

    ```cpp
  ~WeakPtr()
    ```

- **lock**
  The lock() function attempts to convert the `WeakPtr` to a `SharedPtr`. If the object has been deleted, it returns an empty `SharedPtr`.

    ```cpp
  WeakPtr<int> wp{sp};
  SharedPtr<int> sp2 = wp.lock();
  if(sp2) {
      std::cout << *sp2 << std::endl;  // Use the object safely
  }
    ```

- **expired**
  The expired() function checks if the object being pointed to has been deleted.

    ```cpp
  WeakPtr<int> wp{sp};
  if(!wp.expired()) {
      SharedPtr<int> sp2 = wp.lock();
      // Use sp2...
  }
    ```

- **use_count**
  Returns the number of `SharedPtr` instances that share ownership of the object.

    ```cpp
  SharedPtr<int> sp1{new int{10}};
  SharedPtr<int> sp2{sp1};
  WeakPtr<int> wp{sp1};
  std::cout << wp.use_count() << std::endl;  // output: 2
    ```

- **reset**
  The reset() function releases the reference to the managed object.

    ```cpp
  WeakPtr<int> wp{sp};
  wp.reset();  // wp no longer references anything
    ```

- **swap**
  Swaps the contents of two `WeakPtr` objects.

    ```cpp
  WeakPtr<int> wp1{sp1}, wp2{sp2};
  wp1.swap(wp2);  // wp1 now watches sp2's object, wp2 watches sp1's
    ```

## Notes on Implementation

1. A `WeakPtr` should not affect the reference count used by `SharedPtr` for deletion.
2. `WeakPtr` should work with the control block used by `SharedPtr` to track both strong and weak references.
3. The `WeakPtr` should become expired when the last `SharedPtr` to its object is destroyed.
4. All member functions should be exception-safe.
5. Move operations should be marked as noexcept.

## Example Usage

Here's a typical use case showing how `WeakPtr` can break circular references:

```cpp
struct Node {
    SharedPtr<Node> next;
    WeakPtr<Node> prev;  // Using WeakPtr instead of SharedPtr
};

SharedPtr<Node> node1{new Node};
SharedPtr<Node> node2{new Node};

node1->next = node2;
node2->prev = node1;  // No circular reference!
```


Acknowledgement : Amirkabir University of Technology 1400-2 —— Advanced Programming Course Project 4 'Smart Pointers'   