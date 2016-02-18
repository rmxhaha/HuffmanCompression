#include "../include/bitwriter.hpp"

BitWriter::BitWriter(ofstream& s) : stream(s), buffer(0), buffer_bid(7){}

void BitWriter::writeBit(bool b){
    if(b)
        buffer |= 1 << buffer_bid;

    buffer_bid --;
    if( buffer_bid < 0 ){
        flush();
    }
}

void BitWriter::flush(){
    stream << buffer;
    buffer = '\0';
    buffer_bid = 7;
}

