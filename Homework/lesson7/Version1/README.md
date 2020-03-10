# 程序说明

## 实现的功能

编程将小写字母转换成大写字母输出。要求：

- [x] 要转换的字符从键盘读入
- [x] 生成子进程，子进程的功能是输出大写的26个字母，exec系列函数加载子进程的功能
- [ ] 从键盘读入的字符作为转换函数的参数
- [x] 输入特定字符可以结束转换过程

## 程序流程图

> 图片加载可能较慢，请耐心等待

![lesson7_flow_v1](https://github.com/ZHJ0125/Embedded_Linux/blob/master/Image/Homework/lesson7/lesson7_flow_v1.png)

## 程序执行过程

* 运行主函数`main`
* 创建一个子进程
* 子进程调用功能函数`function`，同时父进程阻塞，等待子进程结束
* 被调用的`function`程序，用来接收用户输入的字符串，对字符串进行裁剪后，将其转换为大写字符输出
* 调用结束后，主程序`main`结束

## 测试过程

> 图片加载可能较慢，请耐心等待

![lesson7_flow_v1](https://github.com/ZHJ0125/Embedded_Linux/blob/master/Image/Homework/lesson7/lesson7_test_v1.png)
