/*
 * TreeNode.cpp
 *
 *  Created on: Jul 31, 2011
 *      Author: Moises Osorio
 */

#include <stdlib.h>
#include <stdio.h>

#include "treenode.h"

TreeNode::TreeNode(int id) {
	this->id = id;
	
	left = NULL;
	right = NULL;
}

TreeNode::~TreeNode() {
	
}

int TreeNode::getSubtreeIds(int *ids) {
	if (left == NULL && right == NULL) {
		ids[0] = id;
		return 1;
	}
	
	int count = left->getSubtreeIds(ids);
	count += right->getSubtreeIds(ids + count);
	
	return count;
}

int TreeNode::setSubtreeIds(int *ids) {
	if (id >= 0) {
		id = ids[0];
		return 1;
	}
	
	int count = left->setSubtreeIds(ids);
	count += right->setSubtreeIds(ids + count);
	
	return count;
}

TreeNode *TreeNode::clone() {
	TreeNode *clone = new TreeNode(id);
	if (left != NULL)
		clone->setLeft(left->clone());
	if (right != NULL)
		clone->setRight(right->clone());
	
	return clone;
}

int TreeNode::getId() {
	return id;
}

void TreeNode::setLeft(TreeNode *left) {
	this->left = left;
	if (left != NULL)
		left->setParent(this);
}

void TreeNode::setRight(TreeNode *right) {
	this->right = right;
	if (right != NULL)
		right->setParent(this);
}

TreeNode *TreeNode::getLeft() {
	return left;
}

TreeNode *TreeNode::getRight() {
	return right;
}

void TreeNode::setParent(TreeNode *parent) {
	this->parent = parent;
}

TreeNode *TreeNode::getParent() {
	return parent;
}

string TreeNode::toString() {
	if (left == NULL && right == NULL) {
		char buffer[10];
		snprintf(buffer, sizeof(buffer), "%d", id);
		return string(buffer);
	}
	
	return "(" + (left == NULL ? "NULL" : left->toString()) + "," + (right == NULL ? "NULL" : right->toString()) + ")";
}
