#ifndef CUSTOMPOINTER_H
#define CUSTOMPOINTER_H

#include <iostream>
template <class T>
class CustomPointer
{
    T* ptr;
    public:
        explicit CustomPointer(T *p = 0){
            ptr = p;
        }
        T& operator*(){
            return *ptr;
        }
        T* operator->(){
            return ptr;
        }
        CustomPointer<T>& operator=(CustomPointer<T>& otherptr){
            if(this != otherptr){
                delete ptr;
                ptr = otherptr.ptr;
                otherptr.ptr = NULL;
            }
            return *this;
        }
        void copyPtr(const CustomPointer<T> &r){
            copy(r);
        }
        virtual ~CustomPointer(){
            delete ptr;
        }
    protected:
    private:
        struct counter{
            counter(T* p = 0, unsigned c = 1) : ptr(p), count(c) {}
            T* ptr;
            unsigned    count;
        } *custCounter;
         void acquire(counter* c) throw()
        {
            custCounter = c;
            if (c) ++c->count;
        }

        void release()
        {
        if (custCounter) {
            if (--custCounter->count == 0) {
                delete custCounter->ptr;
                delete custCounter;
	            custCounter = 0;
                }
            }
        }
        void copy(const CustomPointer<T>& r)  {ptr = r.ptr ? new T(*r.ptr) : 0;}
};

#endif // CUSTOMPOINTER_H
