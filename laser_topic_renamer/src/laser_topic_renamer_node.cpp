#include "ros/ros.h"
#include <ros/console.h>
#include "std_msgs/String.h"
#include "sensor_msgs/LaserScan.h"

#include <sstream>

//Intitialize global Variables
int iFirstRun = 0;
sensor_msgs::LaserScan scan_1_data;
sensor_msgs::LaserScan scan_2_data;
ros::Publisher scan_1_publisher;
ros::Publisher scan_2_publisher;

void forwardedScanData_1(const sensor_msgs::LaserScan::ConstPtr& scan_in){
  scan_1_data = *scan_in;
  scan_1_publisher.publish(scan_1_data);
}
void forwardedScanData_2(const sensor_msgs::LaserScan::ConstPtr& scan_in){
  scan_2_data = *scan_in;
  scan_2_publisher.publish(scan_2_data);
}

int main(int argc, char **argv)
{ 
  ros::init(argc, argv, "laser_topic_renamer_node");
  ros::NodeHandle n;
  ros::Rate loop_rate(10);

  if (iFirstRun == 0){
    //This is the place where the topics name can be set       V
    scan_1_publisher = n.advertise<sensor_msgs::LaserScan>("scan_1", 10);
    scan_2_publisher = n.advertise<sensor_msgs::LaserScan>("scan_2", 10);
    iFirstRun = 1;
  }
  
  ros::Subscriber scan_1_subscriber = n.subscribe("sick_safetyscanner_1/scan", 10, forwardedScanData_1);
  ros::Subscriber scan_2_subscriber = n.subscribe("sick_safetyscanner_2/scan", 10, forwardedScanData_2);
   
  loop_rate.sleep();

  ros::spin();

  return 0;
}
