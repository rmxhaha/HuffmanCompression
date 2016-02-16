#ifndef HEADER_H
#define HEADER_H

#include "../include/file.hpp"
#include "../include/folder.hpp"

struct Header {
    vector<Folder> folders;
    vector<File> files;
};

Header buildHead( const string& rootDirectory );

string getFullDir( Folder *fl, Header *header );

void printHead( Header& header );

void Bin2Header( Header& header, ifstream& infile );

void Header2Bin( Header& header, ofstream& myfile );
#endif
