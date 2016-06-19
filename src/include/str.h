#ifndef STR
#define STR

#include <string>
#include <algorithm>
#include <sstream>

namespace str
{
    using std::string;
    using std::vector;

    const char * alphas_only = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const char * alphanumeric = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const char * full = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#@$%^&*()_+=-`?/\\{}~";

    string random_string( size_t length, const char * alphabet = alphas_only )
    {
        srand( time( NULL ) );
        auto rnd_char = [ = ]()
        {
            return alphabet[rand() % strlen( alphabet )];
        };

        string result( length, 0 );
        std::generate_n( result.begin(), length, rnd_char );

        return result;
    }


    string random_text( size_t count_words, const char * alphabet = full )
    {
        string result = random_string( rand() % 20, alphabet );

        for( size_t i = 0; i < count_words; ++i )
        {
            result += " " + random_string( rand() % 20, alphabet );
        }

        return result;
    }

    vector<string> split_by( string const & s, string const & delim )
    {
        size_t cur = 0;
        size_t nxt = 0;
        vector<string> result;
        while( ( nxt = s.find( delim, cur ) ) != string::npos )
        {
            result.emplace_back( s.substr( cur, nxt - cur ) );
            cur = nxt + 1;
        }
        result.emplace_back( s.substr( cur, nxt ) );

        return result;
    }

    vector<string> split_by( const string & s, char delim )
    {
        std::stringstream ss( s );
        string item;
        vector<string> tokens;
        while( getline( ss, item, delim ) )
        {
            tokens.emplace_back( item );
        }

        return tokens;
    }


    // TODO find out with passing tmp objects and reference
    string trim( string & s )
    {
        // trim from left
        auto it = s.begin();
        while( *it == ' ' )
        {
            ++it;
        }
        s.erase( s.begin(), it );

        // TODO : make trim right using iterators
        size_t i = s.length() - 1;
        while( s[i] == ' ' )
        {
            i -= 1;
        }
        s.replace( i + 1, s.length(), "" );

        return s;
    }

    vector<string> tokenize( string & s, string const & delim )
    {
        auto trimmer = []( string token ) -> string
        {
            return trim( token );
        };

        s = trim( s );

        vector<string> res = split_by( s, delim );
        for( auto & token : res )
        {
            token = trimmer( token );
        }

        return res;
    }

    bool endwith( string & s, const string & suffix )
    {
        if( suffix.size() > s.size() )
        {
            return false;
        }

        auto suf_it = suffix.rbegin();
        auto str_it = s.rbegin();
        for( ; suf_it != suffix.rend(); ++suf_it, ++str_it )
            if( *suf_it != *str_it )
            {
                return false;
            }

        return true;
    }

    bool startwith( string & s, string const & prefix )
    {
        auto str_it = s.begin();
        auto prf_it = prefix.begin();
        for( ; prf_it != prefix.end(); ++str_it, ++prf_it )
            if( *str_it != *prf_it )
            {
                return false;
            }

        return true;
    }

    vector<int> KMPSearch( string str, string pattern )
    {
        const size_t PSIZE = pattern.size();
        const size_t SSIZE = str.size();

        vector<int> matches;
        vector<int> pi( PSIZE + 1, -1 );

        for( size_t i = 1; i <  PSIZE; ++i )
        {
            int pos = pi[i - 1];

            while( pos != -1 && pattern[pos] != pattern[i - 1] )
            {
                pos = pi[pos];
            }

            pi[i] = pos + 1;
        }

        // Find matches using prefix function
        size_t str_pos = 0;
        size_t pat_pos = 0;
        while( str_pos < SSIZE )
        {
            while( pat_pos != -1 && ( pat_pos == PSIZE || pattern[pat_pos] != str[str_pos] ) )
            {
                pat_pos = pi[pat_pos];
            }

            ++str_pos;
            ++pat_pos;

            if( pat_pos == PSIZE )
            {
                matches.emplace_back( str_pos - PSIZE );
            }
        }
        return matches;
    }
}
#endif // STR

