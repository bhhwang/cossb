# cossb [![Build Status](https://travis-ci.org/bhhwang/cossb.svg)](https://travis-ci.org/bhhwang/cossb)
Component-based Open Simple Service Broker & Framework

* Notice : This source code will be dynamically updated by releasing version 0.1. (now 0.0.1)
 

Features
===============
1. IoT(Internet of Things) software framework for Robotic services.
2. Service components can be downloaded/installed/uninstalled/updated dynamically responding to what devices have services in same network environment. Thus, our goal is that any services can be changed dynamically with no user or supervisor intervention. (Except the initial setting up).
3. Fast by using C/C++. Lesser computational power might be required under the same condition. You can obtain more advantages for the device form-factor, budget and so on..
4. loose-coupled with other services by Service Broker. This gives advantages like a service re-configuration or re-combination)
5. Not only for High performance computing machine(like a PC), It is going for the cheap embedded hardware devices like Raspberry Pi, Odroid..

Dependency
===============
* libtinyxml2 (required)
* libpopt (required)
* libboost [thread, mutex, posix_time..] (required)
* [google test framework 1.7.0](http://code.google.com/p/googletest/downloads/list) (only for test, optional)
* [Doxygen](http://www.doxygen.org) (for auto-documentation / optional)
  - Graphviz (for doxygen, optional)
* [avahi-daemon](http://avahi.org/) (only for compzeroconf component, optional)
* libmicrohttpd (only for comphttpserver component, optional)
* json serialization/deserialization for C++ [json](https://github.com/nlohmann/json)



Getting Started
===============
* If you want to test all codes, Google Test Framework installation should be installed. (Use gtest_setup.sh)
* All supported utilities cannot be executed directly. it runs as a shared library.

COSSB Usage
-------
1. Edit manifest.xml

Manifest.xml file contained all information about running environments like below.
You should edit just <required> tags, then the COSSB components surrounding <required> tag will be loaded. 

```
<?xml version="1.0" encoding="utf-8"?>
<manifest>
	<!-- product information (IMPORTANT section) -->
	<product>
		<serial>NSGW00000000FFFFFFFFFFFF</serial>
		<manufacturer>Nsynapse Inc.</manufacturer>
		<license>cdefabcd-cdefabcd-cdefabcd-cdefabcd</license>
		<hostname>cossbgw.local</hostname>
	</product>
	<!-- accessible repository server address -->
	<repository>
		<uri></uri>
	</repository>
	<!-- required component cannot be stopped by user -->
	<!-- required library for advanced user or our support -->
	<required type="component" for="service">compzeroconf</required>
	<required type="component" for="service">messagepub</required>
	<required type="library" for="log">libcblog.so</required>
	<!-- do not edit this path -->
	<property>
		<path name="home">./cossb_home/</path>
		<path name="include">./include/</path>
		<path name="component">./component/</path>
		<path name="library">./library/</path>
	</property>
	
</manifest>
```

2. Just run with manifest

COSSB will find and load manifest.xml file at first when gives 'run' option.

```
$ ./cossb --run
```

COSSB Utility Usage
-------
1. createcomp (Not support yet completely)

This utility generates empty component class and its default profile into the own directory. Target directory will be created as 'CURRENT_DIRECTORY/COMPONENT_PATH/YOUR_CLASSNAME'. Note that this utility requires root permission to create directories.
```
$ sudo ./cossb --utility createcomp <your component class name>
```


2. find (Not support yet)
This utility tries to find devices, services. Summarized result will be presented.
```
$ sudo ./cossb --utility find --[device|service] <specific name>
```


License
===============
You can freely use, modify, redistribute this source code under the 3-clause BSD License.
Some parts of the components and core libraries use open source code under the other license(LGPL, MIT..).
