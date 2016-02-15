#ifndef HEADER_H
#define HEADER_H

#include "../include/file.hpp"
#include "../include/folder.hpp"

struct Header {
    vector<Folder> folders;
    vector<File> files;
};

Header buildHead( const string& rootDirectory );


void printHead( Header& header );

void Bin2Header( Header& header, const string& fn );

void Header2Bin( Header& header, const string& fn );
#endif
