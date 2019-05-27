#include <string>
#include "syntax_tree.h"
using namespace std;
namespace rd {
	string token;
	int k = 0;
	grammar g = create("product.txt");
	
	node* E();
	node* T();
	node* B();
	node* A();
	node* F();
	node* C();
	node* M();

	node* E() {
		node *root = new node("E", get_type(g, "E"));
		char c = token[k];
		string temp = string{ c };
		if (getfirst("E", g).count(temp) != 0 || (getfirst("E", g).count("`") != 0 && getfollow("E", g).count(temp) != 0)) {
			node* f1 = T();
			node* f2 = B();
			if (f1 && f2) {
				root->children.push_back(f1);
				root->children.push_back(f2);
				cout << "分析成功" << endl;
				return root;
			}

		} else {
			cout << "分析失败" << endl;
			return NULL;
		}
	}

	node* T() {
		char c = token[k];
		string temp = string{ c };
		node* p = new node("T", get_type(g, "T"));
		if (getfirst("T", g).count(temp) != 0 || (getfirst("T", g).count("`") != 0 && getfollow("T", g).count(temp) != 0)) {
			node* f1 = F();
			if (f1) {
				node * f2 = C();
				if (f2) {
					p->children.push_back(f1);
					p->children.push_back(f2);
					return p;
				}
			}
		}
		return NULL;
	}

	node* B() {
		char c = token[k];
		string temp = string{ c };
		node* p = new node("B", get_type(g, "B"));
		if (getfirst("B", g).count(temp) != 0 || (getfirst("B", g).count("`") != 0 && getfollow("B", g).count(temp) != 0)) {
			node* f1 = A();
			if (f1) {
				node* f2 = T();
				if (f2) {
					node* f3 = B();
					if (f3) {
						p->children.push_back(f1);
						p->children.push_back(f2);
						p->children.push_back(f3);
						return p;
					}
				}
			}
			return p;
		} else {
			node* f1 = A();
			if (f1) {
				node* f2 = T();
				if (f2) {
					node* f3 = B();
					if (f3) {
						p->children.push_back(f1);
						p->children.push_back(f2);
						p->children.push_back(f3);
						return p;
					}
				}
			}
		}
		return NULL;
	}

	node* F() {
		char c = token[k];
		string temp = string{ c };
		node *p = new node("F", get_type(g, "F"));
		if (temp == "(") {
			node* f1 = new node("(", get_type(g, "("));
			p->children.push_back(f1);
			k++;
			node *f2 = E();
			if (f2) {
				p->children.push_back(f2);
				char c = token[k];
				string temp = string{ c };
				if (temp == ")") {
					node* f3 = new node(")", get_type(g, ")"));
					p->children.push_back(f3);
					k++;
					return p;
				}
			}

		} else if (temp == "i") {
			node* f4 = new node("i", get_type(g, "i"));
			p->children.push_back(f4);
			k++;
			return p;
		}
		return NULL;
	}

	node* C() {
		char c = token[k];
		string temp = string{ c };
		node* p = new node("C", get_type(g, "C"));
		if (getfirst("C", g).count(temp) != 0 || (getfirst("C", g).count("`") != 0 && getfollow("C", g).count(temp) != 0)) {
			node* f1 = M();
			if (f1) {
				p->children.push_back(f1);
				node * f2 = F();
				if (f2) {
					p->children.push_back(f2);
					node * f3 = C();
					if (f3) {
						p->children.push_back(f3);
						return p;
					}
				}
			}
			return p;
		} else {
			node* f1 = M();
			if (f1) {
				p->children.push_back(f1);
				node * f2 = F();
				if (f2) {
					p->children.push_back(f2);
					node * f3 = C();
					if (f3) {
						p->children.push_back(f3);
						return p;
					}
				}
			}
		}
		return NULL;
	}
	node* A() {
		char c = token[k];
		string temp = string{ c };
		if (temp == "+") {
			node *p = new node("+", get_type(g, "+"));
			k++;
			return p;
		} else if (temp == "-") {
			node *p = new node("-", get_type(g, "-"));
			k++;
			return p;
		}
		return NULL;
	}

	node* M() {
		char c = token[k];
		string temp = string{ c };
		if (temp == "*") {
			node *p = new node("*", get_type(g, "*"));
			k++;
			return p;
		} else if (temp == "/") {
			node *p = new node("/", get_type(g, "/"));
			k++;
			return p;
		}
		return NULL;
	}
}