/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

// #include <iostream>
// using namespace std;
//Write your code below this line

SymNode::SymNode(){
    key="";
    height=0;

    ///////////////////    Address??     /////////////////////

    par=NULL;
    left=NULL;
    right=NULL;
}

SymNode::SymNode(string k){
    key=k;
    height=0;

    ///////////////////    Address??     /////////////////////

    par=NULL;
    left=NULL;
    right=NULL;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* b=right;
    SymNode* b_left=b->left;
    b->left=this;
    b->par=this->par;
    this->par=b;
    this->right=b_left;
    if(b_left!=NULL) b_left->par=this;
    return b;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* b=left;
    SymNode* b_right=b->right;
    b->right=this;
    b->par=this->par;
    this->par=b;
    this->left=b_right;
    if(b_right!=NULL) b_right->par=this;
    return b;
}

SymNode* SymNode::LeftRightRotation(){
    SymNode* c=right;
    this->right=c->RightRightRotation();
    return (this->LeftLeftRotation());
}

SymNode* SymNode::RightLeftRotation(){
    SymNode* c=left;
    this->left=c->LeftLeftRotation();
    return (this-> RightRightRotation());
}

SymNode::~SymNode(){
    // cout<<"hi";
    key.clear();
    height=0;
    address=-1;
    // delete par;
    // delete left;
    // delete right;

    par=NULL;
    left=NULL;
    right=NULL;
}