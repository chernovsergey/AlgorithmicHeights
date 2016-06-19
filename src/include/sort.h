#ifndef SEARCH_SORT_SELECT
#define SEARCH_SORT_SELECT

#include <algorithm>

// Hoare like
template<class T>
int partition( std::vector<T>& v, int l, int r )
{
    const int m = l + ( r - l ) / 2;

    const int pivot = v[m];
    std::swap( v[m], v[l] );

    int i = l + 1;
    int j = r;
    while( i <= j )
    {
        while( i <= j && v[i] <= pivot ) i++;
        while( i <= j && v[j] >  pivot ) j--;

        if( i < j )
            std::swap( v[i], v[j] );
    }
    std::swap( v[i - 1], v[l] );
    return i - 1;
}

// Simplest way for partitioning
template<class T>
int partition_simple( std::vector<T>& v, int left, int right )
{
    T pivot = v[left];
    int j = left;
    for( int i = left + 1; i < right; ++i )
        if( v[i] <= pivot )
            j += 1, std::swap( v[j], v[i] );

    std::swap( v[left], v[j] );
    return j;
}

template<class T>
int partition3( std::vector<T>& v, int l, int r )
{
    // TODO
    return 0;
}


template<class T>
T quickselect( std::vector<T>& array , int begin, int end, int k )
{
    while( begin <= end )
    {
        int pivot = partition( array, begin, end );
        if( pivot == k ) return array[k];
        if( pivot >  k ) end = pivot;
        if( pivot <  k ) begin = pivot + 1;
    }
}

template<class T>
void quicksort( std::vector<T>& a, int l, int r )
{
    if( l >= r )
        return;
    int pivot = partition( a, l, r );
    quicksort( a, l, pivot - 1 );
    quicksort( a, pivot + 1, r );
}

template<class T>
void quicksort3( std::vector<T>& a, int l, int r )
{
    // TODO
}

template<class fwd_it>
void quicksort_stl( fwd_it begin, fwd_it end )
{
    if( begin == end ) return;
    auto pivot = *std::next( begin, std::distance( begin, end ) / 2 );

    auto midle1 = std::partition( begin, end, [pivot]( auto & elem )
    {
        return elem < pivot;
    } );

    auto midle2 = std::partition( begin, end, [pivot]( auto & elem )
    {
        return !( pivot < elem );
    } );
    quicksort_stl( begin, midle1 );
    quicksort_stl( midle2, end );
}


template<class iter>
void mergesort( iter begin, iter end )
{
    if( end - begin > 1 )
    {
        iter middle = begin + ( end - begin ) / 2;
        mergesort( begin, middle ); // [first, middle)
        mergesort( middle, end ); // [middle, last)
        std::inplace_merge( begin, middle, end );
    }
}

// TODO fixme
template<typename iter>
void heapsort( iter begin, iter end )
{
    std::make_heap( begin, end );

    iter start = begin;
    iter stop  = --end;
    while( stop - start > 0 )
    {
        std::swap( *stop, *start );
        --stop;
        std::make_heap( start, stop );
    }
}

template<typename T>
void insertionsort( std::vector<T>& array )
{
    if( array.size() < 2 )
        return;

    for( size_t i = 1; i < array.size(); i++ )
        for( size_t j = i; j > 0 && array[j - 1] > array[j]; j-- )
            std::swap( array[j - 1], array[j] );
}

void countsort( std::vector<int>& array, int min, int max )
{
    std::vector<int> counts( max - min + 1 );

    for( size_t i = 0; i < array.size(); ++i )
        counts[array[i] - min] += 1;

    int fillpos = 0;
    for( int i = min; i <= max; ++i )
    {
        while( counts[i - min] > 0 )
        {
            array[fillpos] = i;
            fillpos += 1;
            counts[i - min] -= 1;
        }
    }
}

template <class iter, class cmp>
void partial_sort( iter first, iter middle, iter last, cmp* )
{
    std::make_heap( first, middle );
    for( iter it = middle; it < last; ++it )
        if( *it < *first )
            std::pop_heap( first, middle, it, cmp( *it ) );
    std::sort_heap( first, middle );
}

#endif // SEARCH_SORT_SELECT

