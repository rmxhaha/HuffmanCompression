#include <iostream>
#include <fstream>
using namespace std;

class HuffmanTree {
public:
	struct node
{
	unsigned char c; //karakter pada daun
	int weight; //frekuensi kemunculan karakter
	int order; //nomor node
	bool NYT;
	node *left;
	node *right;
	node *parent;
};
	// Constructor
	HuffmanTree() {
		n = new node;
		n->weight = 0;
		n->order = 513;
		n->NYT = true;
		n->c = 'z';
		n->left = NULL;
		n->right = NULL;
		n->parent = NULL;
	}
	
	// Destructor
	~HuffmanTree() {
        dealokasi(n);
    }
    	
	void dealokasi(node *P) {
		if (P != NULL) {
			dealokasi(P->left);
			dealokasi(P->right);
			delete(P);
			P = NULL;
		}
	}

	// Mengecek apakah _n merupakan daun
	bool isLeaf(node *_n) {
		if ((_n->left == NULL) && (_n->right == NULL)) {
			return true;
		} else {
			return false;
		}
	}
	
	/* Getter */
	
	// Mengembalikan node pohon
	node *getNode() {
		return n;
	}
	
	// Menambahkan karakter pada pohon
	void addNextChar(unsigned char _c) {
		if (bSearch(n,_c)) {
			addExistingChar(_c);
		} else {
			addNewChar(_c);
		}
	}
	
	// Menambahkan karakter baru pada pohon
	void addNewChar(unsigned char _c) {
		node *_n = search(n);
		
		_n->left = new node;
		_n->right = new node;
		
		node *Left = _n -> left;
		node *Right = _n -> right;
		
		_n -> c = 'z';
		_n -> NYT = false;
		
		Left -> left = NULL;
		Left -> right = NULL;
		Left -> parent = _n;
		Left -> NYT = true;
		Left -> weight = 0;
		Left -> order = (_n -> order) - 2;
		Left -> c = 'z';
		
		Right -> left = NULL;
		Right -> right = NULL;
		Right -> parent = _n;
		Right -> NYT = false;
		Right -> weight = 0;
		Right -> order = (_n -> order) - 1;
		Right -> c = _c;
		
		update(Right);
	}
	
	// Menambahkan karakter yang sudah ada
	void addExistingChar(unsigned char _c) {
		node *_n = search(n,_c);
		update(_n);
	}
    
    // Update posisi node P
    void update(node *P) {
		if (P != NULL) {
			P->weight++;
		}
		if (P->parent != NULL) {
			if (check(P)) {
			} else {
				update(P->parent);
			}
		}
	}
	
	// Cek apakah node P dapat ditukar
	bool check(node *P) {
		node *_n = search(n,P->order+1);
		if (P->parent == _n) {
			_n = search(n,P->order+2);
		}
		if (_n != NULL) {
			if (P->weight > _n->weight) {
				swap(P,_n);
				return true;
			} else {
				return false;
			}
		}
		return false;
	}
	
	// Menukar parent dari P dan _P
    void swapParent(node *P, node *_P) {
		node *temp;
		
		if (P->parent->left == P) {
			if (_P->parent->left == _P) {
				P->parent->left = _P;
				_P->parent->left = P;
			} else {
				P->parent->left = _P;
				_P->parent->right = P;
			}
		} else {
			if (_P->parent->left == _P) {
				P->parent->right = _P;
				_P->parent->left = P;
			} else {
				P->parent->right = _P;
				_P->parent->right = P;
			}
		}
		temp=P->parent;
		P->parent = _P->parent;
		_P->parent = temp;
	}
	
	// Menukar dua node
    void swap(node *P, node *_P) {
		int _order;
		swapParent(P,_P);
		_order = P->order;
		P->order = _P->order;
		_P->order = _order;
	}
	
	/* Fungsi dan Prosedur Pencarian */
	
	// Mengecek apakah ada node yang merupakan NYT
	bool bSearch(node *P) {
		if (P == NULL) {
			return false;
		}
		else if (P->NYT == true) {
			return true;
		}
		else {
			return (bSearch(P->left) || bSearch(P->right));
		}
	}
	
	// Mengecek apakah ada node dengan order tertentu
	bool bSearch(node *P, int _order) {
		if (P == NULL) {
			return false;
		}
		else if (P->order == _order) {
			return true;
		}
		else {
			return (bSearch(P->left, _order) || bSearch(P->right, _order));
		}
	}

	// Mengecek apakah ada node degnan karakter tertentu
	bool bSearch(node *P, unsigned char _c) {
		if (P == NULL) {
			return false;
		}
		else if ((P->c == _c) && isLeaf(P) && !(P->NYT)) {
			return true;
		}
		else {
			return (bSearch(P->left, _c) || bSearch(P->right, _c));
		}
	}
	
	// Mengembalikan node yang merupakan NYT
	node *search(node *P) {
		if (P == NULL) {
			return NULL;
		} else if ((P->NYT) && (isLeaf(P))) {
			return P;
		} else if (bSearch(P->left)) {
			return search(P->left);
		} else if (bSearch(P->right)) {
			return search(P->right);
		} else {
			return NULL;
		}
	}
	
	// Mengembalikan node dengan order tertentu
	node *search(node *P, int _order) {
		if (P == NULL) {
			return NULL;
		} else if (P->order == _order) {
			return P;
		} else if (bSearch(P->left, _order)) {
			return search(P->left, _order);
		} else if (bSearch(P->right, _order)) {
			return search(P->right, _order);
		} else {
			return NULL;
		}
	}
	
	// Mengembalikan node dengan karakter tertentu
	node *search(node *P, unsigned char _c) {
		if (P == NULL) {
			return NULL;
		} else if ((P->c == _c) && (isLeaf(P)) && (!P->NYT)) {
			return P;
		} else if (bSearch(P->left, _c)) {
			return search(P->left, _c);
		} else if (bSearch(P->right, _c)) {
			return search(P->right, _c);
		} else {
			return NULL;
		}
	}
	
	// Membentuk array of boolean berupa letak karater _c pada pohon
	void searchNum(node *P, unsigned char _c, unsigned char &x, int &count, ostream &output) {
		if (P != NULL) {
			if ((P->c == _c) && (isLeaf(P))) {
			} else if (bSearch(P->left, _c)) {
				count++;
				x = x << 1;
				x &= ~(1);
				if (count == 8) {
					output.write((char*) &x, sizeof(char));
					count = 0;
				}
				searchNum(P->left, _c, x, count, output);
			} else if (bSearch(P->right, _c)) {
				count++;
				x = x << 1;
				x |= 1;
				if (count == 8) {
					output.write((char*) &x, sizeof(char));
					count = 0;
				}
				searchNum(P->right, _c, x, count, output);
			}
		}
	}
	
	// Membentuk array of boolean berupa letak karater _c pada pohon
	void searchNum(node *P, unsigned char &x, int &count, ostream &output) {
		if (P != NULL) {
			if ((P->NYT) && (isLeaf(P))) {
			} else if (bSearch(P->left)) {
				count++;
				x = x << 1;
				x &= ~(1);
				if (count == 8) {
					output.write((char*) &x, sizeof(char));
					count = 0;
				}
				searchNum(P->left, x, count, output);
			} else if (bSearch(P->right)) {
				count++;
				x = x << 1;
				x |= 1;
				if (count == 8) {
					output.write((char*) &x, sizeof(char));
					count = 0;
				}
				searchNum(P->right, x, count, output);
			}
		}
	}

	// Prosedur dekode, c berupa masukan karakter (hasil enkode), curr_c
	// merupakan karakter yang sedang dibaca, size merupakan panjang
	// array of karakter tersebut
	void decode(int size) {
		unsigned char x; unsigned char c; 
		node *_n;
		int count;
		int read;
		ifstream input("output", ios::binary | ios::in);
		ofstream output("hasil.jpg", ios::binary | ios::out);
		input.read((char*) &x, sizeof(char));	
		output.write((char*) &x, sizeof(char));
		addNewChar(x);
		count = 0; read = 1; _n = n;
		// Membaca sampai sudah tidak ada yang dapat dibaca
		while (read < size) {
			if (!(input.eof())) {
				input.read((char*) &x, sizeof(char));
				// Mengubah karakter ke bit (array of boolean)
				count = 8;
			}
			// Mengubah beberapa karakter yang telah dibaca menjadi bit
			// menjadi karakter untuk di outputkan
			while (count > 0)
			{
				// Keluar apabila sudah menghasilkan bit yang sesuai saat dibaca
				if (read >= size) {
					break;
				}
				// Apabila merupakan daun, outputkan karakter
				if (isLeaf(_n)) {
					read += 1;
					if ((_n->NYT)==true) {
							unsigned char z;
							input.read((char*) &c, sizeof(char));
							char_Bit_decode(c,x,count,output,z);
							addNewChar(z);
							_n = n;
					} else {
						unsigned char z;
						z = _n->c;
						output.write((char*) &z, sizeof(char));
						addExistingChar(z);
						_n = n;
					}
				}
				// Bergeser sesuai pohon dan bit yang diterima
				if (((x >> 7) & 1) == 0) {
					x = x << 1;
					_n = (_n-> left);
					count--;
				} else {
					x = x << 1;
					_n = (_n -> right);
					count--;
				}
			}
		}
		input.close();
		output.close();
	}
	
	// Mengubah char menjadi bit (array of boolean)
	void char_Bit_decode (unsigned char c, unsigned char &x, int &count, ostream &output, unsigned char &z) {
		if (count == 0) {	
			z = c;
			x = c;
			output.write((char*) &x, sizeof(char));
		} else {
			x = x >> (8-count);
			for (int i=0; i<(8-count); i++) {
				x = x << 1;
				x &= ~(1);
				x |= ((c >> (7-i)) & 1);
			}	
			output.write((char*) &x, sizeof(char));
			z = x;
			x = c << (8-count);
		}
	}
	
	// Mengubah char menjadi bit (array of boolean)
	void char_Bit (unsigned char c, unsigned char &x, int &count, ostream &output) {
		if (count == 0) {
			output.write((char*) &c, sizeof(char));
		} else {
			for (int i=0; i<8; i++) {
				x = x << 1;
				x &= ~(1);
				x |= (c >> (7-i)) & 1;
				count++;
				if (count == 8) {
					output.write((char*) &x, sizeof(char));
					count = 0;
				}
			}
		}
	}

	// Proses enkode adaptive huffman, arr_c merupakan hasil dari enkode,
	// disimpan menjadi array karakter, curr_c merupakan indeks c, dan
	// size merupakan banyaknya bit yang di enkode
	void encode(int &size) {
	/* Prosedur akan membaca input dan menghasilkan hasil enkripsi dari
	 * karakter yang ditulis, adaptive huffman */
		unsigned char c; 
		unsigned char x;
		int count = 0; 
		ifstream input("huffman3.exe", ios::binary | ios::in);
		ofstream output("output", ios::binary | ios::out);
		if (input != NULL)
		{
			input.read((char*) &c, sizeof(char));
			addNewChar(c);
			size+=1;
			char_Bit(c,x,count,output);
			input.read((char*) &c, sizeof(char));
			while (!(input.eof())) {
				// update pohon dan mengenkripsi
				if (bSearch(getNode(),c)) {
					// karakter sudah ada
					searchNum(getNode(),c,x,count,output);
					addExistingChar(c);
					size+=1;
				} else {
					// karakter belum ada
					searchNum(getNode(),x,count,output);
					char_Bit(c,x,count,output);
					addNewChar(c);
					size+=1;
				}
				input.read((char*) &c, sizeof(char));
			} 
			if (count != 0) {
				// Menyelesaikan bit yang belum diubah dengan menambahkan
				// '0' sampai membentuk 8 bit
				x = x << (8 - count);
				output.write((char*) &x, sizeof(char));
			}
		}
		else
		{
			printf("File tidak dapat dibuka.\n");
		}
		input.close();
		output.close();
	}

	// Data
	node *n;
	
	void prin(node *P) {
		if (P != NULL) {
			if (isLeaf(P)) {
				cout << P->c << "  ";
			}
			prin(P->left);
			prin(P->right);
		}
	}
		void PrintTree (node *P, int h)
	{	/* Kamus Lokal */
		int i;
		
		/* Algoritma */
		if (P != NULL)
		{
			if (isLeaf(P)) {
				printf("%c %d\n", P->c, P->weight);
			} else {
				printf("@ %d\n", P->weight);
			}
			for (i=1; i<=h; i++)
			{
				printf(" ");
			}
			PrintTree(P->left,1+h);
			for (i=1; i<=h; i++)
			{
				printf(" ");
			}
			PrintTree(P->right,1+h);
		}
		else
		{
			printf(".\n");
		}
	}
};



int main() {
	int size = 0;
	HuffmanTree *H = new HuffmanTree;
	H->encode(size);
	delete(H);
	HuffmanTree *T = new HuffmanTree;
	T->decode(size);
	return 0;
}
