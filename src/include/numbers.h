#ifndef NUMERIC
#define NUMERIC

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>


int64_t extended_GCD( int64_t a, int64_t b, int64_t& x, int64_t& y )
{
    if( a == 0 )
    {
        x = 0;
        y = 1;
        return b;
    }
    int64_t p, q;
    int64_t d = extended_GCD( a % b, b, p, q );
    x = q - ( b / a ) * p;
    y = p;
    return d;
}



template<typename iter, typename cmp>
bool next_permutation( iter begin, iter end, cmp predicate )
{
    bool has_next_permutation = false;

    auto rbegin = make_reverse_iterator( end );
    auto rend = make_reverse_iterator( begin );

    // ind the largest index k such that a[k] < a[k + 1]
    auto pivot = std::is_sorted_until( rbegin, rend, predicate );

    if( pivot != rend )
    {
        std::iter_swap( pivot, std::upper_bound( rbegin, pivot, *pivot, predicate ) );
        has_next_permutation = true;
    }
    std::reverse( rbegin, pivot );

    return has_next_permutation;
}

template<typename T>
std::vector<int> longest_increasing_subseq( std::vector<T> array )
{
    auto N = array.size();
    std::vector<int> dest( N );
    std::vector<int> parent( N );

    for( int i = 0; i < N; ++i )
    {
        dest[i] = 1;
        parent[i] = -1;

        for( int j = 0; j < i; ++j )
        {
            if( array[j] < array[i]  &&  dest[i] < 1 + dest[j] )
            {
                parent[i] = j;
                dest[i] = 1 + dest[j];
            }
        }
    }


    // Obtain path
    vector<int> path;
    auto argmax = std::distance( dest.begin(), std::max_element( dest.begin(), dest.end() ) );

    T LIS_length = dest[argmax];
    ( void )LIS_length;

    while( argmax != -1 )
    {
        path.push_back( argmax );
        argmax = parent[argmax];
    }
    reverse( path.begin(), path.end() );

    return path;
}

#endif // NUMERIC

