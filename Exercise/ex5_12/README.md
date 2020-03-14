# 程序说明

1. 调用getpid函数获取当前进程的标识号
2. 将该标识号追加作为文件名创建新文件
3. 在新文件中写入`TMP file`，然后关闭文件

## 测序测试

1. 执行程序，会提示getpid()函数调用成功
2. 会在当前目录下创建`tmp.xxx`文件
3. 其中的`XXX`是进程的标识号
4. 再次执行程序，会创建不同的文件

```shell
zhj@thinkpad-vmware:~/Linux/Exercise/ex5_12$ gcc ex5_12.c -o ex5_12
zhj@thinkpad-vmware:~/Linux/Exercise/ex5_12$ ./ex5_12 
call getpid() success
zhj@thinkpad-vmware:~/Linux/Exercise/ex5_12$ cat tmp.3594 
TMP filezhj@thinkpad-vmware:~/Linux/Exercise/ex5_12$ 
zhj@thinkpad-vmware:~/Linux/Exercise/ex5_12$ ./ex5_12 call getpid() success
zhj@thinkpad-vmware:~/Linux/Exercise/ex5_12$ lsex5_12  ex5_12.c  tmp.3594  tmp.3609
zhj@thinkpad-vmware:~/Linux/Exercise/ex5_12$ cat tmp.3609 
TMP filezhj@thinkpad-vmware:~/Linux/Exercise/ex5_12$ 
zhj@thinkpad-vmware:~/Linux/Exercise/ex5_12$ 
```
