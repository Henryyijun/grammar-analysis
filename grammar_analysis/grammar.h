#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
using namespace std;

struct product {  //产生式
	string left;
	string right;
	product() {}
	product(string left, string right) {
		this->left = left;
		this->right = right;
	}
	friend ostream & operator << (ostream &out, const product &p) {
		if (p.left == "" && p.right == "")
			out << "";
		else
			out << p.left << "->" << p.right;
		return out;
	}
};
struct grammar {  //文法四元组
	set<string> Vt;
	set<string> Vn;
	vector<product> P;
	string startSymbol;
};

grammar create(string fileName) {
	grammar g;
	fstream file;
	file.open(fileName);
	bool flag = false;
	if (file.is_open()) {
		while (!file.eof()) {
			char buff[1024];
			file.getline(buff, 1024);
			string ss(buff);
			for (char c : ss) {
				if (isupper(c) && !flag) {
					g.startSymbol = string{ c };
					flag = true;
					break;
				} else {
					continue;
				}
			}
			product p;
			size_t position = ss.find("->");
			p.left = ss.substr(0, position);
			p.right = ss.substr(position + 2, ss.length() - position - 2);
			g.P.push_back(p);
			if (ss != "") {
				for (int i = 0; i < ss.length(); i++) {
					if (i == position || i == position + 1) {
						continue;
					} else if (isupper(ss[i])) {
						g.Vn.insert(string{ ss[i] });
					} else {

						g.Vt.insert(string{ ss[i] });
						
					}
				}
			}
		}

	} else {
		cout << "文件无法打开" << endl;
	}
	return g;
}

string get_type(grammar g, string symbol) {
	if (g.Vn.count(symbol) != 0) {
		return "Vn";
	} else if (g.Vt.count(symbol) != 0) {
		return "Vt";
	}
}