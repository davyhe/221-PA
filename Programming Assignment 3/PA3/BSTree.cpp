#include "BSTree.h"
#include <cstdlib>
#include <iostream>
#include <queue>
using std::queue;

using namespace std;

///////////////////////////////////
// Already Implemented Functions //
///////////////////////////////////

// These functions are already implemented for you. Scroll below to
// see the functions that you have to implement

// constructors
BSTree::BSTree() : size(0), root(nullptr) {}

// input / output operators
ostream &operator<<(ostream &out, BSTree &tree)
{
  tree.print_level_by_level(out);
  return out;
}

ostream &operator<<(ostream &out, Node &node)
{
  return out << node.value << "[" << node.search_time << "]";
}

istream &operator>>(istream &in, BSTree &tree)
{
  /*
      take input from the in stream, and build your tree
      input will look like
      4 
      2 
      6 
      1 
      3 
      5 
      7
    */
  int next;
  while (in >> next)
  {
    tree.insert(next);
  }
  return in;
}

// Example recursive function
// If you try to use it without care, you will get a memory leak.
void BSTree::copy_helper(Node *&newNode, const Node *sourceNode)
{
  //Don't copy if the node is nullptr
  if (sourceNode == nullptr)
    return;

  //Change the new node to a copy of sourceNode
  newNode = new Node(sourceNode->value);
  //Copy over the search cost
  newNode->search_time = sourceNode->search_time;

  //Copy left subtree
  if (sourceNode->left != nullptr)
    copy_helper(newNode->left, sourceNode->left);
  //Copy right subtree
  if (sourceNode->right != nullptr)
    copy_helper(newNode->right, sourceNode->right);
}

// recursive function
int BSTree::get_total_search_time(Node *node)
{
  if (node != nullptr)
  {
    return node->search_time + get_total_search_time(node->left) + get_total_search_time(node->right);
  }
  return 0;
}

// implemented
float BSTree::get_average_search_time()
{
  int total_search_time = get_total_search_time(root);
  if (total_search_time == 0)
    return -1;

  return ((float)total_search_time) / size;
}

///////////////////////////////////
//     Functions to Implement    //
///////////////////////////////////

// These are the functions you should implement
// Feel free to call the functions above or create new helper functions

// copy constructor
Node *copyHelper(const Node *toCopy)
{
  if (toCopy == NULL)
    return NULL;
  Node *copyNode = new Node;
  copyNode->value = toCopy->value;
  copyNode->left = copyHelper(toCopy->left);
  copyNode->right = copyHelper(toCopy->right);
  return copyNode;
}

BSTree::BSTree(const BSTree &other)
{
  //if(other.root == NULL)
  //root = NULL;

  //copy_helper(this->root, other.root);
  root = nullptr;
  size = other.size;

  if (other.root == nullptr)
    root = NULL;

  //Copy left subtree
  else
  {
    root = new Node(other.root->value);
    root->search_time = other.root->search_time;
    size = other.size;
    if (other.root->left != nullptr)
    {
      copy_helper(root->left, other.root->left);
    }
    if (other.root->right != nullptr)
    {
      copy_helper(root->right, other.root->right);
    }
  }
  //root = copyHelper(other.root);
  // while(other.root!=NULL){
  // root->value=other.root->value;
  // //root->search_time
  // root->left=other.root->left;
  // root->right=other.root->right;
  // size++;
  // root->left=BSTree(other.root->left);
  // }
}

// move constructor
BSTree::BSTree(BSTree &&other)
{
  root = other.root;
  size = other.size;
  other.root = nullptr;
  other.size = 0;
}

//copy assignment
BSTree &BSTree::operator=(const BSTree &other)
{
  if(&other==this){
    return *this;
  }
  this->~BSTree();
  root = nullptr;
  size = other.size;

  if (other.root == nullptr)
    return *this;

  //Copy left subtree
  else
  {
    root = new Node(other.root->value);
    root->search_time = other.root->search_time;
    size = other.size;
    if (other.root->left != nullptr)
    {
      copy_helper(root->left, other.root->left);
    }
    if (other.root->right != nullptr)
    {
      copy_helper(root->right, other.root->right);
    }
  }
  return *this;
}

// move assignment
BSTree &BSTree::operator=(BSTree &&other)
{
  if(&other==this){
    return *this;
  }
  this->~BSTree();
  root = other.root;
  size = other.size;
  other.root = nullptr;
  other.size = 0;
  return *this;

}

// destructor

void postorder(Node *tree)
{
  if (tree->left != nullptr)
  {
    postorder(tree->left);
  }
  if (tree->right != nullptr)
  {
    postorder(tree->right);
  }
  delete tree;
}

BSTree::~BSTree()
{
  // Make sure to call delete on every node of the tree
  // You can use a recursive helper function to do this
  if (root != nullptr)
  {
    postorder(root);
  }
  root=nullptr;
}

Node * BSTree::insert_help(int obj, Node *&root, int time)
{
  if (root == nullptr)
  {
    root = new Node(obj);
    size++;
    root->search_time=time;
    root->left=nullptr;
    root->right=nullptr;
    return root;
    //root->value = obj;
  }
  else
  {
    if(obj == root->value){
      return nullptr;
    }
    if (obj < root->value)
    {
      return insert_help(obj, root->left, time+1);
    }
    if (obj > root->value)
    {
      return insert_help(obj, root->right, time+1);
    }
  }
}

Node *BSTree::insert(int obj)
{
  /* insert a node into the tree
    first find where the node should go
    then modify pointers to connect your new node */
  return insert_help(obj, root, 1);
}

Node * search_help(Node *&tree, int obj)
{
  if(tree==nullptr){
    return nullptr;
  }
  if(tree->value==obj){
    return tree;
  }

  if(obj<tree->value){
    return search_help(tree->left,obj);
  }
  else if(obj>tree->value){
    return search_help(tree->right,obj);
  }
  
  return nullptr;

  /*
  if (tree->left != nullptr)
  {
    if(tree->value==obj){
      return tree;
    }
    return search_help(tree->left,obj);
  }
  if (tree->right != nullptr)
  {
    if(tree->value==obj){
      return tree;
    }
    return search_help(tree->right,obj);
  }
  
  return nullptr;*/
  
}
Node *BSTree::search(int obj)
{
  /* recursively search down the tree to find the node that contains obj
    if you don't find anything return nullptr */
  return search_help(root, obj);
  
}

void search_times_help(Node *&tree, int time){
  //int time=0;





  if(tree!=nullptr){
    tree->search_time=time;
  }

  if (tree->left != nullptr)
  {
    search_times_help(tree->left, time+1);
  }
  if (tree->right != nullptr)
  {
    search_times_help(tree->right, time+1);
  }
  

}

void BSTree::update_search_times()
{
  /* do a BFS or DFS of your tree and update the search times of all nodes at once
      The root has a search time of 1, and each child is 1 more than its parent */
  if(root==nullptr){
    root->search_time=0;
  }
  search_times_help(root, 1);
}

void inorder_help(Node *tree, ostream &out){
  if(tree==nullptr){
    return;
  }
  inorder_help(tree->left, out);
  out<<tree->value<<"["<<tree->search_time<<"]\n";
  inorder_help(tree->right, out);
}

void BSTree::inorder(ostream &out)
{
  /* print your nodes in infix order
    If our tree looks like this:

       4
     2   6
    1 3 5 7

    It should output:
    1[3] 2[2] 3[3] 4[1] 5[3] 6[2] 7[3]
    You can use the << operator to print the nodes in the format shown */

  //if (left != nullptr) left->inorder(op)
  inorder_help(root, out);
}

void BSTree::print_level_by_level(ostream &out)
{
  /* Print the tree using a BFS so that each level contains the values for a level of the tree.
    Use X to mark empty positions. 
    
      if our tree looks like this:

       4
     2   6
    1   5 7
           9

    it should output:

    4[1]
    2[2] 6[2]
    1[3] X 5[3] 7[3]
    X X X X X X X 9[4]

    it might be helpful to do this part with the std::queue data structure.
    Hint: the Nth level contains 2^(N-1) nodes (with a value or with an X). Watch out
    for nodes like the left child of 6 above, and print the descendents of an empty
    node as also empty
    You can use the << operator to print nodes in the format shown */
//queue Node* q=new queue ;
//Queue Node* q = new Queue();
queue <Node *> q;
//Queue q; // This queue contains elements from a level and its children
q.push(root);
int elementsInLevel = 1; // Elements in the current level
bool nonNullChild = false;
while (elementsInLevel > 0){
  Node* node = q.front();
  q.pop();
  elementsInLevel-=1;
  if (node !=nullptr){
    out<<*node<<" ";
    q.push(node->left);
    q.push(node->right);
    //enqueue the children of node into q
    if (node->left!=nullptr || node->right!=nullptr){
      nonNullChild = true;
    }
  }
  
  else{
    out<<"X ";
    q.push(nullptr);
    q.push(nullptr);
  }
  if (elementsInLevel == 0){
    out<<endl;
    if (nonNullChild == true){
      nonNullChild = false;
      elementsInLevel = q.size();
  } // The next level is non-empty
  } // We have reached the end of the current level
    
  
    
}

}
