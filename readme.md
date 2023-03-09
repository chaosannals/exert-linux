# exert-linux

## 命令

```bash
# 查看谁登录了系统
who

# 查看进程打开文件
ls -l /proc/<process_id>/fd

# 查看文件相关进程
lsof <path_to_file_or_dir>

# 清空命令记录
history -c

# 查看进程树
pstree
```

```bash
# 列举磁盘
fdisk -l

# 加 i 查看索引信息
ls -li 
```

## 内核参数修改

```bash
# 查看内核参数（方便手工查看）
/sbin/sysctl -a

# 查看内核参数，目录表示里面有子项，文件是配置内容
# （方便命令行直接获取值）
ls /proc/sys

# 以下2个 tcp_tw_* 配置最好是关闭的，不然用户如果内网用户数太多，很容易端口号爆了。导致无法申请端口号而发不出请求。

# 打印 tcp 重用配置
cat /proc/sys/net/ipv4/tcp_tw_reuse

# 查看 快速回收，一般这个最好查出来是关闭的。
cat /proc/sys/net/ipv4/tcp_tw_recycle

# 起效 /etc/sysctl.conf
/sbin/sysctl -p

# 修改 /etc/sysctl.conf 起效后是永久的
# 通过以下命令修改是临时的
/sbin/sysctl -w net.ipv4.tcp_tw_reuse=1
```