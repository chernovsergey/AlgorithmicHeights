#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

#include <algorithm>
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

#endif // PERMUTATIONS_H
