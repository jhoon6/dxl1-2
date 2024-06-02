#ifndef SUB_HPP
#define SUB_HPP

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "dxl/dxl.hpp"
#include <memory>
#include <functional>

class MySub
{
public:
    MySub();
    void run();

private:
    void mysub_callback(const geometry_msgs::msg::Vector3::SharedPtr msg);

    rclcpp::Node::SharedPtr node_;
    Dxl dxl_;
    std::function<void(const geometry_msgs::msg::Vector3::SharedPtr msg)> fn_;
};

#endif