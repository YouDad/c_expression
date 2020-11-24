[TOC]

# lex yacc 练习

练习仓库，lex是词法分析器，yacc是语法分析器。

## 使用方法

(cly: c++ lex yacc)
```shell
make       # 编译
./cly      # 运行运算
make test  # 运行测试
./cly -vvv # 以DEBUG模式运行运算
```

cly的功能：
- 支持C语言的大部分运算符
- 拥有变量存储的功能
- 捕获除0异常
- ERROR/WARN/INFO/DEBUG，0~3级运行log输出

cly的使用方法：
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
