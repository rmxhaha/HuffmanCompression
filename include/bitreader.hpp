#ifndef BIT_READER_H
#define BIT_READER_H
#include <fstream>

using namespace std;

class BitReader {
public:
    BitReader( ifstream& _stream );
    bool eof();
    bool readBit();
private:
    void read2buffer();

    char buffer[1024];
    int buffer_bid;
    int buffer_id;
    int buffer_length;
    ifstream& stream;

};

#endif // BIT_READER_H
