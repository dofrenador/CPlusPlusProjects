#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>
#include <cstddef>
#include <stdexcept>

using namespace std;

template <class T>
class Stack {

    private:
        /* array keeping the items of the stack */
        T* items;
        /* number of items in the stack */
        size_t size;
        /* capacity of the stack */
        size_t capacity;

    public:
        /*** Do not modify the interface ***/

        /* Creates a stack of given "capacity"
           defult is 8 items
           */
        Stack(int capacity=8);

        /* Copy constructor, Assignment operator, Destructor*/
        Stack(const Stack<T>& stack);
        Stack<T>& operator=(const Stack<T>& stack);
        ~Stack();

        /* pushes the "item" to the top of the stack
           increases the capacity as needed
           doubles the capacity when full
           */
        void push(const T& item);
        /* pops the item at the top of the stack and returns
           decreases the capacity when needed
           halves the capacity when less then 1/3 full
           */
        T pop();
        /* returns the item at the top of the stack witout modifiying the stack
           (take a look at the top item)
           */
        const T& top() const;
        /* clears the contents of the stack */
        void clear();
        /* returns true if the stack is empty, false otherwise */
        bool isEmpty() const;
        /* returns the number of items in the stack */
        size_t getSize() const;
        /* returns the capacity the stack */
        size_t getCapacity() const;
        /* prints the contents of the stack
           from top to bottom, one item per line
           assumes the objects in the stack have operator<< overloaded
           */
        void print() const;
        /* prints the contents of the stack
           from bottom to top, one item per line
           assumes the objects in the stack have operator<< overloaded
           */
        void printReversed() const;

};


template <class T>
Stack<T>::Stack(int capacity) {
    this->capacity=capacity;
    items= new T[capacity];
    size=0;
}

//done
template <class T>
Stack<T>::Stack(const Stack<T>& stack){
    size = stack.size;
    capacity=stack.capacity;

    items = new T[capacity];

    for (int i = 0; i < size; i++) {
        items[i]=stack.items[i];
    }

}
//done
template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stack){

    if(this != &stack) {
        delete[] this->items;  // donate back useless memory

        this->size = stack.size;
        this->capacity = stack.capacity;

        this->items = new T[stack.capacity];

        for (int i = 0; i < (this->size); i++) {
            this->items[i]=stack.items[i];
        }
    }
    	return *this;
}

// completed
template <class T>
Stack<T> :: ~Stack(){
    delete[] items;
}

//check
template <class T>
void Stack<T>::push(const T& item){
    if(size<capacity){
        items[size] = item;
    }
    else{
        capacity*=2;
        T* newItems = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            newItems[i]=items[i];
        }
        newItems[size] = item;
        items = newItems;
    }
    size++;
}

//done
template <class T>
T Stack<T>::pop(){
    if(size<1) throw out_of_range("exception");
    T popik=top();
    if(size*3<capacity){
        if (capacity<16) {
            capacity=8;
        }
        else {
            capacity=capacity/2;
        }

        T* newItems2= new T[capacity];
        for (size_t i = 0; i < size; i++) {
            newItems2[i]=items[i];
        }
        items = newItems2;
    }
    size--;
    return popik;
}


template <class T>
const T& Stack<T>::top() const {
    if(size<1) throw out_of_range("exception");
    return items[size-1];
}

//done
template <class T>
void Stack<T>::clear(){
    if(size==0) return;
    delete[] items;
    capacity=8;
    size=0;
    items = new T[capacity];
}

//done
template <class T>
bool Stack<T>::isEmpty() const {
    return size==0;
}

//done
template <class T>
size_t Stack<T>::getSize() const {
    return size;
}

//done
template <class T>
size_t Stack<T>::getCapacity() const{
    return capacity;
}

//done
template <class T>
void Stack<T>::print() const {
    if(size<1) return;
    for (int i = (size-1); i >=0 ; i--) {
    cout << items[i] << endl;
    }

}
//done
template <class T>
void Stack<T>::printReversed() const {
    if(size<1) return;
    for (int i = 0; i < size; i++) {
        cout << items[i] << endl;
    }

}


#endif
