#include <iostream>
#include <gtest/gtest.h>
#include "test/all_tests.h"

using namespace std;
int main(int __argc, char **__argv)
{
    ::testing::InitGoogleTest(&__argc, __argv);
    return RUN_ALL_TESTS();
}

