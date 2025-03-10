// include ros related header file
#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"

// get the spec string in an buffer
#include <regex>

// get the output string after enter cmd
std::string execCommand(const char* cmd) 
{   
    // create an buffer 
    std::array<char, 128> buffer;
    std::string result;

    // open an pipe
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) 
    {
        ROS_ERROR("Failed to run command");
        return "";
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) 
    {
        result += buffer.data();
    }
    
    // return
    return result;
    
}

// get the wifi status
void getWiFiStatus(float &rssi, float &tx_bitrate, float &rx_bitrate) 
{   
    // get the output string after enter cmd
    std::string output = execCommand("iw dev wlp0s20f3 link");

    // get RSSI
    std::regex rssi_regex(R"(signal: (-?\d+) dBm)");
    std::smatch rssi_match;
    if (std::regex_search(output, rssi_match, rssi_regex)) 
    {
        rssi = std::stod(rssi_match[1]);
    } 
    else 
    {
        rssi = -100.0;
    }

    // get tx Bitrate
    std::regex tx_regex(R"(tx bitrate: ([\d.]+))");
    std::smatch tx_match;
    if (std::regex_search(output, tx_match, tx_regex)) 
    {
        tx_bitrate = std::stod(tx_match[1]);
    } 
    else 
    {
        tx_bitrate = 0.0;
    }

    // get RX Bitrate
    std::regex rx_regex(R"(rx bitrate: ([\d.]+))");
    std::smatch rx_match;
    if (std::regex_search(output, rx_match, rx_regex)) 
    {
        rx_bitrate = std::stod(rx_match[1]);
    } 
    else 
    {
        rx_bitrate = 0.0;
    }
}



// main function
int main(int argc, char **argv)
{
    // initialze ros node
    ros::init(argc, argv, "wifi_monitor");
    ros::NodeHandle nh("~");

    // create the publisher 
    ros::Publisher status_pub = nh.advertise<std_msgs::Float32MultiArray>("wifi_status", 1);
     
    // create the message object
    std_msgs::Float32MultiArray msg;

    // define the buffer
    float rssi, tx_bitrate, rx_bitrate;
    
    // define the rate
    ros::Rate rate(10);
    while (ros::ok())
    {
        // get the wifi status
        getWiFiStatus(rssi, tx_bitrate, rx_bitrate);
        ROS_WARN("RSSI: %.3f (dbm) / RX Bitrate: %.3f (MBit/s) / TX Bitrate: %.3f (MBit/s)", rssi, tx_bitrate, rx_bitrate);

        // fill-in the message 
        msg.data = {rssi, tx_bitrate, rx_bitrate};

        // pub the message
        status_pub.publish(msg);

        // sleep 
        rate.sleep();
    }
    
    // return
    return 0;
}