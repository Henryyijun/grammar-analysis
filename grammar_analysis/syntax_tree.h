
#include "analysis.h"
#include <deque>
const int MAXNODESIZE = 10;
struct node {
	vector<node*> children;
	string value;
	string nodekind;

	node(string v, string nk) {
		value = v;
		nodekind = nk;
	}
};


int check(string left, deque<node*> nodes) {
	for (int i = 0; i < nodes.size(); i++) {
		if (left == nodes[i]->value) {
			return i;
		}
	}
	return -1;
}
node* create_tree(grammar g) {
	node *root = new node(g.startSymbol, get_type(g, g.startSymbol));;
	node *tail = root;
	deque<node*> nodes;
	nodes.push_back(root);
	for (product p : g.P) {
		int index = check(p.left, nodes);
		node* n = nodes[index];
		if (index != -1) {
			nodes.erase(nodes.begin() + index);
			for (char s : p.right) {
				node* temp = new node(string{ s }, get_type(g, string{ s }));
				n->children.push_back(temp);
				nodes.push_front(temp);
			}
		} 
	}
	return root;
}

node* create_tree(grammar g, vector<product> ps) {
	node *root = new node(g.startSymbol, get_type(g, g.startSymbol));;
	node *tail = root;
	deque<node*> nodes;
	nodes.push_back(root);
	for (product p : ps) {
		int index = check(p.left, nodes);
		node* n = nodes[index];
		if (index != -1) {
			nodes.erase(nodes.begin() + index);
			for (char s : p.right) {
				node* temp = new node(string{ s }, get_type(g, string{ s }));
				n->children.push_back(temp);
				nodes.push_front(temp);
			}
		} else {

		}

	}
	return root;
}

void print_tree(node *root) {
	if (root != NULL && root->nodekind == "Vn" && root->value != "`") {
		if (root->children.size() > 0) {
			cout << root->value << '(';
			for (node* n : root->children) {
				print_tree(n);

			}
			cout << ")";
		} else {
			cout << root->value;
		}
	} 
	else if (root != NULL && root->nodekind == "Vt" && root->value != "`") {
		cout << root->value;
	}
}
void print_left(node* root) {
	if (root != NULL) {
		if (root->children.size() == 0) {
			cout << root->value;
		}
		for (node* n : root->children) {
			print_left(n);
		}
	}
}
int indentno = 0;
#define INDENT  indentno += 2
#define UNINDENT indentno -= 2
void printSpaces() {
	int i;
	for (i = 0; i < indentno; i++)
		cout << " ";
}

void print_tree1(node* root) {
	INDENT;
	printSpaces();
	if (root != NULL && root->nodekind == "Vn") {
		
		if (root->children.size() > 0) {
			cout << root->value << '{' << endl;
			for (node* n : root->children) {			
				print_tree1(n);			
			}
			printSpaces();
			cout << "}" << endl;
		} else {
			cout << root->value << endl;
		}
		
	} else if (root != NULL && root->nodekind == "Vt") {
		cout << root->value << endl;
	}
	UNINDENT;
	//
	
}


/*
S->ABCD
A->aA
B->AB
B->b
D->d

*/