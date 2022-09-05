# lib demo

```bash
# 查看导出函数
nm -D libdlibone.so

# 查看导出函数
objdump -tT libdlibone.so
```

```bash
# 编译 dlibone
gcc -shared -fPIC -o libdlibone.so dlibone/main.cpp

# 编译 cmdone
g++ cmdone/main.cpp  -o cmdone.out -L. -ldlibone -ldl
```
