#include "grammar.h"
using namespace std;


grammar G;
void set_g() {
	G.Vt = set<string>{ "i", "+", "-", "*", "/" ,"(", ")"};
	G.Vn = set<string>{ "E", "B", "T", "F", "D", "A", "M",  };
	G.startSymbol = "E";
	G.P.push_back(product{ "B", "ATB" });
	G.P.push_back(product{ "E", "TB"});
	G.P.push_back(product{ "B","ε" });
	G.P.push_back(product{ "T","FD" });
	G.P.push_back(product{ "D","MFD" });
	G.P.push_back(product{ "D", "ε" });
	G.P.push_back(product{ "F","(E)" });
	G.P.push_back(product{ "F", "i" });
	G.P.push_back(product{ "A", "+" });
	G.P.push_back(product{ "A", "-" });
	G.P.push_back(product{ "M", "*" });
	G.P.push_back(product{ "M", "/" });
}


bool check(string x, grammar g) {
	for (vector<product>::iterator it = g.P.begin(); it != g.P.end(); it++) {
		if (it->left == x && it->right == "`") {
			return true;
		}
	}
	return false;
}
set<string> getfirst(string x, grammar g) {
	set<string> first;
	if (g.Vt.count(x) != 0) {
		first.insert(x);
		return first;
	} 
	if (check(x, g)) {
		first.insert("`");
	}
	for (vector<product>::iterator it = g.P.begin(); it != g.P.end(); it++) {
		if (it->left == x) {
			int i = 0;
			for (char c : it->right) {
				i++;
				string y{ c };
				set<string> temp = getfirst(y, g);
				if (temp.count("`") != 0) {
					for (string s : temp) {
						if (s != "`") {
							first.insert(s);
							if (i == it->right.length()) {
								first.insert("`");
							}
						}
					}
				} else {
					for (string s : temp) {
						if (s != "`") {
							first.insert(s);
						}
					}
					break;
				}
				temp.clear();
			}
		}
	}
	return first;
}

set<string> getfollow(string x, grammar g) {
	set<string>  follow;
	if (x == g.startSymbol) {
		follow.insert("#");
		//return follow;
	}
	for (product p : g.P) {
		if (p.right.size() >= 3) {
			size_t index = p.right.find(x);
			if (index != string::npos && index != p.right.size() - 1) {
				string b{ p.right[index + 1]};
				set<string> temp = getfirst(b, g);
				if (temp.count("`") != 0) {
					for (string s : temp) {
						if (s != "`") {
							follow.insert(s);
						}
					}
					set<string> temp2 = getfollow(p.left, g);
					for (string s : temp2) {
						follow.insert(s);
					}
				} else {
					for (string s : temp) {
						follow.insert(s);
					}
				}
			}
		}
	}
	for (product p : g.P) {
		if (p.right.size() >= 2 && p.left != x) {
			size_t index = p.right.find(x);
			if (index != string::npos && index == p.right.size() - 1) {
				set<string> temp2 = getfollow(p.left, g);
				for (string s : temp2) {
					follow.insert(s);
				}
			}
		}
	}
	return follow;
}

void printfirst(grammar g) {
	cout << "非终结符得first集合:" << endl;
	for (string s : g.Vn) {
		set<string> result = getfirst(s, g);
		cout << s << ":";
		for (string x : result) {
			cout << x << " " ;
		}
		cout << endl;
	}
}

void printfollow(grammar g) {
	cout << "非终结符得follow集合:" << endl;
	for (auto s : g.Vn) {
		set<string> result = getfollow(s, g);
		cout << s << ":";
		for (string x : result) {
			cout << x << " " ;
		}
		cout << endl;
	}
}

