/*
 * Tree.h
 *
 *  Created on: Jul 31, 2011
 *      Author: Moises Osorio
 */

#ifndef TREE_H_
#define TREE_H_

#include <stdlib.h>
#include <string>

#include "treenode.h"

using namespace std;

class Tree {
public:
	Tree();
	virtual ~Tree();
	
	void setRoot(TreeNode *root);
	TreeNode *getRoot();
	Tree *clone();
	bool isValid(int n);
	string toString();
	
private:
	TreeNode *root;
	
	void destroySubtree(TreeNode *root);
};

#endif /* TREE_H_ */
