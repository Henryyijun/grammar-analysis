// grammar_analysis.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

//#include "recursion_descent1.h"
#include "prediction_analysis.h"
int main() {
	/*grammar g1 = create("test.txt");
	node* groot = create_tree(g1);
	print_tree(groot);
	cout << endl;
	print_tree1(groot);
	cout << endl;
	print_left(groot);
	cout << endl;
	cout << "递归下降分析法!!!" << endl;
	rd::token = "i+i+(i-i)#";
	cout << "分析的输入串为:" << rd::token << endl;
	node* root = rd::E();
	cout << "语法树为:";
	print_tree(root);
	cout << endl;
	cout << rd::token[rd::k] << endl;
	//print_tree1(root);
	
	node *root;
	grammar g = create("product.txt");
	root = predict(g, "i+i*i#");
	print_tree(root);
	cout << endl;
	print_tree1(root);*/
	grammar g = create("product.txt");
	printfirst(g);
	printfollow(g);
	set_map(g);
	set_table(g);
	print_table(g);
	
}
/*
E(T(F(i)C(*F((E(T(F(i)C)B(+T(F(i)C)B))))C))B)
E(T(F(i)C(*F((E(T(F(i)C)B)))C))B(+T(F(i)C)B))
|| (getfirst("B", g).count("`") != 0 && getfollow("B", g).count(temp) != 0)
*/