#include "alt_search_sort.cpp"

#include "gtest/gtest.h"
#include <vector>

class SortTest : public ::testing::Test {
  public:
    static const int sorted_array[5] { 1, 3, 4, 7, 9 };
    static const std::vector<double> sorted_vec { 1.7, 3.0, 4.3, 9.2, 12.6, 12.7, 12.8 };

  protected:
    SortTest( ) : test_array{ 3, 9, 1, 4, 7 }
                , test_vec{ 1.7, 9.2, 3.0, 12.6, 12.7, 12.8, 4.3 }
                { }

    int test_array[5];
    std::vector<double> test_vec;
};

template<class T, size_t SIZE>
bool compare(T lhs[], T rhs[]) {
    for (size_t i = 0; i < SIZE; i++) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}


TEST_F(SortTest, BubbleSortWorks) {
    sort::bubble(&test_array[0], &test_array[4]);
    sort::bubble(test_vec.begin(), test_vec.end());
    EXPECT_TRUE(::compare<int,5>(test_array, sorted_array));
    EXPECT_EQ(test_vec, sorted_vec);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
