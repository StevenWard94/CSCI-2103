#include "List.cpp"
#include <gtest/gtest.h>

class ListTest : public ::testing::Test {
  protected:
    ListTest( ) : intList_{} { }
    List<int> intList_;
};

TEST_F(ListTest, DefaultInitializationWorks) {
    ASSERT_TRUE(intList_.isEmpty());
    ASSERT_EQ(0, intList_.size());
    EXPECT_TRUE(intList_.head() == nullptr);
}

TEST_F(ListTest, InsertionMethodsWork) {
    int const numbers[10] { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90 };
    intList_.append(numbers[9]);
    ASSERT_FALSE(intList_.isEmpty());
    ASSERT_EQ(1, intList_.size());
    EXPECT_FALSE(intList_.head() == nullptr);
    EXPECT_EQ(90, intList_.front());

    intList_.prepend(numbers[2]);
    ASSERT_FALSE(intList_.isEmpty());
    ASSERT_EQ(2, intList_.size());
    EXPECT_FALSE(intList_.head() == nullptr);
    EXPECT_EQ(20, intList_.front());

    intList_.insert(numbers[5], 6);
    ASSERT_EQ(2, intList_.size());

    intList_.insert(numbers[5], 1);
    ASSERT_EQ(3, intList_.size());
    EXPECT_NE(50, intList_.front());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
