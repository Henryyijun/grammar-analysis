/*
E->TB
B->ATB
B->`
T->FC
C->MFC
C->`
F->(E)
F->i
A->+
A->-
M->*
M->/
E(T(F(i)C(*F((E(T(F(i)C)B(+T(F(i)C)B))))C))B)
E(T(F(i)C(*F((E(T(F(i)C)B(+T(F(i)C)B))))C))B)
*/
#include <string>
#include "syntax_tree.h"
using namespace std;
namespace rd1 {
	string token;
	int k = 0;
	grammar g = create("product.txt");
	node *root = NULL;
	bool E();
	bool T();
	bool B();
	bool A();
	bool F();
	bool C();
	bool M();


	bool match(char c, char p) {
		return c == p;
	}
	bool E() {
		root = new node("E", get_type(g, "E"));
		cout << "E(";
		char c = token[k];
		string temp = string{ c };
		if (getfirst("E", g).count(temp) != 0 || (getfirst("E", g).count("`") != 0 && getfollow("E", g).count(temp) != 0)) {
			bool f1 = T();
			bool f2 = B();
			cout << ")";
			if (f1 && f2)
				cout << "分析成功" << endl;
			return f1 && f2;
		} else {
			cout << "分析失败" << endl;
		}
	}

	bool T() {
		cout << "T(";
		char c = token[k];
		string temp = string{ c };
		if (getfirst("T", g).count(temp) != 0 || (getfirst("T", g).count("`") != 0 && getfollow("T", g).count(temp) != 0)) {
			if (F()) {
				if (C()) {
					cout << ")";
					return true;
				}
			}
		}
		return false;

	}

	bool B() {
		cout << "B(";
		char c = token[k];
		string temp = string{ c };
		if (getfirst("B", g).count(temp) != 0 || (getfirst("B", g).count("`") != 0 && getfollow("B", g).count(temp) != 0)) {
			if (A()) {
				if (T()) {
					if (B()) {
						cout << ")";
						return true;
					}
				}

			}
			return true;
		} else if (A()) {
			if (T()) {
				if (B()) {
					cout << ")";
					return true;
				}
			}

		}
		return false;
	}

	bool F() {
		cout << "F(";
		char c = token[k];
		string temp = string{ c };
		if (temp == "(") {
			cout << temp;
			k++;
			if (E()) {
				char c = token[k];
				string temp = string{ c };
				if (temp == ")") {
					k++;
					return true;
				}
			}

		} else if (temp == "i") {
			cout << temp << ")";
			k++;
			return true;
		}
		return false;
	}

	bool C() {
		cout << "C(";
		char c = token[k];
		string temp = string{ c };
		if (getfirst("C", g).count(temp) != 0 || (getfirst("C", g).count("`") != 0 && getfollow("C", g).count(temp) != 0)) {
			if (M()) {
				if (F()) {
					if (C()) {
						cout << ")";
						return true;
					}
				}
			}
			return true;
		} else if (M()) {
			if (F()) {
				if (C()) {
					cout << ")";
					return true;
				}
			}
		}
		return false;
	}
	bool A() {
		char c = token[k];
		string temp = string{ c };
		if (temp == "+") {
			cout << temp;
			k++;
			return true;
		} else if (temp == "-") {
			cout << temp;
			k++;
			return true;
		}
		return false;
	}

	bool M() {
		char c = token[k];
		string temp = string{ c };
		if (temp == "*") {
			cout << temp;
			k++;
			return true;
		} else if (temp == "/") {
			cout << temp;
			k++;
			return true;
		}
		return false;
	}
}