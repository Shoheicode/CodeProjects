#include <iostream>

using namespace std;

class null_ptr_exception : public runtime_error {
public:
    null_ptr_exception(char str[]) : runtime_error(str) {
    }
};

template <typename T> 
class smart_ptr {
public:
    smart_ptr() : ptr_(NULL), ref_(NULL) {

    }
    // Create a smart_ptr that is initialized to nullptr. The reference count
    // should be initialized to nullptr.

    explicit smart_ptr(T*& raw_ptr) {
        if (raw_ptr == NULL) {
            ptr_ = NULL;
            ref_ = NULL;
        }
        else {
            try {
                ptr_ = raw_ptr;
                ref_ = new int(1);
            }
            catch (bad_alloc) {
                delete ptr_; // deletes the ptr
                ptr_ = NULL; // assigns ptr to NULL
                if (ref_ != NULL) { //If the reference count somehow has a value
                    delete ref_; // delete the reference and set ref_ to NULL
                    ref_ = NULL;
                }
                throw;
            }
        }
    }
    // Create a smart_ptr that is initialized to raw_ptr. The reference count
    // should be one. No change is made to raw_ptr.

    explicit smart_ptr(T*&& raw_ptr) {
        if (raw_ptr == NULL) { // If the raw ptr is NULL, then set the values to NULL
            ptr_ = NULL;
            ref_ = NULL;
        }
        else {
            try {
                ptr_ = raw_ptr;
                ref_ = new int(1);
            }
            catch (bad_alloc) {
                if (ref_ != NULL) { //If the reference count somehow has a value
                    delete ref_; // delete the reference and set ref_ to NULL
                    ref_ = NULL;
                }
                delete raw_ptr;
                throw;
            }
        }
    }
    // Create a smart_ptr that is initialized to raw_ptr. The reference count
    // should be one. If the constructor fails raw_ptr is deleted.	

    smart_ptr(const smart_ptr& rhs) noexcept{
        if (rhs.ptr_ != NULL) { // If the RHS pointer does not eqaul NULL, set this values equal to RHS
            ptr_ = rhs.ptr_;
            ref_ = rhs.ref_;
            (*ref_)++; // incrememnt by 1
        }
        else { // Otherwise, set the pointers to null
            ptr_ = NULL;
            ref_ = NULL;
        }
    }
    // Copy construct a pointer from rhs. The reference count should be 
    // incremented by one.

    smart_ptr(smart_ptr&& rhs) noexcept{
        if (rhs.ptr_ != NULL) { // If the RHS pointer does not eqaul NULL, set this values equal to RHS
            ptr_ = rhs.ptr_; // This moves the ownership of the data to ptr and ref_
            rhs.ptr_ = NULL; // set RHS pointer to NULL
        }
        else { // Otherwise, set the pointers to null
            ptr_ = NULL;
            ref_ = NULL;
        }

    }
    // Move construct a pointer from rhs.

    smart_ptr& operator=(const smart_ptr& rhs) noexcept{
        if (rhs.ptr_ != NULL) { //If the right hand reference ptr does not equal NULL
            if (ptr_ != NULL) { // If the current pointer exists
                if (*ref_ == 1) { // If the reference value equals 1, then delete both the ptr and the reference
                    delete ptr_;
                    delete ref_;
                }
                else { // Otherwise, deincrement the reference count
                    (*ref_)--;
                }
            }
            ptr_ = rhs.ptr_; // Make a shallow copy of the right hand side pointer data
            ref_ = rhs.ref_; // Make a shallow copy of the right hand side reference data
            (*ref_)++; // Increment the reference count
        }
        else { //If the right hand reference ptr does equal NULL
            ptr_ = NULL; // Set the pointer data to NULL
            ref_ = NULL; // Set the reference data to NULL
        }

        return *this;

    }
    // This assignment should make a shallow copy of the right-hand side's
    // pointer data. The reference count should be incremented as appropriate.

    smart_ptr& operator=(smart_ptr&& rhs) noexcept{
        if (rhs.ptr_ != NULL) { //If the right hand side pointer does not equal NULL
            ptr_ = rhs.ptr_;
            rhs.ptr_ = NULL;
            delete rhs.ptr_;// Delete the information from rhs
            delete rhs.ref_;
        }
        else { //Otherwise if the right hand pointer equals NULL, then set the pointer and reference count to NULL
            ptr_ = NULL; 
            ref_ = NULL;
        }

        return *this;

    }
    // This move assignment should steal the right-hand side's pointer data.

    bool clone() {
        if (ptr_ == NULL || *ref_ == 1) {
            return false;
        }
        else {
            T* temp = NULL;
            int* temp1 = NULL;

            temp = new T(*ptr_); //Creates a new pointer for the smart pointer (Clones the pointer)
            try {
                (*ref_)--; //Decreases the Reference Value
                temp1 = new int(1);
            }
            catch (bad_alloc) {
                delete temp; //Delete the temporary data
                temp = NULL; // Set the temps to NULL

                delete temp1;
                temp1 = NULL;

                (*ref_)++; // Increases the reference count if reference count throws an exception.
           
                throw;
                 
            }

            ptr_ = temp;
            ref_ = temp1;

            return true;
        }
    }
    // If the smart_ptr is either nullptr or has a reference count of one, this
    // function will do nothing and return false. Otherwise, the referred to
    // object's reference count will be decreased and a new deep copy of the
    // object will be created. This new copy will be the object that this
    // smart_ptr points and its reference count will be one. 

    int ref_count() const noexcept{
        if (ref_ == NULL) {
            return 0;
        }
        return (*ref_);
    }
    // Returns the reference count of the pointed to data.

    T& operator*() {
        if (ptr_ == NULL) {
            char message[] = "null_ptr_exception";
            throw null_ptr_exception(message);
        }
        return *ptr_;
    }
    // The dereference operator shall return a reference to the referred object.
    // Throws null_ptr_exception on invalid access. 

    T* operator->() {
        if (ptr_ == NULL) {
            char message[] = "null_ptr_exception";
            throw null_ptr_exception(message);
        }
        return ptr_;
    }
    // The arrow operator shall return the pointer ptr_. Throws null_ptr_exception
    // on invalid access.

    ~smart_ptr() {
        if (ref_ != NULL) { // If the reference ptr is not null, decrease the reference value
            (*ref_)--;
        }
        if (ref_ != NULL && *ref_ == 0) { // If the reference ptr exists and reference equals 0
            delete ptr_; //delete data
            delete ref_;
        }
    }
    // deallocate all dynamic memory

private:
    T* ptr_;               // pointer to the referred object
    int* ref_;             // pointer to a reference count
};

int main() {
    try {
        int* p{ new int { 42 } };
        smart_ptr<int> sp1{ p };

        cout << "Ref count is " << sp1.ref_count() << endl;	// Ref Count is 1

        {
            smart_ptr<int> sp2{ sp1 };
            cout << "Ref count is " << sp1.ref_count() << endl;	// Ref Count is 2
            cout << "Ref count is " << sp2.ref_count() << endl;	// Ref Count is 2
        }

        cout << "Ref count is " << sp1.ref_count() << endl;	// Ref Count is 1

        smart_ptr<int> sp3;

        cout << "Ref count is " << sp3.ref_count() << endl;	// Ref Count is 0

        sp3 = sp1;

        smart_ptr<int> sp5 = sp1;

        cout << "Second Ref count is for sp5: " << sp5.ref_count() << endl; // Should be 3
        cout << "Value for sp5: " << *sp5 << endl;
        //cout << "Secound Ref count is for sp6: " << sp6.ref_count() << endl; //Should be 1
        //cout << "Value for sp6: " << *sp6 << endl;
        cout << "Ref count is for sp1: " << sp1.ref_count() << endl;

        sp5 = smart_ptr<int>(new int(1));

        cout << "Second Ref count is for sp5: " << sp5.ref_count() << endl; // Should be 3
        cout << "Value for sp5: " << *sp5 << endl;
        //cout << "Secound Ref count is for sp6: " << sp6.ref_count() << endl; //Should be 1
        //cout << "Value for sp6: " << *sp6 << endl;
        cout << "Ref count is for sp1: " << sp1.ref_count() << endl;
        //smart_ptr<int> sp6{ std::move(sp5)};

        cout << "Ref count is " << sp1.ref_count() << endl;	// Ref Count is 2
        cout << "Ref count is " << sp3.ref_count() << endl;	// Ref Count is 2

        smart_ptr<int> sp4{ std::move(sp1) };

        

        cout << *sp4 << " " << *sp3 << endl;        // prints 42 42
        cout << "HIII" << endl;
        cout << *sp1 << endl;                       // throws null_ptr_exception
    }
    catch (null_ptr_exception& e) {
        cout << e.what() << endl;
    }

    struct Point { int x = 2; int y = -5; };

    smart_ptr<Point> sp{ new Point };
    cout << sp->x << " " << sp->y << endl;   // prints 2 -5

    smart_ptr<double> dsp1{ new double {3.14} };
    smart_ptr<double> dsp2, dsp3;

    dsp3 = dsp2 = dsp1;

    cout << "FIRST PART" << endl;
    cout << dsp1.ref_count() << " " << dsp2.ref_count() << " " << dsp3.ref_count() << endl;
    // prints 3 3 3

    cout << "Second Part" << endl;
    cout << *dsp1 << " " << *dsp2 << " " << *dsp3 << endl;
    //prints 3.14 3.14 3.14

    dsp1.clone();        // returns true

    cout << dsp1.ref_count() << " " << dsp2.ref_count() << " " << dsp3.ref_count() << endl;
    // prints 1 2 2
    cout << *dsp1 << " " << *dsp2 << " " << *dsp3 << endl;
    // prints 3.14 3.14 3.14

}