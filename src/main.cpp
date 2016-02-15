#include "../include/folder.hpp"
#include "../include/file.hpp"
#include "../include/header.hpp"

#include <iostream>
#include <fstream>
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
    ofstream outfile;
    outfile.open ("sample.hu", ios::out | ios::binary);
    Header2Bin(head,outfile);
    outfile.close();

    ifstream infile("sample.hu");
    Bin2Header(head,infile);
    infile.close();
	return 0;
}
