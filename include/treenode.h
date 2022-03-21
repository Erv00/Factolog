#ifndef treenode_H
#define treenode_H

#include <iostream>

class TreeNode{
public:
    virtual std::ostream& printDot(std::ostream& os) const = 0;
    virtual ~TreeNode(){};
};

#endif //treenode_H