// grammar_analysis.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

//#include "recursion_descent1.h"
#include "prediction_analysis.h"
int main() {


	grammar g1 = create("test.txt");
	node* groot = create_tree(g1);
	print_tree(groot);
	cout << endl;
	print_tree1(groot);
	/*rd::token = "i*(i+i)#";
	node* root = rd::E();
	print_tree(root);
	cout << endl;
	print_tree1(root);*/

	node *root;
	grammar g = create("product.txt");
	root = predict(g, "i*(i+i)#");
	print_tree(root);
	cout << endl;
	print_tree1(root);
	
}
/*
E(T(F(i)C(*F((E(T(F(i)C)B(+T(F(i)C)B))))C))B)
E(T(F(i)C(*F((E(T(F(i)C)B)))C))B(+T(F(i)C)B))
*/