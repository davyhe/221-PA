#include "Library.h"
#include "TemplatedDLList.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::string;

std::vector<Record> Library::search(std::string title)
{
    std::vector<Record> match;
    char letter = title[0];
    letter = letter - 65;
    DLListNode<Record> *node = book_db[letter].first_node();
    while (node != book_db[letter].after_last_node())
    {
        if (node->obj.get_title() == title)
        {
            match.push_back(node->obj);
        }
        node = node->next;
    }
    return match;
}

int Library::import_database(std::string filename)
{
    int num_record = 0;
    Record book;
    ifstream ifs(filename);
    if (!ifs.is_open())
    {
        cout << filename << ".txt not found";
        return 1;
    }
    while (ifs >> book)
    {
        //cout<<"rec value: "<<rec<<endl;
        add_record(book);
        //vec.push_back(book);
        num_record++;
    }
    return num_record;
}

int Library::export_database(std::string filename)
{
    int num_record = 0;
    std::ofstream outfs;
    outfs.open(filename);
    while (!outfs.is_open())
    {
        cout << "couldn't open" << filename << ".txt" << endl;
        return 1;
    }
    for (int i = 0; i < book_db.size(); i++)
    {
        DLListNode<Record> *node = book_db[i].first_node();
        while (node != book_db[i].after_last_node())
        {
            outfs << node->obj.get_title() << endl;
            outfs << node->obj.get_author() << endl;
            outfs << node->obj.get_ISBN() << endl;
            outfs << node->obj.get_year() << endl;
            outfs << node->obj.get_edition() << endl;
            outfs << endl;
            num_record++;
            node = node->next;
        }
    }
    return num_record;
}

void Library::print_database()
{
    for (int i = 0; i < book_db.size(); i++)
    {
        DLListNode<Record> *node = book_db[i].first_node();
        while (node != book_db[i].after_last_node())
        {
            cout << node->obj << endl;
            node = node->next;
        }
    }
}

bool operator<(const Record &r1, const Record &r2)
{
    if (r1.get_title() < r2.get_title())
    {
        return true;
    }
    else if (r1.get_title() > r2.get_title())
    {
        return false;
    }

    if (r1.get_author() < r2.get_author())
    {
        return true;
    }
    else if (r1.get_author() > r2.get_author())
    {
        return false;
    }

    if (r1.get_ISBN() < r2.get_ISBN())
    {
        return true;
    }
    else if (r1.get_ISBN() > r2.get_ISBN())
    {
        return false;
    }
    return false;
}

bool Library::add_record(Record book)
{

    char letter = (book.get_title()[0]) - 65;
    DLListNode<Record> *node = book_db[letter].first_node();

    while (node != book_db[letter].after_last_node() && book < node->obj)
    {
        if (book == node->obj)
        {
            return false;
        }
        node = node->next;
    }
    book_db[letter].insert_before(*node, book);
    return true;
}

void Library::remove_record(Record book)
{
    char letter = (book.get_title()[0]) - 65;
    DLListNode<Record> *node = book_db[letter].first_node();
    while (node != book_db[letter].after_last_node())
    {
        if (node->obj == book)
        {
            node = node->next;
            book_db[letter].remove_before(*node);
            break;
        }
        node = node->next;
    }
}

char Library::prompt_yes_no()
{
    cout << "Please Enter Y/N: " << flush;
    char enter;
    cin >> enter;
    while (enter != 'Y' && enter != 'N')
    {
        cout << "Please Enter Y/N: " << flush;
        cin >> enter;
        
    }
    return enter;
}

int Library::prompt_menu(std::vector<std::string> vec )
{   
    for (int i = 0; i < vec.size(); i++){
        cout<<i+1<<". "<<vec[i]<<endl;
    }
    cout << "Please select an option" << endl;
    int input;
    cin>>input;
    input-=1;
    
    return input;
}

Record Library::prompt_record()
{
    Record book;

    cout << "Please enter a title: ";
    string title;
    cin >> title;
    book.set_title(title);

    cout << "Please enter Author: ";
    string author_first;
    cin >> author_first;
    string author_last;
    cin>>author_last;
    book.set_author(author_first+" "+author_last);

    cout << "Please enter ISBN: ";
    string isbn;
    cin >> isbn;
    book.set_ISBN(isbn);

    cout << "Please enter year: ";
    string year;
    cin >> year;
    book.set_year(year);

    cout << "Please enter edition: ";
    string edition;
    cin >> edition;
    book.set_edition(edition);

    return book;
}

std::string Library::prompt_title()
{
    string title;
    cout << "Please enter a title: ";
    cin >> title;
    return title;
}

std::string Library::prompt_string(std::string prompt)
{
    cout << prompt;
    string input;
    cin >> input;
    return input;
}