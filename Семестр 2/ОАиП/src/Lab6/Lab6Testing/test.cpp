#include "pch.h"
#include "../Task5/Task5.h"

TEST(Task5Testing, Task5Test1) {
	int ans = run(7, 15, "codec", "decup");
	EXPECT_EQ(ans, 1);
}