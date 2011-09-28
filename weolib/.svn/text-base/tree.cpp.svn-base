/*
 * Tree.cpp
 *
 *  Created on: Jul 31, 2011
 *      Author: Moises Osorio
 */

#include "tree.h"

Tree::Tree() {
	root = NULL;
}

Tree::~Tree() {
	if (root != NULL) {
		destroySubtree(root);
		root = NULL;
	}
}

void Tree::setRoot(TreeNode *root) {
	this->root = root;
	root->setParent(NULL);
}

TreeNode *Tree::getRoot() {
	return root;
}

string Tree::toString() {
	return root->toString();
}

bool Tree::isValid(int n) {
	int *ids = new int[n];
	root->getSubtreeIds(ids);
	
	bool ok = true;
	for (int i = 0; i < n && ok; i++)
		if (ids[i] < 0 || ids[i] >= n)
			ok = false;
		else
			for (int j = 0; j < i && ok; j++)
				if (ids[i] == ids[j])
					ok = false;
	
	delete [] ids;
	return ok;
}

Tree *Tree::clone() {
	Tree *clone = new Tree();
	clone->setRoot(root->clone());
	return clone;
}

void Tree::destroySubtree(TreeNode *root) {
	if (root == NULL)
		return;
	
	destroySubtree(root->getLeft());
	destroySubtree(root->getRight());
	delete root;
}
