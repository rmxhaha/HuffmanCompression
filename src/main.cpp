#include "../include/folder.hpp"
#include "../include/file.hpp"
#include "../include/header.hpp"

#include <iostream>

using namespace std;


int main(){
    Header head;
    head = buildHead(".");
    for( auto it = head.folders.begin(); it != head.folders.end(); ++ it ){
        cout << it->folderName << endl;
    }
	return 0;
}
