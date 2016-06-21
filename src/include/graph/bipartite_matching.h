#ifndef BIPARTITE_MATCHING_H
#define BIPARTITE_MATCHING_H

#include <vector>

bool kuhn_max_matching( int src,
                        const std::vector<std::vector<int>> & graph,
                        std::vector<int> & matching,
                        std::vector<bool> & visited )
{
    if( visited[src] )
        return false;

    visited[src] = true;
    for( size_t i = 0; i < graph[src].size(); ++i )
    {
        int target = graph[src][i];
        if( matching[target] == -1 || kuhn_max_matching( matching[target], graph, matching, visited ) )
        {
            matching[target] = src;
            return true;
        }
    }
    return false;
}

#endif // BIPARTITE_MATCHING_H
