//Implement a countdown tree
#include "countdowntree.h"
#include <iostream>

void Node::rebalance()
{
    if(left != nullptr)
        left->rebalance();
    if(right != nullptr)
        right->rebalance();
    
    auto countBal = [] (Node* temp)
    {
        int leftHeight, rightHeight;
        if(temp->left == nullptr)
           leftHeight = 0;
        else
           leftHeight = temp->left->height;

        if(temp->right == nullptr)
           rightHeight = 0;
        else
           rightHeight = temp->right->height;
        
        int countBal;
        countBal = rightHeight - leftHeight;
        return countBal;
    };
    
    int val = countBal(this);
    if(val != -1 && val != 1 && val != 0)
    {
        int leftVal, rightVal;
        if (left == nullptr)
           leftVal = 0;
        else
           leftVal = countBal(left);

        if (right == nullptr)
           rightVal = 0;
        else
           rightVal = countBal(right);
        
        //If left is imbalanced
        if(val <= -2) 
        {
            if(leftVal > 0)
            {
                left->right->rotateLeft();
                left->rotateRight();
                this->updateHeight();
                parent->left->updateHeight();
                parent->updateHeight();
            }
            else if(leftVal <= 0)
            {
                left->rotateRight();
                this->updateHeight();
                parent->left->updateHeight();
                parent->updateHeight();
            }
        }
        //If right is imbalanced
        else if(val >= 2) 
        {
            if(rightVal >= 0)
            {
                right->rotateLeft();
                this->updateHeight();
                parent->right->updateHeight();
                parent->updateHeight();
            }
            else if(rightVal < 0)
            {
                right->left->rotateRight();
                right->rotateLeft();
                this->updateHeight();
                parent->right->updateHeight();
                parent->updateHeight(); 
            }
        }
    }
    else
        updateHeight();
}

void Node::rotateLeft()
{
    parent->right = left;
    if(left != nullptr)
        left->parent = parent;
    
    left = parent;
    parent = parent->parent;

    if(left->isLeftChild())
        parent->left = this;
    else if(left->isRightChild())
        parent->right = this;

    left->parent = this;
}

void Node::rotateRight()
{
    parent->left = right;
    if(right != nullptr)
        right->parent = parent;
    
    right = parent;
    parent = parent->parent;

    if(right->isLeftChild())
        parent->left = this;
    else if(right->isRightChild())
        parent->right = this;

    right->parent = this;
}


bool Node::isLeftChild() const
{
    return parent != nullptr && parent->left == this;
}


bool Node::isRightChild() const
{
    return parent != nullptr && parent->right == this;
}

void Node::updateHeight()
{
    if(left != nullptr || right != nullptr)
    {
        int leftHeight, rightHeight;
        if(left == nullptr)
            leftHeight = 0;
        else 
            leftHeight = left->height;

        if(right == nullptr)
            rightHeight = 0;
        else 
            rightHeight = right->height;
        
        if(leftHeight > rightHeight)
            height = leftHeight + 1;
        else
            height = rightHeight + 1;
    }
    else if(left != nullptr & right != nullptr)     
    {
        height = std::max(left->height, right->height) + 1;
    }
    else
        height = 1;
}


bool CountdownTree::contains(int val) const
{
    if(root == nullptr || root->search(val) == nullptr)
        return false;
    else
        return true;
}


Node* Node::search(int val)
{
    if(val == data)
        return this;
    else if(val < data)
    {
        if(left != nullptr)
            return left->search(val);
        else
            return nullptr;
    }
    else
    {
        if(right != nullptr)
            return right->search(val);
        else
            return nullptr;
    }
}


void CountdownTree::insert(int x)
{
    if(root != nullptr)
        root->insert(x);
    else 
        root = new Node(x);
	
	size++;

    //countdown
	count--;
    if(count == 0)
    {
        root->rebalance();
        Node* node = root;
        if(node != nullptr)
        {
            while(node->parent)
               node = node->parent;
        }
        root = node;

        if(getHeight() > MINIMUM_COUNTDOWN)
           count = getHeight();
        else
           count = MINIMUM_COUNTDOWN;
    }
}


void Node::insert(int val)
{
    Node* node = new Node(val);
    if(val < data)
    {
        if(left != nullptr)
            left->insert(val);
        else
        {  
            left = node;
            left->parent = this;
        }
    }
    else
    {
        if(right != nullptr)
            right->insert(val);
        else
        {
            right = node;
            right->parent = this;
        }
    }
}


void CountdownTree::remove(int val)
{
    if(root == nullptr)
        return; //empty BST

    Node* victim = root->search(val);
    if(victim == nullptr)
        return; //doesn't contain that value

    if(victim == root) //update root if deleting
        root = victim->remove();
    else
        victim->remove();
    
    size--;

    //countdown
    count--;
    if(count == 0)
    {
        root->rebalance();
        Node* node = root;
        if(node != nullptr)
        {
            while(node->parent)
               node = node->parent;
        }
        root = node;

        if(getHeight() > MINIMUM_COUNTDOWN)
           count = getHeight();
        else
           count = MINIMUM_COUNTDOWN;
    }
}


Node* Node::remove()
{
    Node* node = this->parent;

    int num_Children = (left != NULL) + (right != NULL);

    if(num_Children == 0)
    {
        if(isLeftChild())
            parent->left = nullptr;
        else if(isRightChild())
            parent->right = nullptr;
        
        delete this;
        return nullptr;
    }
    else if(num_Children == 1)
    {
        Node* child;
        if(left != nullptr)
            child = left;
        else
            child = right;

        child->parent = parent;

        if(isLeftChild())
            parent->left = child;
        else if(isRightChild())
            parent->right = child;

        left = right = nullptr;
        delete this;
        return child;
    }
    else
    {
        Node* swap = left->max();
        data = swap->data;
        swap->remove();
        return this;
    }

    while(node != NULL)
    {
        node->updateHeight();
        node = node->parent;
    }
}


Node* Node::max()
{
    if(right == nullptr)
        return this;
    else
        return right->max();
}