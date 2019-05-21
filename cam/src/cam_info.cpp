#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>
#include <bits/stdc++.h>

int main(int argc, char **argv){
    ros::init(argc,argv,"cam_param");
    ros::NodeHandle nh;

    ros::Publisher Info_Pub = nh.advertise<sensor_msgs::CameraInfo>("camera_info", 1000);
    sensor_msgs::CameraInfo Camera;
    int height,width;
    nh.getParam("image_height",height);
    nh.getParam("image_width",width);
    nh.getParam("distortion_coefficients/data",Camera.D);
    
    std::vector<float> Kresults;
    std::vector<float> Rresults;
    std::vector<float> Presults;

    nh.getParam("rectification_matrix/data",Rresults);
    for (int i=0;i<9;i++) Camera.R[i]=Rresults.at(i);
    
    nh.getParam("projection_matrix/data",Presults);
    for (int i=0;i<12;i++) Camera.P[i]=Presults.at(i);

    nh.getParam("camera_matrix/data",Kresults);
    for (int i=0;i<9;i++) Camera.K[i]=Kresults.at(i);

    nh.getParam("distortion_model",Camera.distortion_model);;
    nh.getParam("camera_name",Camera.header.frame_id);
    Camera.binning_x = 0;
    Camera.binning_y = 0;
    Camera.height=height;
    Camera.width=width;

    //nh.getParam("image_width",Camera.height);
    while (ros::ok()){
        ros::Time time=ros::Time::now();
        Camera.header.stamp=ros::Time::now();
        Info_Pub.publish(Camera);
    }
    return 0;
}