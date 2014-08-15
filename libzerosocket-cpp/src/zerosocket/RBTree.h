/********************************************************************************
 * XAPTUM CONFIDENTIAL
 * ________________________________________________________________
 * 
 *  [2012] - [2014] Xaptum Incorporated 
 *  All Rights Reserved.
 * 
 * NOTICE:  All information contained herein is, and remains
 * the property of Xaptum Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Xaptum Incorporated
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Xaptum Incorporated.
 * 
 * /libzerosocket-cpp/RBTree.h
 * RBTree.h
 * 
 * Created on: Aug 15, 2014
 *     Author: pradeepbarthur Inc.
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
