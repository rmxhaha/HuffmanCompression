
#include "../include/bitreader.hpp"

BitReader::BitReader( ifstream& _stream ) : stream( _stream ) {
    stream.unsetf(ios::skipws);
    read2buffer();
}

bool BitReader::eof(){
    return stream.eof() && buffer_id > buffer_length;
}

bool BitReader::readBit(){
    bool out = (buffer[buffer_id] << buffer_bid) & 0x80;

    buffer_bid ++;
    if( buffer_bid > 7 ){
        buffer_bid = 0;
        buffer_id ++;
        if( buffer_id > buffer_length )
            read2buffer();
    }

    return out;
}

void BitReader::read2buffer(){
    if( stream.eof() ) return;

    stream.read(buffer,1024);
    buffer_length = stream.gcount();
    buffer_bid = 0;
    buffer_id = 0;
}
