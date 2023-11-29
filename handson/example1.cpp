#include <iostream>
#include <gsl/gsl>
#include <cstring>

using namespace std;
using namespace gsl;

void handle_help(){
    cout << "Usage: echo [SHORT-OPTION]... [STRING]...\n"
        << " or: echo LONG-OPTION\n"
        << "Echo the STRING(s) to standard output.\n"
        << "\n"
        << " -n do not output the trailing newline\n"
        << " --help display this help and exit\n"
        << " --version output version information and exit\n";
    ::exit(EXIT_SUCCESS);
}
void handle_version(){
    cout << "echo (example) 1.0\n"
        << "Copyright (C) Yango\n"
        << "\n"
        << "Written by Rian Quinn.\n" << endl;

    ::exit(EXIT_SUCCESS);
}
int protected_main(int argc, char**argv){
    auto endl = true;
    auto args = make_span(argv, argc);

    //cout << "input argc: " << argc << "\n";

    for(int i=1,num=0; i < argc; i++){
        // cstring_span<> span_arg = ensure_z(args.at(i));
        czstring span_arg = args[i];
        //cout << i << ": " << span_arg << "\n"; 
        
        if(strcmp(span_arg,"-n") == 0){
            endl = false;
            continue;
        }

        if(strcmp(span_arg ,"--help") == 0){
            handle_help();
        }
        

        // if(span_arg == "--version"){
        if(strcmp(span_arg, "--version") == 0)
        {
            //cout << "match --version" << "\n";
            handle_version();
        }

        if(num++ > 0){
            cout << " ";
        }

        cout << span_arg;
    }

    if(endl){
        cout << "\n";
    }

    return EXIT_SUCCESS;
}
int main(int argc, char **argv){
    cout << "hello example1" << "\n\n";
    try{
        return protected_main(argc, argv);
    }catch(const exception &e){
        cerr << "Caught unhandled exception:\n";
        cerr << " - what(): " << e.what() << "\n";
    }
    catch(...){
        cerr << "Caught unknown exception\n";
    }

    return 0;
}