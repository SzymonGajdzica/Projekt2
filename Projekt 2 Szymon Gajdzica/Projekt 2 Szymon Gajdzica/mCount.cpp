//
// Created by szymon on 21.01.2018.
//

#include "stdafx.h"
#include "mList.h"

enum countMode {
    ADD, DIFFERENCE, MULTIPLICATION
};

int doSumOrDifference(int val1, int val2, int val3, countMode mode) {
    switch (mode) {
        case ADD:
            return val1 + val2 + val3;
        case DIFFERENCE:
            return val1 - val2 + val3;
        default:
            return val1 + val2 + val3;
    }
}

void fillLeftNumbers(Node<int> *current, Node<int> *guard3, int forwarding){
    Node<int> *tmp = current;
    while (tmp->next != nullptr) {
        tmp = tmp->next;
        int sum = tmp->val + forwarding;
        add(sum, guard3);
        forwarding = 0;
    }
}

void negateNumbers2(Node<int> *guard) {
    Node<int> *tmp = guard;
    if(tmp->next == nullptr)
        return;
    while (tmp->next->next != nullptr) {
        tmp = tmp->next;
        tmp->val = 9 - tmp->val;
    }
    tmp = tmp->next;
    tmp->val = tmp->val - 1;
}

void negateNumbers(Node<int> *guard) {
    Node<int> *tmp = guard;
    bool done = false;
    if(tmp->next == nullptr)
        return;
    while (tmp->next != nullptr) {
        tmp = tmp->next;
        if(!done && tmp->val != 0 || !done && tmp->next == nullptr){
            tmp->val = 10 - tmp->val;
            done = true;
        }else if(done){
            tmp->val = 9 - tmp->val;
        }
    }
}

void doMultiplication(Node<int> *guard1, Node<int> *guard2,  Node<int> *guard3) {
    Node<int> *tmp1 = guard1;
    Node<int> *tmp3 = guard3;
    add(0, guard3);
    while(tmp1->next != nullptr){
        tmp1 = tmp1->next;
        tmp3 = tmp3->next;
        Node<int> *tmp2 = guard2;
        Node<int> *tmp4 = tmp3;
        int forwarding = 0;
        bool first = false;
        while(tmp2->next != nullptr){
            if(first){
                if(tmp4->next == nullptr)
                    add(0, guard3);
                tmp4 = tmp4->next;
            }
            tmp2 = tmp2->next;
            int sum = tmp1->val * tmp2->val + forwarding;
            forwarding = sum / 10;
            sum %= 10;
            int tempSum = sum + tmp4->val;
            if(tempSum > 9){
                tempSum %= 10;
                forwarding++;
            }
            tmp4->val = tempSum;
            first = true;
        }
        if(forwarding != 0)
            add(forwarding, guard3);
    }
}

void countLists(Node<int> *guard1, Node<int> *guard2, Result<int> *result , countMode mode) {
    int forwarding = 0;
    Node<int> *guard3 = result->digit;
    if(mode == MULTIPLICATION){
        doMultiplication(guard1, guard2, guard3);
        return;
    }
    Node<int> *tmp1 = guard1;
    Node<int> *tmp2 = guard2;
    bool problem = false;
    while (tmp1->next != nullptr && tmp2->next != nullptr) {
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
        if(mode == DIFFERENCE){
            if(tmp1->val < tmp2->val)
                problem = true;
            if(tmp1->val > tmp2->val)
                problem = false;
        }
        int sum = doSumOrDifference(tmp1->val, tmp2->val, forwarding, mode);
        forwarding = sum / 10;
        sum %= 10;
        if (sum < 0) {
            sum += 10;
            forwarding--;
        }
        add(sum, guard3);
    }
    if(mode == DIFFERENCE && tmp1->next == nullptr && tmp2->next == nullptr && problem)
        negateNumbers(guard3);
    if(tmp1->next != nullptr) {
        fillLeftNumbers(tmp1, guard3, forwarding);
        if(mode == ADD)
            forwarding = 0;
    }
    if(tmp2->next != nullptr){
        if(mode == DIFFERENCE){
            problem = true;
            forwarding = 0;
            negateNumbers2(guard2);
            fillLeftNumbers(tmp2, guard3, forwarding);
        } else
            fillLeftNumbers(tmp2, guard3, forwarding);
    }
    if(forwarding != 0 && mode == ADD)
        add(forwarding, guard3);
    result->sign = problem;
}