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
# 查看内核参数，目录表示里面有子项，文件是配置内容
ls /proc/sys

# 打印 tcp 重用配置
cat /proc/sys/net/ipv4/tcp_tw_reuse

# 起效 /etc/sysctl.conf
/sbin/sysctl -p
```