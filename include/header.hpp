#ifndef HEADER_H
#define HEADER_H

#include "../include/file.hpp"
#include "../include/folder.hpp"

struct Header {
    vector<Folder> folders;
    vector<File> files;
};

Header buildHead( const string& rootDirectory );

Header parseHead( const string& bin );

void printHead( Header& header );

string Header2Bin( Header& header );

#endif
