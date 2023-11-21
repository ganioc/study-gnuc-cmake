#include <iostream>
#include <exception>

using namespace std;

void test(int i){
    if( i == 42){
        throw 42;
    }
}

int main(void){
    try{
        test(1);
        cout << "attempt #1: passed" << endl;

        test(231);
        cout << "attempt #2: passed" << endl;

        test(42);

    }catch(...){
        std::cout << "exception caught" << endl;
        //std::cout << e.what() << endl;
    }
}