# linux 服务

## systemctl service

配置文件目录：

- 默认路径（红帽建议不要改这个目录下的）： /usr/lib/systemd/system/
- 路径（后添加的放到这个目录，通过特殊的处理，可以影响到默认路径的配置）：/etc/systemd/system/

### 配置简介

```conf
# 以下以 sshd 配置做示例
[Unit] # systemd 的服务单元的配置，包括相关性的依赖。
# 描述
Description=OpenSSH server daemon
After=network.target sshd-keygen.service
Wants=sshd-keygen.service

[Service] # 服务相关的配置
# 启动方式：
# simple 默认值 
# forking
# oneshot
# dbus
# idle
Type=simple

# 
EnvironmentFile=/etc/sysconfig/sshd
# 开始命令
ExecStart=/usr/sbin/sshd -D $OPTIONS
# 重载命令
ExecReload=/bin/kill -HUP $MAINPID

# 关闭模式
# process 只关闭主进程
# control-group 连同生成的都杀死
# none 不会执行关闭，有点可怕。
KillMode=process

# 重启配置
# 鸟哥说是 1  或者 0 ，布尔值。
# 阮一峰的
; no（默认值）：退出后不会重启
; on-success：只有正常退出时（退出状态码为0），才会重启
; on-failure：非正常退出时（退出状态码非0），包括被信号终止和超时，才会重启
; on-abnormal：只有被信号终止和超时，才会重启
; on-abort：只有在收到没有捕捉到的信号终止时，才会重启
; on-watchdog：超时退出，才会重启
; always：不管是什么退出原因，总是重启
Restart=on-failure

RestartSec=42s

[Install] # 这个指 服务单元被安装的配置
# 挂载在哪个 target
WantedBy=multi-user.target
```

注： 有什么问题，参考下原有的服务配置文件。

### 覆盖 /usr/lib/systemd/system/ 下原有的服务

对于 /usr/lib/systemd/system/aaa.service 做出以下操作可改变原有行为。

- /etc/systemd/system/aaa.service.d/custom.conf：累加其他设置
- /etc/systemd/system/aaa.service.wants/*：目录内必须为链接文件，最好加上这些服务（弱依赖，有就开启）
- /etc/systemd/system/vsftpd.service.requires/*：目录内必须为链接文件，强依赖，表示事先这些服务必须启动。


## 旧式 service

配置文件目录： /etc/init.d/

```bash
service aaa.service start
```

