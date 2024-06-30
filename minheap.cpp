/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line

HeapNode* new_node(HeapNode* root, int& n, int& two_h);
int calculate_two_h(HeapNode* root);
void heapify_up(HeapNode* leaf, HeapNode* const root);
void heapify_down(HeapNode* root);
void del_heap(HeapNode* &root);


MinHeap::MinHeap(){
    size=0;
}

void MinHeap::push_heap(int num){
    if(root->val==-1){
        root->val=num;
        size++;
        return;
    }
    int n=size;
    int two_h=calculate_two_h(root);

    HeapNode* new_heap_node= new_node(root, n, two_h);
    new_heap_node->val=num;

    heapify_up(new_heap_node, root);
    size++;
}

int MinHeap::get_min(){
    return root->val;
}

void MinHeap::pop(){
    if(root->left==NULL && root->right==NULL){
        size--;
        root->val=-1;
        return;
    }

    
}

MinHeap::~MinHeap(){
    del_heap(root);
    root=NULL;
}



int calculate_two_h(HeapNode* root){
    if(root->left==NULL && root->right==NULL) return 1;

    return 2*calculate_two_h(root->left);
}



HeapNode* new_node(HeapNode* root, int &n, int &two_h){
    HeapNode* new_heap_node=new HeapNode();
    if(root->left==NULL){
        root->left=new_heap_node;
        new_heap_node->par=root;
        return new_heap_node;
    }

    if(root->right==NULL){
        root->right=new_heap_node;
        new_heap_node->par=root;
        return new_heap_node;
    }

    if(n==2*two_h-1){
        HeapNode* temp=root;
        while(temp->left!=NULL){
            temp=temp->left;
        }
        temp->left=new_heap_node;
        new_heap_node->par=temp;
        return new_heap_node;
    }

    if(two_h <= n && n <= 3*(two_h/2)-2){
        n=n-(two_h/2);
        two_h/=2;
        return new_node(root->left, n, two_h);
    }
    
    else{
        n=n-two_h;
        two_h/=2;
        return new_node(root->right, n, two_h);
    }
    return NULL;
}

void heapify_up(HeapNode* leaf, HeapNode* const root){
    if(leaf==root) return;
    if(leaf->par->val > leaf->val){
        int t=leaf->val;
        leaf->val=leaf->par->val;
        leaf->par->val=t;
        return heapify_up(leaf->par, root);
    }
    return;
}

void heapify_down(HeapNode* root){
    if(root->left==NULL && root->right==NULL) return;
    if(root->left!=NULL && root->right==NULL){
        if(root->left->val < root->val){
            int t=root->val;
            root->val=root->left->val;
            root->left->val=t;
            heapify_down(root->left);
        }
        return;
    }
    
    if(root->left->val < root->right->val){
        if(root->left->val < root->val){
            int t=root->val;
            root->val=root->left->val;
            root->left->val=t;
            heapify_down(root->left);
        }
        return;
    }

    else{
        if(root->right->val < root->val){
            int t=root->val;
            root->val=root->right->val;
            root->right->val=t;
            heapify_down(root->right);
        }
        return;
    }
}


void del_heap(HeapNode* &root){
    if(root){
        del_heap(root->left);
        del_heap(root->right);
        delete root;
        root=NULL;
    }
}