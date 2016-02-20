
#include "../include/bitreader.hpp"

BitReader::BitReader( ifstream& _stream ) : stream( _stream ) {
    stream.unsetf(ios::skipws);
    buffer = new char[31457280];
    read2buffer();
}

bool BitReader::eof(){
    return stream.eof() && buffer_id >= buffer_length;
}

#include <iostream>
using namespace std;

bool BitReader::readBit(){
    bool out = (buffer[buffer_id] >> buffer_bid) & 1;

    buffer_bid --;
    if( buffer_bid < 0 ){
        buffer_bid = 7;
        buffer_id ++;
        if( buffer_id >= buffer_length )
            read2buffer();
    }

    return out;
}

unsigned char BitReader::readByte(){
    unsigned char c = 0;
    unsigned char t;
    for( int i = 7; i >= 0; --i ){
        t = readBit();
        c |= t << i;
    }
    return c;
}


void BitReader::read2buffer(){
    if( stream.eof() ) return;

    stream.read(buffer,31457280);
    buffer_length = stream.gcount();

    buffer_bid = 7;
    buffer_id = 0;
}
