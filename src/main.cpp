#include "../include/folder.hpp"
#include "../include/file.hpp"
#include "../include/header.hpp"
#include "../include/archieve.hpp"

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
    printHead(head);
    ofstream outfile;
    outfile.open ("sample.hu", ios::out | ios::binary);
    Header2Bin(head,outfile);
    fillArchieve(head,outfile,"sample");
    outfile.close();

    ifstream infile("sample.hu", ios::in | ios::binary);
    head.files.clear();
    head.folders.clear();
    Bin2Header(head,infile);
    buildFolder(head,"sample2");
    infile.close();

    printHead(head);

	return 0;
}
