#include "pch.h"
#include "Task3.h"
#include "Task3.cpp"
#include <vector>

TEST(task3testing, task3test1) {
    int matrix[3][3]{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<int> ans = createVector(matrix);
    std::vector<int> expected{};
    int mult = multOfElements(ans);
    EXPECT_EQ(ans, expected);
    //EXPECT_EQ(mult, 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}