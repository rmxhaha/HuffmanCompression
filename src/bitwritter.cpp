#include "../include/bitwriter.hpp"

BitWriter::BitWriter(ofstream& s) : stream(s), buffer(0), buffer_bid(7){ resetCounter(); }

void BitWriter::resetCounter(){ bit_count = 0; }
long long BitWriter::getBitCount() const { return bit_count; }
void BitWriter::writeBit(bool b){
    if(b)
        buffer |= 1 << buffer_bid;

    buffer_bid --;
    if( buffer_bid < 0 ){
        flush();
    }

    ++ bit_count;
}

void BitWriter::writeByte(char c){
    for( int i = 7; i >= 0; --i ){
        writeBit((c>>i)&1);
    }
}

void BitWriter::flush(){
    if( buffer_bid == 7) return;
    stream << buffer;
    buffer = '\0';
    buffer_bid = 7;
}

