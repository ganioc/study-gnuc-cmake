#include <iostream>
#include <fcntl.h>
#include <string.h>

using namespace std;

void test_io(void){
    auto n = 0;
    cout << "Please input some number:" << endl;
    cin >> n;
    cout << "input: " << n << endl;
}
class CustomError{};
// errno 是一个全局变量,
ostream &operator << (ostream &os, const CustomError &e){
    return os << "CustomError: " << strerror(errno);
}
void test_cust(){
    if(open("filename.txt", O_RDWR) == -1){
        cout << CustomError{} << endl;
    }
}
struct Object_t{
    int data1;
    int data2;
};
ostream &operator <<(ostream &os, const Object_t &obj){
    os << "data1:" << obj.data1 << endl;
    os << "data2:" << obj.data2 << endl;
    return os;
}
istream &operator >> (istream &is, Object_t &obj){
    is >> obj.data1;
    is >> obj.data2;
    return is;
}
int main(){
    // test_io();
    test_cust();

    // 测试
    // Object_t obj;
    // cin >> obj;
    // cout << obj;


}