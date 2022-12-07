#include <ros.h>
#include <std_msgs/Int8.h>

ros::NodeHandle nh; // If fail, modify the buffer size.

std_msgs::Int8 pub_msg;
ros::Publisher pub("publisher_topic", &pub_msg);

void messageCb(const std_msgs::Int8& str_msg)
{
  pub_msg.data = str_msg.data;
  pub.publish(&pub_msg);
}

ros::Subscriber<std_msgs::Int8> sub("subscriber_topic", &messageCb);

void setup()
{
  Serial.begin(57600);

  nh.initNode();
  nh.advertise(pub);
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  
  pub_msg.data = -1;
  pub.publish(&pub_msg);

  delay(100);
}
