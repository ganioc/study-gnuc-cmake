#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

using namespace std;

void testIPC(){
    cout << "Test IPC" << endl;
    
}


int main(void){
    int data = 10;

    int rtn = fork();

    if(rtn != 0){
        cout << "Hello process from parent" << endl;
        cout << "id: " << rtn << endl;
        data = 42;
        wait(nullptr);
    }else{
        cout << "Hello from child" << endl;
        cout << "The answer data is: " << data << endl;
    }
    
    testIPC();

    return 0;
}