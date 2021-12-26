// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class DLList; // class declaration

// doubly linked list node
template <typename T>
struct DLListNode
{
    T obj;
    DLListNode<T> *prev, *next;
    // constructor
    DLListNode(T e = T(), DLListNode *p = nullptr, DLListNode *n = nullptr) : obj(e), prev(p), next(n) {}
};

// doubly linked list class
template <typename T>
class DLList
{
private:
    DLListNode<T> header, trailer;

public:
    DLList();                                   // default constructor
    DLList(const DLList<T> &dll);               // copy constructor
    DLList(DLList<T> &&dll);                    // move constructor
    ~DLList();                                  // destructor
    DLList<T> &operator=(const DLList<T> &dll); // copy assignment operator
    DLList<T> &operator=(DLList<T> &&dll);      // move assignment operator
    // return the pointer to the first node
    DLListNode<T> *first_node() const { return header.next; }
    // return the pointer to the trailer
    const DLListNode<T> *after_last_node() const { return &trailer; }
    // return if the list is empty
    bool is_empty() const { return header.next == &trailer; }
    T first() const;          // return the first object
    T last() const;           // return the last object
    void insert_first(T obj); // insert to the first node
    T remove_first();         // remove the first node
    void insert_last(T obj);  // insert to the last node
    T remove_last();          // remove the last node
    void insert_after(DLListNode<T> &p, T obj);
    void insert_before(DLListNode<T> &p, T obj);
    T remove_after(DLListNode<T> &p);
    T remove_before(DLListNode<T> &p);
};
template <typename T>
DLList<T>::DLList() : header(T()), trailer(T())
{
    //exit(1);
    header.next = &trailer;
    trailer.prev = &header;
}

template <typename T>
DLList<T>::DLList(const DLList<T> &dll)
{ // copy constructor

    header = DLListNode<T>();
    trailer = DLListNode<T>();
    header.next = &trailer;
    trailer.prev = &header;

    DLListNode<T> *curr = dll.first_node();
    DLListNode<T> *ccurr = &header;


    while (curr != &dll.trailer){
        DLListNode<T> *newnode = new DLListNode<T> (curr->obj,ccurr, ccurr->next);
        ccurr->next->prev = newnode;
        ccurr->next = newnode;
        ccurr = newnode;

        curr = curr->next;
    }


    /*
    header = DLListNode<T>();
    trailer = DLListNode<T>();
    header.next = &trailer;
    trailer.prev = &header;

    DLListNode<T> *tempother = dll.header.next;
    header = dll.header;

    while (tempother != &(dll.trailer))
    {
        this->insert_before((this->trailer), tempother->obj);
        tempother = tempother->next;
    }*/
}

template <typename T>
DLList<T>::DLList(DLList<T> &&dll)
{ //move constructor
    /*
    header.next = dll.header.next; 
    trailer.prev = dll.trailer.prev;*/
    if (dll.is_empty() == false)
    {
        header = dll.header;
        trailer = dll.trailer;
        dll.header.next->prev = &header;
        dll.trailer.prev->next = &trailer;
    }
    else
    {
        header.next = &trailer;
        trailer.prev = &header;
    }
    dll.header.next = &(dll.trailer);
    dll.trailer.prev = &(dll.header);
}

template <typename T>
DLList<T>::~DLList()
{ // destructor
    DLListNode<T> *prev_node, *node = header.next;
    while (node != &trailer)
    {
        prev_node = node;
        node = node->next;
        delete prev_node;
    }
    header.next = &trailer;
    trailer.prev = &header;
}

template <typename T>
DLList<T> &DLList<T>::operator=(const DLList<T> &dll)
{ // copy assignment operator
    if (&(dll) == (this))
    {
        return *this;
    }

    DLListNode<T> *prev_node, *node = header.next;
    while (node != &trailer)
    {
        prev_node = node;
        node = node->next;
        delete prev_node;
    }
    header = 0;
    trailer = 0;
    header.next = &trailer;
    trailer.prev = &header;

    DLListNode<T> *tempother = dll.header.next;
    header = dll.header;

    while (tempother != &(dll.trailer))
    {
        this->insert_before((this->trailer), tempother->obj);
        tempother = tempother->next;
    }

    return *this;
}

template <typename T>
DLList<T> &DLList<T>::operator=(DLList<T> &&dll)
{ // move assignment operator
    if (&(dll) == (this))
    {
        return *this;
    }
    this->~DLList(); // destory the orginal
    if (dll.is_empty() == false)
    {
        header = dll.header;
        trailer = dll.trailer;
        dll.header.next->prev = &header;
        dll.trailer.prev->next = &trailer;
    }
    else
    {
        header.next = &trailer;
        trailer.prev = &header;
    }
    dll.header.next = &(dll.trailer);
    dll.trailer.prev = &(dll.header);
    return *this;
}
/*
template <typename T>
DLListNode<T> *DLList<T>::first_node() const { return header.next; } 

template <typename T>
const DLListNode<T> *DLList<T>::after_last_node() const { return &trailer; }

template <typename T>
bool DLList<T>::is_empty() const { return header.next == &trailer; }
*/
template <typename T>
T DLList<T>::first() const
{
    if (is_empty())
    {
        throw std::invalid_argument("Empty Doubly Linked List");
    }
    return header.next->obj;
}

template <typename T>
T DLList<T>::last() const
{
    if (is_empty())
    {
        throw std::invalid_argument("Empty Doubly Linked List");
    }
    return trailer.prev->obj;
}

template <typename T>
void DLList<T>::insert_first(T obj)
{
    DLListNode<T> *newNode = new DLListNode<T>(obj, &header, header.next);
    header.next->prev = newNode;
    header.next = newNode;
}

template <typename T>
T DLList<T>::remove_first()
{
    if (is_empty())
    {
        throw std::invalid_argument("Empty Doubly Linked List");
    }
    DLListNode<T> *node = header.next;
    node->next->prev = &header;
    header.next = node->next;
    T object = node->obj;
    delete node;
    return object;
}

template <typename T>
void DLList<T>::insert_last(T obj)
{
    DLListNode<T> *newNode = new DLListNode<T>(obj, trailer.prev, &trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
}

template <typename T>
T DLList<T>::remove_last()
{
    if (is_empty())
    {
        throw std::invalid_argument("Empty Doubly Linked List");
    }
    DLListNode<T> *node = trailer.prev;
    node->prev->next = &trailer;
    trailer.prev = node->prev;
    T object = node->obj;
    delete node;
    return object;
}

template <typename T>
void DLList<T>::insert_after(DLListNode<T> &p, T obj)
{
    DLListNode<T> *newNode = new DLListNode<T>(obj, &p, p.next);

    p.next->prev = newNode;
    p.next = newNode;
}

template <typename T>
void DLList<T>::insert_before(DLListNode<T> &p, T obj)
{
    DLListNode<T> *newNode = new DLListNode<T>(obj, p.prev, &p);

    p.prev->next = newNode;
    p.prev = newNode;
}

template <typename T>
T DLList<T>::remove_after(DLListNode<T> &p)
{
    if (is_empty() || p.next == &trailer)
    { // check if the list is empty or the p.next is a null pointer
        throw std::invalid_argument("Empty Doubly Linked List");
    }
    DLListNode<T> *newNode = p.next;
    p.next = p.next->next;
    p.next->prev = &p;

    T object = newNode->obj;
    delete newNode;
    return object;
}

template <typename T>
T DLList<T>::remove_before(DLListNode<T> &p)
{
    if (is_empty() || p.prev == &header)
    { // check if the list is empty or the p.next is a null pointer
        throw std::invalid_argument("Empty Doubly Linked List");
    }
    DLListNode<T> *newNode = p.prev;
    p.prev = p.prev->prev;
    p.prev->next = &p;

    T object = newNode->obj;
    delete newNode;
    return object;
}

// output operator
template <typename T>
ostream &operator<<(ostream &out, const DLList<T> &dll)
{
    DLListNode<T> *newNode = dll.first_node();
    while (newNode != dll.after_last_node())
    {
        out << newNode->obj << ", ";
        newNode = newNode->next;
    }
    return out;
}

#endif
