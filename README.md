## CMake project

Books
* Modern CMake for C++
* "Hands-on System Programming with C++"
* "C++ Data Structures and Algorithms"
* "C++ Reactive Programming"

template programming, 让编译器来生成代码, type-safe, 优越性，容易维护。

functional programming
With compiler assistance, in the form of lambda functions. 

Error handling, 错误处理
To get an error code from a function,
* Constrain the output of a function, 一些函数返回的值被认为是一种故障、错误
* 得到一个数据结构，手动解析这个结构
```cpp
std::pair<int, int>
auto [val, error_code] = func()
```

APIs and C++ containers容器
STL, standard template library, 提供了基本的API, C++提供了需要的数据结构, 

## C, C++, Posix标准
C语言用于system, embedded, kernel-level 编程。
标准分为3个部分:
* Environment
    描述一些信息，使compiler writer更好地理解如果去实现一个C编译器,
    How programs are linked and started,
* Language
    与C syntax相关,
* Libraries
    标准C语言提供的库功能, 包含输出字符串到stdout,分配内存，使用时间、定时器。系统编程

**C程序的启动**
操作系统和标准C环境, 会运行，在调用main()之前.

* -lc: tells the linker to link in libc. By default GCC links libc
* -lgcc_s: a static library , linked automatically by GCC to provide support for compiler-specific operations including 64-bit operations on a 32-bit CPU, and facilites such as exception unwinding, 
* Scrt1.o, crti.o,crtbeginS.o,crtendS.o, crtn.o: 这些函数提供了代码，在应用开始或停止时使用

特别的是，C runtime libraries, (CRT)库，提供了需要bootstrap the applicaiton的代码, 包括:
* 执行global constructors, destructors, 因为GCC提供了constructor, destructors in C, even though这不是一个标准的C能力
* 设置unwinding to support exception supporting. 处理异常。虽然只是C++ exception的需求，c并不执行异常的捕捉。They are still needed for linking in the set jump exception logic. 
* 提供_start 函数，在默认的GCC compiler提供的对任意的C-based application的入口

这些库，会给main()函数提供pass in的参数, 并截获main()返回的值, 并执行exit()函数。
首先会运行global constructor(),在运行main()之前。

```shell
make VERBOSE=1
```

static libraries: linked at compile time
dynamic libraries: linked at load time
>lazy loading, ldd a.out,

链接的库:
* linux-vdso.o, a library provided by OS to speed up the process of making system calls,
* libstdc++.so.6, 
* libc.so.6, standard C library
* libm.so.6
* ld-linux-x86-64.so, dynamic linker iteself, responsible for lazy-loading, 
* libgcc_s.so

**scope**
代码作用范围

**pointers and arrays**
指针和数组,
可能会发生buffer overflow, 
指针可以有值，也可以是空的null,

C++提供了一个概念reference, 索引值, non-optional pointer, 必须指向一个有效的，typed,memory location. 不能是null。
在C的环境中，public-facing API通常必须检验null pointer. private API不需要检查指针的null pointer, 以提高性能。只要公共接口不会收到Null指针，那么私有API也不会。

标准的C数组与指针类似。

标准C还提供了一系列库帮助进行System Programming
* errno.h, 
* inttypes.h, 
* limits.h, 每个数据类型的极值、范围
* setjump.h, c-style exception handling, 
* signal.h, 信号的发送, 
* stdbool.h, 
* stddef.h, 提供类型信息
* stdint.h, 
* stdio.h, 
* stdlib.h, various utilities, dynamic memory allocation APIs
* time.h, working with clocks,

**C++标准**
提供higer-level facilites than C, 包括better type safety, object-oriented programming, with system programming in mind. C++在提供C的性能和效率的同时，提供高级语言的特性。

标准分为3个部分
* General convention and concepts. 定义了types, program start-up and shutdown, memory and linking.
* Language sytax, 语法
* Libraries, 库,

**Linking C++ applications**
nm -gC hello , 打印外部symbol
name -g hello, 

_init(), For global construciton and destruction.生成需要支持std::cout的代码,
_fini(), 生成销毁这些全局变量的代码.
__cxa_atexit(), global object的注册,
__cxa_finalize(), 全局对象的销毁,

_C option to demangle the function names,

function names are mangled in C++
* 函数名编码进了参数名，实现函数重载, 
* 类型信息编码进了函数名称，可以分辨调用的库，接口,

Public-facing APIs do not change.

**scope**
C++大量地使用了对象的初始化和销毁回收。有个概念叫:Resource Acquisition is Initializatin (RAIS)

**指针 versus references**
reference增加了程序的性能和稳定性。尤其是系统编程, resources, performance, stability很关键的时候。

**C++库**
* Console input output library. iostream, iomanip, string, 
* Memory management libraries. 避免dangling pointers,
* File input/output libraries. fstream, filesystem, 
* Time libraries, chrono library
* Threading libraries, thread, mutex, conditional_varaible lib,
* Error-handling libraries. exception support lib

libc提供的内存管理功能是符合POSIX-specific标准的，但是没有满足所有的标准要求。比如aligned memory.

POSIX common folders

## System Types
系统的类型定义, 
C, C++ default types, 数据类型包括
```cpp
char, wchar_t
short int(2 bytes), int (4 bytes), long int (8 bytes on 64-bit CPU),
float(4 bytes), double(8 bytes) , long double (16 bytes),
bool(c++ only, 1 byte)
```

数据类型的长度问题, 为了解决这个问题, 
在stdint.h头文件里，定义了下面的类型
```cpp
int8_t,uint8_t
int16_t, uint16_t
int32_t, uint32_t
int64_t, uint64_t
```
stdint.h是一个编译器提供的头文件，针对每一个CPU架构和操作系统组合，会生成不同的内容。
```cpp
<typeinfo> // mangled version of this type information
<cxxabi.h> // demangler built into C++ itself
```

**structure packing**

```cpp
#pragma pack(push, 1) // using a byte granularity,
// not allowed to make a substitution optimization
struct mystruct{
    uint64_t data1;
    uint16_t data2;
};
#pragma pack(pop)
```
packed structures
bit fields,
需要避免,因为会byte aligned, not cache aligned.
alignas(16), to cache align the structure,
stdint.h,
GSL, Guideline Support Library
RAII, Resource Acquisition Is Initialization

**C++ 17的新特性**
```cpp
// can be evaluated at compile time
constexpr const auto val = true;
// compile-time function, 
static-assert()
// structured bindings
[z,b] = get_sth()
// inline variables
inline auto msg = "hello world\n";
```
**库的改变**
To remove direct access to both pointers and arrays. 有很多错误来自于对指针和数组的错误处理。

C++ Core Guidelines,
避免一些常见的错误在使用C++的时候。
```cpp
// string view wrapper of char array,
std::string_view
// .front(), back(), at(1), data(), std::out_of_range()
// .size(), .max_size(), .empty(), 
#include <string_view>
//
std::any{}
// type-safe union
std::variant{}
// nullable value type,
std::optional{}

```

### RAII
RAII 设置了整个C++库的基础和设计模式, 是其它很多语言的设计灵感。带来了超越C的安全性。
std::runtime_error("");
这是一件简单，然而强大的功能，特性, feature

### GSL
Guideline support library
主要有几点，best practice, 最佳实践,programming in C++,
* Pointer ownership, 一个简单的方式来防止内存泄漏，指针错误的方法是定义指针的owner是谁。std::uniqe_ptr{}, std::shared_ptr{}, 
>gsl::owner<>{}, 
* Expectation management, 期望管理, what a function应该期望输入和输出, 将这些概念转移到C++ contracts, 合约?
* No pointer arithmetic, 禁止对指针的算数操作,

https://github.com/isocpp/CppCoreGuidelines/

GSL, include types like
```cpp
owner<>
not_null<>
span<>
string_span
```

gsl-lite, 可以仅包含头文件

microsoft-gsl
>这里也只是一组头文件吗？

```cpp
gsl::owner<>{}
gsl::not_null<>{} // 在debug模式会throw an exception
// 未debug模式，则不做任何处理,
gsl::span{}, // a safe interface for working with pointers 
// including arrays
```

std::clog, same as cerr,but with buffering, 
std::wclog,

**contracts**
a C++ contract documents a contract between the author of an API and the user of the API. compile-time and runtime validation of the contract. 合约

Expects()
Ensures()

**Utilities**

## Programming Linux/Unix Systems
Linux ABI
Unix filesystem
Unix process APIs
Unix signal APIs

System V ABI, 包括
* The register layout
* The stack frame
* function prologs and epilogs
>function 执行在代码运行前和运行后执行的代码,如setting up a stack frame, saving current state of CPU registers, allocating space for local variables. 准备函数执行时的环境变量。cleanup, 恢复cpu寄存器状态，释放本地变量，执行被中断的任务。
* The calling convention , parameters passing
* exception handling
* virutal memory layout
* Debugging
* binary object format, ELF
* program loading and linking

Intel 64-bit, AMD64, 
rip, a program's current location in executable memroy,
rsp, stack pointer
rbp, base pointer, 定义栈的位置
rax,rbx,rcx,rdx, 
rdi,rsi,
r8,r9,r10,... r15,
floating point register
wide register, to speed up calculations, SSE, aVX,

stack frame:
grows down, 每一个frame都代表一个函数调用, funciton call, first 6 arguments are passed as registers. 返回地址push进stack。
Memory after the return address属于函数调用使用的参数。stack-based variables. 每次函数返回时, stack shrinks. 
操作系统负责管理栈的大小，
call
ret, pop the return address from the stack, and jump to the address popped.

red zone. only applies to leaf function (does not call any other fucntion)
red zone 必须被关掉，如果有中断的话, gcc, -mno-red-zone flag

**calling convention**
调用规则
那些寄存器是易失的，那些是non-volatile的，哪些使用寄存器来传递参数，用什么次序，那些寄存器用来存放返回值。

non-volatile register,
Is restored to its original value, 在function leave之前, in eiplog,
System V ABI定义了rbx, rbp, r12, r13, r14, r15,
volatile register,
可以随意使用, 不介意寄存器值的改变,
%rdx, 存放第3个参数,
看起来rbx, rbp是存放前2个参数吧,

System V's calling convention 传递参数的顺序:
rdi, rsi, rdx, rcx, r8, r9,

edi, esi存放两个输入的参数， 将结果放在eax寄存器里返回，多个参数的话，再增加rdx,

e 表示32位寄存器
r 表示64位寄存器

**Exception Handling, debugging**
异常处理和debugging,

C++异常处理比较耗费时间，不要在控制逻辑里使用。
-fno-exceptions flag, 如果不想使用C++ exceptions的话,

DWARF specification,
.eh_frame table, embedded in the application itself.
绝大多数的Unix based applications 都会编译成二进制 ELF格式,
ELF应用支持C++ exception support的，都会包含一个特殊的表，叫做.eh_frame表格，这个就是exception handling framework, 异常处理框架,

DWARF还定义了指令，可以reverse the stack. 反向执行指令，修改non-volatile寄存器的内容,
readelf --debug-dump=frames a.out
FDE, (Frame Description Entry),
DWARF instructions, compressed instructions designed to be as small as possible, to reduce the size of .eh_frame table,

**Virtual memory layout**
虚拟内存的布局, 这个也是System V specification规定的,


**ELF** file standard,
Executable and Linkable Format, 0x7F hex number, continues with the ELF string.
hexdump -C a.out
一个ELF64文件可以view as segments or sections,
sections,
sections 组成segments,
section如何load 加载, 有些是read-write, 有些是read-execute,read-write-execute,

**ELF sections**
readelf -SW aaa

## Unix Processes
Unix进程, 

fork(),
一个简单的系统调用，生成一个duplicate child version of the process. 包括打开的文件操作符，内存等。区别在子进程有一个新的进程ID,

wait(),
等待子进程结束,

IPC,
进程间通讯, Interprocess Communication
synchronization,
deadlock
race conditions,
* Unix pipes
>a pipe is a file in RAM, one process can write to, and the other can read from.
* Unix shared memory
>共享内存, a buffer read, written by both processes.

ftok(filename, id),获取一个id作为key,
shmget(key,size, param)

exec()
fork() will be followed by exec 来覆盖existing process成为一个新的进程。
execl(), 绝对路径
execlp, PATH environment, 使用了环境变量,
execv(), 可以定义argv[]作为一个独立的变量,
execvp(),使用PATH环境变量,

system()
合格等于fork(), exec(),

**输出重定向**
捕获进程的输出。我们可以制造一个Unix pipe, 告诉子进程将它的输出通过pipe重定向给父进程。
dup2(), 

**unix signals**
捕捉Ctrl+C command,
signal(NUM, handler)
deadlock, corruption, race conditions, 使用signal handler时,
kill(id, SIGNAL), 对id发送信号,

## Program Console 对终端的I/O进行编程
获取用户输入，提供输出，支持debug和diagnostics. C里面的printf()/scanf() IO functions. 
C++提供stream-based IO, 与C-style相比的话。

stream-based IO
优点：
* preferred over the standard C functions, 
* 可以处理user-defined 类型，提供更清晰，type-safe IO
* 更加安全，accidental-buffer overflow vulnerabilities,
* 提供implicit memory managemnt, 内存管理, 不需要variadic functions,

缺点:
* 性能较差
* Format specifiers 更加灵活，比<iomanip>

用户定义的类型重载<<,>>,可以提供定制的，类型安全的IO,
输入的buffer大于space allocated, 造成buffer overflow situation,

```cpp
scanf("%2s", buf);
```
或者用模版来输入buffer的size, 
或者使用std::string, 会动态分配内存，从而避免buffer overflow.
    std::bad_alloc, 抛出, program aborts,

endl; 会flush the buffer,
"\n", 则不会,

```cpp
#define NDEBUG
#define DEBUG(...) fprintf(stdout, __VA_ARGS__);
#else
#endif
```
第二种是定义一个debug level, 允许developer dial in how verbose the program is while debugging.

NDEBUG: 
在Release mode, 这个会被定义。a macro, assert(), 
这是一个标准的宏定义,Not Debug, c89, c99, 

constexpr auto g_ndebug = true;
debug level , is a compile-time feature in this example.
```cpp
-DDEBUG_LEVEL=xxxx,
```
将C的宏定义为C++的constexpr, 

第三种是包含当前的文件名，和代码的行号,

为了提高性能可以使用 std::stringstream,

manipulator
std::boolalpha, 
std::noboolalpha, true, false, 1,0
std::dec,
std::oct,
std::uppercase
std::showbase
std::noshowbase,
reinterpret_cast<unitprt_t>（&i）

std::setw()
std::setfill()

C++ GSL span?
a sequence of continuous objects.
C++ Core Guideline compliant,

```cpp
ensure_z()

```



