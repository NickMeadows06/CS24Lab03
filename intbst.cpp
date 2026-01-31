// intbst.cpp
// Implements class IntBST
// Nicholas Meadows 1/30/26

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(0) { 

}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if(!n) return;
    clear(n-> left);
    clear(n-> right);
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if(!root){
        root = new Node(value);
        return true;
    }
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if(value == n-> info) return false;
    if(value < n-> info){
        if(!n -> left){
            n -> left = new Node(value);
            return true;
        }
        return insert(value, n-> left);
    }else{
            if(!n-> right){
                n->right = new Node(value);
                return true;
            }
            return insert(value, n -> right);
        }
    }

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
    count << endl;
    //cout << "IMPLEMENT printPreOrder public method";; // IMPLEMENT HERE
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if(!n) return;
    cout << n-> info << " ";
    printPreOrder(n->left);
    printPreOrder(n-> right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
    count << endl;
}
void IntBST::printInOrder(Node *n) const {
    if(n == nullptr) return;
    printInOrder(n->left);
    cout << n-> info << " ";
    printInOrder(n->right);
    
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
    count << endl;
}

void IntBST::printPostOrder(Node *n) const {
    if(!n) return;
    printPostOrder(n -> left);
    printPostOrder(n -> right);
    cout << n-> info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(!n) return 0;
    return n-> info + sum(n -> left) + sum(n -> right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(!n) return 0;
    return 1 + count(n-> left) + count(n -> right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if(!n) return 0;
    if(value == n-> info) return n;
    if(value < n-> info) return getNodeFor(value, n-> left);
    return getNodeFor(value, n -> right);
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    return getNodeFor(value, root) != 0;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* n = getNodeFor(value, root);
    if(!n) return 0;
    if(n-> left){
        Node* p = n-> left;
        while(p-> right) {
            p = p-> right;
        }
        return p;
    }
    Node *pred = 0;
    Node *curr = root;
    while(curr){
        if(value > curr -> info){
            pred = curr;
            curr = curr -> right;
        }
        else{
            curr = curr -> left;
        }
    }
    return pred;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node *p = getPredecessorNode(value);
    return p ? p-> info : 0;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node *n = getNodeFor(value, root);
    Node *succ = 0;
    Node *curr = root;

    // Case 1: value is in the tree and has a right subtree
    if (n && n->right) {
        Node *s = n->right;
        while (s->left) s = s->left;
        return s;
    }

    // Case 2: general case (works even if value is not in the tree)
    while (curr) {
        if (value < curr->info) {
            succ = curr;
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    return succ;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node *s = getSuccessorNode(value);
    return s ? s-> info : 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node *parent = 0;
    Node *curr = root;

    while (curr && curr->info != value) {
        parent = curr;
        if (value < curr->info) curr = curr->left;
        else curr = curr->right;
    }

    if (!curr) return false;

    if (curr->left && curr->right) {
        Node *succ = curr->right;
        Node *succParent = curr;
        while (succ->left) {
            succParent = succ;
            succ = succ->left;
        }
        curr->info = succ->info;
        curr = succ;
        parent = succParent;
    }

    Node *child = curr->left ? curr->left : curr->right;

    if (!parent) {
        root = child;
    } else if (parent->left == curr) {
        parent->left = child;
    } else {
        parent->right = child;
    }

    delete curr;
    return true;
}
