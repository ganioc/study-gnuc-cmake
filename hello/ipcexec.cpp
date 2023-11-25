#include <unistd.h>
#include <iostream>

using namespace std;

int main(void){
    execl("/bin/ls", "ls", nullptr);
    // below will no longer be executed
    cout << "Hello exec" << endl;
}
