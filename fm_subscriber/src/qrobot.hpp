#ifndef QROBOT_HPP
#define QROBOT_HPP

#include <QObject>
#include <QMutex>
#include <QPixmap>
#include <QTimer>
#include <sensor_msgs/Image.h>

#include "fm_subscriber/MsgAuroraStatus.h"
#include "qros.hpp"

class QRobot : public QObject
{
    Q_OBJECT
public:
    explicit QRobot(QObject *parent = 0);
    ~QRobot();
    bool RobotInit();
    bool IsRobotOK(){
        return m_IsOK;
    }
    bool ChangeAuroraStatus(std::string drive_mode, int drive_status, int spray_status, int error_status);
    bool FollowImageRequest(bool start);
    QPixmap GetFollowImg();
    enum RobotInfo {
        ROS_OPEND,
        ROS_CLOSED,
        ROS_SHUTDOWN
    };
    fm_subscriber::MsgAuroraStatus m_AuroraStatus;
private:
    bool RosOpen();
    void RosClose();
    void SubFollowImageCB(const sensor_msgs::Image& message_holder);
    void SubAuroraStatusCB(const fm_subscriber::MsgAuroraStatus& message_holder);

private:
    QRos m_ROS;
    bool m_IsOK = false;
    ros::Subscriber m_SubAuroraStatus;
    ros::Subscriber m_SubFollowImage;
    ros::Publisher m_PubAuroraStatus;
    uchar m_FollowImgBuf[ROS_FOLLOW_IMG_DATA_SIZE];
    QImage* m_pFollowImg = NULL;
    QMutex m_FollowImgMutex;
    QTimer m_OpenTimer;

signals:
    void FollowImageReadySignal();
    void RobotInfoSignal(QRobot::RobotInfo info);
    void AuroraStatusSignal();

public slots:
    void RosShutdownSlot();
    void RosOpenTimeoutSlot();
};

#endif // QROBOT_HPP
