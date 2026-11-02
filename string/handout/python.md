# Python IDLE 数学计算速查手册

> **适用对象**：需要用 Python 快速完成各类数学计算的学生、工程师、科研人员  
> **适用环境**：Python 3.8+ 自带的 IDLE（Shell 交互窗口）  
> **版本**：v1.0　　**整理日期**：2026-11-01

---

## 目录

1. [直接输入表达式](#1-直接输入表达式)
2. [math 模块：工程计算主力](#2-math-模块工程计算主力)
3. [精度问题：decimal 与 fractions](#3-精度问题decimal-与-fractions)
4. [符号计算与矩阵：sympy 与 numpy](#4-符号计算与矩阵sympy-与-numpy)
5. [IDLE 快捷键：提速的关键](#5-idle-快捷键提速的关键)
6. [把常用公式做成模板：calc.py](#6-把常用公式做成模板calcpy)
7. [常见坑与提示](#7-常见坑与提示)
8. [附录 A：math 函数速查表](#附录-amath-函数速查表)
9. [附录 B：打印与排版建议](#附录-b打印与排版建议)

---

## 1. 直接输入表达式

IDLE 的 `>>>` 提示符就是 Python 解释器，输入表达式按回车即刻出结果。

### 1.1 基本运算

```python
>>> 2 + 3 * 4
14
>>> (1 + 2) ** 3 / 4
6.75
>>> 2 ** 100
1267650600228229401496703205376
>>> 10 % 3, 10 // 3, -7 // 2
(1, 3, -4)
```

| 运算符 | 含义 | 示例 | 结果 |
|--------|------|------|------|
| `+` `-` `*` `/` | 四则运算 | `7 / 2` | `3.5` |
| `//` | 整除（向下取整） | `-7 // 2` | `-4` |
| `%` | 取余 | `10 % 3` | `1` |
| `**` | 乘方 | `2 ** 10` | `1024` |

### 1.2 实用技巧

```python
>>> _              # 下划线 = 上一个结果
>>> _ * 2          # 继续基于上次结果计算
>>> 1.6e-19        # 科学计数法
>>> 3e8
```

**要点**
- Python 整数**自动高精度**，不会溢出，`2 ** 1000` 也能精确算。
- 幂运算优先级高于乘除，高于加减；不确定就加括号。

---

## 2. math 模块：工程计算主力

### 2.1 导入方式

```python
>>> import math                    # 推荐：命名空间清晰
>>> math.sqrt(2)
1.4142135623730951

>>> from math import *             # 偷懒写法：少打 math.
>>> sqrt(2), pi, cos(0)
(1.4142135623730951, 3.141592653589793, 1.0)
```

> ⚠️ `from math import *` 会覆盖同名变量（如你自己定义的 `e`），
> 一般脚本里推荐 `import math`，临时手算用 `*` 更省事。

### 2.2 常用示例

```python
>>> math.pi, math.e
(3.141592653589793, 2.718281828459045)

>>> math.sin(math.pi / 6)
0.49999999999999994          # 注意这是浮点误差，理论值 0.5

>>> math.log(100, 10)        # 以 10 为底
2.0
>>> math.log(math.e)         # 自然对数
1.0
>>> math.log2(1024)
10.0

>>> math.factorial(20)
2432902008176640000
>>> math.gcd(48, 18)
6
>>> math.hypot(3, 4)         # 勾股定理 √(3²+4²)
5.0

>>> math.degrees(math.pi), math.radians(180)
(180.0, 3.141592653589793)
```

### 2.3 三角函数务必注意角度单位

```python
>>> math.sin(30)             # ❌ 30 被当成 30 弧度
-0.9880316240928618
>>> math.sin(math.radians(30))   # ✅ 先转弧度
0.49999999999999994
```

---

## 3. 精度问题：decimal 与 fractions

### 3.1 浮点误差从哪来

```python
>>> 0.1 + 0.2
0.30000000000000004
```

二进制无法精确表示 0.1，这是**所有语言共有**的现象，不是 Python 的 bug。需要精确时换类型。

### 3.2 decimal：定点小数（财务、高精度）

```python
>>> from decimal import Decimal, getcontext
>>> getcontext().prec = 50           # 设定有效位数
>>> Decimal(1) / Decimal(3)
Decimal('0.33333333333333333333333333333333333333333333333333')

>>> Decimal('0.1') + Decimal('0.2')  # 用字符串构造，避免先变成 float
Decimal('0.3')
```

### 3.3 fractions：精确有理数（分数运算）

```python
>>> from fractions import Fraction
>>> Fraction(1, 3) + Fraction(1, 6)
Fraction(1, 2)
>>> Fraction('0.25')
Fraction(1, 4)
>>> Fraction(1, 3) * 3
Fraction(1, 1)
```

### 3.4 复数

```python
>>> import cmath
>>> cmath.sqrt(-1)
1j
>>> (1 + 2j) * (3 - 1j)
(5+5j)
>>> abs(3 + 4j)          # 模长
5.0
```

---

## 4. 符号计算与矩阵：sympy 与 numpy

### 4.1 sympy：代数、方程、微积分（需 `pip install sympy`）

```python
>>> from sympy import *
>>> x, y = symbols('x y')

>>> expand((x + y)**2)
x**2 + 2*x*y + y**2

>>> factor(x**2 - 1)
(x - 1)*(x + 1)

>>> solve(x**2 - 4, x)
[-2, 2]

>>> diff(sin(x)*exp(x), x)          # 求导
exp(x)*sin(x) + exp(x)*cos(x)

>>> integrate(x**2, (x, 0, 1))      # 定积分
1/3

>>> limit(sin(x)/x, x, 0)           # 极限
1
```

### 4.2 numpy：矩阵与数值线性代数（需 `pip install numpy`）

```python
>>> import numpy as np
>>> A = np.array([[1, 2], [3, 4]])

>>> np.linalg.det(A)
-2.0000000000000004

>>> np.linalg.inv(A)
array([[-2. ,  1. ],
       [ 1.5, -0.5]])

>>> np.linalg.eigvals(A)            # 特征值
array([-0.37228132,  5.37228132])
```

---

## 5. IDLE 快捷键：提速的关键

| 快捷键 | 作用 |
|--------|------|
| `Alt + P` / `Alt + N` | 调出上一条 / 下一条历史输入 |
| `↑` / `↓` | 同上（光标在行首时） |
| `Alt + /` | 按上下文循环补全单词 |
| `Ctrl + ↑` / `Ctrl + ↓` | 补全上一条 / 下一条历史 |
| `Ctrl + C` | 中断卡住的命令（如死循环） |
| `Ctrl + U` | 清空当前行 |
| `F5` | 运行当前编辑的脚本 |

**最实用的场景**：长公式打错一个字符 —— `Alt + P` 调回，在行内改完回车，无需重打。

---

## 6. 把常用公式做成模板：calc.py

在 IDLE 中 `File → New File` 新建文件，粘贴以下内容，保存为 `calc.py`，按 `F5` 运行。
之后在 Shell 里可直接调用这些函数。

```python
# calc.py —— 在 IDLE 中 F5 运行后，Shell 里即可使用下列函数
import math
from math import sin, cos, tan, sqrt, pi, e, log, exp


def quad(a, b, c):
    """求解 ax² + bx + c = 0"""
    d = b*b - 4*a*c
    if d < 0:
        return "无实根"
    r = math.sqrt(d)
    return ((-b + r) / (2*a), (-b - r) / (2*a))


def dist(x1, y1, x2, y2):
    """两点间距离"""
    return math.hypot(x2 - x1, y2 - y1)


def mean(*xs):
    """算术平均"""
    return sum(xs) / len(xs)


def std(*xs):
    """总体标准差"""
    m = mean(*xs)
    return math.sqrt(sum((x - m) ** 2 for x in xs) / len(xs))


print("calc.py 已加载：quad, dist, mean, std")
```

运行后即可使用：

```python
>>> quad(1, -5, 6)
(3.0, 2.0)
>>> dist(0, 0, 3, 4)
5.0
>>> mean(1, 2, 3, 4, 5)
3.0
>>> std(1, 2, 3, 4, 5)
1.4142135623730951
```

> 💡 **扩展思路**：把你自己领域常用的公式（如面积体积、复利、单位换算）
> 都写进 `calc.py`，一次编写，长期复用。

---

## 7. 常见坑与提示

**① Shell 不支持多行粘贴**
IDLE Shell 会逐行执行粘贴内容，多行逻辑（`for`、`if`、`def`）请
`File → New File` 写脚本再 `F5`。

**② Shell 里只能写单行函数**
用 `;` 分隔简单语句：
```python
>>> a = 3; b = 4; print((a*a + b*b) ** 0.5)
5.0
```
（上面第 6 节的 `def` 之所以能写，是因为 IDLE 在 `def ...:` 回车后
会自动进入缩进续行模式，输完按两次回车结束。）

**③ 输出太长被截断**
调大缓存行数：`Options → Configure IDLE → Shell/Ed`，或改用脚本 `print`。

**④ 想查某个函数的用法**
```python
>>> help(math.log)
```

**⑤ 浮点比较别用 `==`**
```python
>>> math.isclose(0.1 + 0.2, 0.3)     # ✅
True
```

**⑥ 大整数运算慢于浮点**
`2 ** 10**7` 这类运算会耗时数秒甚至更久，注意别误以为卡死。

---

## 附录 A：math 函数速查表

### 常数

| 名称 | 含义 | 值 |
|------|------|-----|
| `math.pi` | 圆周率 π | 3.141592653589793 |
| `math.e` | 自然常数 e | 2.718281828459045 |
| `math.tau` | 2π | 6.283185307179586 |
| `math.inf` | 无穷大 | — |
| `math.nan` | 非数 | — |

### 幂与根

| 函数 | 说明 |
|------|------|
| `sqrt(x)` | 平方根 |
| `isqrt(n)` | 整数平方根（向下取整，整数专用） |
| `cbrt(x)` | 立方根（Python 3.11+） |
| `pow(x, y)` | 幂（等价 `x ** y`） |

### 对数与指数

| 函数 | 说明 |
|------|------|
| `log(x)` | 自然对数 ln x |
| `log(x, b)` | 以 b 为底 |
| `log10(x)` | 常用对数 |
| `log2(x)` | 以 2 为底 |
| `exp(x)` | e 的 x 次方 |

### 三角函数

| 函数 | 说明 |
|------|------|
| `sin(x)` `cos(x)` `tan(x)` | 三角（**弧度制**） |
| `asin(x)` `acos(x)` `atan(x)` | 反三角 |
| `atan2(y, x)` | 方位角，自动处理象限 |
| `degrees(x)` `radians(x)` | 弧度 ↔ 角度 |
| `sinh` `cosh` `tanh` | 双曲函数 |

### 取整与数值

| 函数 | 说明 |
|------|------|
| `ceil(x)` | 向上取整 |
| `floor(x)` | 向下取整 |
| `trunc(x)` | 向零截断 |
| `fabs(x)` | 绝对值（返回 float） |
| `abs(x)` | 内置绝对值（保持类型） |

### 组合与数论

| 函数 | 说明 |
|------|------|
| `factorial(n)` | 阶乘 |
| `comb(n, k)` | 组合数 C(n, k)（3.8+） |
| `perm(n, k)` | 排列数（3.8+） |
| `gcd(*ints)` | 最大公约数 |
| `lcm(*ints)` | 最小公倍数（3.9+） |

---