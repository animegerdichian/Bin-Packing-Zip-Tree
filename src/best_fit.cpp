#include "project2.h"
#include "merge_sort.h"
#include <algorithm>
#include <cmath>
#include "ZipTree.h"



/* helper function for checking double equality) */
bool equal(double x, double y){
   return std::fabs(x - y) <= 1e-10;
}

/* traverse: traverses tree finds a node with a capacity(key) that can fit the itemSize(x)
/*Input: node pointer, item size,
/*    boolean flag, reference to double and reference to node pointer to be assigned of correct
/*    values are found.
/*Returns: none
*/
void traverse(node<double, std::vector<int>>* n,double x,bool& flag,double& newKey,node<double, std::vector<int>>*& foundNode){

    if(n == nullptr || flag == true){
        return;
    }
    traverse(n->left,x,flag,newKey,foundNode);

    if((n->key >= x || std::fabs(x - n->key) < 1e-10) && flag != true){
        newKey = n->key;
        flag = true;
        foundNode = n;
        return;
    }
    traverse(n->right,x,flag,newKey,foundNode);
}

void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
    // rank = randomly generated, key = remaining capacity, value = vector of bin numbers

    ZipTree<double, std::vector<int>> tree;
    int total_bins = 0;
    node<double, std::vector<int>>* treeRoot = tree.getRoot();
    node<double, std::vector<int>>* foundNode = nullptr;
    node<double, std::vector<int>>* new_node = nullptr;

    for(int i=0; i < items.size(); i++){

        if(i == 0 || tree.getSize() == 0){
            // add first bin
            std::vector<int> a;
            a.push_back(i+1);

            // insert into tree
            tree.insert(1-items[i],a);
            assignment[i] = 1;
            free_space.push_back(1-items[i]);
            total_bins += 1;
        }
        else{
            treeRoot = tree.getRoot();
            double newKey = -1.0;
            bool flag = false;
            foundNode = nullptr;
            // traverse tree to find node to insert into
            traverse(treeRoot,items[i],flag,newKey,foundNode);

            if(flag == true){ // bin to put item in is found
                double new_capacity = newKey - items[i]; // calculate new capacity
                if(equal(new_capacity, 0.0)){
                    new_capacity = 0.0;
                }
                // find if there is already a node that has
                // the new capacity of the bin to be inserted into
                new_node = tree.findNode(new_capacity);
                int binNum = -1;
                if(foundNode->value.size() <= 1){ // once this bin is moved, there are no other bins with this capacity
                    binNum = foundNode->value[0];
                    tree.remove(foundNode->key); // remove the node from the tree
                }
                else{
                    // there are other bins with the same capacity
                    // just remove the bin number from the node
                    binNum = foundNode->value.back();
                    foundNode->value.pop_back();
                }
                if(new_node != nullptr){ // there is a node with correct capacity
                    // insert bin into the correct node
                    new_node->value.push_back(binNum);

                    // assign item to bin
                    assignment[i] = binNum;
                    free_space[binNum - 1] = new_capacity;
                }

                else{ // need to create new node with correct capacity
                    std::vector<int> b;
                    b.push_back(binNum);
                    tree.insert(new_capacity,b);
                    assignment[i] = binNum;
                    free_space[binNum - 1] = new_capacity;
                }

            }
            else{// a correct node was not found
                double new_cap = 1 - items[i]; // calculate new capacity
                if(equal(new_cap, 0.0)){
                    new_cap = 0.0;
                }
                new_node = tree.findNode(new_cap); // find node with correct capacity
                if(new_node != nullptr){ // there is a node with correct capacity
                     // insert bin into the correct node
                     total_bins += 1;
                     new_node->value.push_back(total_bins);

                     // assign item to bin
                     assignment[i] = total_bins;
                     free_space.push_back(new_cap);

                }
                else{
                    // create a new node and insert bin number
                    // int its value
                    std::vector<int> c;
                    c.push_back(total_bins + 1);
                    // create the first bin
                    tree.insert(1-items[i],c);
                    total_bins += 1;
                    assignment[i] = total_bins;// update assignments
                    free_space.push_back(new_cap);
                }
            }

        }
    }

    return;
}
void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
    // copy the items
    std::vector<double> items_copy = items;
    // sort the items and reverse
    merge_sort(items_copy);
    std::reverse(items_copy.begin(), items_copy.end());

    best_fit(items_copy, assignment, free_space);
        return;

}
