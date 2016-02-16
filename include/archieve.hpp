#ifndef ARCHIEVE_H
#define ARCHIEVE_H

#include "../include/header.hpp"
#include <fstream>

using namespace std;

//
void fillArchieve( Header& head, ofstream& myfile, const string& ftarget );
void extractArchieve( Header& head, ifstream& myfile, const string& ftarget );
void buildFolder( Header& head, const string& ftarget );
#endif // ARCHIEVE_H
