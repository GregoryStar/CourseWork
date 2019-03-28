#include "src/robot.h"

   Robot::Robot(){
      x = 200;
      y = 200;
      velX = 10;
      velY = 10;
      color = 1293810;
      radius = 50;
   }
/*
   Robot::~Robot(){
     delete x;
     delete y;
     delete color;
     delete radius;
     delete velX;
     delete velY;
   }
   */
   /*

   Robot::Robot(int c, double xPos, double yPos, double xV, double yV, double r){
      color = c
      x = xPos;
      y = yPos;
      velX = xV;
      velY = yV;
      radius = r;
   }
   */
   int Robot::getColor(){
      return color;
   }
   void Robot::setColor(int c){
      color = c;
   }
   double Robot::getRadius(){
      return radius;
   }
   void Robot::setRadius(double r){
      radius = r;
   }
   void Robot::getVelocity(double *xV, double *yV){
      *xV = velX;
      *yV = velY;
   }
   void Robot::setVelocity(double xV, double yV){
      velX = xV;
      velY = yV;
   }
   void Robot::getPosition(double *xPos, double *yPos){
      *xPos = x;
      *yPos = y;
   }
   void Robot::setPosition(double xPos, double yPos){
      x = xPos;
      y = yPos;
   }
