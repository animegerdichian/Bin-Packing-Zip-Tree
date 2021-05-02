#include "project2.h"
#include <algorithm>
#include <cstdint>
#include <cmath>
#include <cfloat>
#include <climits>
#include <initializer_list>
#include <iostream>


void next_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
        if(items.size() > 0){
            free_space.push_back(1.0);
        }
        	int j = 1;
        	for (int i = 0; i < items.size(); ++i) {
        		if (!(std::fabs(free_space[j-1] - items[i]) > 1e-4)|| (free_space[j-1] - items[i]) > 1e-4) {
        			assignment[i] = j;
        			free_space[j-1] -= items[i];
        		}
        		else {
        			free_space.push_back(1.0);
        			j++;
        			assignment[i] = j;
        			free_space[j-1] -= items[i];
        		}
        	}

}