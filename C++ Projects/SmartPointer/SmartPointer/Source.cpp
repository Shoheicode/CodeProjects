//
//  main.cpp
//  csProj2
//
//  Created by Kristen North on 10/4/23.
//

#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

template <typename T>

class null_ptr_exception : public std::runtime_error { //added exception
public:
    null_ptr_exception() : std::runtime_error("Null Pointer Exception") {}

};

template <typename T>
class smart_ptr {
private:
    T* ptr_;               // pointer to the referred object
    int* ref_;             // pointer to a reference count
public:

    smart_ptr() : ptr_(nullptr), ref_(nullptr) {
    }
    // Create a smart_ptr that is initialized to nullptr. The reference count
    // should be initialized to nullptr.

    explicit smart_ptr(T*& raw_ptr) : ptr_(raw_ptr), ref_(nullptr) {
        if (raw_ptr == NULL) {//if raw ptr is empty set everything to null
            ptr_ = NULL;
            ref_ = NULL;
        }
        try {
            ref_ = new int(1);
            //dynamically allocate reference count to one
        }
        catch (bad_alloc) { //catches if new throws bad alloc
            delete ptr_;//clear ptr data, set to null
            ptr_ = nullptr;
            if (ref_) { //checks if ref holds data
                delete ref_;//clear ref data, set to null
                ref_ = nullptr;
            }
            throw;
        }
    }
    // Create a smart_ptr that is initialized to raw_ptr. The reference count
    // should be one. No change is made to raw_ptr.

    explicit smart_ptr(T*&& raw_ptr) : ptr_(raw_ptr), ref_(nullptr) {
        if (raw_ptr == NULL) {//if raw ptr is empty set everything to null
            ptr_ = NULL;
            ref_ = NULL;
        }
        try {
            ref_ = new int(1);
            //dynamically allocate ref to 1
        }
        catch (bad_alloc) {//catches if new throws bad alloc
            if (ref_) {
                delete ref_;//clear ref data, set to null
                ref_ = nullptr;
            }
            delete raw_ptr;//delete raw ptr if allocation fails
            throw;//rethrow exception
        }
    }
    // Create a smart_ptr that is initialized to raw_ptr. The reference count
    // should be one. If the constructor fails raw_ptr is deleted.

    smart_ptr(const smart_ptr& rhs) noexcept {
        ptr_ = rhs.ptr_; //copy data
        ref_ = rhs.ref_;//copy data
        if (ref_) {
            (*ref_)++; //if ref isn't null, increment ref count
        }
    }
    // Copy construct a pointer from rhs. The reference count should be
    // incremented by one.

    smart_ptr(smart_ptr&& rhs) noexcept {
        ptr_ = rhs.ptr_; //transfers ownership
        rhs.ptr_ = nullptr; //sets previous ptr to null
    }
    // Move construct a pointer from rhs.
  //dont change the reference count

    smart_ptr& operator=(const smart_ptr& rhs) noexcept {
        if (this != &rhs) {//self assign check
            if (ref_) {
                if ((*ref_)-- == 0) {
                    delete ptr_; //clear ptr data
                    delete ref_;//clear ref data
                }
            }
            ptr_ = rhs.ptr_; //stores ptr data
            ref_ = rhs.ref_; //stores ref data
            if (ref_) {
                (*ref_)++; //if ref isn't null, increment ref count
            }
        }
        return *this;//return reference
    }
    // This assignment should make a shallow copy of the right-hand side's
      //just points to right hand sides data
    // pointer data. The reference count should be incremented as appropriate.

    smart_ptr& operator=(smart_ptr&& rhs) noexcept {
        delete[] rhs; //clear rhs data
        ptr_ = rhs.ptr_;//transfers ownership
        rhs.ptr_ = nullptr; //set to null
        return *this;//return reference
    }
    // This move assignment should steal the right-hand side's pointer data.
  //dont change the reference count

    bool clone() {
        if (ptr_ == nullptr || *ref_ == 1) {//check if ptr is null or ref count is one
            return false;//exit function
        }
        T* newPtr = nullptr; //create empty new ptr and new ref (temps)
        int* newRef = nullptr;

        (*ref_)--; //decrement ref count
        newPtr = new T(*ptr_);//dynamically allocate ptr_ to new data (can throw but only one unhandled exception)

        try {
            newRef = new int(1);//dynamically allocate ref count to 1 (can throw if newPtr throws)
        }
        catch (const bad_alloc& e) {//clean up everything to how it was before throw
            delete newPtr; //clear data, set to null
            newPtr = NULL;
            delete newRef;//clear data, set to null
            newRef = NULL;
            (*ref_)++; //restores ref count
            throw; //rethrow exception
        }

        ptr_ = newPtr;//if no throw(s) set to unthrown data
        ref_ = newRef;

        return true;//function ran successfully, exit
    }
    // If the smart_ptr is either nullptr or has a reference count of one, this
    // function will do nothing and return false. 
      //Otherwise, the referred to
    // object's reference count will be decreased and a new deep copy of the
    // object will be created. This new copy will be the object that this
    // smart_ptr points and its reference count will be one.

    int ref_count() const noexcept {
        if (ref_) { //if ref is not null return ref
            return *ref_;
        }
        return 0;//exit function
    }
    // Returns the reference count of the pointed to data.

    T& operator*() {
        if (ptr_ == NULL) { //if ptr_ is null, can't take reference of null
            throw null_ptr_exception<T>();//throw exception and exit function
        }
        return *ptr_; //else return ptr reference
    }
    // The dereference operator shall return a reference to the referred object.
    // Throws null_ptr_exception on invalid access.

    T* operator->() {
        if (ptr_ == NULL) {//if ptr_ is null, ptr_ points to nothing, would be returning nothing
            throw null_ptr_exception<T>();//throw exception and exit function
        }
        return ptr_;
    }
    // The arrow operator shall return the pointer ptr_. Throws null_ptr_exception
    // on invalid access.

    ~smart_ptr() {//
        if (ref_ != nullptr && (*ref_)-- == 0) { //keep deleting until ref is null and next decrement of ref count is 0
            delete ptr_; //clear dynamic memory of ptr and ref
            delete ref_;
        }
    }          // deallocate all dynamic memory
};


//int main() {
//    try {
//        int* p{ new int { 42 } };
//        smart_ptr<int> sp1{ p };
//
//        cout << "Ref count is " << sp1.ref_count() << endl;    // Ref Count is 1
//        {
//            smart_ptr<int> sp2{ sp1 };
//            cout << "Ref count is " << sp1.ref_count() << endl;    // Ref Count is 2
//            cout << "Ref count is " << sp2.ref_count() << endl;    // Ref Count is 2
//        }
//        cout << "Ref count is " << sp1.ref_count() << endl;    // Ref Count is 1
//
//        smart_ptr<int> sp3;
//
//        cout << "Ref count is " << sp3.ref_count() << endl;    // Ref Count is 0
//
//        sp3 = sp1;
//
//        cout << "Ref count is " << sp1.ref_count() << endl;    // Ref Count is 2
//        cout << "Ref count is " << sp3.ref_count() << endl;    // Ref Count is 2
//
//        smart_ptr<int> sp4{ std::move(sp1) };
//
//        cout << *sp4 << " " << *sp3 << endl;        // prints 42 42
//        cout << *sp1 << endl;                       // throws null_ptr_exception
//    }
//    catch (null_ptr_exception<int>) {
//        cout << "null ptr caught" << endl;
//    }
//}
//
