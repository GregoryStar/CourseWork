#include <gtest/gtest.h>
#include "../src/QuackBehavior.h"
#include <string.h>

TEST(SqueakTest, Constructor){
	Squeak my_squeak;
	string expect_str = "Quack at 10 decibels.";
	EXPECT_STREQ(expect_str.c_str(),my_squeak.quack().c_str())<<"FAIL:Squeak Constructor!";
}
