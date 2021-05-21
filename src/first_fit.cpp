#include "project2.h"
#include "merge_sort.h"
#include <algorithm>
#include <cmath>

#include "ZipTree.h"

/* fixBRC: traverses tree and checks that all node BRC values are the max
/*      of their own and their left and right subtrees. Used when an insertion
/*      of an item is made in a pre-existing bin
/*Input: node pointer
/*Returns: none
*/
void fixBRC(node<int, std::pair<double, double>>* node){
    if (node == nullptr){
            return;
    }
    fixBRC(node->left); // check left subtree
    fixBRC(node->right); // check right subtree
    double left = 0.0;
    double right = 0.0;
        if(node->left != nullptr){
            left = node->left->value.first;
        }
        if(node->right != nullptr){
                right = node->right->value.first;
            }
        node->value.first = std::max({left, right, node->value.second});


}
/* updateBins: traverses tree and updates values in free_space vector,
/*      used once after all bin assignments are done.
/*Input: node pointer, vector that holds free space values
/*Returns: none
*/
void updateBins(node<int, std::pair<double, double>>* node, std::vector<double>& free_space){
    if (node == nullptr){
            return;
    }
    updateBins(node->left, free_space);
    free_space.push_back(node->value.second);
    updateBins(node->right, free_space);
}

/* traverseTree: traverses tree to find first node with BRC that is >= the given item size
/*          Also updates the assignments vector
/*Input: reference to the zip tree, node pointer, size of the item, the item number, reference to assignments vector
/*Returns: boolean, true if the BRC values need to be checked and updated
*/
bool traverseTree(ZipTree<int, std::pair<double, double>>& tree, node<int, std::pair<double, double>>* node, double itemSize, int& itemNum, std::vector<int>& assignment ){

    if(node == nullptr){
        return false;
    }
    // the BRC is less than item size, so no node on either subtree has enough capacity
    // insert a new node(bin)
    else if((std::fabs(node->value.first - itemSize) > 1e-10) && ((node->value.first - itemSize) < 0)){
        std::pair<double, double> val = std::make_pair(1-itemSize,1-itemSize);
        tree.insert(tree.getSize()+1,val);
        assignment[itemNum] = tree.getSize();
        return true;
    }
    // traverse the left subtree, BRC > itemSize
    else if(node->left != nullptr && (!(std::fabs(node->left->value.first - itemSize) > 1e-10) ||  (node->left->value.first - itemSize) > 1e-10)){
        traverseTree(tree, node->left, itemSize, itemNum, assignment);
    }
    // found node(bin) to insert into
    else if((!(std::fabs(node->value.second - itemSize) > 1e-10) ||  (node->value.second - itemSize) > 1e-10)){
        node->value.second = node->value.second - itemSize;
        assignment[itemNum] = node->key;
    }
    // traverse the right subtree, BRC <= itemSize
    else if(node->right != nullptr && (!(std::fabs(node->right->value.first - itemSize) > 1e-10) ||  (node->right->value.first - itemSize) > 1e-10)){
        traverseTree(tree, node->right, itemSize, itemNum, assignment);
    }
    // not found, insert into the tree
    else{
        std::pair<double, double> val = std::make_pair(1-itemSize,1-itemSize);
        tree.insert(tree.getSize()+1,val);
        assignment[itemNum] = tree.getSize();
        return true;
    }
    // Update BRC
    double left = 0.0;
    double right = 0.0;
    if(node->left != nullptr){
        left = node->left->value.first;
    }
    if(node->right != nullptr){
            right = node->right->value.first;
        }
    node->value.first = std::max({left, right, node->value.second});
    return false;
}


void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
    // rank = randomly generated key = bin index, value = (best remaining capacity, remaining capacity)

    ZipTree<int, std::pair<double, double>> tree;
    std::pair<double, double> val = std::make_pair(-1.0,0.0);

    node<int, std::pair<double, double>>* treeRoot = tree.getRoot();
    bool fix = false;
    for(int i=0; i < items.size(); i++){

        if(i == 0 || tree.getSize() == 0){
            // create the first bin
            val.first = 1- items[i];
            val.second = 1 - items[i];
            tree.insert(i+1,val);
            assignment[i] = tree.getSize();// update assignments
        }
        else{
            treeRoot = tree.getRoot();
            fix = traverseTree(tree, treeRoot, items[i], i, assignment);// traverse tree and find correct bin

            if(fix){
                treeRoot = tree.getRoot();
                fixBRC(treeRoot);
            }
        }
    }
    treeRoot = tree.getRoot();
    updateBins(treeRoot, free_space);
    return;
}
void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
    // make a copy of the items
    std::vector<double> items_copy = items;
    // sort the items and reverse
    merge_sort(items_copy);
    std::reverse(items_copy.begin(), items_copy.end());

    first_fit(items_copy, assignment, free_space);
    return;
}



