-------------------------------------------------------------------------------
Late Lee readme
coreboot master repository from https://github.com/coreboot/coreboot

----------------------------------------

测试系统：
Ubuntu 14.04.1
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
一、coreboot的编译
1、安装编译环境必备工具：
m4、bison、flex：
$ sudo apt-get install m4 bison flex

安装iasl(在coreboot源码目录中输入)：
$ make iasl

----------------------------------------

2、配置：
$ make menuconfig

在通用设置中，要选择“Allow building with any toolchain”，否则要make crossgcc来新建一个交叉编译器。
General setup  --->
[*] Allow building with any toolchain

主板使用模拟器（QEMU）
Mainboard  --->
Mainboard vendor (Emulation)  --->
Mainboard model (QEMU x86 i440fx/piix4 (aka qemu -M pc))  ---> //使用x86平台的
ROM chip size (8192 KB (8 MB))  --->  // flash大小根据实际情况选择，一般的主板为8MiB

Playload选择SeaBIOS(：
Payload  --->  
 Add a payload (SeaBIOS)  --->
 SeaBIOS version (1.9.0)  --->

注：本仓库中已经包含了SeaBIOS源码，并包含了qemu_x86的配置文件：config_qemu_x86，直接加载即可使用

其它默认。

----------------------------------------

3、编译：
$ make

在此过程，会clone 3rdparty目录仓库，另外会下载用户选择的payload，然后一起编译。
注；编译需要使用vboot，如不想在make时clone，也可以解压vboot.tar.bz2

最终生成：
build/coreboot.rom

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

二、x86 QEMU模拟环境测试
1、安装qemu模拟器（只针对x86）：
$ sudo apt-get install qemu-system-x86
注：qemu还有其它平台的，如下：
* qemu-system-arm
* qemu-system-mips
* qemu-system-misc
* qemu-system-ppc
* qemu-system-sparc
* qemu-system-x86

不使用系统仅启动BIOS的命令如下：
$ qemu-system-i386 -nographic -bios coreboot/build/coreboot.rom

注：由于没有系统，启动后即“死机”，需要关闭终端才可退出。

使用系统仅启动BIOS的命令如下：
$ qemu-system-i386 -nographic -bios coreboot/build/coreboot.rom -hda disk.img

注：disk.img必须是可启动的磁盘镜像