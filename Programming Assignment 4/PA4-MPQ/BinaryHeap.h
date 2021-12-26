 #ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <stdexcept>
#include <iostream>
#include <vector>
#include <math.h>

/*
 * Binary Heap class
 */
template <typename T>
class BinaryHeap {
    public:
        //Implement the below 4 methods. Please note these methods are not from MPQ.h
        //BinaryHeap class does not inherit MPQ class 
        //Implement BinaryHeap insert operation
        //Also implement upheap and downheap operations (functions provided below) and call them from wherever necessary
        void insert(const T& data){
            elements.push_back(data);
            up_heap(elements.size()-1);
            size++;

        }
        // Return true if BinaryHeap is empty otherwise false
        bool is_empty(){
            if(elements.empty()){
                return true;
            }
            return false;
        }
        // Return minimum element in the BinaryHeap
        T min(){
            if(elements.empty()){
                throw std::invalid_argument("BinaryHeap is empty");
            }
            return elements.front();
        }
        // Remove minimum element in the BinaryHeap and return it
        
        T remove_min(){////??????????????????
            if(elements.empty()){
                throw std::invalid_argument("BinaryHeap is empty");
            }
            swap(0, elements.size()-1);
            T minum= elements.back();
            elements.pop_back();
            size--;
            down_heap(0);
            return minum;
        }
    private:
        //
        std::vector<T> elements;
        int size = 0;
        //Implement down heap operation
        void down_heap(int i);
        //Implement up heap operation
        void up_heap(int i);

        //Pre-implemented helper functions
        //swaps two elements at positions a and b
        void swap(int a, int b) { T c(elements[a]); elements[a] = elements[b]; elements[b] = c;}
        //Binary tree (Complete Binary tree) can be represented in vector form and hence, stored in a vector. 
        //Returns the right child index of current index
        int right_child(int i) {return 2*i + 2;}
        //Returns the left child index of current index
        int left_child(int i) {return 2*i + 1;}
        //Returns the parent index of current index
        int parent(int i) {return floor((i-1)/2);}
        //Checks if current index is an internal node
        bool is_internal(int i) {return left_child(i) < size || right_child(i) < size;}
        //Checks if current index is a leaf
        bool is_leaf(int i) {return left_child(i) >= size && right_child(i) >= size;}
};

/*
 * Restores the binary heap property starting from a node that is smaller than its parent
 */
template <typename T>
void BinaryHeap<T>::up_heap(int i){
    int parent_index = parent(i);
    /*
     * Can be computed iteratively or recursively
     */
    if(i && elements[i] < elements[parent_index]){
        swap(i, parent_index);
        up_heap(parent_index);
    }
}

/*
 * Restores the binary heap property starting from an node that is larger than its children
 */
template <typename T>
void BinaryHeap<T>::down_heap(int i){
    int right_index = right_child(i);
    int left_index = left_child(i);
    /*
     * Can be computed iteratively or recursively
     */
    int small=i;
    if(left_index < size && elements[left_index] < elements[i]){
        small=left_index;
    }

    if(right_index < size && elements[right_index] < elements[small]){
        small=right_index;
    }

    if(small != i){
        swap(i, small);
        down_heap(small);
    }

    /*
    if(left_index>=0 && right_index>=0 && elements[left_index] > elements[right_index]){
        left_index=right_index;
    }
    

    if(left_index > 0 && elements[i] > elements[left_index]){
        swap(i, left_index);
        down_heap(left_index);
    }
    */
}
#endif