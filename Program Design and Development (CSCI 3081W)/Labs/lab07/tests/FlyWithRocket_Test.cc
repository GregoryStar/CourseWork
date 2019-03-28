#include <gtest/gtest.h>
#include "../src/FlyBehavior.h"
#include <string.h>

TEST(FlyWithRocketTest, Constructor){
	FlyWithRocket my_flyWithRocket;
	string expect_str = "Fly with wings at speed of 20 mph.";
	EXPECT_STREQ(expect_str.c_str(),my_flyWithRocket.fly().c_str())<<"FAIL:Fly Constructor!";
}
