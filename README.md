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
[37348.419226] [CHARLKM] Initializing the charlkm
[37348.419235] [CHARLKM] Current major number: 511
[37348.419280] [CHARLKM] Device class registered
[37348.419379] [CHARLKM] Device registered
```

### Remove

```shell
$ sudo rmmod charlkm
$ sudo dmesg  | grep CHARLKM
[37348.419226] [CHARLKM] Initializing the charlkm
[37348.419235] [CHARLKM] Current major number: 511
[37348.419280] [CHARLKM] Device class registered
[37348.419379] [CHARLKM] Device registered
[37510.486935] [CHARLKM] Byebye

```

## Reference

[Writing a Linux Kernel Module — Part 2: A Character Device](http://derekmolloy.ie/writing-a-linux-kernel-module-part-2-a-character-device/)