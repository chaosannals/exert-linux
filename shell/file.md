# 文件

```bash
# 修改文件所有者用户
# -c 显示更改
# -f 忽略错误
# -h 修复符号链接
# -v 显示详情
chown <user> /path/to/file

chown <user>:<group> /path/to/file

chown <user>:<group> -R /path/to/dir
```

```bash
# 直接指定权限值
chmod 777 /path/to/file

chmod -R 777 /path/to/dir

# a 等于 ugo
# u 用户
# g 组
# o 其他用户
# r 读
# w 写
# x 运行
# + 添加
# - 去除
# = 设置
# , 多项
# 都添加 r w x
chmod ugo+rwx /path/to/file

chmod ug=rwx,o-x /path/to/file

#清空 go 权限
chmod go= /path/to/file
```