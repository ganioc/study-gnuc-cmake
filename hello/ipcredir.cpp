#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include <array>
#include <iostream>
#include <string_view>

using namespace std;

class mypipe
{
    array<int,2> m_handles;
public:
    mypipe(){
        if(pipe(m_handles.data())< 0){
            exit(1);
        }
    }
    ~mypipe(){
        close(m_handles.at(0));
        close(m_handles.at(1));
    }
    string read(){
        array<char, 256> buf;
        size_t bytes = ::read(m_handles.at(0), buf.data(), buf.size());
        if(bytes > 0){
            return {buf.data(), bytes};
        }
        return {};
    }
    void redirect(){
        dup2(m_handles.at(1), STDOUT_FILENO);
        close(m_handles.at(0));
        close(m_handles.at(1));
    }
};

int main()
{
    cout << "Test redirection" << endl;

    mypipe p;

    if(fork() == 0){
        p.redirect();
        execlp("ls", "ls", nullptr);
    }
    else{
        wait(nullptr);
        cout << "I am parent" << endl;
        cout << p.read() << endl;
    }

    return 0;
}


