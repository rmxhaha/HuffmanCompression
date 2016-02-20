#ifndef HuffmanTree_h
#define HuffmanTree_h

#include <iostream>
#include <fstream>
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

	void searchNum(unsigned char c, unsigned char &x, int &count, ostream &output); // Mengoutputkan path ke karakter c
	void searchNum(unsigned char &x, int &count, ostream &output); // Mengoutputkan path ke NYT

	void compress(int &size); // Proses pemampatan
	void decompress(int size); // Proses penirmampatan
	

private:
	// Data
	int nNYT; // Order NYT
	node *n; // Pohon Huffman
	node *loct[256]; // Array setiap daun
	node arrOrder[600]; // Array setiap order

};

#endif
