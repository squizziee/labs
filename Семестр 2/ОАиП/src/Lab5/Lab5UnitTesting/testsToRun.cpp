#include <iostream>
#include <vector>
#include "pch.h"
#include "../../Lab5/Task3/Task3.h"

/*TEST(execute_Task3, Task3Test1) {
  EXPECT_EQ(execute_Task3(matrix, n, m), 1);
  EXPECT_TRUE(true);
}*/

TEST(task3testing, task3test1) {
    int matrix[3][3] {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> ans = createVector(matrix);
    std::vector<int> expected {};
    int mult = multOfElements(ans);
    EXPECT_EQ(ans, expected);
    EXPECT_EQ(mult, 0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
