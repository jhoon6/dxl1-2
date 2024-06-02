#include "dxl/pub.hpp"

MyPub::MyPub(): loop_rate_(20.0), vel1_(0), vel2_(0), goal1_(0), goal2_(0)
{
    rclcpp::init(0, nullptr);
    node_ = std::make_shared<rclcpp::Node>("node_dxlpub");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    publisher_ = node_->create_publisher<geometry_msgs::msg::Vector3>("topic_dxlpub", qos_profile);
    vel_.x = 0;
    vel_.y = 0;
    vel_.z = 0;
}

void MyPub::update_velocity()
{
    if (Dxl::kbhit())
    {
        char c = Dxl::getch();
        switch(c)
        {
        case 's': goal1_ = 0; goal2_ = 0; break;
        case ' ': goal1_ = 0; goal2_ = 0; break;
        case 'f': goal1_ = 50; goal2_ = -50; break;
        case 'b': goal1_ = -50; goal2_ = 50; break;
        case 'l': goal1_ = -50; goal2_ = -50; break;
        case 'r': goal1_ = 50; goal2_ = 50; break;
        default : goal1_ = 0; goal2_ = 0; break;
        }         
    }

    // generate accel and decel motion
    if(goal1_ > vel1_) vel1_ += 5;
    else if(goal1_ < vel1_) vel1_ -= 5;
    else vel1_ = goal1_;

    if(goal2_ > vel2_) vel2_ += 5;
    else if(goal2_ < vel2_) vel2_ -= 5;
    else vel2_ = goal2_;

    vel_.x = vel1_;
    vel_.y = vel2_;               

    RCLCPP_INFO(node_->get_logger(), "Publish: %lf,%lf", vel_.x, vel_.y);
    publisher_->publish(vel_);
}

void MyPub::run()
{
    while (rclcpp::ok())
    {
        update_velocity();
        loop_rate_.sleep();
    }
    rclcpp::shutdown();
}

int main(int argc, char* argv[])
{
    MyPub my_pub;
    my_pub.run();
    return 0;
}
