#ifndef Record_H
#define Record_H

#include <iostream>
#include <string>

using std::string;
using std::endl;
using std::cout;
using std::cin;

class Record {
private:
    //member variables
    string title, author, ISBN, year, edition;
public:
    //accessor/mutator functions
    string get_title() const;
    string get_author() const;
    string get_ISBN() const;
    string get_year() const;
    string get_edition() const;

    void set_title(string tit);
    void set_author(string auth);
    void set_ISBN(string IS);
    void set_year(string yea);
    void set_edition(string edit);
};

// Stream operators
std::istream& operator>>(std::istream& is, Record& rec);
std::ostream& operator<<(std::ostream& os, Record& rec);

// Comparison operators
bool operator==(const Record& r1, const Record& r2);
#endif