#include "include/graph.h"
#include "include/numbers.h"
#include "include/sort.h"
#include "include/str.h"
#include "include/hash.h"
#include "include/list.h"
#include "include/tree.h"

#include <algorithm>


/********************
 * STRINGS
*********************/

#define TEST_RND_STRING_SIZE_ALPHABET(size, alph) \
TEST(namespace_str, test_rand_string_##_##alph##_##size)\
{\
    EXPECT_EQ(size, str::random_string(size, str::alph).length());\
}\

#define TEST_RND_STRING_SIZE(size) \
    TEST_RND_STRING_SIZE_ALPHABET(size, alphanumeric)\
    TEST_RND_STRING_SIZE_ALPHABET(size, alphas_only)\
    TEST_RND_STRING_SIZE_ALPHABET(size, full)\

#define TEST_RND_STRING \
    TEST_RND_STRING_SIZE(10)\
    TEST_RND_STRING_SIZE(20)\
    TEST_RND_STRING_SIZE(30)\

TEST_RND_STRING


TEST( namespace_str, test_splitting_by )
{
    std::vector<std::string> ans = {"a", "b", "c"};
    auto res = str::split_by( "a b c", " " );
    EXPECT_EQ( ans, res );

    ans = {"aaa", " bb ccc", " ddd", " Eee "};
    res = str::split_by( "aaa, bb ccc, ddd, Eee ", "," );
    EXPECT_EQ( ans, res );
}

TEST( namespace_str, test_trim_string )
{
    std::string t = "   aaa ";
    std::string s = str::trim( t );
    EXPECT_EQ( "aaa", s );

    t = "   aaa bbb   ";
    s = str::trim( t );
    EXPECT_EQ( "aaa bbb", s );
}

TEST( namespace_str, test_tokenize_string )
{
    std::vector<std::string> ans = {"a", "b", "c"};
    std::string q = "a b c";
    EXPECT_EQ( ans, str::tokenize( q, " " ) );

    ans = {"aaa,", "bb", "ccc,", "ddd,", "Eee"};
    q = "aaa, bb ccc, ddd, Eee ";
    EXPECT_EQ( ans, str::tokenize( q, " " ) );
}

TEST( namespace_str, test_endwith )
{
    str::string to_test = "abababa123";
    EXPECT_EQ( true, str::endwith( to_test, "123" ) );
    EXPECT_EQ( false, str::endwith( to_test, "124" ) );
    EXPECT_EQ( true, str::endwith( to_test, "ba123" ) );
    EXPECT_EQ( false, str::endwith( to_test, "daba123" ) );

}

TEST( namespace_str, test_startwith )
{
    str::string to_test = "987abababa123";
    EXPECT_EQ( true, str::startwith( to_test, "987" ) );
    EXPECT_EQ( false, str::startwith( to_test, "987b" ) );
    EXPECT_EQ( true, str::startwith( to_test, "987aba" ) );
    EXPECT_EQ( false, str::startwith( to_test, "987abada" ) );
}



/********************
 * SEARCH SELECT SORT
*********************/

std::vector<int> radom_vector( size_t num_items )
{
    std::vector<int> x;
    x.reserve( num_items );
    std::generate_n( std::back_inserter( x ), num_items, []()
    {
        return rand() % 500;
    } );
    return x;
}

TEST( namespace_seach_sort_select, test_partitioning )
{
    std::vector<int> a = {5, 3, 2, 6, 4, 1, 3, 7};
    int idx = partition( a, 0, a.size() - 1 );
    EXPECT_EQ( true, std::all_of( a.begin(), a.begin() + idx, [idx]( int i )
    {
        return i <= idx;
    } ) );
    EXPECT_EQ( true, std::all_of( a.begin() + idx, a.end(), [idx]( int i )
    {
        return i >= idx;
    } ) );
}

TEST( namespace_seach_sort_select, test_partitioning_simple )
{
    std::vector<int> a = {5, 3, 2, 6, 4, 1, 3, 7};
    int idx = partition_simple( a, 0, a.size() - 1 );

    EXPECT_EQ( true, std::all_of( a.begin(), a.begin() + idx, [idx]( int i )
    {
        return i <= idx;
    } ) );
    EXPECT_EQ( true, std::all_of( a.begin() + idx, a.end(), [idx]( int i )
    {
        return i >= idx;
    } ) );
}


TEST( namespace_seach_sort_select, test_quickselect )
{
    std::vector<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -100};
    std::random_shuffle( a.begin(), a.end() );
    EXPECT_EQ( -100, quickselect( a, 0, a.size() - 1, 0 ) );
    EXPECT_EQ( 4, quickselect( a, 0, a.size() - 1, 5 ) );
}


TEST( namespace_seach_sort_select, test_quicksort_stl )
{
    std::vector<int> a = radom_vector( 10 );
    std::random_shuffle( a.begin(), a.end() );
    quicksort_stl( a.begin(), a.end() );
    EXPECT_EQ( std::is_sorted( a.begin(), a.end() ), true );
}


TEST( namespace_seach_sort_select, test_quicksort )
{
    std::vector<int> a = radom_vector( 10 );
    std::random_shuffle( a.begin(), a.end() );
    quicksort( a, 0, a.size() - 1 );
    EXPECT_EQ( std::is_sorted( a.begin(), a.end() ), true );
}

TEST( namespace_seach_sort_select, test_mergesort )
{
    std::vector<int> a = radom_vector( 10 );
    std::random_shuffle( a.begin(), a.end() );
    mergesort( a.begin(), a.end() );
    EXPECT_EQ( std::is_sorted( a.begin(), a.end() ), true );
}

TEST( namespace_seach_sort_select, test_insertsort )
{
    std::vector<int> a = radom_vector( 10 );
    std::random_shuffle( a.begin(), a.end() );
    insertionsort( a );
    EXPECT_EQ( std::is_sorted( a.begin(), a.end() ), true );
}


// TODO fixme
TEST( namespace_seach_sort_select, test_heapsort )
{
    std::vector<int> a = radom_vector( 10 );
    std::random_shuffle( a.begin(), a.end() );
    heapsort( a.begin(), a.end() );
    EXPECT_EQ( std::is_sorted( a.begin(), a.end() ), true );
}

TEST( namespace_seach_sort_select, test_partial_sort )
{
    std::vector<int> a = radom_vector( 10 );
    std::random_shuffle( a.begin(), a.end() );
    partial_sort( a.begin(), a.begin() + 5, a.end() );
    EXPECT_EQ( std::is_sorted( a.begin(), a.begin() + 5 ), true );
}


TEST( namespace_list, test_linked_list )
{
    LinkedList<int> l;
    l.push_back(5);
    l.push_front(4);
    l.push_back(6);
    l.push_front(3);
    EXPECT_EQ(4, l.size());

    std::cout << l << std::endl;

    l.pop_front();
    l.pop_back();
    EXPECT_EQ(2, l.size());

    EXPECT_EQ(false, l.empty());

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.clear();
    EXPECT_EQ(0, l.size());
}
