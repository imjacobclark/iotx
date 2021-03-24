# iotx

A small IoT Framework for NodeMCU (ESP8266) microcontroller. Built on top of Arduino libraries.

NodeMCU (ESP8266) is an open source platform capable of sending and reciving data via a the WiFi protocol. It has an internal antenna, can operate as both an access point or station, has 13 GPIO pins and is easilly programmable via the Arduino software.

I hope to develop this framework over time to support a common set of tasks useful to IoT applications, including:

* WiFi Management
* Over the air firmware updates
* Web/Mobile administration interface
* Support for common sensors (Barometer, Cameras, Sound, etc)

## Current Features

* Network Manager - Ability to a wireless access point
* File Reader - Read files burned onto ROM, useful for storing credentials 
* Hue Manager - Switch locally connected Hue lights on and off
* Button Input - Listen to tactile button events 

## Getting Started

Working with iotx is as simple as cloning this repository and modifying the `app.ino` file.

1. Setup your Arduino Environment for NodeMCU developmend as outlined [here](https://create.arduino.cc/projecthub/electropeak/getting-started-w-nodemcu-esp8266-on-arduino-ide-28184f)

2. Install the [Arduino plugin for VSCode](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino)

3. 

```shell 
git clone git@github.com:imjacobclark/iotx.git
cd iotx
code .
```

4. Within VSCode select the board (NodeMCU) and serial port

5. Extend `app.ino` as necessary and upload to your Arduino

## Network Information

iotx ships with optinionated network config by default:

```text
Static IP: 192.168.1.136
Gateway: 192.168.1.254
Subnet: 255.255.0.0
Primary DNS: 8.8.8.8
Secondary DNS: 8.8.4.4
```

These defaults can be modified in `src/NetworkManager.cpp`.

In future versions of iotx this will be configurable on first boot through 'hotspot' mode.