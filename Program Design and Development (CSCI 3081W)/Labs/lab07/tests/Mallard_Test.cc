#include <gtest/gtest.h>
#include "../src/Duck.h"
#include <string.h>

TEST(MallardDuckTest, Constructor){
	Duck* duck = new Mallard();
	string expect_str = "I am a Mallard.";
	EXPECT_STREQ(expect_str.c_str(),duck->display().c_str())<<"FAIL:Display!";
}

TEST(MallardDuckTest, performFly){
	Duck* duck = new Mallard();
	string expect_str = "Fly with wings at speed of 5 mph.";
	EXPECT_STREQ(expect_str.c_str(),duck->performFly().c_str())<<"FAIL:FlyBehavior!";
}

TEST(MallardDuckTest, performQuack){
	Duck* duck = new Mallard();
	string expect_str = "Quack at 10 decibels.";
	EXPECT_STREQ(expect_str.c_str(),duck->performQuack().c_str())<<"FAIL:Quack!";
}


TEST(MallardDuckTest, setFlyBehavior){
	Duck* duck = new Mallard();
	FlyBehavior *flyBehavior;
	flyBehavior = new FlyWithWings();
	duck->setFlyBehavior(flyBehavior);
	string expect_str = "Fly with wings at speed of 5 mph.";
	EXPECT_STREQ(expect_str.c_str(),duck->performFly().c_str())<<"FAIL:FlyBehavior!";
}

TEST(MallardDuckTest, setQuackBehavior){
	Duck* duck = new Mallard();
	QuackBehavior *quackBehavior = new Quack();
	duck->setQuackBehavior(quackBehavior);
	string expect_str = "Quack at 10 decibels.";
	EXPECT_STREQ(expect_str.c_str(),duck->performQuack().c_str())<<"FAIL:QuackBehavior!";
}
