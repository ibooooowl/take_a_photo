#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
    // Initialize ROS
    ros::init(argc, argv, "image_publisher_node");
    ros::NodeHandle nh;

    // Create a publisher for the image topic
    ros::Publisher image_pub = nh.advertise<sensor_msgs::Image>("/camera/color/image_raw", 1);

    // Load an image using OpenCV
    cv::Mat image = cv::imread("/home/user/Downloads/image1_D415.jpg", cv::IMREAD_COLOR);

    // Create a sensor_msgs::Image message
    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();

    // Set the timestamp of the message
    msg->header.stamp = ros::Time::now();

    // Set the frame ID of the message
    msg->header.frame_id = "camera_frame";

    // Publish the message
    image_pub.publish(msg);

    // Spin and process callbacks
    ros::spin();

    return 0;
}
