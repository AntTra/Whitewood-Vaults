#pragma once
#include <iostream>
#include <utility>

class Dummy {
public:
    int *num;

    Dummy() {
        num = new int{0};
    }

    Dummy(const Dummy & dum) : Dummy{} {
        *num = *dum.num;
    }

    Dummy& operator=(Dummy dum){
        std::swap(this->num, dum.num);
        return *this;
    }
    
    ~Dummy() {
        delete num;
    }
};

void dummyTest();