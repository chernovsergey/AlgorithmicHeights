#include <iostream>
#include <random>
#include <memory>
#include <array>
#include <algorithm>
#include <assert.h>
#include <string>
#include <iterator>
#include <cstring>

#include "Algorithms/Sortings/Sortings.h"
#include "Algorithms/Sortings/Partials.h"
#include "DataStructures/Lists/List.h"
#include "Algorithms/OrderStatistics/OrderStatistics.h"
#include "DataStructures/Hashing/HashTable.h"
#include "DataStructures/Trees/BST.h"
#include "Algorithms/Sequences/LIS_LDS.h"
#include "Algorithms/Strings/KnuthMorrisPratt.h"
#include "Algorithms/Strings/BoyerMoore.h"

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




int main()
{
    char* source = "IHateStringsButIHaveToLove";
    char* pattern = "ToLo";

    std::cout<<boyer_moore(source, pattern);
}
