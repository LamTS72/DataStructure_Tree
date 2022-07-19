#include "main.h"

Data* Cache::read(int addr) {
    Elem *temp = searchNode(root,addr);
    if(temp != NULL){
        return temp->data;
    }
    else return NULL;
}
Elem* Cache::put(int addr, Data* cont) {
    Elem *temp = NULL;
    if(istack->size() == MAXSIZE){
        if(addr % 2 == 0){
            temp = istack->popE();
            root = deleteNode(root,temp);
        }
        else{
            temp = istack->popH();
            root = deleteNode(root,temp);
        }
    }
    Elem *p = new Elem(addr,cont,true);
    istack->push(p);
    root = insertNode(root,p);
    return temp;
}
Elem* Cache::write(int addr, Data* cont) {
    Elem *temp = root->searchNode(root,addr);
    if(temp != NULL){
        temp->data = cont;
        temp->sync = false;
        return NULL;
    }
    else{
         Elem *temp = NULL;
        if(istack->size() == MAXSIZE){
            if(addr % 2 == 0){
                temp = istack->popE();
                root = deleteNode(root,temp);
            }
            else{
                temp = istack->popH();
                root = deleteNode(root,temp);
            }
        }
        Elem *p = new Elem(addr,cont,false);
        istack->push(p);
        root = insertNode(root,p);
        return temp;
    }
}
void Cache::print() {
	istack->printStack();
}
void Cache::preOrder() {
    printNLR(root);
}
void Cache::inOrder() {
    printLNR(root);
}