#include <algorithm> // For std::clamp
#include <cmath> // For M_PI
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <std_msgs/msg/float32.hpp>

class JoyToAnglesNode : public rclcpp::Node
{
public:
    JoyToAnglesNode() : Node("joy_to_angles_node")
    {
        joy_subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
            "joy", 10, std::bind(&JoyToAnglesNode::joy_callback, this, std::placeholders::_1));

        pitch_publisher_ = this->create_publisher<std_msgs::msg::Float32>("pt_pitch_angle", 10);
        yaw_publisher_ = this->create_publisher<std_msgs::msg::Float32>("pt_yaw_angle", 10);
    }

private:
    float pitch_status_ = 0.0;
    float yaw_status_ = 0.0;
    const float increment_ = 0.1; // Fixed increment value
    const float pitch_limit_ = M_PI / 2; // Limit for pitch
    const float yaw_limit_ = 3 * M_PI / 4; // Limit for yaw

    void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
    {
        if (msg->axes.size() > 7) // Ensure Axis 7 exists
        {
            if (msg->axes[7] != 0.0)
            {
                pitch_status_ += (msg->axes[7] > 0 ? increment_ : -increment_);
                pitch_status_ = std::clamp(pitch_status_, -pitch_limit_, pitch_limit_);
            }
            auto pitch_msg = std_msgs::msg::Float32();
            pitch_msg.data = pitch_status_;
            pitch_publisher_->publish(pitch_msg);
        }

        if (msg->axes.size() > 6) // Ensure Axis 6 exists
        {
            if (msg->axes[6] != 0.0)
            {
                yaw_status_ += (msg->axes[6] > 0 ? increment_ : -increment_);
                yaw_status_ = std::clamp(yaw_status_, -yaw_limit_, yaw_limit_);
            }
            auto yaw_msg = std_msgs::msg::Float32();
            yaw_msg.data = yaw_status_;
            yaw_publisher_->publish(yaw_msg);
        }
    }

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_subscription_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pitch_publisher_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr yaw_publisher_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JoyToAnglesNode>());
    rclcpp::shutdown();
    return 0;
}