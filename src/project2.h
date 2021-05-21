#ifndef PROJECT2_H
#define PROJECT2_H



#include <vector>


void next_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space);

//implement in first_fit.cpp
void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space);
void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space);

// implement in best_fit.cpp
void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space);
void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space);


#endif /* PROJECT2_H */
