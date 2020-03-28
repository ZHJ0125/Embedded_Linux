# 一、实现的功能
1. 循环显示"How are you ?"，循环次数由主函数参数决定
2. 函数调用时，使用if条件语句处理调用失败时的情况
3. 使用信号集函数sigprocmask将SIGINT信号屏蔽掉
4. 使用alarm函数定时5s
5. 使用sigpending函数收集未决状态的信号；使用sigismember函数判断SIGQUIT信号是否在屏蔽集中
6. 使用sigprocmask函数取消对SIGINT的屏蔽

# 二、程序代码
程序代码如图1所示：

![程序代码](https://github.com/ZHJ0125/Embedded_Linux/blob/master/Image/Homework/lessson10/lesson10_show.png)

图1. 程序代码    备用图片链接： https://zhj0125.oss-cn-shanghai.aliyuncs.com/Class/lesson10_show.png

# 三、程序测试
程序测试过程如图2所示：

![程序测试](https://github.com/ZHJ0125/Embedded_Linux/blob/master/Image/Homework/lessson10/lesson10_debug.png)

图2. 程序测试    备用图片链接： https://zhj0125.oss-cn-shanghai.aliyuncs.com/Class/lesson10_debug.png

# 四、程序执行过程分析
1. 执行主函数main，检查主函数参数个数
2. 使用主函数的参数作为循环次数，循环显示字符串"How are you ?"（我感觉以上内容跟信号处理没有多大关系）
3. 分别注册SIGALRM、SIGINT、SIGQUIT的信号处理函数
4. 使用sigprocmask函数将SIGINT添加到信号屏蔽集中
5. 使用alarm函数实现延时5秒的效果（测试中发现，SIGQUIT信号会将sleep函数打断，造成sleep函数失效，使用alarm函数可以避免该问题）。
6. 在5秒的延时过程中，SIGINT已经被屏蔽，这时需要测试人员手动产生SIGINT和SIGQUIT进行测试。通过测试结果可以看到，SIGQUIT信号会被函数处理，而SIGINT信号因为被屏蔽了，所以暂时不能被处理。
7. 延时结束后，使用sigpending函数收集处于未决状态的信号，紧接着使用sigismember函数判断SIGQUIT是否在未决信号集中。我们已经知道，被收集的未决信号肯定都是SIGINT信号而不会有SIGQUIT信号，因为SIGQUIT信号没有被屏蔽。
8. 接下来使用sigprocmask函数取消对SIGINT的屏蔽。此时被阻塞的SIGINT信号就会被信号处理函数处理掉，显示相应的提示语句。这里需要注意，多个SIGINT信号只被处理了一次。
9. 为了熟悉函数的使用，可以再用sigprocmask读取当前屏蔽集，用sigismember检测一下SIGINT信号是否已经解除屏蔽。

# 五、附录
1. 本程序GitHub地址： [https://github.com/ZHJ0125/Embedded_Linux/tree/master/Homework/lesson9](https://github.com/ZHJ0125/Embedded_Linux/tree/master/Homework/lesson9)
2. 参考资料：
[【Linux】信号的理解以及信号集处理函数的使用](https://blog.csdn.net/a1414345/article/details/71663379)
[信号处理中sleep函数失效的问题](https://bbs.csdn.net/topics/350214240)
