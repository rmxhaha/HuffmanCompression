#ifndef BIT_READER_H
#define BIT_READER_H
#include <fstream>

using namespace std;

class BitReader {
public:
    BitReader( ifstream& _stream );
    bool eof();
    bool readBit();
    unsigned char readByte();
private:
    void read2buffer();

    char *buffer;
    int buffer_bid;
    int buffer_id;
    int buffer_length;
    ifstream& stream;

};

#endif // BIT_READER_H
