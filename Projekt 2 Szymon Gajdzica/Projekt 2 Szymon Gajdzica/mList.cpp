//
// Created by szymon on 21.01.2018.
//
#include "stdafx.h"
#include "mList.h"
#include <iostream>
#include <string>

template <typename T>
Node<T>* newList() {
    auto *guard = new Node<T>;
    guard->next = nullptr;
    return guard;
}
template Node<int>* newList<int>();

template <typename T>
void addFront(T val, Node<T> *guard) {
    auto *newNode = new Node<T>;
    newNode->val = val;
    newNode->next = guard->next;
    guard->next = newNode;
}
template void addFront<int>(int val, Node<int> *guard);

template <typename T>
void add(T val, Node<T> *guard) {
    Node<T> *tmp = guard;

    while (tmp->next != nullptr)
        tmp = tmp->next;

    auto * new_node = new Node<T>;
    new_node->val = val;

    tmp->next = new_node;
    new_node->next = nullptr;
}
template void add<int>(int val, Node<int> *guard);

template <typename T>
void add(T val, Node<T> *guard, int position) {
    Node<T> *tmp = guard;
    auto * new_node = new Node<T>;
    new_node->val = val;
    int i = 0;
    while (tmp->next != nullptr && i < position) {
        tmp = tmp->next;
        i++;
    }
    new_node->next = tmp->next;
    tmp->next = new_node;
}
template void add<int>(int val, Node<int> *guard, int position);

void displayList(Node<int> *guard) {
    Node<int> *tmp = guard;
    std::string text;
    while (tmp->next != nullptr) {
        tmp = tmp->next;
        text += std::to_string(tmp->val);
    }
    for(int i = text.length() - 1; i >= 0; i--){
        std::cout << text[i];
    }

    std::cout << std::endl;
}

void displayList(Result<int> *result) {
    Node<int> *guard = result->digit;
    Node<int> *tmp = guard;
    std::string text;
    bool checked = false;
    while (tmp->next != nullptr) {
        tmp = tmp->next;
        text += std::to_string(tmp->val);
    }
    if(result->sign)
        std::cout << "-";
    for(int i = text.length() - 1; i >= 0; i--){
        if(checked || text[i] != '0'){
            std::cout << text[i];
            checked = true;
        }
    }
    std::cout << std::endl;
}

template <typename T>
void remove(Node<T> *guard) {
    Node<T> *tmp = guard;
    while (tmp->next->next != nullptr) {
        tmp = tmp->next;
    }
    delete(tmp->next);
    tmp->next = nullptr;
}
template void remove<int>(Node<int> *guard);

template <typename T>
void remove(Node<T> *guard, int position) {
    Node<T> *tmp = guard;
    Node<T> *tmp2 = guard;
    int i = 0;
    while (tmp->next != nullptr && i < position) {
        tmp = tmp->next;
        i++;
    }
    tmp2 = tmp->next->next;
    delete(tmp->next);
    tmp->next = tmp2;
}
template void remove<int>(Node<int> *guard, int position);

template <typename T>
void removeFront(Node<T> *guard) {
    Node<T> *tmp = guard->next->next;
    delete(guard->next);
    guard->next = tmp;
}
template void removeFront<int>(Node<int> *guard);

template <typename T>
void clearList(Node<T> *guard) {
    Node<T> *tmp = guard;
    Node<T> *tmp2;
    if(tmp == nullptr)
        return;
    tmp = tmp->next;
    while (tmp != nullptr) {
        tmp2 = tmp;
        tmp = tmp->next;
        delete(tmp2);
    }
    guard->next = nullptr;

}
template void clearList<int>(Node<int> *guard);

