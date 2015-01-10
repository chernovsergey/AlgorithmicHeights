#include <iostream>
#include <random>
#include <memory>
#include <array>
#include <algorithm>
#include <assert.h>

#include "Sortings/Sortings.h"
#include "Lists/List.h"

using namespace std;

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

int main()
{
   array<float, 8> A;

   fill(A.data(), A.size());
   QuickSort(A.data(), 7);
   assert(true == is_sorted(A.begin(),A.end()));

   fill(A.data(), A.size());
   MergeSort(A.data(), 0, 7);
   assert(true == is_sorted(A.begin(),A.end()));


    return 0;
}

