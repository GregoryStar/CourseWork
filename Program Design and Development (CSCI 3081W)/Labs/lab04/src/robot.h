#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

class Robot {
private:
  double x;
  double y;
  int color;
  double radius;
  double velX;
  double velY;
  double lastUpdateTime;
public:
  Robot();
  Robot(int c, double xPos, double yPos, double xV, double yV, double r);
  ~Robot();
  void updateRobotPosition(double currentTime){
    x += velX * (currentTime - lastUpdateTime);
    y += velY * (currentTime - lastUpdateTime);
    lastUpdateTime = currentTime;
  }
  int getColor();
  void setColor(int c);
  double getRadius();
  void setRadius(double r);
  void getVelocity(double *xV, double *yV);
  void setVelocity(double xV, double yV);
  void getPosition(double *xPos, double *yPos);
  void setPosition(double xPos, double yPos);
};

#endif
