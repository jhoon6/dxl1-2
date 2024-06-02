#ifndef PUB_HPP
#define PUB_HPP

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "dxl/dxl.hpp"
#include <memory>

class MyPub
{
public:
    MyPub();
    void run();

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr publisher_;
    geometry_msgs::msg::Vector3 vel_;
    rclcpp::WallRate loop_rate_;
    int vel1_;
    int vel2_;
    int goal1_;
    int goal2_;

    void update_velocity();
};

#endif