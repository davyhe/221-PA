#include <string>
#include <iostream>
#include "Stress_ball.h"

using std::cout;
using std::endl;
using std::string;


Stress_ball::Stress_ball() {
	int x = std::rand() % 4;
	if (x == 0) {
		c = Stress_ball_colors::red;
	}
	else if (x == 1) {
		c = Stress_ball_colors::blue;
	}
	else if (x == 2) {
		c = Stress_ball_colors::yellow;
	}
	else {
		c = Stress_ball_colors::green;
	}

	int y = std::rand() % 3;
	if (y == 0) {
		s = Stress_ball_sizes::small;
	}
	else if (y == 1) {
		s = Stress_ball_sizes::medium;
	}
	else {
		s = Stress_ball_sizes::large;
	}
}

Stress_ball::Stress_ball(Stress_ball_colors c, Stress_ball_sizes s) {
	this->c = c;
	this->s = s;
}

bool Stress_ball::operator==(const Stress_ball& sb) {
	if (sb.get_color() == c && sb.get_size() == s) {
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




