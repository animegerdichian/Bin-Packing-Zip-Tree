#include <vector>
#include "merge_sort.h"


/*
 *merge
 *Arguments: reference to vector of ints, int for index of partiton start, 
 *int for index of partition end, int for partition middle
 *Returns: void
 *
 *A function that merges two sorted partitions
 */
void merge(std::vector<double>& nums, int left, int right, int mid){
	
	
	// temporary lists to hold the two partitions
	std::vector<double> Left;
	std::vector<double> Right;


	int partition1Size = mid - left + 1;
	int partition2Size = right - mid;
	
	// add elements to each temp partition list
	for(int i=0; i < partition1Size; i++){

		Left.push_back(nums[left + i]);
		
	}

	for(int j=0; j < partition2Size; j++){
		Right.push_back(nums[mid + j + 1]);
		
	}
	
	int i = 0;
	int j = 0;
	int q = left;

	// compare elements
	while(i < partition1Size && j < partition2Size){
		if(Left[i] <= Right[j]){
			nums[q] = Left[i];
			i++;
		}
		else{
			nums[q] = Right[j];
			j++;
		}

		q++; 
	}
	// add in other elements in the temporary
	// vectors
	while(i < partition1Size){
		nums[q] = Left[i];
		i++;
		q++;
	}

	while( j < partition2Size){
		nums[q] = Right[j];
		j++;
		q++;
	}
}

/*
 *merge_sort_rec
 *Arguments: reference to vector of ints, int for index of partiton start, 
 *int for index of partition end
 *Returns: void
 *
 *A recursive function that uses the merge sort algorithm to sort
 *a vector of ints in place
 *
 *The vector is partitioned and sorted and then the partitions are merged
 */
void merge_sort_rec(std::vector<double>& nums, int left, int right){
	

	if(left >= right)
		return;

	int mid = left + (right - left) / 2;// partition the list
	merge_sort_rec(nums, left, mid); // sort first partition
	merge_sort_rec(nums, mid+1, right); // sort second partition
	merge(nums, left, right, mid); // merge the two sorted partitions

}

/*
 *merge_sort
 *Arguments: reference to vector of ints
 *Returns: void
 *
 *A function that will call function merge_sort_rec
 *to sort the input parameter if the size of the vector
 *is larger than 1
 */
void merge_sort(std::vector<double>& nums){
	

	// there's nothing to sort
	if(nums.size() <= 1)
		return;
  
	merge_sort_rec(nums,0, nums.size()-1);
	

}


