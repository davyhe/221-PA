#include <string>
#include <iostream>
#include "Stress_ball.h"

using std::cout;
using std::endl;
using std::string;

int main() {
	cout << Stress_ball();
	Stress_ball_colors c= Stress_ball_colors::red;
	Stress_ball_sizes s= Stress_ball_sizes::small;
	cout<<Stress_ball(c, s);

	cout << Stress_ball();

}