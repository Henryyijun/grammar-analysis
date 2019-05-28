#include <string>
#include <vector>
#include <map>
#include <stack>
#include <iostream>
#include <iomanip>
#include "syntax_tree.h"
const int row = 10;
const int col = 10;
vector<vector<product>> table (row, vector<product>(col, product{ "", "" }));
map<string, int> m;
void set_map(grammar g) {
	g.Vt.insert("#");
	int i = 0;
	int k = 0;
	for (string s : g.Vn) {
		m[s] = i++;
	}
	for (string s : g.Vt) {
		m[s] = k++;
	}
	
	/*m["E"] = 0;
	m["B"] = 1;
	m["T"] = 2;
	m["C"] = 3;
	m["F"] = 4;
	m["A"] = 5;
	m["M"] = 6;

	m["i"] = 0;
	m["+"] = 1;
	m["-"] = 2;
	m["*"] = 3;
	m["/"] = 4;
	m["("] = 5;
	m[")"] = 6;
	m["#"] = 7;*/
}
void set_table(grammar g) {
	/*table[0][0] = product{ "E", "TB" };
	table[0][5] = product{ "E", "TB" };

	table[1][1] = product{ "B", "ATB" };
	table[1][2] = product{ "B", "ATB" };
	table[1][6] = product{ "B", "`" };
	table[1][7] = product{ "B", "`" };

	table[2][0] = product{ "T", "FC" };
	table[2][5] = product{ "T", "FC" };

	table[3][1] = product{ "C", "`" };
	table[3][2] = product{ "C", "`" };
	table[3][3] = product{ "C", "MFC" };
	table[3][4] = product{ "C", "MFC" };
	table[3][6] = product{ "C", "`" };
	table[3][7] = product{ "C", "`" };

	table[4][0] = product{ "F", "i" };
	table[4][5] = product{ "F", "(E)" };

	table[5][1] = product{ "A", "+" };
	table[5][2] = product{ "A", "-" };

	table[6][3] = product{ "M", "*" };
	table[6][4] = product{ "M", "/" };*/
	g.Vt.insert("#");
	for (product p : g.P) {
		string row = p.left;
		string right = p.right;
		set<string> first = getfirst(string{ p.right[0] }, g);
		set<string> follow = getfollow(string{ p.left[0] }, g);
		for (string a : g.Vt) {
			if (first.count(a) != 0) {
				table[m[p.left]][m[a]] = p;
			}
			if (first.count("`") != 0 && follow.count(a) != 0) {
				table[m[p.left]][m[a]] = p;
			}
		}
	}

}

void print_table(grammar g) {
	g.Vt.insert("#");
	cout << "       " << setw(5);
	for (string v : g.Vt) {
		cout  <<  "|" << setw(6) << v << setw(6);
	}
	cout << endl;
	for (string v : g.Vn) {
		cout << v << setw(5);
		for (string vv : g.Vt) {
			product &p = table[m[v]][m[vv]];
			if (p.left == "" && p.right == "") {
				cout << "|" << setw(5) << "      " << setw(5);;
			} else {
				
				//cout << setiosflags(ios::right);
				//cout.fill(' ');
				cout << "|" << setw(5) << p << setw(2);
			}
		}
		cout << endl;
	}
	cout << endl;
	
}
void print_stack(stack<string>  s) {
	stack<string> ss;
	while (s.empty() == false) {
		ss.push(s.top());
		s.pop();
	}
	while (ss.empty() == false) {
		cout << ss.top();
		ss.pop();
	}
}
node* predict(grammar g, string token) {
	node *root = NULL;
	vector<product> ps;
	set_map(g);
	set_table(g);
	stack<string> s;
	s.push("#");
	s.push(g.startSymbol);
	product p;
	int index = 0;
	cout << "步骤      分析栈      余留剩余串     产生式" << endl;
	bool flag = true;
	int i = 0;
	while (s.top() != "#") {
		i++;
		if (g.Vt.count(s.top()) != 0 || s.top() == "#") {
			if (s.top() == string{ token[index] }) {
				s.pop();
				index++;
			} else {
				cout << "error" << endl;
				flag = false;
				break;
			}
			
		} else if (g.Vn.count(s.top()) != 0) {
			p = table[m[s.top()]][m[string{ token[index] }]];
			ps.push_back(p);
			if (p.left != "" && p.right != "") {
				if (p.right == "`") {
					s.pop();
				} else {
					s.pop();
					string right = p.right;
					for (int i = right.size() - 1; i >= 0; i--) {
						s.push(string{ right[i] });
					}
				}
	
			} else {
				cout << "error" << endl;
				flag = false;
				break;
			}
		}
		cout << i << "          ";
		print_stack(s);
		cout << "        ";
		cout << token.substr(index);
		cout << "        ";
		cout << p << endl;
		p = product{ "", "" };
		
	}
	if (flag) {
		root = create_tree(g, ps);
		cout << "分析成功" << endl;
	}
	
	return root;
}

