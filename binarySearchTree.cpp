//Anthony Gatte

#include<iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

struct Node{
	string word;
	Node* left;
	Node* right;
};

class BinarySearchTree{
private:

public:
	Node* root;

	string word;
	string word2;

	BinarySearchTree(){
		root = NULL;
	}

/*Insert function looks left or right, and chooses the right location for a value.
	Lower values go on the left, higher values go on the right
	O(log n)*/

	void insert (string x){
		if (root == NULL){
			root = new Node;
			root-> word = x;
			root-> left = root->right = NULL;
		}
		else{
			Node* node = new Node;
			node-> word = x;
			node-> left = node->right = NULL;

			Node* check = root;
			Node* found = NULL;

			while (check != NULL){
				found = check;

				if (x == check-> word)
					return;

				if (x < check-> word)
					check = check-> left;
				else
					check = check-> right;
			}

			if (x < found-> word)
				found-> left = node;
			else
				found-> right = node;
		}
	}


//Θ(log n)

	void remove (string x){
		Node* node = root;
		Node* rear = NULL;
		string l = "";

		if (root-> word == x){
			if (root-> right != NULL){
				(root-> right)-> left = root-> left;
				root = root-> right;
			}
			else if (root-> left != NULL){
				(root-> left)-> right = root-> right;
				root = root-> left;
			}
			else{
				root = NULL;
			}
			return;
		}

		while (node != NULL){
			if (node-> word == x){
				if (l == "l")
					rear-> left = node-> left;
				else
					rear-> right = node-> right;

				break;
			}

			rear = node;
			if (x < node-> word){
				node = node-> left;
				l = "l";
			}
			else{
				node = node-> right;
				l = "r";
			}
		}
	}


//Θ(log n).

void inorder(Node* node){
		if (node != NULL){
			inorder (node-> left);
			cout << node-> word << endl;
			inorder (node-> right);
		}
	}

	void inorder(){
		inorder (root);
	}
};

int main(){
	string fileName1, fileName2;
	cout << "Enter first file name:  ";
	cin >> fileName1;
	cout << "Enter second file name: ";
	cin >> fileName2;


BinarySearchTree tree1;
BinarySearchTree tree2;
BinarySearchTree tree3;

string word;
string word2;

/*
tree1: insert all words from file1, remove all words from  file2
tree2: insert all words from file2, remove all words from  file1
tree3: insert only common words from both files
This will then make it so I can find the words that are only in the first file,
the words that are only in the second file, and words that are in both
*/

ifstream file1 (fileName1.c_str());
	while (getline (file1, word)){
		tree1.insert (word);
	}
	file1.close();

	ifstream file2 (fileName2.c_str());
	while (getline (file2, word)){
		tree1.remove (word);
		tree2.insert (word);
	}
	file2.close();

	file1.open (fileName1.c_str());
	while (getline (file1, word)){
		tree2.remove (word);
	}
	file1.close();

	//Tree 3
	file1.open (fileName1.c_str());
	file2.open (fileName2.c_str());
	while (getline (file1, word) && getline (file2,word2)){
		if (word == word2)
			tree3.insert (word);
	}
	file1.close();
	file2.close();

	cout << "Items in " << fileName1 << " and not in " << fileName2 << ":" << endl;
	tree1.inorder();
	cout << "Items in " << fileName2 << " and not in " << fileName1 << ":" << endl;
	tree2.inorder();
	cout << "Items in both files:" << endl;
	tree3.inorder();

	return 0;
	}
