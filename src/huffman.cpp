#include <string> 
#include <bitset> 
#include <iostream>
using namespace std;

struct node
{
	unsigned char c;
	int weight;
	int order;
	node *left;
	node *right;
	node *parent;
	bool NYT;
};

class HuffmanTree {
public:
	
	HuffmanTree() {
		b = new bool[16];
		n = new node;
		n->weight = 0;
		n->order = 513;
		n->NYT = true;
		n->left = NULL;
		n->right = NULL;
		n->parent = NULL;
	}
	
	~HuffmanTree() {
        dealokasi(n);
    }
    	
	void dealokasi(node *P) {
		if (P != NULL) {
			dealokasi(P->left);
			dealokasi(P->right);
			delete(P);
		}
	}
	
	void addNextChar(unsigned char _c) {
		if (bSearch(n,_c)) {
			addExistingChar(_c);
		} else {
			addNewChar(_c);
		}
	}
	
	void addNewChar(unsigned char _c) {
		node *_n = search(n);
		_n->left = new node;
		_n->right = new node;
		_n->left->left = NULL;
		_n->left->right = NULL;
		_n->right->left = NULL;
		_n->right->right = NULL;
		_n->right->parent = _n;
		_n->left->parent = _n;
		_n->NYT = false;
		_n->right->NYT = false;
		_n->left->NYT = true;
		_n->right->order = _n->order - 1;
		_n->left->order = _n->order - 2;
		_n->right->weight = 1;
		_n->left->weight = 0;
		_n->right->c = _c;
		update(_n);
	}
	
	void addExistingChar(unsigned char _c) {
		node *_n = search(n,_c);
		update(_n);
	}
    
    void update(node *P) {
		if (P != NULL) {
			P->weight++;
		}
		if (P->parent != NULL) {
			if (check(P)) {
				update(P);
			} else {
				update(P->parent);
			}
		}
	}
	
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
	
    void swap(node *P, node *_P) {
		int _order;
		swapParent(P,_P);
		_order = P->order;
		P->order = _P->order;
		_P->order = _order;
	}
	
	// Search
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

	bool bSearch(node *P, unsigned char _c) {
		if (P == NULL) {
			return false;
		}
		else if (P->c == _c) {
			return true;
		}
		else {
			return (bSearch(P->left, _c) || bSearch(P->right, _c));
		}
	}
		
	node *search(node *P) {
		if (P == NULL) {
			return NULL;
		} else if (P->NYT == true) {
			return P;
		} else if (bSearch(P->left)) {
			return search(P->left);
		} else if (bSearch(P->right)) {
			return search(P->right);
		} else {
			return NULL;
		}
	}
	
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
	
	node *search(node *P, unsigned char _c) {
		if (P == NULL) {
			return NULL;
		} else if (P->c == _c) {
			return P;
		} else if (bSearch(P->left, _c)) {
			return search(P->left, _c);
		} else if (bSearch(P->right, _c)) {
			return search(P->right, _c);
		} else {
			return NULL;
		}
	}
	
	void searchNum(node *P, unsigned char _c, int *num) {
		if (P != NULL) {
			if (P->c == _c) {
				cout << endl;
			} else if (bSearch(P->left, _c)) {
				b[*num] = false;
				*num = *num + 1;
				cout << 0;
				searchNum(P->left, _c, num);
			} else if (bSearch(P->right, _c)) {
				b[*num] = true;
				*num = *num + 1;
				cout << 1;
				searchNum(P->right, _c, num);
			}
		}
	}
	
	void searchNum(node *P, int *num) {
		if (P != NULL) {
			if (P->NYT) {
			} else if (bSearch(P->left)) {
				b[*num] = false;
				*num = *num + 1;
				searchNum(P->left, num);
			} else if (bSearch(P->right)) {
				b[*num] = true;
				*num = *num + 1;
				searchNum(P->right, num);
			}
		}
	}	
	
	bool *getBit() {
		return b;
	}
	
	node *getNode() {
		return n;
	}
	
	void decode(unsigned char *c, int curr_c) {
		int current = 0;
		int curr_b = 0;
		node *_n;
		bool *_b = new bool [64];
		_n = n;
		addNewChar(c[current]);
		cout << c[current];
		current++;
		while (current <= curr_c) {
			if (current != curr_c) {
				char_Bit(_b,c[current],&curr_b);
			}
			current++;
			bit_Char(_b,c,&curr_b,&current,_n);
		}
	}

	void char_Bit(bool *_b, unsigned char c, int *current) {
		for(int i = *current; i < (*current+8); i++) {
			_b[i] = (c >> (*current+7-i)) & 1;
		}		
		*current += 8;
	}
	
	bool isLeaf(node *_n) {
		if ((_n->left == NULL) && (_n->right == NULL)) {
			return true;
		} else {
			return false;
		}
	}
	
	void bit_Char(bool *_b, unsigned char *c, int *curr_b, int *current, node *_n) {
		unsigned char _c;
		for(int i = 0; i < *curr_b; i++)
		{
			if (isLeaf(_n)) {
				if (_n->NYT) {
					if (*curr_b-i >= 8) {
						bitChar(_b,&_c,i,curr_b);
						cout << _c;
						addNewChar(_c);
					} else {
						char_Bit(_b,c[*current],curr_b);
						bitChar(_b,&_c,i,curr_b);
						addNewChar(_c);
						cout << _c;
						_n=n;
						break;
					}
				} else {
					_c = _n->c;
					addExistingChar(_c);
					cout << _c;
				}
				_n = n;
			}
			if (_b[i] == 0) {
				_n = _n-> left;
			} else {
				_n = _n -> right;
			}

		}
		*curr_b -= 8;
	}

	void bitChar(bool *_b, unsigned char *c, int start, int *curr_b) {
		for(int i = start; i < start+8; i++) {
			*c &= ~(1 << (7 + start - i));
			*c |= (_b[i] & 1) << (7 +start - i);
		}
		for(int i = start+8; i < start+8+*curr_b; i++) {
			_b[i-start-8]=_b[i];
			_b[i]=0;
		}		
		*curr_b -= 8;
		*curr_b -= start;
	}
	
	void bit_Char(bool *_b, unsigned char *c, int *curr_b, int *curr_c) {
		while (*curr_b >= 8) {
			for(int i = 0; i < 8; i++) {
				c[*curr_c] &= ~(1 << (7-i));
				c[*curr_c] |= (_b[i] & 1) << (7 - i);
				_b[i] = 0;
			}
			*curr_b -= 8;
			for(int i = 8; i < 8+*curr_b; i++) {
				_b[i-8]=_b[i];
				_b[i]=0;
			}
			*curr_c += 1;
		}
	}
	
	void combine(bool* a, bool* b, int *curr_b, int j) {
		int i;
		for (i=*curr_b;i<(*curr_b+j);i++) {
			a[i] = b[i-*curr_b];
		}
		*curr_b += j;
	}
		
	void encode(unsigned char *arr_c, int *curr_c) {
		unsigned char c; 
		int i;
		int j;
		int curr_b = 0;
		bool *_b = new bool [64];
		cin >> c;
		addNewChar(c);
		char_Bit(_b,c,&curr_b);
		bit_Char(_b,arr_c,&curr_b,curr_c);
		cin >> c;
		while (c != 'z') {
			if (bSearch(getNode(),c)) {
				j = 0;
				searchNum(getNode(),c,&j);
				combine(_b,getBit(),&curr_b,j);
				bit_Char(_b,arr_c,&curr_b,curr_c);
				addExistingChar(c);
			} else {
				j = 0;
				searchNum(getNode(),&j);
				combine(_b,getBit(),&curr_b,j);
				char_Bit(_b,c,&curr_b);
				bit_Char(_b,arr_c,&curr_b,curr_c);
				addNewChar(c);
			}
			cin >> c;
		}
		if (curr_b != 0) {
			for (i=curr_b;i<8;i++) {
				_b[i] = 0;
			}
			curr_b = 8;
			bit_Char(_b,arr_c,&curr_b,curr_c);
		}
		delete(_b);
	}

	// Data
	node *n;
	bool *b;
};



int main() {
	unsigned char *arr_c = new unsigned char[64];
	HuffmanTree H; HuffmanTree T;
	int curr_c = 0;
	H.encode(arr_c,&curr_c);
	for (int i=0;i<curr_c;i++) {
		cout << arr_c[i];
		cout << endl;
	}
	T.decode(arr_c,curr_c);
	return 0;
	/*a 01100001
2 00110010
? 00111111*/
}
			
