#ifndef PROJECT2_H
#define PROJECT2_H

// DO NOT MODIFY THIS FILE

#include <vector>

// each file should #include this header file
// implement in next_fit.cpp
void next_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space);

//implement in first_fit.cpp
void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space);
void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space);

// implement in best_fit.cpp
void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space);
void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space);

/*
 * details about submitting to Gradescope:
 * - you can create additional header/source files and submit them alongside the required files
 *
 * - you do NOT need to submit project2.h, but you DO need to submit ZipTree.h
 *   make sure you do not modify any of the public ZipTree/bin packing function declarations, as during testing
 *   we will be assuming that these functions have the same parameter/return types
 *
 * - we will be using our own main function while grading, so do NOT submit any files that have a main function defined
 *
 * - the submission should be a zip file consisting of all source code/header files. the zip file should not contain any directories
 *
 * - if you do not implement some of the bin packing algorithms, you should still have empty definitions for those algorithms for your code to compile properly
 *
 *
 * explanations for ZipTree public member functions
 * the tree should be templated: KeyType is a comparable type, to use for ordering the tree. ValType is for any additional data to be stored in the nodes.
 * getRandomRank(): returns a random node rank, chosen independently from a geometric distribution of mean 1
 * insert(): inserts item with parameter key, value, rank into tree
 * remove(): removes item with parameter key from tree
 * find(): returns the value of item with parameter key
 * getSize(): returns the number of nodes in the tree
 * getHeight(): returns the height of the tree
 * getDepth(): returns the depth of the item with parameter key
 *
 * for all bin packing functions
 * params:
 *      items: the items to assign to bins
 *      assignment: the assignment of the ith item to the jth bin for all i items. (bin numbers start from 1, so you should not have any 0th bins in this vector)
 *                  assume assignment.size() == items.size().
 *                  you should not add any new elements to this vector.
 *                  you must modify this vector's elements to indicate the assignment.
 *      free_space: the amount of space left in the jth bin for all j bins created in the algorithm.
 *                  you should add one element for each bin that the algorithm creates.
 *                  when the function returns, this should indicate the final free space available in each bin.
 *
 * example usage:
 *      std::vector<double> items;
 *      ...populate items...
 *      std::vector<int> assignment(items.size(), 0); // same size as items, all values are 0
 *      std::vector<double> free_space; // empty double vector
 *      next_fit(items, assignment, free_space);
 *      // at this point,
 *      // assignment should hold the assignment next_fit makes,
 *      // free_space should have as many elements as bins created by next_fit,
 *      // with the final free space available in the corresponding bins
 */

#endif /* PROJECT2_H */
