#include "../include/folder.hpp"
#include "../include/file.hpp"
#include "../include/header.hpp"
#include "../include/archieve.hpp"
#include "../include/bitreader.hpp"
#include "../include/bitwriter.hpp"
#include <iostream>
#include <fstream>
using namespace std;


int main(){
    Header head;
    head = buildHead("sample");
    ifstream infile("bitread.sample", ios::in | ios::binary);
    ofstream outfile("bitwrite.sample", ios::binary | ios::out );
    BitReader reader(infile);
    BitWriter writer(outfile);
    int x = 0;
    while( !reader.eof() ){
        if( x ++ % 8 == 0) cout << endl;
        bool b = reader.readBit();
        cout << b;
        writer.writeBit(b);
    }

    outfile.close();


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
/*
    printHead(head);
    ofstream outfile;
    outfile.open ("sample.hu", ios::out | ios::binary);
    Header2Bin(head,outfile);
    fillArchieve(head,outfile,"sample");
    outfile.close();

    head.files.clear();
    head.folders.clear();

    ifstream infile("sample.hu", ios::in | ios::binary);
    Bin2Header(head,infile);
    buildFolder(head,"sample2");
    extractArchieve(head,infile,"sample2");
    infile.close();

    printHead(head);
*/
	return 0;
}
