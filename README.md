[TOC]

# lex yacc 练习

练习仓库，lex是词法分析器，yacc是语法分析器。

## 使用方法

(cly: c++ lex yacc)
```shell
make     # 编译
./cly    # 运行，四则运算
```

cly的功能：
- 带括号的四则运算
- 拥有变量存储的功能
- 捕获除0异常

cly的使用方法：
```shell
calc > 1+1*4
yacc.y, 64: 1
yacc.y, 64: 1
yacc.y, 64: 4
yacc.y, 43: 1 * 4

yacc.y, 35: 1 + 4
yacc.y, 30: statement 5
yacc.y, 22: over  (0)
calc > a=3
yacc.y, 64: 3

yacc.y, 27: a = 3
yacc.y, 22: over a (3)
calc > b=a/2
yacc.y, 68: IDENTIFIER a 3
yacc.y, 64: 2
yacc.y, 52: 3 / 2

yacc.y, 27: b = 1
yacc.y, 22: over b (1)
calc > b * (9 ) / 2 - 7
yacc.y, 68: IDENTIFIER b 1
yacc.y, 64: 9
yacc.y, 60: ( 9 )
yacc.y, 43: 1 * 9
yacc.y, 64: 2
yacc.y, 52: 9 / 2
yacc.y, 64: 7

yacc.y, 39: 4 - 7
yacc.y, 30: statement -3
yacc.y, 22: over b (1)
calc > c=d+1
yacc.y, 68: IDENTIFIER d 0
yacc.y, 64: 1

yacc.y, 35: 0 + 1
yacc.y, 27: c = 1
yacc.y, 22: over c (1)
calc > d

yacc.y, 68: IDENTIFIER d 0
yacc.y, 30: statement 0
yacc.y, 22: over d (0)
calc > (a+b)/(c*d)
yacc.y, 68: IDENTIFIER a 3
yacc.y, 68: IDENTIFIER b 1
yacc.y, 35: 3 + 1
yacc.y, 60: ( 4 )
yacc.y, 68: IDENTIFIER c 1
yacc.y, 68: IDENTIFIER d 0
yacc.y, 43: 1 * 0
yacc.y, 60: ( 0 )
yacc.y, 47: div 0 error
yacc.y, 52: 4 / 0

yacc.y, 30: statement 0
yacc.y, 22: over d (0)
calc >
```

## 问题
- [x] 奇怪的空行
- [x] 颜色渲染
- [x] log等级
- [x] 支持C语言的大部分运算符
