/**
 * There is no Collection.cpp for this assignment.
 * Move all the functions from Collection.cpp to this file except Operator>> 
 * Covert the Collection class to a templated form. (Stress_ball should be replaced with typename "Obj".
 *   Stress_ball_colors and Stress_ball_sizes should be replaced with typename "F2").
 * This file has to be uploaded to mimir.
 */

#ifndef Collection_H
#define Collection_H
#include <string>
#include <iostream>
using namespace std;

enum class Sort_choice{bubble_sort, insertion_sort, selection_sort};

class Empty_Collection{};

template <typename Obj, typename F1, typename F2>
class Collection {
    Obj* array;
    int size;
    int capacity;
    void resize();
public:
	Collection();
    Collection(int cap);
    Collection(const Collection& c);
    Collection& operator=(const Collection& c);
    ~Collection();
    Collection(Collection&& c);
    Collection& operator=(Collection&& c);
    void insert_item(const Obj& sb);
    bool contains(const Obj& sb) const;
    Obj remove_any_item();
    void remove_this_item(const Obj& sb);
    void make_empty();
    bool is_empty() const;
    int total_items() const ;
    int total_items(F2 s) const;// SIZE
    int total_items(F1 c) const;// COLOR
    void print_items() const;
    Obj& operator[](int i);
    const Obj& operator[](int i) const;
    
};// end of the collection class parameter

template <typename Obj, typename F1, typename F2>
	Collection<Obj, F1, F2>::Collection(){
        size = 0;
	    capacity = 0;
	    array = nullptr;
    }
template <typename Obj, typename F1, typename F2>
    Collection<Obj, F1, F2>::Collection(int cap){
        capacity = cap;
        size = 0;
        array = new Obj[capacity];
    }

template <typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2>::Collection(const Collection& c): size(c.size), capacity(c.capacity), array(new Obj[c.capacity]){
	for (int i = 0; i < c.capacity;i++) {
	array[i] = c.array[i];
	}
}

template <typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2>& Collection<Obj, F1, F2>::operator=(const Collection& c) {// copy assignment
	if (this == &c) {
		return *this;
	}
	array = new Obj[c.capacity];
	for (int i = 0; i < c.capacity; i++) {
		array[i] = c.array[i];
	}
	size = c.size;
	capacity = c.capacity;
	return *this;
}

template <typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2>::~Collection() {
	delete[] array;
	size = 0;
	capacity = 0;
}

template <typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2>::Collection(Collection&& c): size(c.size), capacity(c.capacity), array(c.array) {// move assignment
	c.size = 0;
	c.capacity = 0;
	c.array = nullptr;
}

template <typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2>& Collection<Obj, F1, F2>::operator=(Collection&& c) {
	if (this == &c) {
		return *this;
	}
	delete[] array;
	array = c.array;
	c.array = nullptr;
	size = c.size;
	capacity = c.capacity;
	c.size = 0;
	c.capacity = 0;
	return *this;
}

template <typename Obj, typename F1, typename F2>
void Collection<Obj, F1, F2>::resize() {
	if(capacity==0){
		capacity=1;
	}
	else{
		capacity *= 2;
	}
	Obj* newarray = new Obj[capacity];
	for (int i = 0; i < size; i++) {
		newarray[i] = array[i];
	}
	delete[] array;
	array = newarray;
}

template <typename Obj, typename F1, typename F2>
void Collection<Obj, F1, F2>::insert_item(const Obj& sb) {
	if (size == capacity) {
		resize();
	}
	array[size] = sb;
	size++;

}

template <typename Obj, typename F1, typename F2>
bool Collection<Obj, F1, F2>::contains(const Obj& sb) const {
	for (int i = 0; i < size; i++) {
		if (array[i]==sb) {
			return true;
		}
	}
	
	return false;
}

template <typename Obj, typename F1, typename F2>
Obj Collection<Obj, F1, F2>::remove_any_item() {
	if (size == 0) {
		throw std::invalid_argument("The collection cannot be empty");
	}
	int x = std::rand() % (size);
	Obj ball = array[x];
	for (int i = x; i < size; i++) {
		array[i] = array[i + 1];
	}
	size -= 1;
	return ball;

}

template <typename Obj, typename F1, typename F2>
void Collection<Obj, F1, F2>::remove_this_item(const Obj& sb) {
	if (size == 0) {
		throw std::invalid_argument("The collection cannot be empty");
	}
	for (int i = 0; i < size; i++) {
		if (array[i]==sb) {
			for (int j = i; j < size - 1; j++) {
				array[j] = array[j + 1];
			}
			size -= 1;
			break;
		}
	}
}

template <typename Obj, typename F1, typename F2>
void Collection<Obj, F1, F2>::make_empty() {
	size = 0;
	capacity = 0;
}

template <typename Obj, typename F1, typename F2>
bool Collection<Obj, F1, F2>::is_empty() const {
	if (size == 0) {
		return true;
	}
	return false;
}

template <typename Obj, typename F1, typename F2>
int Collection<Obj, F1, F2>::total_items() const { return size; }


template <typename Obj, typename F1, typename F2>
int Collection<Obj, F1, F2>::total_items(F2 s) const {// sizes
	int num = 0;
	for (int i = 0; i < size; i++) {
		if (array[i].get_size() == s) {
			num++;
		}
	}
	return num;
}

template <typename Obj, typename F1, typename F2>
int Collection<Obj, F1, F2>::total_items(F1 c) const {// colors
	int num = 0;
	for (int i = 0; i < size; i++) {
		if (array[i].get_color() == c) {
			num++;
		}
	}
	return num;
}

template <typename Obj, typename F1, typename F2>
void Collection<Obj, F1, F2>::print_items() const {
	for (int i = 0; i < size; i++) {
		cout << array[i];
	}
}

template <typename Obj, typename F1, typename F2>
Obj& Collection<Obj, F1, F2>::operator[](int i) {
	return this->array[i];
}

template <typename Obj, typename F1, typename F2>
const Obj& Collection<Obj, F1, F2>::operator[](int i) const {
	return this->array[i];
}


/////
template <typename Obj, typename F1, typename F2>
ostream& operator<<(ostream& os, const Collection<Obj, F1, F2>& c) {
	for (int i = 0; i < c.total_items(); i++) {
		os << c[i];
	}
	return os;
}

template <typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2> make_union(const Collection<Obj, F1, F2>& c1, const Collection<Obj, F1, F2>& c2) {
	Collection <Obj, F1, F2> x;
	for (int i = 0; i < c1.total_items(); i++) {
		x.insert_item(c1[i]);
	}
	for (int i = 0; i < c2.total_items(); i++) {
		x.insert_item(c2[i]);
	}
	return x;
}

template <typename Obj, typename F1, typename F2>
void swap(Collection<Obj, F1, F2>& c1, Collection<Obj, F1, F2>& c2) {
	// how to use move assignment??
	Collection<Obj, F1, F2> temp = move(c1);
	c1 = move(c2);
	c2 = move(temp);
}
template <typename Obj, typename F1, typename F2>
void sort_by_size(Collection<Obj, F1, F2>& c, Sort_choice sort) {
	switch (sort) {
		case Sort_choice::bubble_sort:
			for (int i = 0; i < c.total_items() - 1; i++) {
				for (int j = 0; j < c.total_items() - i - 1; j++) {
					if (c[j].get_size() > c[j + 1].get_size()) {
						swap(c[j], c[j + 1]);
					}
				}
			}// end of big for loop
			break;
		case Sort_choice::insertion_sort:
			///
			F2 siz;
			int index;
			for (int i = 1; i < c.total_items(); i++){
				siz = c[i].get_size();// size of the current index ball
				Obj ball = c[i];// store the current index ball value
				index = i;

				while (index > 0 && siz <c[index-1].get_size() ){// keep moving forward untill the current ball size is not longer less than its predecessor
					c[index] = c[index-1];
					index = index - 1;
				}
				c[index] = ball;// change the current ball postion to the index position
			}
			///
			break;
		case Sort_choice::selection_sort:
			int indexx;
			for (int i = 0; i < c.total_items() - 1; i++) {
				indexx = i;
				for (int j = i + 1; j < c.total_items(); j++) {
					// output the size of the collection object

					if (c[j].get_size() < c[indexx].get_size()) {
						indexx = j;
					}
				}
				swap(c[indexx], c[i]);
			}// end of big for loop
			break;
		default:
			cout << "Something is wrong!!!" << endl;
			break;
	}

}


//your code...
//Templated class collection
//Methods from Collection.cpp
#endif