#define GSL_THROW_ON_CONTRACT_VIOLATION
#include <limits>

#include <typeinfo>
#include <cstdint>
#include <cstdlib>
#include <cxxabi.h>

#include <utility>
#include <string_view>
#include <any>
#include <variant>
#include <optional>


#include <gsl/gsl>
#include <iostream>

#include "MyClass.hpp"


using namespace std;

void test(void){
    cout << "test only" << endl;
}
void test(bool b){
    cout << "test boolean " << b << endl;
}
void testType(void){
    auto num_bytes_signed = sizeof(signed char);
    auto min_signed = numeric_limits<signed char>().min();
    auto max_signed = numeric_limits<signed char>().max();

    auto num_bytes_unsigned = sizeof(unsigned char);
    auto min_unsigned = numeric_limits<unsigned char>().min();
    auto max_unsigned = numeric_limits<unsigned char>().max();

    cout << "num bytes (signed)" << num_bytes_signed << endl;
    cout << "min value (signed)" << +min_signed << endl;
    cout << "max value (signed)" << +max_signed << endl;

    cout << "num bytes (unsigned)" << num_bytes_unsigned << endl;
    cout << "min value (unsigned)" << +min_unsigned << endl;
    cout << "max value (unsigned)" << +max_unsigned << endl;

    auto num_wchar = sizeof(wchar_t);
    auto min_wchar = numeric_limits<wchar_t>().min();
    auto max_wchar = numeric_limits<wchar_t>().max();
    cout << "wchar " << num_wchar << " min " << min_wchar
        << " max " << max_wchar << endl;
    
    auto num_shortint = sizeof(signed short int);
    auto min_shortint = numeric_limits<signed short int>().min();
    auto max_shortint = numeric_limits<signed short int>().max();
    cout <<"short int " << num_shortint << " min: " 
        << min_shortint << " max: " << max_shortint
        << endl;
    
    auto num_unshortint = sizeof(unsigned short int);
    auto min_unshortint = numeric_limits<unsigned short int>().min();
    auto max_unshortint = numeric_limits<unsigned short int>().max();
    cout <<"un short int " << num_unshortint << " min: " 
        << min_unshortint << " max: " << max_unshortint
        << endl;

    auto num_int = sizeof( int);
    auto min_int = numeric_limits< int>().min();
    auto max_int = numeric_limits< int>().max();
    cout <<"int " << num_int << " min: " 
        << min_int << " max: " << max_int
        << endl;

    auto num_longint = sizeof(long int);
    auto min_longint = numeric_limits<long int>().min();
    auto max_longint = numeric_limits<long int>().max();
    cout <<"long int " << num_longint << " min: " 
        << min_longint << " max: " << max_longint
        << endl;

}

template<typename T>
string type_name(){
    int status;
    string name = typeid(T).name();

    // cout << "name: " << name.c_str() << endl;
    auto demangled_name = abi::__cxa_demangle(name.c_str(),
        nullptr, nullptr, &status);

    if(status == 0){
        name = demangled_name;
        free(demangled_name);
    }
    return name;
}
template<typename T1, typename T2>
void are_equal(){
    #define red "\033[1;31m"
    #define reset "\033[0m"

    cout << type_name<T1>() << " vs "
        << type_name<T2>() << endl;
    
    if(sizeof(T1) == sizeof(T2)){
        cout << " - size: both == " << sizeof(T1)
            << endl;
    }else{
        cout << red " - size: " << sizeof(T1) << " != "
            << sizeof(T2) << reset "\n";
    }
    if(type_name<T1>() == type_name<T2>()){
        cout << " - name: both == " << type_name<T1>() << endl;
    }else{
        cout << red " - name: "
            << type_name<T1>()
            << " != "
            << type_name<T2>()
            << reset "\n";
    }
}
struct mystruct{
    uint64_t data1;
    uint64_t data2;
};

#pragma pack(push,1)
struct mystruct_2{
    uint64_t data1;
    uint16_t data2;
};
#pragma pack(pop)

pair<const char*, int>
give_me_a_pair(){
    return {"The answer is: ", 42};
}

void init(int *p){
    *p = 0;
}
gsl::not_null<int *>
test_null(gsl::not_null<int *> p){
    return p;
}
int main(){
    cout << "Test Hello World" << endl;

    test();
    test(false);

    testType();

    type_name<unsigned int>();
    cout << type_name<int>() << endl;

    are_equal<uint8_t, int8_t>();
    are_equal<uint8_t, uint32_t>();
    are_equal<signed short int, int16_t>();

    cout << "size of mystruct: " << sizeof(mystruct) << endl;

    cout << "size of mystruct_2: " << sizeof(mystruct_2) << endl;

    auto p = give_me_a_pair();
    cout << get<0>(p) << get<1>(p) << endl;
    auto [msg, answer]  = give_me_a_pair();
    cout << "msg is: " << msg << endl;
    cout << "answer is: " << answer << endl;

    string_view str("hello string view");
    cout << str.data() << endl;
    str.remove_prefix(1);
    cout <<str.data() << endl;

    auto myany = make_any<int>(44);
    cout << any_cast<int>(myany) << endl;
    myany = 4.2;
    cout << any_cast<double>(myany) << endl;

    variant<int, double> v = 142;
    cout << get<int>(v) << endl;
    v = 142.1;
    cout << get<double>(v) << endl;

    optional<int>o1;

    MyClass c1("test.txt");
    try{
        MyClass c2("notest.txt");
    }
    catch(const exception &e){
        cout << "exception is: " << e.what() << endl;
    }

    gsl::owner<int *> p_gsl = new int;    
    init(p_gsl);
    delete p_gsl;

    auto p1_gsl = make_unique<int>();
    auto p2_gsl = test_null(gsl::not_null(p1_gsl.get()));

    int array[5] = {1,2,3,4,5};
    auto span = gsl::span(array);

    for(const auto &elem: span){
        clog << elem << endl;
    }

    gsl::zstring str_gsl =  "Hello GSL Z String";
    cout << "str content: " << str_gsl << endl;
    // cout << str_gsl.length() << endl;

    try{
        Expects(true);
    }catch(const exception &e){
        cout << "exception: " << e.what() << endl;
    }
    
    gsl::finally([]{
        cout << "Fired in finally()" << endl;
    });

    return 0;
}
