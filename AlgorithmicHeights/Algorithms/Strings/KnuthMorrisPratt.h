#ifndef KMP_H
#define KMP_H
#include <vector>
#include <string>

using std::vector;
using std::string;

vector<int> KMPSearch(string str, string pattern){

    size_t PATTERN_SIZE = pattern.size();
    size_t S_SIZE = str.size();

    vector<int> matches;
    vector<int> pi(PATTERN_SIZE + 1, -1); //prefix function

    // Compute prefix function values
    for(int i = 1; i <  PATTERN_SIZE; ++i){
        int pos = pi[i - 1];
        while( pos != -1 && pattern[pos] != pattern[i -1]){
            pos = pi[pos];
        }
        pi[i] = pos + 1;
    }


    // Find matches using prefix function
    int str_pos = 0;
    int pat_pos = 0;
    while(str_pos < S_SIZE)
    {
        while(pat_pos != -1 && ( pat_pos == PATTERN_SIZE || pattern[pat_pos] != str[str_pos])){
            pat_pos = pi[pat_pos];
        }
        str_pos++;
        pat_pos++;
        if(pat_pos == PATTERN_SIZE) {
            matches.push_back(str_pos - PATTERN_SIZE);
        }
    }


    return matches;
}

#endif // KMP_H
