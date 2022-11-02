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

注：清掉 out 后要修改 CMakeLists.txt （随便换个行，写个#都可以） 让 vs 重新生成项目缓存。
