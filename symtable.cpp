/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

// #include <iostream>
// #include <queue>
// using namespace std;

//Write your code below this line
void update_heights_and_balance(SymNode* new_leaf, SymNode* &root);
SymNode* balance(SymNode* &parent);
void del_table(SymNode* &root);
void inorder(SymNode* root);
void levelordertraversal(SymNode* root);
void height_fixer(SymNode* node);
int height(SymNode* node){
    if (node==NULL) return -1;
    else return node->height;
}

// int return_height(SymNode* root);

SymbolTable::SymbolTable(){
    size=0;
    root=NULL;
}

void SymbolTable::insert(string k){
    if(size==0){
        root=new SymNode(k);
        size++;
        return;
    }

    SymNode* parent=NULL;
    SymNode* temp=root;
    while(temp!=NULL){
        if(temp->key==k) return ;
        else if(temp->key > k){
            parent=temp;
            temp=temp->left;
        }
        else if(temp->key < k){
            parent=temp;
            temp=temp->right;
        }
    }

    size++;

    SymNode* new_leaf=new SymNode(k);
    new_leaf->par=parent;
    new_leaf->height=0;
    if(parent->key>k) parent->left=new_leaf;
    else parent->right=new_leaf;

    // cout<<"Inoder previous: ";
    inorder(root);

    update_heights_and_balance(new_leaf, root);

    // cout<<"\nInorder later: ";
    inorder(this->root);
    // cout<<"\n\n";
}



void SymbolTable:: remove(string k){
    // inorder(root);
    SymNode* temp=root;
    while(temp!=NULL){
        if(temp->key==k) break;
        else if(temp->key > k) temp=temp->left;
        else temp=temp->right;
    }


    if(temp==NULL) return;

    size--;

    SymNode* parent=temp->par;

    SymNode* node_to_start;
    
    if(temp->left==NULL && temp->right==NULL){
        if(parent==NULL){
            delete root;
            root=NULL;
            return;
        }
        node_to_start=temp->par;
        if(node_to_start->left==temp) node_to_start->left=NULL;
        else node_to_start->right=NULL;
        delete temp;
        // cout<<"Flag";
        temp=NULL;


    }
    else if(temp->left==NULL && temp->right!=NULL){
        if(parent==NULL){
            root=temp->right;
            root->par=NULL;
            delete temp;
            return;
        }
        else if(parent->left==temp){
            parent->left=temp->right;
            temp->right->par=parent;
        }
        else{
            parent->right=temp->right;
            temp->right->par=parent;
        }
        node_to_start=parent;
        delete temp;
        temp=NULL;


    }
    else if(temp->left!=NULL && temp->right==NULL){
        if(parent==NULL){
            root=temp->left;
            root->par=NULL;
            delete temp;
            return;
        }
        else if(parent->left==temp){
            parent->left=temp->left;
            temp->left->par=parent;
        }
        else{
            parent->right=temp->left;
            temp->left->par=parent;
        }
        node_to_start=parent;
        delete temp;
        temp=NULL;


    }
    else{
        SymNode* temp1=temp->right;
        while(temp1->left!=NULL){
            temp1=temp1->left;
        }

        SymNode* parent1=temp1->par;
        node_to_start=parent1;
        if(parent1->left==temp1){
            parent1->left=temp1->right;
            if(temp1->right!=NULL) temp1->right->par=parent1;
            temp->key=temp1->key;
            temp->address=temp1->address;
            delete temp1;
            temp1=NULL;
        }
        else{
            parent1->right=temp1->right;
            if(temp1->right!=NULL) temp1->right->par=parent1;
            temp->key=temp1->key;
            temp->address=temp1->address;
            delete temp1;
            temp1=NULL;
        }
    }

    int node_left_ht=height(node_to_start->left);
    int node_right_ht=height(node_to_start->right);

    if(!(-1<=node_right_ht-node_left_ht && node_right_ht-node_left_ht<=1)){
        SymNode* parent=node_to_start->par;
        SymNode* newNode=balance(node_to_start);
        if(node_to_start==root){
            root=newNode;
            return;
        }

        if(parent->right==node_to_start) parent->right=newNode;
        else parent->left=newNode;

    }
    // cout<<"=====================";
    update_heights_and_balance(node_to_start, root);

    int left_ht=height(root->left);
    int right_ht=height(root->right);
    // cout<<"----------- "<<left_ht<<' '<<right_ht<<'\n

    if(-1> right_ht-left_ht || right_ht-left_ht >1){
        root=balance(root);
    }
}



int SymbolTable::search(string k){
    SymNode* temp=root;
    string a;
    while(temp!=NULL){
        a= temp->key;
        if(temp->key==""){
            // std:: cout<<"May be an error";
        }
        if(a==k) return temp->address;
        else if(a>k) temp=temp->left;
        else temp=temp->right;
    }
    // std:: cout<<"Something Fishy";
    return -2;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* temp=root;
    while(temp!=NULL){
        if(temp->key==""){
            // std:: cout<<"May be an error";
        }
        if(temp->key==k) break;
        else if(temp->key>k) temp=temp->left;
        else temp=temp->right;
    }
    // if(temp==NULL) std:: cout<< "Assigning to NULL";
    if(temp==NULL) return;
    temp->address=idx;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    del_table(root);
}


void update_heights_and_balance(SymNode* new_leaf, SymNode* &root){
    // bool balanced=true;
    SymNode* node=new_leaf;
    while(node!=root){
        // cout<<":::::::::::::::\n";
        // cout<<node->key<<'\n';
        int node_left_ht=height(node->left);
        int node_right_ht=height(node->right);
        // cout<<node_left_ht<<' '<<node_right_ht<<'\n';
        if(-1 <= node_right_ht-node_left_ht &&  node_right_ht-node_left_ht<=1){
            node->height=1+max(node_left_ht, node_right_ht);
        }
        else{
            // cout<<"##############################\nError##############################\n";
            // cout<<node->key<<'\n';
            // cout<<node->left->key<<'('<<node->left->height<<')'<<' '<<node->right->key<<'('<<node->right->height<<")\n";
        }
        SymNode* parent=node->par;
        int right_ht=height(parent->right);
        int left_ht=height(parent->left);

        if(-1 <= right_ht-left_ht &&  right_ht-left_ht<=1){
            // cout<<"Go";
            // cout<<left_ht<<' '<<right_ht<<'\n';
            parent->height= max(left_ht, right_ht)+1;
            node=parent;
            // cout<<"0000000000000000 "<< (node->key)<<'\n';
            continue;
        }
        // parent imbalanced
        // if(parent==root){
        //     ///////////////////////////////////////////////
        // }

        SymNode* grandparent=parent->par;

        SymNode* newNode=balance(parent);
        // cout<<"}}}}}}}}}"<< newNode->key;
        // cout<<"===========\n";
        // cout<<newNode->key<<'\n';
        // cout<<newNode->left->key<<' '<<newNode->right->key<<'\n';
        // cout<<parent->par->key<<'\n';
        if(parent==root){
            root=newNode;
            // cout<<"???????????????"<<' '<<root->key<<' '<<"???????????????";
            node=parent;
            // cout<<root->key<<' '<<node->key<<' '<<node->par->key;
            continue;
        }

        // cout<<"Parent: "<<parent->key<<'\n';
        // cout<<"Grandparent: "<<grandparent->key<<'\n';
        if(grandparent->left==parent) grandparent->left=newNode;
        else grandparent->right=newNode;

        node=parent;
    }
    // cout<<node->key<<'\n';
    // if(node->left!=NULL && node->right!=NULL) cout<<node->left->key<<' '<<node->right->key<<'\n';
    int right_ht=height(node->right);
    int left_ht=height(node->left);

    node->height= max(left_ht, right_ht)+1;
    return;
}



SymNode* balance (SymNode* &parent){
    int right_ht=height(parent->right);
    int left_ht=height(parent->left);
    // cout<<parent->key<<'\n';
    // cout<<left_ht<<' '<<right_ht<<'\n';

    if(right_ht > left_ht){
        SymNode* node=parent->right;

        int subtree_right_ht=height(node->right);
        int subtree_left_ht=height(node->left);
        // cout<<subtree_left_ht<<' '<<subtree_right_ht<<'\n';

        if(subtree_right_ht >= subtree_left_ht){
            SymNode* to_return= parent->LeftLeftRotation();
            height_fixer(parent);
            height_fixer(parent->par);
            return to_return;
        }
        else {
            SymNode* to_return= parent->LeftRightRotation();
            SymNode* sibling=parent->par->right;
            int h1=height(sibling->left);
            int h2=height(sibling->right);
            if(!(-1<=h1-h2 && h1-h2<=1)){
                // cout<<"WWWWWWWWWWWWWWWWWW\nBoomWWWWWWWWWWWWWWWWWW";
            }
            sibling->height=1+max(h1, h2);
            height_fixer(parent);
            height_fixer(parent->par);
            return to_return;
        }
    }
    else{
        SymNode* node=parent->left;

        int subtree_right_ht=height(node->right);
        int subtree_left_ht=height(node->left);
        // cout<<subtree_left_ht<<' '<<subtree_right_ht<<'\n';

        if(subtree_right_ht > subtree_left_ht){
            SymNode* to_return= parent->RightLeftRotation();
            SymNode* sibling=parent->par->left;
            int h1=height(sibling->left);
            int h2=height(sibling->right);
            if(!(-1<=h1-h2 && h1-h2<=1)){
                // cout<<"UUUUUUUUUUUUUUUUUUUUU\nErrUUUUUUUUUUUUUUUUUUUUU";
            }
            sibling->height=1+max(h1, h2);
            height_fixer(parent);
            height_fixer(parent->par);
            return to_return;
        }
        else{
            SymNode* to_return= parent->RightRightRotation();
            height_fixer(parent);
            height_fixer(parent->par);
            return to_return;
        }
    }
}

void del_table(SymNode* &root){
    if(root){
        del_table(root->left);
        del_table(root->right);
        root->par=NULL;
        delete root;
        root=NULL;
    }
    return;
}

void inorder(SymNode* root){
    if(root==NULL)return;
    inorder(root->left);
    // cout<< root->key<<'('<<root->height<<')' <<' ';
    inorder(root->right);
}

// int main(){
//     SymbolTable* s=new SymbolTable();
//     // s->insert("20");
//     // s->insert("04");
//     // s->insert("26");
//     // s->insert("03");
//     // s->insert("09");
//     // s->insert("21");
//     // s->insert("30");
//     // s->insert("02");
//     // s->insert("07");
//     // s->insert("11");
//     // s->insert("15");
//     // // cout<<s->get_root()->key<<'\n';
//     // inorder(s->get_root());
//     // cout<<'\n';
//     // levelordertraversal(s->get_root());
//     // cout<<"hello";

//     s->insert("32");
//     s->insert("48");
//     s->insert("16");
//     s->insert("56");
//     s->insert("40");
//     s->insert("08");
//     s->insert("24");
//     s->insert("60");
//     s->insert("04");
//     s->insert("36");
//     s->insert("52");
//     s->insert("44");
//     s->insert("62");
//     s->insert("34");
//     s->insert("58");

//     inorder(s->get_root());
//     cout<<'\n';
//     levelordertraversal(s->get_root());
//     s->remove("04");
//     inorder(s->get_root());
//     cout<<'\n';
//     levelordertraversal(s->get_root());
//     cout<<'\n';
//     // s->remove("12");
//     // inorder(s->get_root());
//     // cout<<'\n';
//     // levelordertraversal(s->get_root());
//     // cout<<"hello";
// }

// void levelordertraversal(SymNode* root){

//     // if(root==NULL){
//     //     return;
//     // }
//     // queue <SymNode*> q;
//     // q.push(root);

//     // while(!q.empty()){
//     //     int s=q.size();
//     //     for(int i=0; i<s; i++){
//     //         SymNode* n=q.front();
//     //         q.pop();

//     //         if(n==NULL) cout<<"null ";
//     //         else cout<<n->key<<' ';

//     //         if(n->left==NULL && n->right==NULL){

//     //         }
//     //         else if(n->right==NULL){
//     //             q.push(n->left);
//     //             q.push(NULL);
//     //         }
//     //         else if(n->left==NULL){
//     //             q.push(NULL);
//     //             q.push(n->right);
//     //         }
//     //         else{
//     //             q.push(n->left);
//     //             q.push(n->right);
//     //         }
//     //     }
//     //     cout<<'\n';
//     // }

    

//     if(root==NULL){
//         return;
//     }
//     queue <SymNode*> q;
//     q.push(root);
//     q.push(NULL);

//     while(!q.empty()){
//         SymNode* temp=q.front();
//         q.pop();
//         if(temp==NULL){
//             cout<<endl;
//             if(!q.empty()){
//                 q.push(NULL);
//             }
//         }
//         else{
//             cout<<temp->key<<" ";
//             if(temp->left){
//                 q.push(temp->left);
//             }
//             if (temp->right){
//                 q.push(temp->right);
//             }
//         }
//     }
// }


void height_fixer(SymNode* node){
    ///////////// Assumption subtrees are AVLs //////////////////
    node->height=1+max(height(node->left), height(node->right));
}