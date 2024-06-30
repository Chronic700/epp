/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

// #include <iostream>
// using namespace std;


// void inorder(ExprTreeNode* node){
//     if(node==nullptr) return;
//     inorder(node->left);
//     if(node->type=="VAL")
// }
// void pre_order(ExprTreeNode * node)
// {
//     if(node->left!=nullptr) 
//     {   // cout<<"(";
//         pre_order(node->left);}
//     if(node->type=="VAR")
//     {
//         // cout<<node->id<<" ";
//     }
//     else if(node->type=="VAL")
//     {
//         // cout<<node->val->get_frac_str()<<" ";
//     }
//     else 
//     {
//         // cout<<node->type<<" ";
//     }
//     if(node->right!=nullptr) 
//     {pre_order(node->right);
//         // // // // // // // // // // // // // // // // cout<<")";
//     }
// }


void del(ExprTreeNode* root);
/////////////////////////////////////////////////////////
ExprTreeNode* make_tree(vector<string> code, int& index, ExprTreeNode* currnode);
void evaluate(ExprTreeNode* root, SymbolTable* symtable);

void del(ExprTreeNode* root){
    if(root==nullptr){
        delete root;
        return;
    }
    if(root->left==nullptr && root->right==nullptr){
        delete root;
        return;
    }

    if(root->left!=nullptr && root->right==nullptr){
        del(root->left);
        root->left=nullptr;
        delete root;
        return;
    }

    if(root->left==nullptr && root->right!=nullptr){
        del(root->right);
        root->right=nullptr;
        delete root;
        return;
    }

    if(root->left!=nullptr && root->right!=nullptr){
        del(root->left);
        del(root->right);
        root->left=nullptr;
        root->right=nullptr;
        delete root;
        return;
    }
}

Evaluator:: Evaluator(){
    symtable= new SymbolTable();
}

Evaluator:: ~Evaluator(){
    delete symtable;
    int s=expr_trees.size();
    for(int i=0; i<s; i++){
        del(expr_trees[i]);
    }
}

void Evaluator:: parse(vector<string> code){

    //////////// ASSUMPTION := always present  and only one in count ////////////////////
    //////////// ASSUMPTION Variable:=Expression ////////////////////////////////////////

    // vector<string> v1;
    // vector<string> v2;
    // bool lhs=true;
    // for(int i=0;i<code.size();i++){
    //     if(code[i]==":="){
    //         lhs=false;
    //         continue;
    //     }
    //     if(lhs) v1.push_back(code[i]);
    //     else v2.push_back(code[i]);
    // }

    // ExprTreeNode* root=new ExprTreeNode();
    // root->left=make_tree(v1, );
    // root->right=make_tree(v2, );

    // expr_trees.push_back(root);

    ExprTreeNode* root=new ExprTreeNode();
    root->type="EQL";
    ExprTreeNode* left_node= new ExprTreeNode();
    left_node->type="VAR";
    left_node->id=code[0];
    root->left=left_node;

    // if(code.size())

    int index=2;
    ExprTreeNode* right_node=new ExprTreeNode();
    
    // // cout<<code[index];
    root->right=right_node;

    right_node=make_tree(code, index, right_node);
    expr_trees.push_back(root);
    
    return;
}

void Evaluator:: eval(){
    int s=expr_trees.size();
    ExprTreeNode* tree= expr_trees[s-1];
    // ExprTreeNode* variable=tree->left;
    // cout<<"????????????????????\n"<< tree->left->id<<'\n';

    evaluate(tree->right, symtable);
    // cout<<tree->right->evaluated_value->get_frac_str()<<'\n';

    symtable->insert(tree->left->id, tree->right->evaluated_value);

}

// ExprTreeNode* make_tree(vector<string>& code, int index){
    
// }

ExprTreeNode* make_tree(vector<string>code, int& index, ExprTreeNode* currnode){
    E:
    // // cout<<'\n'<<code[index]<<'\n';
    //////////////////////////////////////////////////
    // if(index>=code.size()) return nullptr;
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
    else if(code[index]=="%"){
        currnode->type="MOD";
        ExprTreeNode* node= new ExprTreeNode();
        index++;
        currnode->right=make_tree(code, index, node);
        // return currnode;
        goto E;
    }
    else if(code[index]==")"){
        index++;
        return currnode;
    }
    else if(('0'<=code[index][0] && code[index][0]<='9') || 
                (code[index][0]=='-' && code[index].size()>1 && '0'<=code[index][1] && code[index][1]<='9')){
        
        UnlimitedInt* num=new UnlimitedInt(code[index]);
        currnode->type="VAL";
        UnlimitedInt* one=new UnlimitedInt(1);
        UnlimitedRational* r=new UnlimitedRational(num, one);
        currnode->val=r;
        // ExprTreeNode* node=new ExprTreeNode("VAL", num);
        
        // // cout<<'\n'<< code[index]<<'\n';

        index++;
        return currnode;
    }
    else{
        // ExprTreeNode* var=new ExprTreeNode();
        // var->id=code[index];
        // var->type="VAR";
        // var->val=symtable->search(code[index]);
        currnode->type="VAR";
        currnode->id=code[index];
        index++;
        // if(var->val==nullptr) symtable->insert(var->id, nullptr);
        return currnode;
    }
    return nullptr;
    // return currnode;

}

void evaluate(ExprTreeNode* root, SymbolTable* symtable){
    if(root->type==""){
        ExprTreeNode* leaf=root->left;
        if(leaf->type=="VAL"){
            leaf->evaluated_value=leaf->val;
            root->evaluated_value=leaf->evaluated_value;
            // return leaf->val;
            return;
        }
        else if(leaf->type=="VAR"){
            leaf->val=symtable->search(leaf->id);
            leaf->evaluated_value=leaf->val;
            root->evaluated_value=leaf->evaluated_value;
            // return leaf->val;
            return;
        }
    }
    if(root->type=="VAL"){
        root->evaluated_value=root->val;
        // return root->val;
        return;
    }
    if(root->type=="VAR"){
        root->val=symtable->search(root->id);
        root->evaluated_value=root->val;
        // cout<< '\n'<< root->id<<' '<< root->val->get_frac_str()<<'\n';
        // cout<<"Hi ";
        // return root->val;
        return;
    }
    if(root->type=="ADD"){
        evaluate(root->left, symtable);
        // cout<<root->left->evaluated_value->get_frac_str()<<'\n';
        evaluate(root->right, symtable);
        // cout<<root->right->evaluated_value->get_frac_str()<<'\n';

        // UnlimitedRational* evaluated=root->evaluated_value;

        root->evaluated_value=UnlimitedRational::add(root->left->evaluated_value, root->right->evaluated_value);
        return;
    }

    if(root->type=="SUB"){
        evaluate(root->left, symtable);
        // cout<<root->left->evaluated_value->get_frac_str()<<'\n';
        evaluate(root->right, symtable);
        // cout<<root->right->evaluated_value->get_frac_str()<<'\n';

        // UnlimitedRational* evaluated=root->evaluated_value;

        root->evaluated_value=UnlimitedRational::sub(root->left->evaluated_value, root->right->evaluated_value);
        return;
    }

    if(root->type=="MUL"){
        evaluate(root->left, symtable);
        // cout<<root->left->evaluated_value->get_frac_str()<<'\n';
        evaluate(root->right, symtable);
        // cout<<root->right->evaluated_value->get_frac_str()<<'\n';

        // UnlimitedRational* evaluated=root->evaluated_value;

        root->evaluated_value=UnlimitedRational::mul(root->left->evaluated_value, root->right->evaluated_value);
        return;
    }

    if(root->type=="DIV"){
        evaluate(root->left, symtable);
        // cout<<root->left->evaluated_value->get_frac_str()<<'\n';
        evaluate(root->right, symtable);
        // cout<<root->right->evaluated_value->get_frac_str()<<'\n';

        // UnlimitedRational* evaluated=root->evaluated_value;

        root->evaluated_value=UnlimitedRational::div(root->left->evaluated_value, root->right->evaluated_value);
        return;
    }
    /////////////////////////////////////////////////

    if(root->type=="MOD"){
        UnlimitedInt* i_left;
        UnlimitedInt* i_right;

        UnlimitedRational* r_left=root->left->evaluated_value;
        UnlimitedRational* r_right=root->right->evaluated_value;

        i_left=i_left->div(r_left->get_p(), r_left->get_q());
        i_right=i_right->div(r_right->get_p(), r_right->get_q());

        UnlimitedInt* evaluated_int;
        evaluated_int=evaluated_int->mod(i_left, i_right);

        UnlimitedInt* one= new UnlimitedInt(1);
        root->evaluated_value=new UnlimitedRational(evaluated_int, one);
        return;
    }

    /////////////////////////////////////////////////
}


// int main(){
//     // // cout<<"Hello";
//     Evaluator* e;
//     vector<string> code=   {"x", ":=", "(", "2", "+", "3", ")"};
//     e->parse(code);
//     pre_order(e->expr_trees[0]);
// }



//////////////    code=["(", "3", ")"] /////////////////////////////////////