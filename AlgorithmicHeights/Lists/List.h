#ifndef LIST_H
#define LIST_H
#include <memory>
#include <iostream>
using namespace std;

template<typename T>
class LinkedList{

    struct Node{
        shared_ptr<Node> next;
        T value;
        Node(T _value, shared_ptr<Node> _next = 0){
            this->value = _value;
            this->next = _next;
        }
        ~Node(){
            cout << "removing " << value << endl;
        }
    };

    shared_ptr<Node> head;

public:
    LinkedList(){}

    void printMe(){
        shared_ptr<Node> p;
        for(p = head; p != 0; p = p->next){
            cout << p->value << " ";
        }
        cout << endl;
    }

    void push_back(T val){
        shared_ptr<Node> new_element(new Node(val, 0));

        if(head == 0){
            head = new_element;
            return;
        }

        auto current = head;
        while(current->next != 0){
            current = current->next;
        }
        current->next = new_element;
    }

    void push_front(T val){
        shared_ptr<Node> new_element(new Node(val, head));
        head = new_element;
    }

    void pop_front(){
        head = head->next;
    }

    void pop_back(){
        if(head == 0)return;
        if(head->next == 0)pop_front();

        auto current = head;
        while(current->next->next != 0){
            current = current->next;
        }
        current->next = 0;
    }

};


template<typename T>
class DoubleLinkedList{
    struct Node{
      shared_ptr<Node> next;
      shared_ptr<Node> prev;
      T value;
      Node(T _val, auto _prev, auto _next){
          this->value = _val;
          this->prev = _prev;
          this->next = _next;
      }


    };
};
#endif // LIST_H
