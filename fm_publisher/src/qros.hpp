#ifndef QROS_HPP
#define QROS_HPP

#include <QObject>
#include <QThread>
#include <string>
#include <sstream>
#include <iostream>
#include <ros/ros.h>
#include <ros/node_handle.h>

#define ROS_NODE_NAME "fm_publisher"
#define ROS_MASTER "http://localhost:11311"
#define ROS_HOSTNAME "localhost"
#define ROS_FOLLOW_IMG_W 640
#define ROS_FOLLOW_IMG_H 480
#define ROS_FOLLOW_IMG_DATA_SIZE (ROS_FOLLOW_IMG_W * ROS_FOLLOW_IMG_H * 3)
#define ROS_FOLLOW_IMG_TOPIC "/cona_hf/colorstream"
#define ROS_AURORA_STATUS_TOPIC "/aurora_status"

class QRos : public QThread
{
    Q_OBJECT
public:
    explicit QRos();
    virtual ~QRos();
    bool rosOpen();
    void rosClose();
    void run();
    bool isRosOK();

    /////////////////////////////
    // Topic - Subscribe
    template<class M, class T>
    ros::Subscriber Subscribe(const std::string &topic, uint32_t queue_size, void(T::*fp)(M), T *obj){
        if(!isRosOK()) return ros::Subscriber();
        ros::Subscriber retSS = pNH->subscribe(topic, queue_size, fp, obj);
        return retSS;
    }
    bool isValidSubscriber(ros::Subscriber &sub){
        if(!sub) return false;
        return true;
    }
    void UnSubscribe(ros::Subscriber &sub){
        if(!sub) return;
        sub.shutdown();
    }

    /////////////////////////////
    // Topic - Publish
    template<class M >
    ros::Publisher Advertise(const std::string &topic, uint32_t queue_size, bool latch=false){
        if(!isRosOK()) return ros::Publisher();
        ros::Publisher retPS = pNH->advertise<M>(topic, queue_size, latch);
        return retPS;
    }
    bool isValidPublisher(ros::Publisher &pub){
        if(!pub) return false;
        return true;
    }
    template<class M>
    bool Publish(ros::Publisher &pub, const M &message) const{
        if(!pub) return false;
        pub.publish(message);
        return true;
    }
    void UnAdvertise(ros::Publisher &pub){
        if(!pub) return;
        pub.shutdown();
    }

    /////////////////////////////
    // Serivce - Call
    template<class Service>
    bool ServiceCall(const std::string &service_name, Service &service){
        if(!isRosOK()) return false;
        return ros::service::call(service_name, service);
    }

    /////////////////////////////
    // Parameter - Get/Set
    template<typename T>
    bool GetParam(const std::string &key, T &val){
        if(!isRosOK()) return false;
        return pNH->getParam(key, val);
    }
    template<typename T>
    bool SetParam(const std::string &key, T &val, T &retVal, bool diffVal=true){
        if(!isRosOK()) return false;
        pNH->setParam(key, val);
        if(!GetParam(key, retVal) || (diffVal && val != retVal)) return false;
        return true;
    }

private:
    ros::NodeHandle *pNH = NULL;

signals:
    void rosShutdown();
public slots:
};


#endif // QROS_HPP
