#include "polinom.h"

using namespace std;

class Node
{
public:
	string key;
	Polinom pol;
	Node* left;
	Node* right;
	int height;
	Node(const string &key, Polinom &pol): 
		key(key),pol(pol),left(nullptr), right(nullptr),height(1) {}
};

class AVLtree
{
private:
	Node* root;
	int Height(Node* node)
	{
		if (node == nullptr)
			return 0;
		else
			return node->height;
	}
	int Balance(Node* node)
	{
		if (node == nullptr)
			return 0;
		else
			return (Height(node->left) - Height(node->right));
	}
	Node* LeftR(Node* L)
	{
		Node* R1 = L->right;
		Node* L2 = R1->left;

		R1->left = L;
		L->right = L2;

		L->height = max(Height(L->left), Height(L->right)) + 1;
		R1->height = max(Height(R1->left), Height(R1->right)) + 1;

		return R1;
	}
	Node* RightR(Node* R)
	{
		Node* L1 = R->left;
		Node* R2 = L1->right;


		L1->right = R;
		R->left = R2;

		R->height = max(Height(R->left), Height(R->right)) + 1;
		L1->height = max(Height(L1->left), Height(L1->right)) + 1;

		return L1;
	}
	Node * minNode(Node* node) 
	{
		Node* cur = node;
		while (cur->left != nullptr) 
			cur = cur->left;
		return cur;
	}
	Node* search(const string& key)
	{
		Node* node = root;
		while (node != nullptr && key != node->key) 
			if (key < node->key)
				node = node->left;
			else
				node = node->right;

		return node;
	}
	Node* Insert(Node* node, const string& key, Polinom poli)
	{
		if (!node) 
			return new Node(key, poli);

		if (key < node->key)
			node->left = Insert(node->left, key, poli);
		else if (key > node->key)
			node->right = Insert(node->right, key, poli);
		else
			node->pol = poli;

		node->height = max(Height(node->left), Height(node->right)) + 1;
		int bal = Balance(node);

		if ((bal > 1) && (key < (node->left)->key))
			return RightR(node);

		if ((bal < -1) && (key > (node->right)->key))
			return LeftR(node);

		if ((bal > 1) && (key > (node->left)->key))
		{
			node->left = LeftR(node->left);
			return RightR(node);
		}

		if ((bal < -1) && (key < (node->right)->key))
		{
			node->right = RightR(node->right);
			return LeftR(node);
		}
		return node;
	}
	Node* Remove(Node* node, const string& key)
	{
		if (!node)
			return node;
		if (key < node->key)
			node->left = Remove(node->left, key);
		else if (key > node->key)
			node->right = Remove(node->right, key);
		else
		{
			if ((!node->left) || (!node->right))
			{
				Node* tmp = node->left ? node->left : node->right;
				if (!tmp)
				{
					tmp = node;
					node = nullptr;
				}
				else
					*node = *tmp;
				delete tmp;
			}
			else
			{
				Node* tmp = minNode(node->right);
				node->key = tmp->key;
				node->pol = tmp->pol;
				node->right = Remove(node->right, tmp->key);
			}
		}

		if (!node) return node;

		node->height = max(Height(node->left), Height(node->right)) + 1;
		int bal = Balance(node);

		if ((bal > 1) && (Balance(node->left) >= 0))
			return RightR(node);

		if ((bal < -1) && (Balance(node->right) <= 0))
			return LeftR(node);

		if ((bal > 1) && (Balance(node->left) >= 0))
		{
			node->left = LeftR(node->left);
			return RightR(node);
		}

		if ((bal < -1) && (Balance(node->right) > 0))
		{
			node->right = RightR(node->right);
			return LeftR(node);
		}
		return node;
	}
	void Print(Node* node)
	{
		if (node != nullptr) 
		{
			Print(node->left);
			cout << node->key << ": ";
			node->pol.Print();
			cout << endl;
			Print(node->right);
		}
	}
public:
	AVLtree() : root(nullptr) {}
	void Delete(Node* node)
	{
		if (node == nullptr)
			return;

		Delete(node->left);
		Delete(node->right);
		delete node;
	}
	~AVLtree()
	{
		Delete(root);
	}
	void addPol(const string& key, Polinom& poli)
	{
		root = Insert(root, key, poli);
	}
	void delPol(const string& key)
	{
		root = Remove(root, key);
	}
	Polinom* searchPol(const string& key)
	{
		Node* node = search(key);
		if (node != nullptr) 
			return &node->pol;
		else 
			return nullptr;
	}
	void Print()
	{
		Print(root);
	}
};