# Character driver practice

## Quick Start

### Build

```shell
make
```

### Install

```shell
$ sudo insmod charlkm.ko
$ lsmod | grep charlkm
charlkm                16384  0
$ ls -al /dev/charlkm
crw------- 1 root root 511, 0  4月  5 18:32 /dev/charlkm
$ sudo dmesg  | grep CHARLKM
[54436.595307] [CHARLKM] Initializing the charlkm
[54436.595314] [CHARLKM] Current major number: 510
[54436.595337] [CHARLKM] Device class registered
[54436.595389] [CHARLKM] Device registered
$ modinfo charlkm.ko
filename:       /home/zonda/Projects/lkm/charlkm/charlkm.ko
version:        0.1
description:    Simple character device driver for LKM
author:         Zonda Yang
license:        GPL
srcversion:     BDC7518A0BD180D5C604E85
depends:
retpoline:      Y
name:           charlkm
vermagic:       5.17.0-1-MANJARO SMP preempt mod_unload
```

### Client

```shell
$ sudo ./client
===== Character driver client =====
Enter string to send to the character driver:
test data
Ready send [test data] to character driver
Press ENTER to read message from character driver

Ready read message from character driver
Read message [test data(9 letters)]
Bye!!
$ sudo dmesg  | grep CHARLKM
[54436.595307] [CHARLKM] Initializing the charlkm
[54436.595314] [CHARLKM] Current major number: 510
[54436.595337] [CHARLKM] Device class registered
[54436.595389] [CHARLKM] Device registered
[54441.034206] [CHARLKM] Device has been opened 1 times
[54443.469691] [CHARLKM] Received 9 characters from the user
[54444.367787] [CHARLKM] Sent 20 characters to the user
[54444.368129] [CHARLKM] Device closed
```

### Remove

```shell
$ sudo rmmod charlkm
$ sudo dmesg  | grep CHARLKM
[54436.595307] [CHARLKM] Initializing the charlkm
[54436.595314] [CHARLKM] Current major number: 510
[54436.595337] [CHARLKM] Device class registered
[54436.595389] [CHARLKM] Device registered
[54441.034206] [CHARLKM] Device has been opened 1 times
[54443.469691] [CHARLKM] Received 9 characters from the user
[54444.367787] [CHARLKM] Sent 20 characters to the user
[54444.368129] [CHARLKM] Device closed
[54475.249275] [CHARLKM] Byebye
```

## Reference

[Writing a Linux Kernel Module — Part 2: A Character Device](http://derekmolloy.ie/writing-a-linux-kernel-module-part-2-a-character-device/)
[Crash when trying to access const char* buffer](https://stackoverflow.com/questions/45978645/crash-when-trying-to-access-const-char-buffer)