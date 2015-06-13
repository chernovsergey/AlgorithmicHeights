#ifndef LIS_LDS_H
#define LIS_LDS_H

#include <utility>
#include <vector>
#include <algorithm>

template<typename T>
std::vector<int> longestIncreasingSubsequence(std::vector<T> arr){
    std::vector<int> dest;
    std::vector<int> parent;

    auto N = arr.size();
    dest.resize(N);
    parent.resize(N);

    for( int i = 0; i < N; ++i){
        dest[i] = 1;
        parent[i] = -1;
        for( int j = 0; j < i; ++j){
            if(arr[j] < arr[i]  &&  dest[i] < 1 + dest[j]){
                dest[i] = 1 + dest[j];
                parent[i] = j;
            }
        }
    }


    // Obtain path
    vector<int> path;
    auto argmax = std::distance(dest.begin(), std::max_element(dest.begin(), dest.end()));
    T LIS_length = dest[argmax];

    while (argmax != -1) {
        path.push_back (argmax);
        argmax = parent[argmax];
    }
    reverse (path.begin(), path.end());

    return path;
}


template<typename T>
std::vector<int> longestDecreasingSubsequence(std::vector<T> arr){
    std::vector<int> dest;
    std::vector<int> parent;

    auto N = arr.size();
    dest.resize(N);
    parent.resize(N);

    for( int i = 0; i < N; ++i){
        dest[i] = 1;
        parent[i] = -1;
        for( int j = 0; j < i; ++j){
            if(arr[j] > arr[i]  &&  dest[i] < 1 + dest[j]){
                dest[i] = 1 + dest[j];
                parent[i] = j;
            }
        }
    }


    // Obtain path
    vector<int> path;
    auto argmax = std::distance(dest.begin(), std::max_element(dest.begin(), dest.end()));
    T LIS_length = dest[argmax];

    while (argmax != -1) {
        path.push_back (argmax);
        argmax = parent[argmax];
    }
    reverse (path.begin(), path.end());

    return path;
}

#endif // LIS_LDS_H
