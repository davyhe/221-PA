//implementation of record class

#include "Record.h"
#include <iostream>
#include <string>

using std::endl;
using std::cout;
using std::string;

string Record::get_title() const{return title;}

string Record::get_author() const{return author;}

string Record::get_ISBN() const{return ISBN;}

string Record::get_year() const{return year;}

string Record::get_edition() const{return edition;}

void Record::set_title(string tit){title=tit;}
void Record::set_author(string auth){author=auth;}
void Record::set_ISBN(string IS){ISBN=IS;}
void Record::set_year(string yea){year=yea;}
void Record::set_edition(string edit){edition=edit;}

std::istream& operator>>(std::istream& is, Record& rec){
    string title, author, ISBN, year, edition, emptyline;
    getline(is, emptyline);
    getline(is, title);
    getline(is, author);
    getline(is, ISBN);
    getline(is, year);
    getline(is, edition);

    //line>>emptyline>>title>>author>>ISBN>>year>>edition;
    rec.set_title(title);
    rec.set_author(author);
    rec.set_ISBN(ISBN);
    rec.set_year(year);
    rec.set_edition(edition);
    //cout<<"I got here (operator >>)"<<endl;
    return is;
}

std::ostream& operator<<(std::ostream& os, Record& rec){
    os<<rec.get_title()<<endl;
    os<<rec.get_author()<<endl;
    os<<rec.get_ISBN()<<endl;
    os<<rec.get_year()<<endl;
    os<<rec.get_edition()<<endl;
    os<<endl;
    return os;
}

bool operator==(const Record& r1, const Record& r2){
    /*
    string title1, title2, author1, author2, ISBN1, ISBN2;
    title1=r1.get_title();
    title2=r2.get_title();
    author1=r1.get_author();
    author2=r2.get_author();
    ISBN1=r1.get_ISBN();
    ISBN2=r2.get_ISBN();*/
    if(r1.get_title()==r2.get_title() && r1.get_author()==r2.get_author() && r1.get_ISBN()==r2.get_ISBN() ){
        return true;
    }
    return false;
}

