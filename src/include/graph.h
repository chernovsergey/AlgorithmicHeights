#ifndef GRAPH
#define GRAPH

#include <queue>
#include <vector>
#include <array>
using std::vector;
using std::queue;
using std::array;

bool kuhn_max_matching( int src, const vector<vector<int>>& graph, vector<int>& matching, vector<bool>& visited )
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


#endif // GRAPH

