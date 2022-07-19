#ifndef CACHE_H
#define CACHE_H

#include "main.h"

class BSTree{
    public:
    
    Elem *elem;
   // BSTree *root;
    BSTree *left;
    BSTree *right;
    friend class Cache;
    BSTree (){left = NULL; right = NULL;};
    BSTree *newNode(Elem *elem);
    ~BSTree(){};
    BSTree *insertNode(BSTree *root,Elem *elem);
    BSTree *deleteNode(BSTree *root,Elem *elem);
    Elem *searchNode(BSTree *root,int addr);
    BSTree *minValue(BSTree *root);
    void printLNR(BSTree *root);//print inOder
    void printNLR(BSTree *root);//print preOder
};

//create a node to BSTree
BSTree *BSTree::newNode(Elem *elem){
    BSTree *newNode = new BSTree();
    newNode->elem = elem;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
//insertNode to BSTree
BSTree *BSTree::insertNode(BSTree *root,Elem *elem) {
    if(root == NULL){
        return newNode(elem);
    }
    if(elem->addr < root->elem->addr){
        root->left = insertNode(root->left,elem);
    }
    else{
        root->right = insertNode(root->right,elem);
    }
    return root;
}

BSTree *BSTree::minValue(BSTree *root){
    BSTree *curr = root;
    while (curr != NULL && curr->left != NULL){
        curr = curr->left;
    }
    return curr;
}

//deleteNode from BSTree
BSTree *BSTree::deleteNode(BSTree *root,Elem *elem){
    if(root == NULL) return root;
    if(elem->addr < root->elem->addr){
        root->left = deleteNode(root->left,elem);
    }
    else if(elem->addr > root->elem->addr){
        root->right = deleteNode(root->right,elem);
    }
    else{
        if(root->left == NULL && root->right == NULL) return NULL;
        else if(root->left == NULL){
            BSTree *temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == NULL){
            BSTree *temp = root->left;
            delete root;
            return temp;
        }
        BSTree *temp = minValue(root->right);
        root->elem = temp->elem;
        root->right = deleteNode(root->right,temp->elem);
    }
    return root;
}

//searchNode from BSTree
Elem *BSTree::searchNode(BSTree *root,int addr){
    if(root == NULL) return NULL;
    else{
        BSTree *curr = root;
        while(curr != NULL){
            if(addr == curr->elem->addr){
                return curr->elem;
            }
            else if(addr < curr->elem->addr){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
        }
        return NULL;
    }
}

//printLNR or inOder from BSTree
void BSTree::printLNR(BSTree *root){
    if(root == NULL) return;
    else{
        printLNR(root->left);
        root->elem->print();
        printLNR(root->right);
    }
}

//printNLR or preOder from BSTree
void BSTree::printNLR(BSTree *root){
    if(root == NULL) return;
    else{
        root->elem->print();
        printNLR(root->left);
        printNLR(root->right);
    }
}
class Node{
    public:
    Elem *elem;
    Node *next;
    Node(){this->next = NULL;}
    ~Node() {this->elem = NULL;}
};
class IStack{
    Node *top;
    int count;
    public:
    IStack(){this->top = NULL; count = 0;};
    void push(Elem*elem);
    Elem* popH();
    Elem* popE();
    void printStack();
    int size(){return this->count;};
};

//push newNode to stack
void IStack::push(Elem*elem){
        Node *newNode = new Node();
        newNode->elem = elem;
        newNode->next = top;
        top = newNode;
        count++;
}

//popH at head of stack
Elem* IStack::popH(){
    if(top == NULL) return NULL;
    else{
        Node *temp = top;
        Elem *tmp = top->elem;
        top = top->next;
        delete temp;
        count--;
        return tmp;
    }
}

//popE at tail of stack
Elem* IStack::popE(){
    if(top == NULL) return NULL;
    else{
        Node *temp = top;
       while(temp->next != NULL){
            temp = temp->next;
       }
       Elem *tmp = temp->elem;
       delete temp;
       temp->next = NULL;
       return tmp;
    }
}

//printStack from stack
void IStack::printStack(){
    if(top == NULL) return;
    else{
        Node *temp = top;
        while(temp != NULL){
            temp->elem->print();
            temp = temp->next;
        }
    }
}
class Cache : public BSTree {
    
    IStack *istack;
    BSTree *root;
	public:
    Cache(int s)  {
      //  root = NULL;
       istack = new IStack();
    }
    ~Cache() {
        //size_cache  = 0;
       delete root;
       delete istack;
    }
		Data* read(int addr);
		Elem* put(int addr, Data* cont);
		Elem* write(int addr, Data* cont);
		void print();
		void preOrder();
		void inOrder();
};
#endif