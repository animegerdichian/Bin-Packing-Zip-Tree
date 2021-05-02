#include "project2.h"
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <cmath>
#include <cfloat>
#include <climits>
#include <initializer_list>
#include "ZipTree.h"

/*
// check that all BRC values are correct
void fixBRC(node<int, std::pair<double, double>>* node){
    if (node == nullptr){
            return;
    }
    fixBRC(node->left);
    fixBRC(node->right);
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

void updateBins(node<int, std::pair<double, double>>* node, std::vector<double>& free_space){
    if (node == nullptr){
            return;
    }
    updateBins(node->left, free_space);
    free_space.push_back(node->value.second);
    updateBins(node->right, free_space);
}
bool visitInorder(ZipTree<int, std::pair<double, double>>& tree, node<int, std::pair<double, double>>* node, double itemSize, int itemNum, std::vector<int>& assignment ){
   //std::fabs(v1[i] - v2[i]) > 1e-3


    if(node == nullptr){
        return false;
    }
    else if((std::fabs(node->value.first - itemSize) > 1e-4) && ((node->value.first - itemSize) < 0)){
        std::pair<double, double> val = std::make_pair(1-itemSize,1-itemSize);
        tree.insert(tree.getSize()+1,val);
        assignment[itemNum] = tree.getSize();
        return true;

    }
    else if(node->left != nullptr && (!(std::fabs(node->left->value.first - itemSize) > 1e-4) ||  (node->left->value.first - itemSize) > 1e-4)){
        visitInorder(tree, node->left, itemSize, itemNum, assignment);
    }
    else if((!(std::fabs(node->value.second - itemSize) > 1e-4) ||  (node->value.second - itemSize) > 1e-4)){
        node->value.second = node->value.second - itemSize;
        assignment[itemNum] = node->key;
    }
    else if(node->right != nullptr && (!(std::fabs(node->right->value.first - itemSize) > 1e-4) ||  (node->right->value.first - itemSize) > 1e-4)){
        visitInorder(tree, node->right, itemSize, itemNum, assignment);
    }
    else{


        std::pair<double, double> val = std::make_pair(1-itemSize,1-itemSize);
        tree.insert(tree.getSize()+1,val);
        assignment[itemNum] = tree.getSize();
        return true;


    }
    // UPDATE BEST REMAINING CAPACITY?????? --> check node's own RC
    // CHECK THAT NODE HAS LEFT AND RIGHT
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
    // A FUNCTION TO CHECK BRC EVERY TIME THERE'S AN INSERT

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
            fix = visitInorder(tree, treeRoot, items[i], i, assignment);

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
    std::vector<double> items_copy;
    for(int i=0; i < items.size(); i++){
        items_copy.push_back(items[i]);
    }
    std::sort(items_copy.begin(), items_copy.end(), std::greater<double>());
    ZipTree<int, std::pair<double, double>> tree;
        std::pair<double, double> val = std::make_pair(-1.0,0.0);

        node<int, std::pair<double, double>>* treeRoot = tree.getRoot();
        bool fix = false;
        for(int i=0; i < items_copy.size(); i++){

            if(i == 0 || tree.getSize() == 0){
                // create the first bin
                val.first = 1- items_copy[i];
                val.second = 1 - items_copy[i];
                tree.insert(i+1,val);

                assignment[i] = tree.getSize();// update assignments

            }
            else{
                treeRoot = tree.getRoot();
                fix = visitInorder(tree, treeRoot, items_copy[i], i, assignment);

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

*/

