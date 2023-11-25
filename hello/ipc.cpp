#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

using namespace std;

int main(void){
    if(fork() != 0){
        sleep(1);
        cout << "parent" << endl;
        wait(nullptr);
        cout << "parent after wait" << endl;
    }else{
        cout << "child" << endl;
    }
}
