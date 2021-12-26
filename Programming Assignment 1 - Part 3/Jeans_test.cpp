/**
 *  Fill the (...) below in such a way that Collection objects are created.
 *  Use aliases CollectionJN for Collection of Jeans.
 *  Implement Operator>> (identical to the one you did for Stress_ball in PA1-p2) for Collection of Jeans.
 *  This file needs to be uploaded to Mimir.
 * 
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include "Jeans.h"
#include "Collection.h"
using CollectionJN = Collection <Jeans , Jeans_colors , Jeans_sizes >;
istream& operator>>(istream& is, CollectionJN& c){
  //Implement this method  
  string color;
	string size;
	Jeans_colors en_colo;
	Jeans_sizes en_siz;
	while (is >> color >> size) {// won't input when it reach the end of file
		if (color == "white") {
			en_colo = Jeans_colors::white;
		}
		else if (color == "black") {
			en_colo = Jeans_colors::black;
		}
		else if (color == "blue") {
			en_colo = Jeans_colors::blue;
		}
		else {
			en_colo = Jeans_colors::grey;
		}

		if (size == "small") {
			en_siz = Jeans_sizes::small;
		}
		else if (size == "medium") {
			en_siz = Jeans_sizes::medium;
		}
    else if (size == "large") {
			en_siz = Jeans_sizes::large;
		}
		else {
			en_siz = Jeans_sizes::xlarge;
		}
		Jeans ball(en_colo, en_siz);
		c.insert_item(ball);
		//return is;
	}  
  return is;
}
void test_jeans(){
        Jeans jeans_1 = Jeans(Jeans_colors::grey, Jeans_sizes::small);
        Jeans jeans_2 = Jeans(Jeans_colors::grey, Jeans_sizes::large);
        Jeans jeans_3 = Jeans(Jeans_colors::blue, Jeans_sizes::large);
        Jeans jeans_4 = Jeans(Jeans_colors::black, Jeans_sizes::medium);
        Collection <Jeans , Jeans_colors , Jeans_sizes > collection_0;
        Collection <Jeans , Jeans_colors , Jeans_sizes > collection_1;
        Collection <Jeans , Jeans_colors , Jeans_sizes > collection_2(3);
        Collection <Jeans , Jeans_colors , Jeans_sizes > collection_3(5);
        Collection <Jeans , Jeans_colors , Jeans_sizes > collection_file(1);
        collection_0.insert_item(jeans_1);
        collection_0.make_empty();
        collection_1.insert_item(jeans_1);
        collection_2.insert_item(jeans_2);
        
        collection_2.print_items();
        collection_2.insert_item(Jeans(Jeans_colors::blue, Jeans_sizes::small));
        collection_2.insert_item(jeans_3);
        collection_2.insert_item(jeans_3);
        Collection <Jeans , Jeans_colors , Jeans_sizes > collection_copy(collection_1);
        collection_1.insert_item(Jeans(Jeans_colors::black, Jeans_sizes::small));
        Collection <Jeans , Jeans_colors , Jeans_sizes > collection_7 = move(collection_1);
        collection_2.insert_item(Jeans(Jeans_colors::blue, Jeans_sizes::medium));
        collection_2.insert_item(Jeans(Jeans_colors::grey, Jeans_sizes::large));
        collection_2.insert_item(Jeans(Jeans_colors::grey, Jeans_sizes::large));
        collection_2.remove_this_item(jeans_2);
        
        collection_2.print_items();
        collection_copy.make_empty();
        if(collection_2.is_empty()){
            collection_2.insert_item(Jeans(Jeans_colors::black, Jeans_sizes::small));
        }
        ifstream ifs("jeans1.data");
        ifs >> collection_file;
        collection_file.insert_item(jeans_3);
        collection_file.insert_item(jeans_3);
        collection_2.insert_item(jeans_3);
        collection_2.insert_item(jeans_3);
        collection_2.insert_item(jeans_2);
        collection_2.insert_item(jeans_1);
        collection_file.print_items();

        swap(collection_file,collection_2);

        collection_3 = make_union(collection_file,collection_2);                
        cout<<collection_3;
}
