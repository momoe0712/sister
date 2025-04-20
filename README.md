# Kitchen Safety Improvement Through an MQTT-Based Home Automation System

This repository contains the source code for the implementation of the MQTT protocol, an IoT communication protocol. The protocol is used to develop a Safety Improvement System for kitchen environments.

In this repository, the author conducts code prototyping using two microcontroller systems: Arduino Uno R4 as the publisher and ESP32 as the subscriber. The ESP32 is connected to several actuators, including a buzzer, an air cooler, and a humidifier. 

### Repository Structures
<pre>
sister
├── publisher_code
│   ├── pubgas
│   │   ├── pubgas.ino
│   ├── pubtemp 
│   │   ├── pubtemp.ino
├── subscriber_code
│   ├── subgas
│   │   ├── subgas.ino
│   ├── subtemp
│   │   ├── subtemp.ino
</pre>


#### Minor Information
| File Name     | Description                          |
|---------------|--------------------------------------|
| pubgas.ino    | Publisher code for Gas Detection     |
| pubtemp.ino   | Publisher code for Temperature       |
| subgas.ino    | Subscriber code for Gas Detection    |
| subtemp.ino   | Subscriber code for Temperature      |


### Full Documentation
See the full documentation at [Kitchen Safety Improvement Through an MQTT-Based Automation System](https://drive.google.com/file/d/1DNDnZ9h3SAyXrIKQbVtqkGSQnIINWQWs/view?usp=drive_link).