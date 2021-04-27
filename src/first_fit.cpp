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
    NEED TO CHECK

*/

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

    if(node == nullptr){
        std::cout << "one" << std::endl;
        return false;
    }
    else if((node->value.first - itemSize) < -0.10){ // when the root BRC < itemSize
        std::cout << "itemSize = " << itemSize << std::endl;
        std::cout << "two: "  << node-> key<< std::endl;
       // IS THIS CORRECT?
        if(1-itemSize > node->value.first){
            node->value.first = 1-itemSize;
        }
        std::pair<double, double> val = std::make_pair(1-itemSize,1-itemSize);
        tree.insert(tree.getSize()+1,val);
        assignment[itemNum] = tree.getSize();
        // DO BRC CHECK
        return true;
    }
    else if(node->left != nullptr && (std::abs(node->left->value.first - itemSize) < DBL_EPSILON || (node->left->value.first - itemSize) > DBL_EPSILON)){
        std::cout << "three: "  << node-> key<< std::endl;
        visitInorder(tree, node->left, itemSize, itemNum, assignment);
    }
    else if(std::abs(node->value.second - itemSize) <= DBL_EPSILON || (node->value.second - itemSize) > DBL_EPSILON){
        std::cout << "three and a half: "  << node-> key<< std::endl;
        //node->value.second -= itemSize;
        node->value.second = std::ceil((node->value.second - itemSize) * 100.0) / 100.0;
        assignment[itemNum] = node->key;
    }
    else if(node->right != nullptr && (std::abs(node->right->value.first - itemSize) < DBL_EPSILON || (node->right->value.first - itemSize) > DBL_EPSILON)){
        std::cout << "four: "  << node-> key<< std::endl;
        visitInorder(tree, node->right, itemSize, itemNum, assignment);
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
        std::cout << "PRINTING TREE: " << std::endl;
        tree.printTFF();
        std::cout << "PRINTING END: " << std::endl;

    }

    treeRoot = tree.getRoot();
    updateBins(treeRoot, free_space);
    std::cout << "ASSIGNEMTS" << std::endl;
    for(int i= 0; i < assignment.size(); i++){
        std::cout << assignment[i] << std::endl;
    }
    std::cout << "free_space" << std::endl;
        for(int i= 0; i < free_space.size(); i++){
            std::cout << free_space[i] << std::endl;
        }


    return;
}
void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
    return;
}



