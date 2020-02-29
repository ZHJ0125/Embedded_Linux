> 说明：之前Linux我们写过[类似的程序](https://github.com/ZHJ0125/Linux_Class/tree/master/lesson10)，本程序在之前程序的基础上，删改了部分功能

# 一、实现的功能

1. 随机生成学生的姓名(英文姓名,首字母大写)、成绩(要求成绩<60和成绩>90的学生不多于总人数的10%)
2. 按序生成学生的学号(1~n)
3. 计算总成绩、平均成绩，计算学生的排名
4. 按学生成绩升序显示学生数据
5. 按学号将学生信息记录在cj.txt文件中
6. 记录最近一次保存数据的时间

主函数如图1所示，文件写入过程如图2所示：
![lesson6_show1](https://zhj0125.oss-cn-shanghai.aliyuncs.com/Class/lesson6_show1.png)
图1.主函数

![lesson6_show2](https://zhj0125.oss-cn-shanghai.aliyuncs.com/Class/lesson6_show2.png)
图2.文件写入函数

# 二、功能测试

1. 随机生成学生数据，计算总成绩等信息并按名次显示在屏幕
2. 数据保存至cj.txt文件中，使用cat命令查看
3. 改变随机生成的学生人数

测试过程如图3所示：
![lesson6_test](https://zhj0125.oss-cn-shanghai.aliyuncs.com/Class/lesson6_test.jpg)
图3.功能测试