#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/battery_state.hpp"
#include "std_msgs/msg/float32.hpp"

class BatteryToFloatNode : public rclcpp::Node
{
public:
    BatteryToFloatNode()
    : Node("battery_to_float_node")
    {
        battery_sub_ = this->create_subscription<sensor_msgs::msg::BatteryState>(
            "/battery_state", 10,
            std::bind(&BatteryToFloatNode::battery_callback, this, std::placeholders::_1));

        float_pub_ = this->create_publisher<std_msgs::msg::Float32>("/battery_percentage", 10);
    }

private:
    void battery_callback(const sensor_msgs::msg::BatteryState::SharedPtr msg)
    {
        auto float_msg = std_msgs::msg::Float32();
        float_msg.data = msg->percentage;  // You can also use msg->voltage or msg->current
        float_pub_->publish(float_msg);
    }

    rclcpp::Subscription<sensor_msgs::msg::BatteryState>::SharedPtr battery_sub_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr float_pub_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BatteryToFloatNode>());
    rclcpp::shutdown();
    return 0;
}
