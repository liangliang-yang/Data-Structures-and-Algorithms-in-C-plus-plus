
// Stack.h
// HW_1
// Created by Liangliang Yang on 06/11/2016

#ifndef STACK_H
#define STACK_H

#include<iostream>
using namespace std;

//template <class T> 
class Stack
{
public: 
    Stack();
    ~Stack();
    void Push(int item);
    //void push(const T& object);
    int Pop();
    bool IsEmpty() const;
    void Reverse();
    void Display(ostream& writer) const;

private:
    typedef struct node {
        int data;
        node *next;
    } NODE;

    NODE *top;

};

Stack::Stack() // define constructor
{
    top = NULL;
}

Stack::~Stack() //define destructor
{
    while (!IsEmpty())
    {
        Pop();
    }
    IsEmpty();
}

void Stack::Push(int item)
{
    NODE *p = new NODE;
    p->next = top;
    p->data = item;
    top = p;
}

int Stack::Pop()
{
    if(!IsEmpty())
    {
        NODE *tmp = top;
        int value = top->data;
        top = top->next;
        delete tmp;
        return value;
    }
}

bool Stack::IsEmpty() const
{
    return top==NULL;
}

void Stack::Reverse()
{
    node* prev   = NULL;
    node* current = top;
    node* next;
    while (current != NULL)
      {
        next  = current->next; 
        current->next = prev;  
        prev = current;
        current = next;
      }
        top = prev;
}

void Stack::Display (std::ostream&writer) const
    {
        node *p=new node;
        p=top;
        while(p !=NULL)
        {
        writer<< p->data<<" ";
            p=p->next;
        }
        writer<<"\n";
    }


#endif
