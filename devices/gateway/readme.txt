COSSB Gateway is employed Mediatek MT7601 WiFi Chipset.
Operating System does not have that driver, so require setting up the driver.

1. download the driver for linux kernel 3.18.11+
(Linux cossb 3.18.11+ #781 PREEMPT Tue Apr 21 18:02:18 BST 2015 armv6l GNU/Linux)

2. tar zxf <source file>
3. ./install.sh

That's it.

or follow this steps.

$ wget https://dl.dropboxusercontent.com/u/80256631/mt7601-3.18.11-776.tar.gz
$ tar xzf mt7601-3.18.11-776.tar.gz
$ ./install.sh



If you want to connect to the secure network.
edit /etc/network/interface file.