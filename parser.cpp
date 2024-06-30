/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
// #include <iostream>
// using namespace std;

//Write your code below this line
// void del(ExprTreeNode* root);
ExprTreeNode* make_tree(vector<string> code, int& index, ExprTreeNode* currnode);


//////////////////////////////////////////////////////////////////
Parser::Parser(){
    symtable=new SymbolTable();
}
//////////////////////////////////////////////////////////////////

void Parser::parse(vector<string> expression){


    if(expression[0]=="del"){
        ExprTreeNode* root=new ExprTreeNode();
        root->type="EQL";
        ExprTreeNode* left_node=new ExprTreeNode();
        ExprTreeNode* right_node=new ExprTreeNode();

        root->left=left_node;
        root->right=right_node;

        left_node->type="DEL";
        right_node->type="VAR";
        right_node->id=expression[2];

        expr_trees.push_back(root);

        return;

    }


    ExprTreeNode* root=new ExprTreeNode();
    root->type="EQL";
    ExprTreeNode* left_node= new ExprTreeNode();
    left_node->type="VAR";
    left_node->id=expression[0];
    root->left=left_node;

    if(expression[0]=="ret"){
        left_node->type="RET";
        left_node->id="";
    }

    // if(code.size())
    // cout<<"Go";

    int index=2;
    ExprTreeNode* right_node=new ExprTreeNode();
    
    // // cout<<code[index];
    root->right=right_node;

    right_node=make_tree(expression, index, right_node);
    expr_trees.push_back(root);

    if(root->left->type=="VAR") symtable->insert(expression[0]);
    else if(root->left->type=="DEL") symtable->remove(root->right->id);
    
    
    return;
}

Parser::~Parser(){
    delete symtable;
    int s=expr_trees.size();
    for(int i=0;i<s;i++){
        delete expr_trees[i];
    }
    expr_trees.clear();
}

// void del(ExprTreeNode* root){
//     if(root==NULL){
//         delete root;
//         return;
//     }
//     if(root->left==NULL && root->right==NULL){
//         delete root;
//         return;
//     }

//     if(root->left!=NULL && root->right==NULL){
//         del(root->left);
//         root->left=NULL;
//         delete root;
//         return;
//     }

//     if(root->left==NULL && root->right!=NULL){
//         del(root->right);
//         root->right=NULL;
//         delete root;
//         return;
//     }

//     if(root->left!=NULL && root->right!=NULL){
//         del(root->left);
//         del(root->right);
//         root->left=NULL;
//         root->right=NULL;
//         delete root;
//         return;
//     }
// }


ExprTreeNode* make_tree(vector<string>code, int& index, ExprTreeNode* currnode){
    E:
    // // cout<<'\n'<<code[index]<<'\n';
    //////////////////////////////////////////////////
    // if(index>=code.size()) return NULL;
    int s=code.size();
    if(index>=s) return currnode;
    //////////////////////////////////////////////////
    if(code[index]=="("){
        ExprTreeNode* node= new ExprTreeNode();
        index++;
        currnode->left=make_tree(code, index, node);
        
        goto E;
    }
    else if(code[index]=="+"){
        currnode->type="ADD";
        ExprTreeNode* node= new ExprTreeNode();
        index++;
        currnode->right=make_tree(code, index, node);
        // return currnode;
        goto E;
    }
    else if(code[index]=="-"){
        currnode->type="SUB";
        ExprTreeNode* node= new ExprTreeNode();
        index++;
        currnode->right=make_tree(code, index, node);
        goto E;
    }
    else if(code[index]=="*"){
        currnode->type="MUL";
        ExprTreeNode* node= new ExprTreeNode();
        index++;
        currnode->right=make_tree(code, index, node);
        // return currnode;
        goto E;
    }
    else if(code[index]=="/"){
        currnode->type="DIV";
        ExprTreeNode* node= new ExprTreeNode();
        index++;
        currnode->right=make_tree(code, index, node);
        // return currnode;
        goto E;
    }
    // else if(code[index]=="%"){
    //     currnode->type="MOD";
    //     ExprTreeNode* node= new ExprTreeNode();
    //     index++;
    //     currnode->right=make_tree(code, index, node);
    //     // return currnode;
    //     goto E;
    // }
    else if(code[index]==")"){
        index++;
        return currnode;
    }
    else if(('0'<=code[index][0] && code[index][0]<='9') || 
                (code[index][0]=='-' && code[index].size()>1 && '0'<=code[index][1] && code[index][1]<='9')){
        
        currnode->num=stoi(code[index]);
        currnode->type="VAL";
        index++;
        return currnode;
    }
    else{
        currnode->type="VAR";
        currnode->id=code[index];
        index++;
        return currnode;
    }
    return NULL;
    // return currnode;

}