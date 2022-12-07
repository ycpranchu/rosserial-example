#include <ros.h>
#include <std_msgs/Int8.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);
ros::NodeHandle nh; // if fail, modify the buffer size.

int msg;
String val;

void messageCb(const std_msgs::Int8& str_msg)
{
  int number = str_msg.data;
  int count = 0;

  char value[10];
  itoa(number, value, 10);

  while (number != 0)
  {
    count += 1;
    number /= 10;
  }

  value[count] = ',';
  BTSerial.write(value);
}

std_msgs::Int8 pub_msg;
ros::Subscriber<std_msgs::Int8> sub("publisher_topic", &messageCb);
ros::Publisher pub("subscriber_topic", &pub_msg);

void setup()
{
  Serial.begin(57600);
  BTSerial.begin(38400);

  nh.initNode();
  nh.advertise(pub);
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  val = "";

  while (BTSerial.available())
  {
    delay(10);
    char c = BTSerial.read();

    if (c == ',')
    {
      const char* temp = val.c_str();
      int number = atoi(temp);
      pub_msg.data = number;
      pub.publish(&pub_msg);

      break;
    }

    val += c;
  }

  pub_msg.data = -1;
  pub.publish(&pub_msg);

  delay(100);
}
