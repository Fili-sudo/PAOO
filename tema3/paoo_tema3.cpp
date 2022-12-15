#include <iostream>
#include <memory> // for std::shared_ptr
#include <string>


//Item 13
class Dog {
public:
  // constructor that takes ownership of a string
  Dog(std::shared_ptr<std::string> sound) : sound_(sound) {}

  // bark method that uses the string resource
  void bark() const {
    std::cout << *sound_ << std::endl;
  }

private:
  std::shared_ptr<std::string> sound_;
};

class Cat {
public:
  // constructor that takes ownership of a string
  Cat(std::auto_ptr<std::string> sound) : sound_(sound) {}

  // meow method that uses the string resource
  void meow() const {
    std::cout << *sound_ << std::endl;
  }

private:
  std::auto_ptr<std::string> sound_;
};


//Item 14
template <typename T>
class RCWrapper
{
public:
    RCWrapper(T *ptr) : ptr_(ptr), ref_count_(new int(1)) {}

    // copy constructor
    RCWrapper(const RCWrapper& other)
        : ptr_(other.ptr_), ref_count_(other.ref_count_)
    {
        ++(*ref_count_);
    }

    // assignment operator
    RCWrapper& operator=(const RCWrapper& other)
    {
        if (this != &other)
        {
            // decrement the reference count of the current object
            if (--(*ref_count_) == 0)
            {
                delete ptr_;
                delete ref_count_;
            }

            // copy the data from the other object
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;

            // increment the reference count
            ++(*ref_count_);
        }
        return *this;
    }

    // destructor
    ~RCWrapper()
    {
        // decrement the reference count and free the underlying resource
        // if no other objects are using it
        if (--(*ref_count_) == 0)
        {
            delete ptr_;
            delete ref_count_;
        }
    }

    T* get(){
        return ptr_;
    }

    int *get_ref_count(){
        return ref_count_;
    }

private:
    T *ptr_;
    int *ref_count_;
};


int main() {
  // create a string resource that is shared by multiple Dog objects
  std::shared_ptr<std::string> shared_sound(new std::string("bark"));

  // create two Dog objects that share the same string resource
  Dog dog1(shared_sound);
  Dog dog2(shared_sound);

  // have the dogs bark
  dog1.bark();
  dog2.bark();

  // when all the dogs go out of scope, the string is automatically freed

  std::auto_ptr<std::string> cat_sound(new std::string("meow"));

  // create a Cat object that owns the string resource
  Cat cat(cat_sound);

  // have the cat meow
  cat.meow();

  // when the cat goes out of scope, the string is automatically freed


  // create a new RCWrapper object that manages a dynamically allocated string
  RCWrapper<std::string> wrapper(new std::string("hello world"));

  // create a new object that is a copy of the first one
  RCWrapper<std::string> wrapper2 = wrapper;   

  // create another object using the copy constructor
  RCWrapper<std::string> wrapper3(wrapper);    
  // assign the first object to the third object
  wrapper = wrapper3;  
  // print the underlying string managed by the first object
  std::cout << *(wrapper.get()) << std::endl;
  std::cout << *(wrapper.get_ref_count()) << std::endl;

  return 0;
}