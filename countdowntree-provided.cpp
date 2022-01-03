#include "countdowntree.h"

//Returns the height of this tree
int CountdownTree::getHeight() const
{
  if (root != nullptr)
    return root->height; 
  else
    return 0;
}

//Validates that the size, parent pointers, heights, and
//BST property are all correct
void CountdownTree::validate() const
{
  int tempSize = 0;
  if (root != nullptr)
    root->validate(tempSize);

  if (size != tempSize)
    cout << "Number of nodes (" << tempSize << ") doesn't match size (" << size << ")\n";
}

//Recursively validates the height, parent pointers, and
//BST property in the subtree rooted at this node
//Accumulates the number of nodes in the subtree to size
void Node::validate(int& size) const
{
  //Count this node
  size++;

  //Validate height
  if (left == nullptr && right == nullptr)
  {
    if (height != 1)
      cout << "Height of " << data << " = " << height << " (leaf)\n";
  }
  else if (right == nullptr)
  {
    if (height != left->height + 1)
      cout << "Height of " << data << " = " << height << " (child height = " << left->height << ")\n";
  }
  else if (left == nullptr)
  {
    if (height != right->height + 1)
      cout << "Height of " << data << " = " << height << " (child height = " << right->height << ")\n";
  }
  else if (left->height >= right->height)
  {
    if (height != left->height + 1)
      cout << "Height of " << data << " = " << height << " (children:  " << left->height << " and " << right->height << ")\n";
  }
  else if (height != right->height + 1)
    cout << "Height of " << data << " = " << height << " (children:  " << left->height << " and " << right->height << ")\n";

  //Validate BST property and child <-> parent pointers
  //Validate left and right subtrees recursively
  if (left != nullptr)
  {
    if (left->data > data)
      cout << "Left child of " << data << " has value " << left->data << '\n';
    if (left->parent != this)
      cout << "Parent pointer for " << left->data << " not set to " << data << '\n';
    left->validate(size);
  }
  if (right != nullptr)
  {
    if (right->data < data)
      cout << "Right child of " << data << " has value " << right->data << '\n';
    if (right->parent != this)
      cout << "Parent pointer for " << right->data << " not set to " << data << '\n';
    right->validate(size);
  }
}

//Print all nodes in the CountdownTree
ostream& operator<<(ostream& out, const CountdownTree& tree)
{
  return out << tree.root;
}

//Recursively print the subtree rooted at this node
//Format:  (data [height] L=left_subtree R=right_subtree)
ostream& operator<<(ostream& out, const Node* node)
{
  if (node != nullptr)
    return out << '(' << node->data 
               << " [" << node->height 
               << "] L=" << node->left 
               << " R=" << node->right << ')';
  else
    return out;
}