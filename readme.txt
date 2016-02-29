基于4.3版本创建的仓库，用于学习目的。


todo：

coreboot+seabios+hd img(最小系统，演示启动过程)

coreboot+uboot


#  其它小笔记：

编译生成的build/config.h文件，有很多定义为0的宏，这些宏在代码中使用。
如CONFIG_CHROMEOS，即使使用其它板子，该宏也必须存在，否则编译失败