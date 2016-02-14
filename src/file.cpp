#include "../include/file.hpp"
#include <string>

using namespace std;

File::File(){
    fileName = "";
    size = 0;
}

File::File( const string& fn, unsigned s ){
    fileName = fn;
    size = s;
}

