#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"

class TwistToTwistStampedNode : public rclcpp::Node
{
public:
    TwistToTwistStampedNode()
    : Node("twist_to_twist_stamped_node")
    {
        twist_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel", 10,
            std::bind(&TwistToTwistStampedNode::twist_callback, this, std::placeholders::_1));

        twist_stamped_pub_ = this->create_publisher<geometry_msgs::msg::TwistStamped>("/cmd_vel_stamped", 10);
    }

private:
    void twist_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
    {
        auto twist_stamped_msg = geometry_msgs::msg::TwistStamped();
        twist_stamped_msg.header.stamp = this->now();
        twist_stamped_msg.header.frame_id = "base_link";  // You can adjust the frame_id as needed
        twist_stamped_msg.twist = *msg;
        twist_stamped_pub_->publish(twist_stamped_msg);
    }

    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr twist_sub_;
    rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr twist_stamped_pub_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TwistToTwistStampedNode>());
    rclcpp::shutdown();
    return 0;
}