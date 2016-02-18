#ifndef BITWRITER_H
#define BITWRITER_H

#include <fstream>

using namespace std;

class BitWriter {
public:
    BitWriter(ofstream&);

    void writeBit(bool b);

    void flush();
private:
    ofstream& stream;
    char buffer;
    int buffer_bid;
};

#endif // BITWRITER_H
