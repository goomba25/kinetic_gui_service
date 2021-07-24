#include <QDebug>
#include "qros.hpp"

QRos::QRos()
{

}

QRos::~QRos()
{
    rosClose();
}

bool QRos::rosOpen()
{
    rosClose();

    std::map<std::string,std::string> remappings;
    remappings["__master"] = ROS_MASTER;
    remappings["__hostname"] = ROS_HOSTNAME;
    ros::init(remappings, ROS_NODE_NAME);
    if (!ros::master::check()){
        return false;
    }
    
    ros::start();
    pNH = new ros::NodeHandle();
    start();
    return true;
}

void QRos::rosClose()
{
    if(ros::isStarted()){
        ros::shutdown();
        ros::waitForShutdown();
    }
    if(pNH){
        delete pNH;
        pNH = NULL;
    }
    wait();
}

bool QRos::isRosOK()
{
    return ros::isStarted() && ros::ok() && ros::master::check();
}

void QRos::run() {
    while (ros::ok() && ros::master::check()){
        ros::spinOnce();
    }
    emit rosShutdown();
}


