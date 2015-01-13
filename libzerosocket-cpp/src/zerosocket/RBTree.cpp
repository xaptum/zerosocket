/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *
 * Created on:Aug 13, 2014
 *     Author: Pradeep Barthur
 ********************************************************************************/

#include <stdio.h>
#include <limits.h>
#include <RBTree.h>

#ifdef INT_MAX
# define MAX_INT INT_MAX
#endif

#ifdef INT_MIN
# define MIN_INT INT_MIN
#else
# define MIN_INT (-MAX_INT - 1)
#endif



namespace zerosocket {

RBTree::RBTree() {
	nil = new RBNode();
	nil->left = nil->right = nil->parent = nil;
	nil->red = 0;
	nil->key = MIN_INT;
	nil->storedEntry = NULL;

	root = new RBNode();
	root->parent = root->left = root->right = nil;
	root->key = MAX_INT;
	root->red = 0;
	root->storedEntry = NULL;
}

RBTree::~RBTree() {
	// TODO Auto-generated destructor stub
}

Connection* RBTree::deleteNode(RBNode* node) {
}

RBNode* RBTree::insert(Connection* obj) {
	RBNode * y;
	RBNode * x;
	RBNode * newNode;

	x = new RBNode(obj);
	TreeInsertHelp(x);
	newNode = x;
	x->red = 1;
	while (x->parent->red) { /* use sentinel instead of checking for root */
		if (x->parent == x->parent->parent->left) {
			y = x->parent->parent->right;
			if (y->red) {
				x->parent->red = 0;
				y->red = 0;
				x->parent->parent->red = 1;
				x = x->parent->parent;
			} else {
				if (x == x->parent->right) {
					x = x->parent;
					LeftRotate(x);
				}
				x->parent->red = 0;
				x->parent->parent->red = 1;
				RightRotate(x->parent->parent);
			}
		} else { /* case for x->parent == x->parent->parent->right */
			/* this part is just like the section above with */
			/* left and right interchanged */
			y = x->parent->parent->left;
			if (y->red) {
				x->parent->red = 0;
				y->red = 0;
				x->parent->parent->red = 1;
				x = x->parent->parent;
			} else {
				if (x == x->parent->left) {
					x = x->parent;
					RightRotate(x);
				}
				x->parent->red = 0;
				x->parent->parent->red = 1;
				LeftRotate(x->parent->parent);
			}
		}
	}
	root->left->red = 0;
	return (newNode);

#ifdef CHECK_RB_TREE_ASSUMPTIONS
	check();
#elif defined(DEBUG_ASSERT)
	Assert(!nil->red,"nil not red in RedBlackTree::Insert");
	Assert(!root->red,"root not red in RedBlackTree::Insert");
#endif
}

RBNode* RBTree::getPredecessor(RBNode* node) const {
}

RBNode* RBTree::getSuccessor(RBNode* node) const {
}

RBNode* RBTree::get(int key) {
}

void RBTree::check() const {
}

void RBTree::LeftRotate(RBNode* node) {
	RBNode* ref;

	ref = node->right;
	node->right = ref->left;

	if (ref->left != nil)
		ref->left->parent = node;

	ref->parent = node->parent;
	if (node == node->parent->left) {
		node->parent->left = ref;
	} else {
		node->parent->right = ref;
	}
	ref->left = node;
	node->parent = ref;

#ifdef CHECK_RB_TREE_ASSUMPTIONS
	check();
#elif defined(DEBUG_ASSERT)
	Assert(!nil->red,"nil not red in RBTree::LeftRotate");
#endif
}

void RBTree::RightRotate(RBNode* node) {
	RBNode* ref;

	ref = node->left;
	node->left = ref->right;

	if (nil != ref->right)
		ref->right->parent = node;

	ref->parent = node->parent;
	if (node == node->parent->left) {
		node->parent->left = ref;
	} else {
		node->parent->right = ref;
	}
	ref->right = node;
	node->parent = ref;

#ifdef CHECK_RB_TREE_ASSUMPTIONS
	check();
#elif defined(DEBUG_ASSERT)
	Assert(!nil->red,"nil not red in RBTree::RightRotate");
#endif
}

void RBTree::TreeInsertHelp(RBNode* node) {
	RBNode* x;
	RBNode* y;

	node->left = node->right = nil;
	y = root;
	x = root->left;
	while (x != nil) {
		y = x;
		if (x->key > node->key) {
			x = x->left;
		} else { /* x->key <= node->key */
			x = x->right;
		}
	}
	node->parent = y;
	if ((y == root) || (y->key > node->key)) {
		y->left = node;
	} else {
		y->right = node;
	}

#if defined(DEBUG_ASSERT)
	Assert(!nil->red,"nil not red in RBTree::TreeInsertHelp");
#endif
}

void RBTree::TreePrintHelper(RBNode* node) const {
}

void RBTree::FixUpMaxHigh(RBNode* node) {
}

void RBTree::DeleteFixUp(RBNode* node) {
}

} /* namespace zerosocket */
