# 程序说明

##　实现的功能

1. 实现一个简单的仿Linux Shell的程序
2. 提交命令的参数最多为８个
3. 可以选择后台和前台执行
4. 一行命令中若同时有多个命令，则使用分号隔开
5. readcmd函数用来读取用户输入的命令，统计命令个数
6. docommand函数用来逐条处理命令，调用exec族函数执行命令

## 程序细节理解

### readcmd函数

用来读取用户输入的命令。各个命令之间以";"分隔，将命令保存在cmdbuf二维数组中，每个命令以'\0'结尾。

### docommand函数

首先逐条处理每一个指令，将处理后的指令保存在args中。

注意：*arglp指向了argsp，然后argsp指向了args，args用来存放每条数据；argl相当于argsp

```markdown
`;`  -->  作为每条命令的分隔符
`&`  -->  作为后台执行的标志
`\0` -->  作为命令的终止符
```

本程序的难点在于命令字符串的处理，`但这并不是程序的重点`

`程序的重点是fork、exec和setpgrp函数的使用`
