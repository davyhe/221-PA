#ifndef UNSORTEDMPQ_H
#define UNSORTEDMPQ_H

#include <stdexcept>
#include <vector>
#include "MPQ.h"
using std::vector;

/**
 * Minimum Priority Queue based on a vector
 */
template <typename T>
class UnsortedMPQ: MPQ<T> {
   // Implement the four funtions (insert, is_empty, min, remove_min) from MPQ.h
   // To hold the elements use std::vector
   // For remove_min() and min() just throw exception if the UnsortedMPQ is empty. Mimir already has a try/catch block so don't use try/catch block here.
private:
   vector <T> vec;

public:

   void insert(const T& data){
      vec.push_back(data);
   }

   bool is_empty(){
      if(vec.size()==0){
         return true;
      }
      return false;
   }

   T min(){
      if(vec.empty()){
         throw std::invalid_argument("UnsortedMPQ is empty");
      }
      T minum= vec[0];
      for (int i=0; i<vec.size();i++){
         if(vec[i] < minum){
            minum=vec[i];
         }
      }
      return minum;
   }

   T remove_min(){
      if(vec.empty()){
         throw std::invalid_argument("UnsortedMPQ is empty");
      }
      
      int index=0;
      T minum= vec[0];
      for (int i = 0; i<vec.size(); i++){
         if(vec[i]< minum){
            minum=vec[i];
            index=i;
         }
      }
      vec[index]=vec.back();
      vec.pop_back();
      //vec.erase(it);
      return minum;

   }

};

#endif