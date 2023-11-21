#include <cstdint>

struct mystruct{
    uint64_t data1;
    uint64_t data2;
};

mystruct test(){
    return {10,11};
}

int main(void){
    auto ret = test();
}