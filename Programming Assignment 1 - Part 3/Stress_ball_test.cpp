/**
 *  Fill the (...) below in such a way that Collection objects are created.
 *  Use aliases CollectionSB for Collection of Stress_balls.
 *  Reuse Operator>> (from PA1-p2) for Collection of Stress_balls.
 *  This file needs to be uploaded to Mimir.
 * 
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include "Stress_ball.h"
#include "Collection.h"
using CollectionSB = Collection <Stress_ball , Stress_ball_colors , Stress_ball_sizes >;
istream& operator>>(istream& is, CollectionSB& c){
  //Implement this method
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
  return is;
}// end of operator >>

void test_stress_balls(){
        Stress_ball stress_ball_1 = Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::large);
        Stress_ball stress_ball_2 = Stress_ball(Stress_ball_colors::yellow, Stress_ball_sizes::large);
        Stress_ball stress_ball_3 = Stress_ball(Stress_ball_colors::green, Stress_ball_sizes::small);
        Stress_ball stress_ball_4 = Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::medium);
        Collection<Stress_ball, Stress_ball_colors, Stress_ball_sizes> collection_1;
        Collection<Stress_ball, Stress_ball_colors, Stress_ball_sizes> collection_2(3);
        Collection<Stress_ball, Stress_ball_colors, Stress_ball_sizes> collection_3(5);
        Collection<Stress_ball, Stress_ball_colors, Stress_ball_sizes> collection_file(1);
        collection_2.insert_item(stress_ball_2);
        collection_2.insert_item(stress_ball_4);
        collection_1.insert_item(stress_ball_1);
        collection_2.insert_item(stress_ball_2);
        collection_2.insert_item(Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::small));
        collection_2.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_3);
        Collection<Stress_ball, Stress_ball_colors, Stress_ball_sizes> collection_4 = collection_1;
        Collection<Stress_ball, Stress_ball_colors, Stress_ball_sizes> collection_5(move(collection_4));
        collection_1.insert_item(Stress_ball(Stress_ball_colors::green, Stress_ball_sizes::small));
        collection_2.insert_item(Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::medium));
        collection_2.insert_item(Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::large));
        collection_2.insert_item(Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::large));
        collection_2.remove_this_item(stress_ball_2);        
        collection_2.print_items();
        ifstream ifs("stress_ball1.data");
        ifs >> collection_file;
        collection_file.insert_item(stress_ball_3);
        collection_file.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_2);
        collection_2.insert_item(stress_ball_1);
        
        collection_file.print_items();
        collection_3 = make_union(collection_file,collection_2);
        cout<<collection_3;
}

