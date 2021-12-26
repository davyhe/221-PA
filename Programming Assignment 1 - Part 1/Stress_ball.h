#ifndef Stress_ball_H
#define Stress_ball_H

#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

enum class Stress_ball_colors { red, blue, yellow, green };
enum class Stress_ball_sizes { small, medium, large };
class Stress_ball {

private:
	Stress_ball_colors c;
	Stress_ball_sizes s;

public:
	Stress_ball();
	Stress_ball(Stress_ball_colors c, Stress_ball_sizes s);
	Stress_ball_colors get_color() const { return c; }
	Stress_ball_sizes get_size() const { return s; }
	bool operator==(const Stress_ball& sb);
};


std::ostream& operator<<(std::ostream& o, const Stress_ball& sb);




















#endif