#include <iostream>
#include <random>
#include <memory>
#include <array>
#include <algorithm>
#include <assert.h>

#include "Algorithms/Sortings/Sortings.h"
#include "DataStructures/Lists/List.h"
#include "Algorithms/OrderStatistics/OrderStatistics.h"

using namespace std;


/*
 * TEST_ASSERT_NOT_NULL();
 * TEST_ASSERT_EQUAL_INT();
 * TEST_ASSERT_NULL();
*/


template<typename T>
void fill(T* x, int size){
    default_random_engine generator;
    int R = rand()/1000000;
    uniform_real_distribution<T> UNIFORM_X(-R, R);
    for(int i = 0; i < size; i++){
        x[i] = UNIFORM_X(generator);
    }
}

template<typename T>
void show(T *x, int size){
    for(int i = 0; i < size; i++){
        cout << x[i] << endl;
    }
    cout << endl << endl;
}

void testList(){}

void testDoublyLinkedList(){}

void testBinaryHeap(){}

void testQuickSort(){}

void testMergeSort(){}

void testInsertionSort(){}

void testHeapSort(){}

void test_nth_element(){}

void test_k_greatest(){}

void test_k_lowest(){}
