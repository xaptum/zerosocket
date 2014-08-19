/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *
 * Created on:Aug 13, 2014
 *     Author: Pradeep Barthur
 ********************************************************************************/

#ifndef RBTREE_H_
#define RBTREE_H_
namespace zerosocket {
class Connection;
} /* namespace zerosocket */

namespace zerosocket {

class RBNode {
	friend class RBTree;
public:
	RBNode();
	RBNode(Connection * obj);
	virtual ~RBNode();

	Connection * GetEntry() const;
	//void Print(RBNode*, RBNode*) const;
protected:
	Connection * storedEntry;
	int key;
	int red; /* if red=0 then the node is black */
	RBNode * left;
	RBNode * right;
	RBNode * parent;
};

/*
 *
 */
class RBTree {
public:
	RBTree();
	virtual ~RBTree();
	void print() const;
	Connection * deleteNode(RBNode * node);
	RBNode * insert(Connection * obj);
	RBNode * getPredecessor(RBNode * node) const;
	RBNode * getSuccessor(RBNode * node) const;
	RBNode * get(int key);
	//TemplateStack<RedBlackTreeNode *> * Enumerate(int low, int high) ;
	void check() const;
private:
	RBNode * root;
	RBNode * nil;
	void LeftRotate(RBNode * node);
	void RightRotate(RBNode * node);
	void TreeInsertHelp(RBNode * node);
	void TreePrintHelper(RBNode * node) const;
	void FixUpMaxHigh(RBNode * node);
	void DeleteFixUp(RBNode * node);
};

} /* namespace zerosocket */

#endif /* RBTREE_H_ */
