#include "../include/folder.hpp"
#include "../include/file.hpp"
#include "../include/header.hpp"

#include <iostream>

using namespace std;


int main(){
    Header head;
    head = buildHead("sample");
    for( auto it = head.folders.begin(); it != head.folders.end(); ++ it ){
        cout << it->folderName << endl;
    }
    cout << endl;
    for( auto& it : head.files ){
        cout << it.fileName << endl;
    }

    cout << endl;
    printHead(head);

	return 0;
}
