# 用户权限相关

```bash
# 列举用户
cat /etc/passwd
# 列举组
cat /etc/group
```

```bash
# 添加用户
useradd myuser

# 添加用户和组
useradd -g mygroup myuser

#添加系统用户
useradd -r myuser

# 添加用户指定 home 目录
useradd -d /home/myuser myuser

# -u 指定ID
useradd myuser -u 4444

# 添加不能登录的用户
useradd -s /usr/sbin/nologin myuser
useradd -s /bin/false myuser
```

```bash
# 禁止登录
usermod -s /usr/sbin/nologin myuser

# 用户的 shell 被禁止
usermod -s /bin/false myuser

```

```bash
# 删除用户
# -h 查看说明
userdel myuser

# 连同 home 目录
userdel -f myuser
```


```bash
# 该命令做的事比较多，相当于封装了 useradd usermod groupadd 等命令
# 会创建 home 目录

# 创建 myuser 指定组 mygroup
adduser -g mygroup myuser

# 创建系统用户
adduser -r myuser

# 添加用户并指定 home 目录
adduser -d /home/myuser myuser
```

```bash
#
runuser -u www -s /bin/bash -c "pwd"
# 等同
runuser www -s /bin/bash -c "pwd"


```