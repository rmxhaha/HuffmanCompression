#ifndef HuffmanTree_h
#define HuffmanTree_h

#include <iostream>
#include <fstream>
#include "../include/bitreader.hpp"
#include "../include/bitwriter.hpp"

using namespace std;

struct node {
	unsigned char c; //karakter pada daun
	int weight; //frekuensi kemunculan karakter
	int order; //nomor node
	bool NYT;
	node *left;
	node *right;
	node *parent;
};

class HuffmanTree {
public:

	HuffmanTree(); // Konstruktor
	~HuffmanTree(); // Desktruktor

	node *getNode(); // Mengembalikan node pohon
	bool isLeaf(node *_n); // Cek apakah node tersebut merupakan daun

	void char_Bit (unsigned char c, unsigned char &x, int &count, ostream &output); // Memasukan char ke dalam karakter tampungan (encode)
	void char_Bit_decode (unsigned char c, unsigned char &x, int &count, ostream &output, unsigned char &z); // Memasukan char ke dalam karakter tampungan (decode)

	void addNewChar(unsigned char _c); // Menambahkan karakter baru pada pohon
	void addExistingChar(unsigned char _c); // Menambahkan karakter yang sudah ada

    void update(node *P); // Update sebuah node dan seluruh parentnya

	void searchNum(BitWriter&, unsigned char c); // Mengoutputkan path ke karakter c
	void searchNumNYT(BitWriter&); // Mengoutputkan path ke NYT

	void compress(BitWriter& writer, const string& filepath); // Proses pemampatan
	void decompress(BitReader& reader, const string& filepath, int size); // Proses penirmampatan


private:
	// Data
	int nNYT; // Order NYT
	node *n; // Pohon Huffman
	node *loct[256]; // Array setiap daun
	node arrOrder[600]; // Array setiap order

};

#endif
