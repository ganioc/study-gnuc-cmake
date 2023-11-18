#pragma once
#include <iostream>

class MyClass
{
public:
    MyClass(const char* filename):
        m_file{fopen(filename, "rb")}{
        if(m_file == 0){
            throw std::runtime_error("Unable to open the file.");
        }
    }
    ~MyClass(){
        if(m_file){
            fclose(m_file);
            std::clog << "Hello from destructor\n";
        }
    }

private:
    FILE *m_file;
};