#pragma once
#include<iostream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <unordered_map>

using namespace std;
struct Quote {
	float price = 0.f;
	uint32_t size = 0;
};

struct BidAskPair {
	Quote bid;
	Quote ask;
};
struct TreeNode{
	float price;
	TreeNode* left;
	TreeNode* right;
	unordered_map<char, Quote> treeList;
};
class Tree
{
public:
	Tree();
	int max(int a, int b){
		return (a > b ? a : b);
	}
	int height(TreeNode *temp){
		int h = 0;
		if (temp != NULL)
		{
			int l_height = height(temp->left);
			int r_height = height(temp->right);
			int max_height = max(l_height, r_height);
			h = max_height + 1;
		}
		return h;
	}

	TreeNode* createTreeNode(Quote bid){
		TreeNode* node = new TreeNode();
		node->price = bid.price;
		node->left = NULL;
		node->right = NULL;
		return node;
	}
	int diff(TreeNode *temp)
	{
		int l_height = height(temp->left);
		int r_height = height(temp->right);
		int b_factor = l_height - r_height;
		return b_factor;
	}
	TreeNode *rr_rotation(TreeNode *parent)
	{
		TreeNode *temp;
		temp = parent->right;
		parent->right = temp->left;
		temp->left = parent;
		return temp;
	}
	TreeNode* ll_rotation(TreeNode *parent)
	{
		TreeNode *temp;
		temp = parent->left;
		parent->left = temp->right;
		temp->right = parent;
		return temp;
	}
	TreeNode* lr_rotation(TreeNode *parent)
	{
		TreeNode *temp;
		temp = parent->left;
		parent->left = rr_rotation(temp);
		return ll_rotation(parent);
	}
	TreeNode* rl_rotation(TreeNode *parent)
	{ 
		TreeNode *temp;
		temp = parent->right;
		parent->right = ll_rotation(temp);
		return rr_rotation(parent);
	}
	TreeNode* balance(TreeNode *temp)
	{
		if (temp == NULL)
			return temp;
		int bal_factor = diff(temp);
		if (bal_factor > 1)
		{
			if (diff(temp->left) > 0)
				temp = ll_rotation(temp);
			else
				temp = lr_rotation(temp);
		}
		else if (bal_factor < -1)
		{
			if (diff(temp->right) > 0)
				temp = rl_rotation(temp);
			else
				temp = rr_rotation(temp);
		}
		return temp;
	}
	TreeNode* insertNode(TreeNode *root, Quote bid, char exch)
	{
		if (root == NULL)
		{
			root = createTreeNode(bid);
			root->treeList[exch] = bid;
		}
		else if (bid.price < root->price)
		{
			root->left = insertNode(root->left, bid, exch);
			root = balance(root);
		}
		else if (bid.price > root->price)
		{
			root->right = insertNode(root->right, bid, exch);
			root = balance(root);
		}
		else{
			root->treeList[exch] = bid;
		}
		return root;
	}
	TreeNode* minValueNode(TreeNode* node)
	{
		if (!node)
			return NULL;
		TreeNode* current = node;
		while (current->left != NULL)
			current = current->left;

		return current;
	}
	TreeNode* deleteNode(TreeNode* root, Quote quote, char exch)
	{
		if (root == NULL)
			return root;
		if (quote.price < root->price)
			root->left = deleteNode(root->left, quote, exch);

		else {
			if (quote.price > root->price){
				root->right = deleteNode(root->right, quote, exch);
			}
			else{
				if (root->treeList.size() > 1){
					root->treeList.erase(exch);
				}
				else{
					if ((root->left == NULL) || (root->right == NULL)){
						TreeNode *temp = root->left ? root->left : root->right;
						if (temp == NULL)
						{
							temp = root;
							root = NULL;
						}
						else {
							TreeNode* swap = root;
							root = temp;
							temp = swap;
						}
						free(temp);
					}
					else{
						TreeNode* temp = minValueNode(root->right);
						root->price = temp->price;
						root->treeList = temp->treeList;
						quote.price = temp->price;
						temp->treeList.clear();
						root->right = deleteNode(root->right, quote, exch);
					}
				}
			}
		}
		balance(root);
		return root;
	}
	~Tree();
};

