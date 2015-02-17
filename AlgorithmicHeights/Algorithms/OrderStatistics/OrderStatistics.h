#ifndef ORDERSTATISTICS_H
#define ORDERSTATISTICS_H

template<typename T>
T find_nth_element(T* array, int left, int right, int k){
    int i = left, j = right;

    // pivot choosing may be random-based as well
    T pivot = array[ (left + right)/2 ];

    // partition
    do{
        while(array[i] < pivot) i++;
        while(array[j] > pivot) j--;

        if(i <= j){
            std::swap(array[i], array[j]);
            i++;
            j--;
        }
    }while(i <= j);

    if(left <= k && k <= j) find_nth_element(array, left, j, k);
    if(i <= k && k <= right) find_nth_element(array, i, right, k);
    return array[k];
}

#endif // ORDERSTATISTICS_H
