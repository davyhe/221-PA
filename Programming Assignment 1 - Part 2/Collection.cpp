#include "Collection.h"
#include "Stress_ball.h"
#include <iostream>

using std::cout;
using std::endl;
using std::move;

Collection::Collection() {
	size = 0;
	capacity = 0;
	array = nullptr;
}

Collection::Collection(int cap) {
	capacity = cap;
	size = 0;
	array = new Stress_ball[capacity];
}

Collection::Collection(const Collection& c): size(c.size), capacity(c.capacity), array(new Stress_ball[c.capacity]) {// copy constructor
	for (int i = 0; i < c.capacity;i++) {
		array[i] = c.array[i];
	}
}

Collection& Collection::operator=(const Collection& c) {// copy assignment
	if (this == &c) {
		return *this;
	}
	array = new Stress_ball[c.capacity];
	for (int i = 0; i < c.capacity; i++) {
		array[i] = c.array[i];
	}
	size = c.size;
	capacity = c.capacity;
	return *this;
}

Collection::~Collection() {
	delete[] array;
	size = 0;
	capacity = 0;
}

Collection::Collection(Collection&& c): size(c.size), capacity(c.capacity), array(c.array) {// move assignment
	c.size = 0;
	c.capacity = 0;
	c.array = nullptr;
}

Collection& Collection::operator=(Collection&& c) {// move constructor
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
void Collection::resize() {
	if(capacity==0){
		capacity=1;
	}
	else{
		capacity *= 2;
	}
	Stress_ball* newarray = new Stress_ball[capacity];
	for (int i = 0; i < size; i++) {
		newarray[i] = array[i];
	}
	delete[] array;
	array = newarray;
}


void Collection::insert_item(const Stress_ball& sb) {////???????????
	if (size == capacity) {
		resize();
	}
	array[size] = sb;
	size++;

}

bool Collection::contains(const Stress_ball& sb) const {
	for (int i = 0; i < size; i++) {
		if (array[i]==sb) {
			return true;
		}
	}
	
	return false;
}

Stress_ball Collection::remove_any_item() {
	if (size == 0) {
		throw std::invalid_argument("The collection cannot be empty");
	}
	int x = std::rand() % (size);
	Stress_ball ball = array[x];
	for (int i = x; i < size; i++) {
		array[i] = array[i + 1];
	}
	size -= 1;
	return ball;

}

void Collection::remove_this_item(const Stress_ball& sb) {///array[i].get_color() == sb.get_color() && array[i].get_size() == sb.get_size()
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

void Collection::make_empty() {///???
	size = 0;
	capacity = 0;
	// what is deallocate allocated memory
}

bool Collection::is_empty() const {
	if (size == 0) {
		return true;
	}
	return false;
}

int Collection::total_items() const { return size; }

int Collection::total_items(Stress_ball_sizes s) const {
	int num = 0;
	for (int i = 0; i < size; i++) {
		if (array[i].get_size() == s) {
			num++;
		}
	}
	return num;
}

int Collection::total_items(Stress_ball_colors c) const {
	int num = 0;
	for (int i = 0; i < size; i++) {
		if (array[i].get_color() == c) {
			num++;
		}
	}
	return num;
}

void Collection::print_items() const {
	for (int i = 0; i < size; i++) {
		cout << array[i];
	}
}

Stress_ball& Collection::operator[](int i) {
	return this->array[i];
}

const Stress_ball& Collection::operator[](int i) const {
	return this->array[i];
}

istream& operator>>(istream& is, Collection& c) {
	string color;
	string size;
	Stress_ball_colors en_colo;
	Stress_ball_sizes en_siz;
	while (is >> color >> size) {// won't input when it reach the end of file
		if (color == "red") {
			en_colo = Stress_ball_colors::red;
		}
		else if (color == "blue") {
			en_colo = Stress_ball_colors::blue;
		}
		else if (color == "green") {
			en_colo = Stress_ball_colors::green;
		}
		else {
			en_colo = Stress_ball_colors::yellow;
		}

		if (size == "small") {
			en_siz = Stress_ball_sizes::small;
		}
		else if (size == "medium") {
			en_siz = Stress_ball_sizes::medium;
		}
		else {
			en_siz = Stress_ball_sizes::large;
		}
		Stress_ball ball(en_colo, en_siz);
		c.insert_item(ball);
		//return is;
	}
}

ostream& operator<<(ostream& os, const Collection& c) {
	for (int i = 0; i < c.total_items(); i++) {
		os << c[i];
	}
	return os;
}

Collection make_union(const Collection& c1, const Collection& c2) {
	Collection x;
	for (int i = 0; i < c1.total_items(); i++) {
		x.insert_item(c1[i]);
	}
	for (int i = 0; i < c2.total_items(); i++) {
		x.insert_item(c2[i]);
	}
	return x;
}

void swap(Collection& c1, Collection& c2) {
	// how to use move assignment??
	Collection temp = move(c1);
	c1 = move(c2);
	c2 = move(temp);
}

void sort_by_size(Collection& c, Sort_choice sort) {
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
			Stress_ball_sizes siz;
			int index;
			for (int i = 1; i < c.total_items(); i++){
				siz = c[i].get_size();// size of the current index ball
				Stress_ball ball = c[i];// store the current index ball value
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