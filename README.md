# Countdown-Tree
This project creates a countdown tree, which is a type of AVL tree. A countdown tree, like an AVL tree, keeps track of its height and strives to guarantee that the heights of the left and right subtrees deviate by no more than one for each node in the tree. The countdown tree, unlike an AVL tree, does not ensure this property after every operation and instead employs regular BST insertion and deletion. Instead, it maintains a countdown that reduces with each insertion and deletion, and when the countdown hits zero, it rebalances all of its nodes at once.

Correct output for provided driver:  output.txt  
Output after inserting 0-9:  output-10.txt  
Output after inserting 0-19:  output-20.txt  
Output after inserting 0 down to -9:  output-neg10.txt  
