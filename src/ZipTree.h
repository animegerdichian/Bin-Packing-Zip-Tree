#ifndef ZIPTREE_H
#define ZIPTREE_H

#include <random>
#include <iostream>
#include <cmath>

// nodes of the zip tree
template <typename KeyType, typename ValType>
struct node{
        KeyType key;
        ValType value;
        unsigned rank;
        node* left = nullptr;
        node* right = nullptr;
        std::string x;
        node() : left(nullptr), right(nullptr) {};
    };


// explanations for public member functions are provided in project2.h
// each file that uses a WAVL tree should #include this file
template <typename KeyType, typename ValType>
class ZipTree
{
public:
	// DO NOT MODIFY METHOD SIGNATURES BELOW THIS LINE
	ZipTree();
	~ZipTree();
	static unsigned getRandomRank();
	void insert(const KeyType& key, const ValType& val, unsigned rank = getRandomRank());
	void remove(const KeyType& key);
	ValType find(const KeyType& key);
	unsigned getSize();
	int getHeight();
	unsigned getDepth(const KeyType& key);
	// DO NOT MODIFY METHOD SIGNATURES ABOVE THIS LINE

	// define new public methods
	void recDelete(node<KeyType,ValType>* n); // a helper method to recursively delete nodes used in destructor
    void printTree(node<KeyType,ValType>* n, int space);
    void printT();
    node<KeyType,ValType>* getRoot();
    node<KeyType, ValType>* findNode(const KeyType& key);


private:
	// define private methods
	node<KeyType,ValType>* root; // root node
	unsigned height; // tree height
	unsigned size; // tree size - number of nodes





};



// fill in the definitions for each required member function and for any additional member functions you define

// Constructor
template <typename KeyType, typename ValType>
ZipTree<KeyType, ValType>::ZipTree()
{

	root = nullptr;
	height = 0;
	size = 0;
}

// Destructor
template <typename KeyType, typename ValType>
ZipTree<KeyType, ValType>::~ZipTree()
{

    // call helper method to delete root and its subtrees
    recDelete(root);

}

template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::getRandomRank()
{
    // use geometric distribution and rand num generator to produce a rank
    std::random_device device; // source of entropy
    std::default_random_engine engine{device()};
    std::geometric_distribution<int> distribution{0.5}; // geometric distribution
    unsigned rank = distribution(engine);
	return rank;
}

template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::insert(const KeyType& key, const ValType& val, unsigned rank)
{
     size += 1;

            node<KeyType,ValType>* cur = root;
            node<KeyType,ValType>* prev = nullptr;
            node<KeyType,ValType>* fix = nullptr;
            node<KeyType,ValType>* newNode = new node<KeyType,ValType>;
            newNode->key = key;
            newNode->value = val;
            newNode->rank = rank;
            newNode->left = nullptr;
            newNode->right = nullptr;

            while(cur != nullptr && (rank < cur->rank || (rank == cur->rank && key > cur->key))){
                prev = cur;
                if(key < cur->key){
                    cur = cur->left;
                }
                else{
                    cur = cur->right;
                }
            }
            if(cur == root){
                // one
                root = newNode;
                newNode->x = "one";
            }
            else if(key < prev->key){
                // two
                prev->left = newNode;
                newNode->x = "two";
            }
            else{
                // three
                prev->right = newNode;
                newNode->x = "three";

            }

            if(cur == nullptr){
                // four --> LEAF : BRC = RC
                newNode->left = nullptr;
                newNode->right = nullptr;
                newNode->x = "four";
                return;
            }

            if(key < cur->key){
                // five
                newNode->right = cur;
                newNode->x = "five";
            }
            else{
                // six
                newNode->left = cur;
                newNode->x = "six";
            }
            // seven
            prev = newNode;
            newNode->x = "seven";

            while(cur != nullptr){
                fix = prev;
                if(cur->key < key){
                    while(cur != nullptr && cur->key <= key){
                        prev = cur;
                        cur = cur->right;
                    }
                }
                else{
                    while(cur != nullptr && cur->key >= key){
                        prev = cur;
                        cur = cur->left;
                    }
                }
                if(fix->key > key || (fix == newNode && prev->key > key)){
                    // eight --> NOT LEAF - BRC is max(RC of subtrees)
                    fix->left = cur;
                    newNode->x = "eight";
                }
                else{
                    // nine --> NOT LEAF - BRC is max(RC of subtrees)
                    fix->right = cur;
                    newNode->x = "nine";
                }

            }
}

template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::remove(const KeyType& key)
{
    node<KeyType,ValType>* cur = root;
      	node<KeyType,ValType>* prev;
      	node<KeyType,ValType>* left;
      	node<KeyType,ValType>* right;
      	while(key != cur->key){
      	    prev = cur;
      	    if(key < cur->key){
      	        cur = cur->left;
      	    }
      	    else{
      	        cur = cur->right;
      	    }
      	}
      	left = cur->left;
      	right = cur->right;

      	if(left == nullptr){
      	    cur = right;
      	}
      	else if(right == nullptr){
      	    cur = left;
      	}
      	else if(left->rank >= right->rank){
      	    cur = left;
      	}
      	else{
      	    cur = right;
      	}

      	if(root->key == key){
      	    root = cur;
      	}
      	else if(key < prev->key){
      	    prev->left = cur;
      	}
      	else{
      	    prev->right = cur;
      	}

      	while(left != nullptr && right != nullptr){
      	    if(left->rank >= right->rank){
      	        while(left != nullptr && left->rank >= right->rank){
      	            prev = left;
      	            left = left->right;
      	        }
      	        prev->right = right;
      	    }
      	    else{
      	        while(right != nullptr && left->rank < right->rank){
      	            prev = right;
      	            right = right->left;
      	        }
      	        prev->left = left;
      	    }

      	}

      	size--;
}

template <typename KeyType, typename ValType>
ValType ZipTree<KeyType, ValType>::find(const KeyType& key)
{
    node<KeyType,ValType>* cur = root;
    while(cur){
        if(key < cur->key){
            cur = cur->left;
        }
        else if(key > cur->key){
            cur = cur->right;
        }
        else{
            return cur->value;
        }

    }

	return 0;
}


template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::getSize()
{
	return size;
}

template <typename KeyType, typename ValType>
int ZipTree<KeyType, ValType>::getHeight()
{
	return height;
}

template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::getDepth(const KeyType& key)
{
	node<KeyType,ValType>* cur = root;
	int depth = 0;

        while(cur != nullptr){
            if(key < cur->key){
                cur = cur->left;
                depth += 1;
            }
            else if(key > cur->key){
                cur = cur->right;
                depth += 1;
            }
            else{
                return depth;
            }
        }

    	return depth;
}

// helper methods
/* recDelete: used in destructor to delete a node and its left and right subtrees recursively
*   input: pointer to node n
*   returns: none
*/
template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::recDelete(node<KeyType,ValType>* n)
{
    // recursively delete the left and right subtrees of node n

	if(n){
	    recDelete(n->left);
	    recDelete(n->right);

	    delete n;

	}

}

template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::printTree(node<KeyType,ValType>* n, int space){
/*
    if (n != nullptr) {
            if (n->right != nullptr){
                printTree(n->right, space + 15);
            }
            for (int j = 0; j < space; ++j) {
                std::cout << ' ';
            }
            std::cout << "(" << n->key << ",  " << "bins: ";
            for(int i=0;i < n->value.size(); i++){
                std::cout << n->value[i] << " , ";
            }
            std::cout << std::endl;
            if (n->left){
                printTree(n->left, space + 15);
            }
    }

*/

}

template <typename KeyType, typename ValType>
node<KeyType, ValType>* ZipTree<KeyType, ValType>::findNode(const KeyType& key)
{
    node<KeyType,ValType>* cur = root;

    while(cur){
        if(std::fabs(key - cur->key) < 1e-10){
            return cur;
        }
        else if(key < cur->key){
            cur = cur->left;
        }
        else if(key > cur->key){
            cur = cur->right;
        }

        else{
            return cur;
        }

    }

	return nullptr;
}

template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::printT(){


    printTree(root,10);

}


template <typename KeyType, typename ValType>
node<KeyType,ValType>* ZipTree<KeyType, ValType>::getRoot(){
    return root;
}


#endif
