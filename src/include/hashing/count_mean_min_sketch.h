#ifndef COUNT_MEAN_MIN_SKETCH_H
#define COUNT_MEAN_MIN_SKETCH_H

#include "count_min_sketch.h"

template<typename Key, typename Hash = std::hash<Key> >
struct CountMeanMinSketch : public CountMinSketch<Key>
{
    /*
     *
     *  Correction to noise. Look at F. Deng, D. Rafiei paper
     *  "New Estimation Algorithms for Streaming Data: Count-min Can Do More"
     *
     */

    using CountMinSketch<Key>::seen_count;
    using CountMinSketch<Key>::sketch_depth;
    using CountMinSketch<Key>::sketch_width;
    using CountMinSketch<Key>::storage;
    using CountMinSketch<Key>::next_hash;


    CountMeanMinSketch(float delta = 0.01, float epsilon = 0.001, uint64_t prime = 179426081)
        : CountMinSketch<Key>(delta, epsilon, prime)
    {}

    uint64_t count(Key key)
    {
        std::vector<uint64_t> estimations(sketch_depth);
        uint64_t count_value = 0;
        uint64_t noise_value = 0;
        for(size_t i = 0; i < sketch_depth; ++i)
        {
            count_value = storage[i][next_hash(key, i)];
            noise_value = (seen_count - count_value) / (sketch_width - 1);
            estimations[i] = count_value - noise_value;
        }

        uint64_t result = quickselect(estimations, 0, sketch_depth - 1, sketch_depth/2);
        return result;
    }
};

#endif // COUNT_MEAN_MIN_SKETCH_H
