//
// Created by szymon on 21.01.2018.
//

#ifndef LIST_MLIST_H
#define LIST_MLIST_H

template <typename T>
struct Node {
    Node<T> *next;
    T val;
};

template <typename T>
struct Result {
    bool sign;
    Node<T> *digit;
};

template <typename T>
Node<T>* newList();

template <typename T>
void addFront(T val, Node<T> *guard);

template <typename T>
void add(T val, Node<T> *guard);

template <typename T>
void add(T val, Node<T> *guard, int position);

void displayList(Node<int> *guard);

void displayList(Result<int> *result);

template <typename T>
void remove(Node<T> *guard);

template <typename T>
void remove(Node<T> *guard, int position);

template <typename T>
void removeFront(Node<T> *guard);

template <typename T>
void clearList(Node<T> *guard);

#endif //LIST_MLIST_H
