# 程序说明

## 实现的功能

编程将小写字母转换成大写字母输出。要求：

- [x] 要转换的字符从键盘读入
- [x] 生成子进程，子进程的功能是输出大写的26个字母，exec系列函数加载子进程的功能
- [x] 从键盘读入的字符作为转换函数的参数
- [x] 输入特定字符可以结束转换过程

## 程序流程图

> 图片加载可能较慢，请耐心等待

![lesson7_flow_v2](https://github.com/ZHJ0125/Embedded_Linux/blob/master/Image/Homework/lesson7/lesson7_flow_v2.png)

## 程序执行过程

* 运行主函数`main`
* 开辟一段共享内存区，用来保存程序结束标志
* 创建一个子进程
* 子进程接收用户输入的字符串，对字符串进行裁剪等处理，如果遇到结束符#则将结束标志置位
* 子进程将处理完成的字符串，作为`function`功能函数的参数，通过`execl`函数实现`function`的调用
* `function`功能函数仅用于转换字符，不对字符串进行多余处理
* 父进程一直处于阻塞状态，直到子进程结束
* 子进程结束后，父进程通过判断结束标志位，决定用户是否需要进行下一次输入

## 测试过程

> 图片加载可能较慢，请耐心等待

![lesson7_test_v2](https://github.com/ZHJ0125/Embedded_Linux/blob/master/Image/Homework/lesson7/lesson7_test_v2.png)
