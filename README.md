# c_expression

c_expression: C语言表达式解析

## 使用方法

```shell
make                # 编译，第一次编译会有错误，再来一次即可
./c_expression      # 运行运算
make test           # 运行测试
./c_expression -vvv # 以DEBUG模式运行运算
```

c_expression的功能：
- 支持C语言的大部分运算符
- 拥有变量存储的功能
- 捕获除0异常
- ERROR/WARN/INFO/DEBUG，0~3级运行log输出

c_expression的使用方法：
```shell
calc > 1
INTEGER 1
statement 1
calc result: 1

calc > a=1
INTEGER 1
a = 1
statement 1
calc result: 1

calc > a+3
IDENTIFIER get a, val = 1
INTEGER 3
1 + 3
statement 4
calc result: 4

calc > a<<7
IDENTIFIER get a, val = 1
INTEGER 7
1 << 7
statement 128
calc result: 128

calc >
```

## 问题
- [x] 奇怪的空行
- [x] 颜色渲染
- [x] log等级
- [x] 支持C语言的大部分运算符
