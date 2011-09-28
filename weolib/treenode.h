/*
 * TreeNode.h
 *
 *  Created on: Jul 31, 2011
 *      Author: Moises Osorio
 */

#ifndef TREENODE_H_
#define TREENODE_H_

#include <stdlib.h>
#include <string>

using namespace std;

class TreeNode {
public:
	TreeNode(int id);
	virtual ~TreeNode();
	
	int getId();
	void setLeft(TreeNode *left);
	void setRight(TreeNode *right);
	void setParent(TreeNode *parent);
	TreeNode *getLeft();
	TreeNode *getRight();
	TreeNode *getParent();
	
	int getSubtreeIds(int *ids);
	int setSubtreeIds(int *ids);
	TreeNode *clone();
	string toString();
	
private:
	int id;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
};

#endif /* TREENODE_H_ */
