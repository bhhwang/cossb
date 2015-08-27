# cossb [![Build Status](https://travis-ci.org/bhhwang/cossb.svg)](https://travis-ci.org/bhhwang/cossb)
Component-based Open Simple Service Broker & Framework

Features
===============
1. Service components can be downloaded/installed/uninstalled/updated dynamically responding to what devices have services in same network environment. Thus, our goal is that any services can be changed dynamically with no user or supervisor intervention. (Except the initial setting up).
2. Fast by using C/C++. Lesser computational power might be required under the same condition. You can obtain more advantages for the device form-factor, budget and so on..
3. loose-coupled with other services by Service Broker. This gives advantages like a service re-configuration or re-combination)
4. Not only for High performance computing machine(like a PC).  

Dependecy
===============
* libtinyxml2
* libpopt
* libboost (thread, mutex, posix_time..)
* [google test framework 1.7.0](http://code.google.com/p/googletest/downloads/list)



Getting Started
===============
* If you want to test all code, requires installation Google Test Framework

License
===============
You can freely use, modify, redistribute this source code under the BSD License.
