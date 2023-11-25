#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include <iostream>

using namespace std;

char * get_shared_memory(){
    auto key = ftok("myfile", 42);
    auto shm = shmget(key, 0x1000, 0666|IPC_CREAT);

    return static_cast<char *>(shmat(shm, nullptr, 0));
}
int main(void){
    if(fork() != 0){
        sleep(1);
        cout << "parent" << endl;

        auto msg = get_shared_memory();
        msg[0] = 42;

        wait(nullptr);
    }else{
        auto msg = get_shared_memory();
        while(msg[0] != 42){
            cout << "child" << endl;
        }
    }
}