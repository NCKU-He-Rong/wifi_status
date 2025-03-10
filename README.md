# Wifi Status Monitor ROS Package  
![Static Badge](https://img.shields.io/badge/Author-HeRong-blue)
![Static Badge](https://img.shields.io/badge/Language-ROS/C++-green?style=for-the-badges)

## Installation
* clone the ros package
    ```
    cd <your_ws>/src
    git clone https://github.com/NCKU-He-Rong/wifi_status.git
    ```
* compile the ros package
    ```
    cd <your_ws>
    catkin build wifi_status
    ```
## Execution
* launch the roscore
    ```
    roscore
    ```
* execute the path planning ros node in another terminal
    ```
    cd <your_ws>
    source devel/setup.bash
    rosrun wifi_status wifi_monitor
    ```
## Ros Topic
* `/wifi_monitor/wifi_status`: Float32MultiArray message type
  * `/wifi_monitor/wifi_status/data[0]`: RSSI (dbm)
  * `/wifi_monitor/wifi_status/data[1]`: TX Bitrate (MBit/s)
  * `/wifi_monitor/wifi_status/data[2]`: RX Bitrate (MBit/s)
