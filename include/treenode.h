/**
 * @file treenode.h
 * @author Pektor Ervin (pektor.ervin@sch.bme.hu)
 * @brief AST alapja
 * @version 0.1
 * @date 2022-03-24
 * @sa AST
 * @copyright Copyright (c) 2022
 */
#ifndef treenode_H
#define treenode_H

#include <iostream>

/**
 * @brief AST alaposztály
 */
class TreeNode{
public:
    /**
     * @brief Részfa kiírása dot formátumban
     * 
     * @param os Célstream
     * @return std::ostream& Célstream
     */
    virtual std::ostream& printDot(std::ostream& os) const = 0;

    /**
     * @brief TreeNode felszabadítása
     */
    virtual ~TreeNode(){};
};

#endif //treenode_H
