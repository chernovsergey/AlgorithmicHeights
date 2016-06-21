#ifndef COUNT_MIN_SKETCH_H
#define COUNT_MIN_SKETCH_H


#include <vector>
#include <limits>
#include "../sort_select/sort.h"


template<typename Key, typename Hash = std::hash<Key>>
struct CountMinSketch
{
    /*
    *
    * Optimal width is sketch_width = 2.71 / epsilon
    * Optimal number of hash functions is sketch_depth = ln(1 / delta)
    *
    */

    protected:
        const size_t sketch_width;
        const size_t sketch_depth;
        const size_t prime;

        std::vector<uint64_t> a, b;
        Hash hasher;

        using CountArray = std::vector<uint64_t>;
        using CountTable = std::vector<CountArray> ;
        CountTable storage;

        size_t seen_count = 0;

        inline size_t next_hash(Key key, size_t i)
        {
            return ((a[i] * hasher(key) + b[i]) % prime ) % sketch_width;
        }

    public:
        CountMinSketch(float delta = 0.01, float epsilon = 0.001, uint64_t prime = 179426081)
            : sketch_width( std::ceil(std::exp(1) / epsilon))
            , sketch_depth( std::ceil(std::log(1/delta)))
            , prime(prime)
        {

            storage.assign(sketch_depth, CountArray(sketch_width));

            srand(42);
            for(size_t i = 0; i < sketch_depth; ++i)
            {
                a.emplace_back(rand() % prime + 1);
                b.emplace_back(rand() % prime);
            }
        }

        void update(Key key)
        {
            for(size_t i = 0; i < sketch_depth; ++i)
                storage[i][next_hash(key, i)] += 1;

            ++seen_count;
        }

        uint64_t count(Key key)
        {
            uint64_t min_count = std::numeric_limits<uint64_t>::max();
            for(size_t i = 0; i < sketch_depth; ++i)
                min_count = std::min(min_count, storage[i][next_hash(key, i)]);

            return min_count;
        }
};


#endif // COUNT_MIN_SKETCH_H
