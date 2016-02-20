#ifndef ARCHIEVE_H
#define ARCHIEVE_H

#include "../include/header.hpp"
#include "../include/BitReader.hpp"
#include "../include/BitWriter.hpp"

#include <fstream>

using namespace std;

//
void fillArchieve( Header& head, BitWriter& writer, const string& ftarget );
void extractArchieve( Header& head, BitReader& reader, const string& ftarget );
void buildFolder( Header& head, const string& ftarget );
#endif // ARCHIEVE_H
