# 程序说明

1. 使用getuid和geteuid函数，分别获取进程的实际用户标识和有效用户标识号
2. 然后用setuid函数讲进程的标识号改变为用户输入的数字
3. 再次调用getuid和geteuid函数，获取新的用户标识号

## 程序测试

1. 如果是以普通用户权限执行的程序，则setuid不能成功调用

```shell
zhj@thinkpad-vmware:~/Linux/Exercise/ex5_11$ ./ex5_11 2
Before uid = 1000, euid = 1000
After uid = 1000, euid = 1000
ret = -1
```

2. 如果是以超级用户权限执行的程序，则setuid可以成功调用

```shell
zhj@thinkpad-vmware:~/Linux/Exercise/ex5_11$ sudo ./ex5_11 2
[sudo] password for zhj: 
Before uid = 0, euid = 0
After uid = 2, euid = 2
ret = 0
```
