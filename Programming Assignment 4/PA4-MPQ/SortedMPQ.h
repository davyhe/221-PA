#ifndef SORTEDMPQ_H
#define SORTEDMPQ_H

#include <stdexcept>
#include <list>
#include "MPQ.h"
using std::list;

/*
 * Minimum Priority Queue based on a linked list
 */
template <typename T>
class SortedMPQ: MPQ<T> {
   // Implement the four funtions (insert, is_empty, min, remove_min) from MPQ.h
   // To hold the elements use std::list
   // For remove_min() and min() throw exception if the SortedMPQ is empty. Mimir already has a try/catch block so don't use try/catch block here.
private:
   list<T> lis;

public:
   void insert(const T& data){// assume the list is sorted??
      auto it=lis.end();
      for(auto i = lis.begin(); i!=lis.end(); i++){
         if(data< *i){
            it=i;
            break;
         }
      }
      lis.insert(it, data);
   }

   bool is_empty(){
      if(lis.size()==0){
         return true;
      }
      return false;
   }

   T min(){
      if(lis.empty()){
         throw std::invalid_argument("UnsortedMPQ is empty");
      }
      return lis.front();
   }

   T remove_min(){
      if(lis.empty()){
         throw std::invalid_argument("UnsortedMPQ is empty");
      }
      T minum=lis.front();
      lis.pop_front();
      return minum;
   }




};

#endif