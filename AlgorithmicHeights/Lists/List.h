#ifndef LIST_H
#define LIST_H

template<typename T>
class LinkedList{

    struct Node{};

    LinkedList(){}
    LinkedList(LinkedList& list){}
    LinkedList operator=(LinkedList& RHS){}
    LinkedList operator+(LinkedList& RHS){}
    virtual ~LinkedList(){}

    void push_front(T val){}
    void push_back(T val){}

    void pop_front(){}
    void pop_back(){}

    // to be continued...

};

#endif // LIST_H
