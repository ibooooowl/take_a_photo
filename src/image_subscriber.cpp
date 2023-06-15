#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try
    {
        cv_bridge::CvImagePtr cvImage = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        cv::Mat image = cvImage->image;

        // Process the image as needed
        // ...

        // Save the image
        std::string image_path = "/home/user/Downloads/image1_D415.jpg";  // Set the desired path to save the image
        cv::imwrite(image_path, image);
        ROS_INFO_STREAM("Image captured and saved: " << image_path);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_subscriber_node");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/camera/color/image_raw", 1, imageCallback);

    ros::spin();

    return 0;
}
