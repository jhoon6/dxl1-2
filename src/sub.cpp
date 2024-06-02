
#include "dxl/sub.hpp"


using namespace std::placeholders;

MySub::MySub()
{
    rclcpp::init(0, nullptr);
    node_ = std::make_shared<rclcpp::Node>("node_camsub");

    if (!dxl_.open())
    {
        RCLCPP_ERROR(node_->get_logger(), "dynamixel open error");
        rclcpp::shutdown();
        throw std::runtime_error("Failed to open Dxl");
    }

    fn_ = std::bind(&MySub::mysub_callback, this, _1);
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    node_->create_subscription<geometry_msgs::msg::Vector3>("topic_dxlpub", qos_profile, fn_);
}

void MySub::mysub_callback(const geometry_msgs::msg::Vector3::SharedPtr msg)
{
    RCLCPP_INFO(node_->get_logger(), "Received message: %lf,%lf", msg->x, msg->y);
    dxl_.setVelocity((int)msg->x, (int)msg->y);
}

void MySub::run()
{
    rclcpp::spin(node_);
    dxl_.close();
    rclcpp::shutdown();
}

int main(int argc, char* argv[])
{
    try
    {
        MySub my_sub;
        my_sub.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
