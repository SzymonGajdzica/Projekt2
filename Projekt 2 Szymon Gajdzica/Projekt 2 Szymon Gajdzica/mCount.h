//
// Created by szymon on 21.01.2018.
//

#ifndef LIST_MCOUNT_H
#define LIST_MCOUNT_H

#include "mList.h"
#include "mCount.h"

enum countMode {
    ADD, DIFFERENCE, MULTIPLICATION
};

int doSumOrDifference(int val1, int val2, int val3, countMode mode);

void fillLeftNumbers(Node<int> *current, Node<int> *guard3, int forwarding);

void negateNumbers(Node<int> *guard);

void negateNumbers2(Node<int> *guard);

void doMultiplication(Node<int> *guard1, Node<int> *guard2,  Node<int> *guard3);

void countLists(Node<int> *guard1, Node<int> *guard2, Result<int> *result , countMode mode);

#endif //LIST_MCOUNT_H
