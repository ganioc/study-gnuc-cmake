#include <unistd.h>
#include <iostream>
#include <signal.h>

using namespace std;

void handler(int sig){
    if(sig == SIGINT){
        cout << "handler called" << endl;
    }
}

int main(void){

    // while(true){
    //     cout << "Hello signal" << endl;
    //     sleep(1);
    // }

    signal(SIGINT, handler);
    for(auto i = 0; i< 10; i++){
        cout << "Hello signal" << endl;
        sleep(1);
    }
}
