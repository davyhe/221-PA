#include <string>
#include <iostream>
#include "Stress_ball.h"

using std::cout;
using std::endl;
using std::string;


Stress_ball::Stress_ball() {
	int x = std::rand() % 4;
	if (x == 0) {
		color = Stress_ball_colors::red;
	}
	else if (x == 1) {
		color = Stress_ball_colors::blue;
	}
	else if (x == 2) {
		color = Stress_ball_colors::yellow;
	}
	else {
		color = Stress_ball_colors::green;
	}

	int y = std::rand() % 3;
	if (y == 0) {
		size = Stress_ball_sizes::small;
	}
	else if (y == 1) {
		size = Stress_ball_sizes::medium;
	}
	else {
		size = Stress_ball_sizes::large;
	}
}

Stress_ball::Stress_ball(Stress_ball_colors c, Stress_ball_sizes s) {
	this->color = c;
	this->size = s;
}

Stress_ball_colors Stress_ball::get_color() const { return color; }
Stress_ball_sizes Stress_ball::get_size() const { return size; }


bool Stress_ball::operator==(const Stress_ball& sb) {
	if (sb.get_color() == color && sb.get_size() == size) {
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& o, const Stress_ball& sb) {
	string co; // check which color it is
	if (sb.get_color() == Stress_ball_colors::red) {
		co = "red";
	}
	else if (sb.get_color() == Stress_ball_colors::blue) {
		co = "blue";
	}
	else if (sb.get_color() == Stress_ball_colors::green) {
		co = "green";
	}
	else {
		co = "yellow";
	}
	string siz;// check which size it is
	if (sb.get_size() == Stress_ball_sizes::small) {
		siz = "small";
	}
	else if (sb.get_size() == Stress_ball_sizes::medium) {
		siz = "medium";
	}
	else {
		siz = "large";
	}


	o << "(" << co << ", " << siz << ")" << endl;
	return o;
}