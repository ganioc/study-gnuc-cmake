#include <iostream>
#include <memory>
#include <thread>
#include <sys/mman.h>

using namespace std;

// global memory,
int bss_mem = 0;
int data_mem = 0;

// The array's address is divisible by a 4k page
// the first bits are zero.
alignas(0x1000) int ptr_g[42];

using aligned_int alignas(0x1000) = int;

constexpr auto PROT_RW = PROT_READ|PROT_WRITE;
constexpr auto MAP_ALLOC = MAP_PRIVATE|MAP_ANONYMOUS;

class Myclass{
public:
    void *operator new[](size_t count, align_val_t al){
        cout << "Myclass" << "\n";
        return ::operator new(count, al);
    }
    void operator delete[](void *ptr, align_val_t al){
        cout << "Myclass delete\n";
        return ::operator delete(ptr, al);
    }
};
using aligned_Myclass alignas(0x1000) = Myclass;

class myclass{
    int m_data{0};
public:
    ~myclass(){
        cout << "myclass deleted\n";
    }
    void inc(){ m_data++; }
};

thread t1;
thread t2;
void thread2(const shared_ptr<myclass> ptr){
    for(auto i=0; i< 100000; i++){
        ptr->inc();
    }
    cout << "thread2: complete\n";
}
void thread1(){
    auto ptr = make_shared<myclass>();
    // 生成一个thread2, 输入ptr,
    t2 = thread(thread2, ptr);

    for(auto i = 0; i<10; i++){
        ptr->inc();
    }
    cout << "thread1: complete\n";
}



int main(){
    int stack_mem = 43;

    cout << bss_mem << "\n";
    cout << data_mem << "\n";
    cout << stack_mem << "\n";


    auto ptr = new int;
    cout << ptr << "\n";
    delete ptr;

    cout << "ptr_g: " << ptr_g << "\n";

    char buffer[0x2000];
    auto ptr1 = reinterpret_cast<uintptr_t>(buffer);
    auto ptr2 = ptr1 - (ptr1 % 0x1000) + 0x1000;

    cout << hex << showbase;
    cout << ptr1 << "\n";
    cout << ptr2 << "\n";

    if(auto ptr = aligned_alloc(0x1000, 44*sizeof(int))){
        cout << "ptr aligned_alloc: " << ptr << "\n";
        free(ptr);
    }

    auto ptr_3 = new aligned_int;
    cout << "ptr_3: " << ptr_3 << "\n";
    delete ptr_3;

    auto mc_ptr1 = new aligned_Myclass;
    auto mc_ptr2 = new aligned_Myclass[42];
    cout << "mc_ptr1: " << mc_ptr1 << "\n";
    cout << "mc_ptr2: " << mc_ptr2 << "\n";

    delete mc_ptr1;
    delete []mc_ptr2;

    auto ptr_unique = std::make_unique<int>(102);
    // cout << ptr_unique << "\n";
    cout << ptr_unique.get() << "\n";
    cout << *ptr_unique << "\n";

    // Threads test
    t1 = thread(thread1);

    t1.join();
    t2.join();

    // shared_ptr
    auto ptr_shared = shared_ptr<int>(new int[42]());
    cout << ptr_shared.get()[0] << "\n";

    auto ptr_map = mmap(0,0x1000, PROT_RW, MAP_ALLOC,-1,0);
    cout << "ptr_map: " << ptr_map << "\n";
    munmap(ptr_map);

    return 0;
}
