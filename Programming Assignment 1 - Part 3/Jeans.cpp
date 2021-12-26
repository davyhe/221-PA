/**
 * In this file, implement the methods from Jeans.h. The implementation is identical to Stress_ball
 * This file needs to be uploaded to Mimir
 */ 
#include "Jeans.h"

using std::cout;
using std::endl;
using std::string;

//using CollectionJN = Collection <Jeans , Jeans_colors , Jeans_sizes >;
Jeans::Jeans() {
	int x = std::rand() % 4;
	if (x == 0) {
		color = Jeans_colors::white;
	}
	else if (x == 1) {
		color = Jeans_colors::black;
	}
	else if (x == 2) {
		color = Jeans_colors::blue;
	}
	else {
		color = Jeans_colors::grey;
	}

	int y = std::rand() % 4;
	if (y == 0) {
		size = Jeans_sizes::small;
	}
	else if (y == 1) {
		size = Jeans_sizes::medium;
	}
    else if (x == 2){
        size = Jeans_sizes::large;
    }
	else {
		size = Jeans_sizes::xlarge;
	}
}

Jeans::Jeans(Jeans_colors c, Jeans_sizes s) {
	this->color = c;
	this->size = s;
}

Jeans_colors Jeans::get_color() const { return color; }
Jeans_sizes Jeans::get_size() const { return size; }


bool Jeans::operator==(const Jeans& sb) {
	if (sb.get_color() == color && sb.get_size() == size) {
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& o, const Jeans& sb) {
	string co; // check which color it is
	if (sb.get_color() == Jeans_colors::white) {
		co = "white";
	}
	else if (sb.get_color() == Jeans_colors::black) {
		co = "black";
	}
	else if (sb.get_color() == Jeans_colors::blue) {
		co = "blue";
	}
	else {
		co = "grey";
	}
	string siz;// check which size it is
	if (sb.get_size() == Jeans_sizes::small) {
		siz = "small";
	}
	else if (sb.get_size() == Jeans_sizes::medium) {
		siz = "medium";
	}
    else if (sb.get_size() == Jeans_sizes::large) {
		siz = "large";
	}
	else {
		siz = "xlarge";
	}


	o << "(" << co << ", " << siz << ")" << endl;
	return o;
}