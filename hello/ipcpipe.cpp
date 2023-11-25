#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include <array>
#include <iostream>
#include <string_view>

using namespace std;

class mypipe{
public:
    mypipe(){
        if(pipe(m_handles.data()) < 0){
            cerr << "Error mypipe()" << endl;
            exit(1);
        }
    }
    ~mypipe(){
        close(m_handles.at(0));
        close(m_handles.at(1));
    }
    string read(){
        array<char, 256> buf;
        size_t bytes = ::read(m_handles.at(0),buf.data(), buf.size());
        if(bytes > 0){
            return {buf.data(), bytes};
        }
        return {};
    }
    void write(const string &msg){
        ::write(m_handles.at(1), msg.data(), msg.size());
    }
private:
    array<int, 2> m_handles;
};
int main(void){
    mypipe p;

    if(fork() != 0){
        sleep(1);
        cout << "parent" << endl;

        p.write("done");
        wait(nullptr);
    }else{
        auto msg = p.read();

        cout << "child" << endl;
        cout << "msg: " << msg << endl;
    }
}