#include <gtest/gtest.h>
#include "../src/Duck.h"
#include <string.h>

TEST(RubberDuckTest, Constructor){
	Duck* duck = new RubberDuck();
	string expect_str = "I am a Rubber Duck.";
	EXPECT_STREQ(expect_str.c_str(),duck->display().c_str())<<"FAIL:Display!";
}

TEST(RubberDuckTest, performFly){
	Duck* duck = new RubberDuck();
	string expect_str = "Cannot fly.";
	EXPECT_STREQ(expect_str.c_str(),duck->performFly().c_str())<<"FAIL:FlyBehavior!";
}

TEST(RubberDuckTest, performQuack){
	Duck* duck = new RubberDuck();
	string expect_str = "Quack at 2 decibels.";
	EXPECT_STREQ(expect_str.c_str(),duck->performQuack().c_str())<<"FAIL:Quack!";
}


TEST(RubberDuckTest, setFlyBehavior){
	Duck* duck = new RubberDuck();
	FlyBehavior *flyBehavior;
	flyBehavior = new FlyWithWings();
	duck->setFlyBehavior(flyBehavior);
	string expect_str = "Fly with wings at speed of 5 mph.";
	EXPECT_STREQ(expect_str.c_str(),duck->performFly().c_str())<<"FAIL:FlyBehavior!";
}

TEST(RubberDuckTest, setQuackBehavior){
	Duck* duck = new RubberDuck();
	QuackBehavior *quackBehavior = new Quack();
	duck->setQuackBehavior(quackBehavior);
	string expect_str = "Quack at 10 decibels.";
	EXPECT_STREQ(expect_str.c_str(),duck->performQuack().c_str())<<"FAIL:QuackBehavior!";
}
