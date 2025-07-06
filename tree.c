#include "tree.h"
root = NULL; // Initialize the root of the AVL tree

Node* create_node(int key,int page,int slot){
    Node* new_node=(Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->key=key;
    new_node->page_no=page;
    new_node->slot=slot;
    new_node->left=NULL;
    new_node->right=NULL;
    new_node->height=1;
    return new_node;
}
int max(int a,int b)
{
    return (a>b)?a:b;
}
int get_height(Node* node)
{
    if(node==NULL) return 0;
    return (node->height);
}
int balance_factor(Node* node)
{
    if(node==NULL) return 0;
    return get_height(node->left)-get_height(node->right);
}
Node* right_rotate(Node* root)
{
    Node* new_root=root->left;
    Node* temp=new_root->right;

    new_root->right=root;
    root->left=temp;

    root->height=1+max(get_height(root->left),get_height(root->right));
    new_root->height=1+max(get_height(new_root->left),get_height(new_root->right));

    return new_root;
}
Node* left_rotate(Node* root)
{
    Node* new_root=root->right;
    Node* temp=new_root->left;

    new_root->left=root;
    root->right=temp;

    new_root->height=1+max(get_height(new_root->left),get_height(new_root->right));
    root->height=1+max(get_height(root->left),get_height(root->right));

    return new_root;
}
Node* search(Node* root,int key)
{
    if(root==NULL){
        return NULL;
    }
    if(root->key==key) return root;
    else if(root->key<key) return search(root->right,key);
    else return search(root->left,key);
}
void index_insert(Node** node, int key, int page, int slot)
{
    if(*node==NULL) {
        *node =create_node(key,page,slot);//in case the passed adress contains null, make a new node
        return;
    }
    if((*node)->key<key) index_insert(&((*node)->right),key,page,slot);
    else if(key<(*node)->key) index_insert(&((*node)->left),key,page,slot);
    else return;//if key already exists then do nothing, eat 5 star


    (*node)->height=1+max(get_height((*node)->left),get_height((*node)->right));//update the heights accordingly

    int balance=balance_factor(*node);
    if(balance>1 && key<(*node)->left->key)// this is the left left case 
    {
        *node=right_rotate(*node);
    }
    else if(balance<-1 && key>(*node)->right->key)// this is right right case
    {
        *node=left_rotate(*node);
    }
    else if(balance>1 && key>(*node)->left->key)// this is left right case
    {
        (*node)->left=left_rotate((*node)->left);// left rotate to bring it to left left case
        *node=right_rotate(*node);
    }
    else if(balance<-1 && key<(*node)->right->key)// this is right left case
    {
        (*node)->right=right_rotate((*node)->right);// first right rotate to being it to right right case
        *node=left_rotate(*node);// now do left roataion
    }
    return;
}
// void print_backened_test(Node* root)
// {
//     if(root==NULL) return;
//     printf("%d ",root->key);
//     print_backend_test(root->left);
//     print_backend_test(root->right);
// }

bool index_find(int key, int* page, int* slot){
    Node* found_node = search(root, key); // Search for the node with the given key
    if(found_node != NULL){
        *page = found_node->page_no; // Pasting the page number
        *slot = found_node->slot; // Pasting the slot number
        return true;    // Return true if the node is found
    }
    return false; // Return false if the node is not found
}


void index_delete(Node** node_pointer, int key){
    Node* node=*node_pointer;
    if (node==NULL){
        return; // Key not found
    }
    if (key<node->key){
        index_delete(&(node->left),key);
    }
    else if (key>node->key){
        index_delete(&(node->right),key);
    }
    else{
        // Node with only one child or no child
        if (node->left==NULL){
            Node* temp=node->right;
            free(node);
            *node_pointer=temp;
            return;
        }
        else if (node->right==NULL){
            Node* temp=node->left;
            free(node);
            *node_pointer=temp;
            return;
        }
        else{
            // Node with two children: Get the smallest node in the right subtree
            Node* temp=node->right;
            while (temp->left!=NULL){
                temp=temp->left;
            }
            // Copy the values of temp to root
            node->key=temp->key;
            node->page_no=temp->page_no;
            node->slot=temp->slot;
            // Delete temp node
            index_delete(&(node->right),node->key);
        }
    }
    node=*node_pointer; // Update the node pointer to the current node after deletion
    if (node == NULL) {
        return; // If the node is now NULL, nothing to update
    }
    // If the node is not NULL, update height after deletion
    node->height=1+max(get_height(node->left),get_height(node->right));
    // Check balance factor and perform rotations if necessary
    int bfactor=balance_factor(node);
    if (bfactor==2 && balance_factor(node->left)>=0){
        node=right_rotate(node); // Left Left Case
    }
    else if (bfactor==2 && balance_factor(node->left)<0){
        node->left=left_rotate(node->left); // Left Right Case
        node=right_rotate(node);
    }
    else if (bfactor==-2 && balance_factor(node->right)<=0){
        node=left_rotate(node); // Right Right Case
    }
    else if (bfactor==-2 && balance_factor(node->right)>0){
        node->right=right_rotate(node->right); // Right Left Case
        node=left_rotate(node);
    }
    *node_pointer=node;
    return;
}
