// implementation of the DLList class
#include "DLList.h"
#include <iostream>

using std::cout;
using std::endl;
using std::move;
using std::string;

DLList::DLList(): header(0), trailer(0) {
    header.next = &trailer; 
    trailer.prev = &header;
}
DLList::DLList(const DLList& dll){// copy constructor
    
    header=0;
    trailer=0;
    header.next = &trailer; 
    trailer.prev = &header;

    DLListNode *tempother =dll.header.next;
    header=dll.header;
    

    while(tempother!=&(dll.trailer)){
        this->insert_before((this->trailer),tempother->obj);
        tempother=tempother->next;
    }
    

}

DLList::DLList(DLList&& dll){//move constructor
    /*
    header.next = dll.header.next; 
    trailer.prev = dll.trailer.prev;*/
    if (dll.is_empty()==false){
        header=dll.header;
        trailer=dll.trailer;
        dll.header.next->prev=&header;
        dll.trailer.prev->next=&trailer;
    }
    else{
        header.next=&trailer;
        trailer.prev=&header;
    }
    dll.header.next=&(dll.trailer);
    dll.trailer.prev=&(dll.header);
}

 DLList::~DLList(){// destructor
    DLListNode*prev_node,*node = header.next;
    while (node != &trailer) {
        prev_node = node;
        node = node->next;
        delete prev_node;
    }
    header.next = &trailer;
    trailer.prev = &header;
 } 

DLList&  DLList::operator=(const DLList& dll){// copy assignment operator
    
    if(&(dll)==(this)){
        return *this;
    }
    this->~DLList();
    header=0;
    trailer=0;
    header.next = &trailer; 
    trailer.prev = &header;

    DLListNode *tempother =dll.header.next;
    header=dll.header;

    while(tempother!=&(dll.trailer)){
        this->insert_before((this->trailer),tempother->obj);
        tempother=tempother->next;
    }

    return *this;
 }

 DLList& DLList::operator=(DLList&& dll){// move assignment operator
    if(&(dll)==(this)){
        return *this;
    }
    this->~DLList();// destory the orginal 
    if (dll.is_empty()==false){
        header=dll.header;
        trailer=dll.trailer;
        dll.header.next->prev=&header;
        dll.trailer.prev->next=&trailer;
    }
    else{
        header.next=&trailer;
        trailer.prev=&header;
    }
    dll.header.next=&(dll.trailer);
    dll.trailer.prev=&(dll.header);
    return *this;
 }



 DLListNode *DLList::first_node() const{
    return header.next;
 }

 const DLListNode *DLList::after_last_node() const{
    return &trailer;
 }

 bool DLList::is_empty() const{
     return header.next == &trailer; 
 }

 int DLList::first() const{
    if (is_empty()){
        throw std::invalid_argument("Empty Doubly Linked List");
    }
    return header.next->obj;
 }

 int DLList::last() const{
    if (is_empty()){
        throw std::invalid_argument("Empty Doubly Linked List");
    }
    return trailer.prev->obj;
 }

void DLList::insert_first(int obj){
    DLListNode*newNode = new DLListNode(obj, &header, header.next);
    header.next->prev = newNode;
    header.next = newNode;
}

int DLList::remove_first(){
    if (is_empty()){
        throw std::invalid_argument("Empty Doubly Linked List");
    }
    DLListNode*node = header.next;
    node->next->prev = &header;
    header.next = node->next;
    int object = node->obj;
    delete node;
    return object;
}

void DLList::insert_last(int obj){
    DLListNode*newNode = new DLListNode(obj, trailer.prev, &trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
}

int DLList::remove_last(){
    if (is_empty()){
        throw std::invalid_argument("Empty Doubly Linked List");
    }
    DLListNode*node = trailer.prev;
    node->prev->next = &trailer;
    trailer.prev = node->prev;
    int object = node->obj;
    delete node;
    return object;
}

void DLList::insert_after(DLListNode &p, int obj){
    DLListNode*newNode = new DLListNode(obj, &p, p.next);

    p.next->prev=newNode;
    p.next = newNode;
}

void DLList::insert_before(DLListNode &p, int obj){
    DLListNode*newNode = new DLListNode(obj, p.prev, &p);

    p.prev->next = newNode;
    p.prev = newNode;
}

int DLList::remove_after(DLListNode &p){
    if (is_empty() || p.next==&trailer ){// check if the list is empty or the p.next is a null pointer
        throw std::invalid_argument("Empty Doubly Linked List");
    }
    DLListNode*newNode = p.next;
    p.next=p.next->next;
    p.next->prev=&p;

    int object =newNode->obj;
    delete newNode;
    return object;
}

int DLList::remove_before(DLListNode &p){
    if (is_empty() || p.prev==&header){// check if the list is empty or the p.next is a null pointer
        throw std::invalid_argument("Empty Doubly Linked List");
    }
    DLListNode*newNode = p.prev;
    p.prev=p.prev->prev;
    p.prev->next=&p;

    int object =newNode->obj;
    delete newNode;
    return object;
}

ostream& operator<<(ostream& out, const DLList& dll){
    DLListNode*newNode=dll.first_node();
    while (newNode!=dll.after_last_node()){
        out<<newNode->obj<<", ";
        newNode=newNode->next;
    }
    return out;
}


