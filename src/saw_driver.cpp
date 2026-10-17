#include <chrono>
#include <functional>
#include <memory>
#include <cmath>

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/teleport_absolute.hpp"
#include "turtlesim/srv/set_pen.hpp"

using namespace std::chrono_literals;

class SawDriver : public rclcpp::Node
{
public:
  SawDriver()
  : Node("saw_driver")
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    timer_ = this->create_wall_timer(100ms, std::bind(&SawDriver::timer_callback, this));
    teleport_client_ = this->create_client<turtlesim::srv::TeleportAbsolute>("/turtle1/teleport_absolute");
    pen_client_ = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
      
  }

private:
  int numCirc = 0;
  bool isFinished = 0;
  bool isInPos = 0;
  bool penUp = 0;
  bool nextSection = 0;
  int t = 1;

  rclcpp::Client<turtlesim::srv::TeleportAbsolute>::SharedPtr teleport_client_;
  rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr pen_client_;

  
  void teleport_turtle(double x, double y, double theta)
  {
    auto request = std::make_shared<turtlesim::srv::TeleportAbsolute::Request>();

    request->x = x;
    request->y = y;
    request->theta = theta;

    teleport_client_->async_send_request(request);
  }

  void set_pen(bool pen_down)
  {
    auto request = std::make_shared<turtlesim::srv::SetPen::Request>();

    request->r = 255;
    request->g = 255;
    request->b = 255;
    request->width = 2;
    request->off = !pen_down;

    pen_client_->async_send_request(request);
  }
  
  void timer_callback()
  {
    switch(numCirc){
      case 0:
      if(!isInPos){
        set_pen(false);
        teleport_turtle(5.5,5.0,0.0);
        set_pen(true);
        isInPos = true;
      }
      else if(t < 41){
        geometry_msgs::msg::Twist msg;
        msg.linear.x = M_PI/4;   // maju 2 unit/detik
   
        msg.angular.z = M_PI/2; // putar kiri 1 rad/detik, radius = 2.0 / 1.0 = 2 unit
        publisher_->publish(msg);
        t++;
      }
      else{
        geometry_msgs::msg::Twist msg;
        msg.linear.x = 0.0;
        publisher_->publish(msg);
        t++;
        set_pen(false);
      }
      if(t == 51){
          isInPos = false;
          t = 1;
          numCirc++;
      }
      break;
      case 1:
      if(!isInPos){
        set_pen(false);
        teleport_turtle(5.5,3.5,0.0);
        set_pen(true);
        isInPos = true;
      }
      else if(t < 41){
        geometry_msgs::msg::Twist msg;
        msg.linear.x = M_PI;   // maju 2 unit/detik
   
        msg.angular.z = M_PI/2; // putar kiri 1 rad/detik, radius = 2.0 / 1.0 = 2 unit
        publisher_->publish(msg);
        t += 1;
      }
      else{
        geometry_msgs::msg::Twist msg;
        msg.linear.x = 0.0;
        publisher_->publish(msg);
        t++;
        set_pen(false);
      }
      if(t == 51){
          isInPos = false;
          t = 0;
          numCirc++;
      }
      break;
      case 2:
      double x2;
      double y2;
      if((!isInPos)&&(t<19)){

        x2 = 5.5 + 3*std::sin(0.34906585039*t);
        y2 = 5.54 + 3*std::cos(M_PI + 0.34906585039*t);
        //double angle = std::atan(((y2-y1)/(x2-x1)));
        teleport_turtle(x2, y2, (M_PI/2) + 0.34906585039*t);
        isInPos = 1;
      }
      else if((!nextSection) && (t<19)){
        set_pen(true);
        geometry_msgs::msg::Twist msg;
        msg.linear.x = 5.0;
        publisher_->publish(msg);

        nextSection=1;
        t++;
      }
      else if((nextSection)&&(t<19)){
        geometry_msgs::msg::Twist msg;
        msg.linear.x = 0.0;
        publisher_->publish(msg);

        nextSection=0;
        isInPos = 0;
      }
      else{
        geometry_msgs::msg::Twist msg;
        msg.linear.x = 0.0;
        publisher_->publish(msg);
        teleport_turtle(1,1,0.0);
        set_pen(false);
      }
      break;
    }
  }


  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SawDriver>());
  rclcpp::shutdown();
  return 0;
}