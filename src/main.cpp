#include "../include/folder.hpp"
#include "../include/file.hpp"
#include "../include/header.hpp"

#include <iostream>

using namespace std;


int main(){
    Header head;
    head = buildHead("sample");
/*
    for( auto& it : head.folders ){
        cout << it.folderName << endl;
    }
    cout << endl;
    for( auto& it : head.files ){
        cout << it.fileName << endl;
    }

    cout << endl;
    printHead(head);
*/
    Header2Bin(head,"sample.hu");
    Bin2Header(head,"sample.hu");
	return 0;
}
