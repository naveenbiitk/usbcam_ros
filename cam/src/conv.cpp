#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "conv");
    ros::NodeHandle nh;
    ros::Publisher img_pub=nh.advertise<sensor_msgs::Image>("/usb_cam/image_raw", 10);
    cv::VideoCapture cap;
    sensor_msgs::Image img;
    std_msgs::Header header;
    cap.open(0);
    cv::Mat frame;
    while(ros::ok())
    {
        cap >> frame;
        cv_bridge::CvImage img_bridge;
        header.seq=0;
        header.stamp=ros::Time::now();
        img_bridge.header=header;
        img_bridge.encoding=sensor_msgs::image_encodings::BGR8;
        img_bridge.image=frame;
        img_bridge.toImageMsg(img);
        img_pub.publish(img);
        ros::spinOnce();
    }
}
