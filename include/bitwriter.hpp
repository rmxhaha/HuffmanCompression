#ifndef BITWRITER_H
#define BITWRITER_H

#include <fstream>

using namespace std;

class BitWriter {
public:
    BitWriter(ofstream&);

    void writeBit(bool b);
    void writeByte(char c);
    void flush();
    void resetCounter();
    long long getBitCount() const;
private:
    ofstream& stream;
    char buffer;
    int buffer_bid;
    long long bit_count;
};

#endif // BITWRITER_H
