# 第 0 讲　字符串的基本模型与 Hash

> **课程定位**：面向已有基本编程、二分与数据结构基础，但**可能第一次系统接触字符串算法**的 ICPC / CCPC / OI 选手。我们不仅给出工具，还解释工具为什么能用。  
> **本讲目标**：学会把题意翻译成 Occurrence、LCP、子串相等、拼接等操作；理解多项式 Hash 的构造与局限；会选择 Hash、二分或数据结构处理典型题。  
> **阅读约定**：字符串从 **0** 开始编号，子串采用半开区间 $S[l,r)$（包含 $l$，不包含 $r$），长度为 $r-l$；$+$ 表示字符串拼接。Hash 相等通常只能作为**概率意义上的相等**。  
> **本讲不做的事**：不要求背诵全部代码，也不深入概率界的严格证明；但重要的定义、公式来历、单调性与变形都会说清楚。

## 0. 从问题出发：字符串题究竟在查询什么？

先观察两个很常见的问题：

- “`aba` 在 `ababa` 里出现了几次？”——我们要找的是**出现位置集合**。
- “从某两个位置开始，最多有多少个字符连续相同？”——我们要找的是**最长公共前缀 LCP**。

字符串题经常不是缺少算法，而是没有把题目的自然语言翻译成一个明确的操作。先认识下面这些对象，后面各章会不断重复使用。

| 对象 / 操作 | 用通俗的话说 | 典型问题 | 后续工具 |
|---|---|---|---|
| **Occurrence** | 模式串在哪里完整出现 | 出现次数、某个范围内的出现位置 | KMP、Z、ACAM、SA、SAM |
| **子串相等** | 两段连续字符是否完全一样 | 重复块、去重、动态比较 | Hash、SA + LCP |
| **LCP** | 两个字符串（或两个后缀）开头连续相同多长 | 字典序、周期、最长重叠 | Hash、SA + RMQ |
| **LCSuff** | 两段字符串结尾连续相同多长 | 重复结构向左延伸 | 反串上的 LCP |
| **字典序** | 像词典一样，谁排在前面 | 子串排序、第 $k$ 小子串 | LCP、SA |
| **Border / Period** | 前后缀相同 / 平移后重叠部分相同 | 循环节、重叠匹配 | KMP、Z、周期引理 |
| **Palindrome** | 从左往右、从右往左读都相同 | 区间回文、回文计数 | Hash、Manacher、PAM |
| **Subsequence** | 可以跳过字符，但保留先后顺序 | 贪心匹配、计数、LCS | Next 自动机、DP |

### 0.0 先分清前缀、后缀、子串、子序列

以 `abcde` 为例：

- **前缀（Prefix）**：从开头取一段，如 `abc`；
- **后缀（Suffix）**：从末尾取一段，如 `cde`；
- **子串（Substring）**：从中间取**连续**的一段，如 `bcd`；
- **子序列（Subsequence）**：可以跳着选，只需保持原来顺序，如 `ace`，但 `eca` 不是子序列。

在后面的几讲中，“能否快速比较两个子串”是主线；第 8 讲再专门研究**不连续**的子序列。若题目只说“模式串出现”，通常默认要求**连续**出现。

例如 `abcde` 的子串 `bcd` 写成 $S[1,4)$，因为下标为 $1,2,3$；右端点 $4$ 不包含在内。这种写法方便计算长度：$4-1=3$。

### 0.1 Occurrence：把“出现”变成一组位置

设文本串 $S$、模式串 $T$，$|T|=m$。我们用

$$
\operatorname{Occ}_S(T)=\{i\mid 0\le i\le |S|-m,\ S[i,i+m)=T\}
$$

表示 **$T$ 在 $S$ 中所有出现的起点**。

例如 $S=\texttt{ababa}$，$T=\texttt{aba}$：

```text
S 下标： 0 1 2 3 4
S      ： a b a b a
          a b a       第一次，从 0 开始
              a b a   第二次，从 2 开始
```

所以 $\operatorname{Occ}_S(T)=\{0,2\}$，出现次数为 $2$。

**注意这两次出现可以重叠。** 如果题目说“不能重叠”，那是另外加上的限制，不是 Occurrence 定义的一部分。

之后我们还会问：哪些出现位置落在给定范围内？一个子串出现了多少次？不同子串的出现位置集合是否相同？这些问题分别引向 KMP/Z、SA、SAM 等工具。

### 0.2 LCP：从两个开头向右看，能看多远？

对任意字符串 $A,B$，**最长公共前缀**（Longest Common Prefix）的长度记为

$$
\operatorname{LCP}(A,B)=\max\{k:A[0,k)=B[0,k)\}.
$$

例如

```text
A = a b c a x
B = a b c b y
    ↑ ↑ ↑ ×
```

开头的 `abc` 一样，第 4 个字符分别为 `a`、`b`，所以 $\operatorname{LCP}(A,B)=3$。

更常见的是**固定一个原串** $S$，询问从下标 $i,j$ 开始的两个后缀：

$$
\boxed{\operatorname{LCP}_S(i,j)=\operatorname{LCP}(S[i,n),S[j,n))}.
$$

不写下标 $S$ 时，就简记为 $\operatorname{LCP}(i,j)$。以后代码中的函数也统一叫 `lcp`。

例如 $S=\texttt{abacaba}$：

```text
从 0 开始：a b a c a b a
从 4 开始：a b a
            ↑ ↑ ↑
```

两个后缀共同的开头是 `aba`，因此 $\operatorname{LCP}_S(0,4)=3$。**只比较还在字符串范围内的字符**；较短后缀结束时就停止。

有时题目给的是两个有限子串 $S[l_1,r_1),S[l_2,r_2)$，而不是完整后缀。这时先求两个起点的 LCP，再截断：

$$
\boxed{\operatorname{LCP}(S[l_1,r_1),S[l_2,r_2))
=\min\bigl(\operatorname{LCP}_S(l_1,l_2),r_1-l_1,r_2-l_2\bigr).}
$$

**为什么需要取最小值？** 因为向右继续看时，不能越过这两个子串各自的右端点。

### 0.3 LCSuff：向左看，可以转成反串上的 LCP

我们用 **LCSuff** 表示“最长公共后缀”，避免和第 8 讲的**最长公共子序列 LCS**混淆。

例如 `xxabc` 与 `yabc` 的最长公共后缀是 `abc`，长度为 3。

“从结尾往左比较”不好复用前面的工具，但把两个串都反转后，原本的结尾就变成开头：

```text
原串：    x x a b c    与    y a b c
反转：    c b a x x    与    c b a y
          ↑ ↑ ↑
```

因此最长公共后缀可以用**反串上的 LCP**求得。

若 $R=\operatorname{reverse}(S)$，要比较两个前缀 $S[0,i)$、$S[0,j)$ 的公共后缀，则

$$
\boxed{\operatorname{LCSuff}_S(i,j)=\operatorname{LCP}_R(n-i,n-j).}
$$

这里 $i,j$ 是原串前缀的**右端点（开区间）**。例如 `ababa` 中 $S[0,3)=\texttt{aba}$ 与 $S[0,5)=\texttt{ababa}$，公共后缀是 `aba`，长度 3。

> **之后反复使用的两个接口**：`lcp(i,j)` 表示从两个位置向右的最长相等长度；在反串上做同样的 LCP，就能研究向左的相等长度。本讲用 Hash + 二分实现，后缀数组一章再介绍 SA + RMQ 实现。

## 1. 多项式 Hash：把字符拼成一个“数字”

### 1.1 为什么想到用进制数表示字符串？

我们已经知道，逐字符比较两个长子串可能要花 $O(n)$ 时间。如果有非常多次比较，希望给每一段字符串算一个很容易比较的“特征值”。

一个自然想法：把每个字符映射成数字，再把整个字符串当成进制数。为了方便理解，暂时约定 `a`→1、`b`→2、`c`→3，使用十进制底数 $B=10$。

```text
abc  ->  1 2 3  ->  123
abca ->  1 2 3 1 -> 1231
```

计算 `abc` 的“数字”就是：

$$
H(\texttt{abc})=1\cdot10^2+2\cdot10+3=123.
$$

如果已经算出了 `abc` 的值，末尾再添加 `a`，就相当于数字左移一位、在末尾填 1：

$$
H(\texttt{abca})=123\cdot10+1=1231.
$$

推广到任意底数 $B$、字符映射 $v(c)$：

$$
\boxed{H(S+c)=H(S)B+v(c).}
$$

对长度为 $n$ 的串，也可以一次性写成

$$
H(S)=\sum_{i=0}^{n-1}v(S_i)B^{n-1-i}.
$$

真正比赛里不会让数字无限变大：我们选择模数 $M$，**每一步都对 $M$ 取模**。于是两种不同的字符串可能得到相同的 Hash（碰撞），后面会专门说明。

> **小提醒**：`a`→1、$B=10$ 只是讲原理的玩具例子。真实模板会使用更合适的字符映射、随机底数以及两个大模数。不要把十进制例子误当成防碰撞的实现方案。

### 1.2 前缀 Hash：像前缀和一样求任意子串

先回忆数字数组的前缀和：要得到区间和，用“右端前缀和 − 左端前缀和”。字符串 Hash 也可以这么做，只是**前面的字符在数字中有位权**，所以减掉前缀之前还要乘一个 $B$ 的幂。

定义：

$$
\begin{aligned}
pow[k]&=B^k\bmod M,\\
h[0]&=0,\\
h[i+1]&=(h[i]B+v(S_i))\bmod M.
\end{aligned}
$$

仍以 $S=\texttt{abca}$、$B=10$ 为例，先不取模：

| $i$ | 前缀 $S[0,i)$ | $h[i]$ |
|---:|---|---:|
| 0 | 空串 | 0 |
| 1 | `a` | 1 |
| 2 | `ab` | 12 |
| 3 | `abc` | 123 |
| 4 | `abca` | 1231 |

现在要求中间的 `bc`，即 $S[1,3)$。`abc` 的 Hash 是 123，其中开头的 `a` 占了百位，减去 $1\times100$ 即可：

$$
H(S[1,3))=h[3]-h[1]\cdot10^2=123-100=23.
$$

为什么幂次是 $2$？因为要保留的 `bc` 长度是 $3-1=2$，左侧 `a` 在整个前缀中的贡献被整体向左推了两位。

一般地，$S[0,r)$ 可以看成 $S[0,l)$ 与 $S[l,r)$ 的拼接：

$$
h[r]=h[l]B^{r-l}+H(S[l,r))\pmod M.
$$

移项得到**本讲最重要的子串公式**：

$$
\boxed{H(S[l,r))=(h[r]-h[l]B^{r-l})\bmod M.}
$$

实际代码需要把减法结果修正到非负范围。预处理 $h$ 和 $pow$ 各需要 $O(n)$，以后取一个子串 Hash 只需 $O(1)$。

**这个公式为什么有用？** 如果比较 $S[100,500)$ 与 $S[700,1100)$，没必要看 400 个字符；只需要取出两个区间的 Hash 再比较。

### 1.3 不同位置的子串，可以直接比较 Hash

我们的定义始终把取出的子串当成一个**从第一位开始编码的新字符串**。

例如 `abcab` 中，位置 $0$ 的 `ab` 与位置 $3$ 的 `ab`，算出的子串 Hash 都是 $12$（玩具示例）。

因此：

$$
\boxed{\text{同长度且 Hash 相等}\ \Longrightarrow\ \text{很可能是同一个字符串}.}
$$

两个字符串分别预处理 Hash 后，也能直接比较各自子串，只要**字符编码、底数、模数完全一致**。

但要牢记：Hash 不同可以确定字符串不同；Hash 相同不能从数学上保证字符串相同。这一点与“用整数编号来唯一代表字符串”不同。

### 1.4 拼接公式：Hash 为什么能配合线段树？

现在不从完整字符串的某个区间取字符，而是把两段 $A,C$ 拼在一起。

例如 `ab` + `cab` = `abcab`。继续用 $B=10$、字母映射为 1、2、3：

$$
H(\texttt{ab})=12,\quad H(\texttt{cab})=312.
$$

要给左边的 `ab` 腾出右边 3 个字符的位置，就乘 $10^3$：

$$
H(\texttt{abcab})=12\cdot10^3+312=12312.
$$

一般公式：

$$
\boxed{H(A+C)=H(A)B^{|C|}+H(C)\pmod M.}
$$

这告诉我们：**合并两段时，不用知道段内每个字符，只需要长度和 Hash。**

因此一段字符串可以压缩成一组信息：

$$
\boxed{(len,hash).}
$$

- 两段合成一段：使用上面的公式。
- 多段合成一段：从左到右依次合并。
- 线段树父节点表示左右儿子的拼接：也使用同一个公式。

这就是 Hash 除了“比较子串”以外，最值得掌握的第二个用途。

## 2. 能调用的接口：C++20 双模数 Hash

以下模板强调**统一接口**：支持静态求子串 Hash、动态向尾部追加字符、不同对象比较、以及拼接 Hash。两个模数分别随机选择底数，降低实战中的碰撞风险；它仍然是概率算法。

```cpp
#include <bits/stdc++.h>
using namespace std;

struct PolyHash {
    using ll = long long;
    using H = pair<ll, ll>;
    static constexpr ll M1 = 1000000007LL;
    static constexpr ll M2 = 1000000009LL;

    inline static mt19937_64 rng{
        (uint64_t)chrono::steady_clock::now().time_since_epoch().count()
    };
    inline static const ll B1 = uniform_int_distribution<ll>(256, M1 - 2)(rng);
    inline static const ll B2 = uniform_int_distribution<ll>(256, M2 - 2)(rng);
    inline static vector<ll> p1{1}, p2{1};

    vector<ll> h1{0}, h2{0};

    static void ensure(int n) {
        while ((int)p1.size() <= n) {
            p1.push_back(p1.back() * B1 % M1);
            p2.push_back(p2.back() * B2 % M2);
        }
    }

    PolyHash() = default;
    PolyHash(const string& s) {
        for (unsigned char c : s) push(c);
    }

    int size() const { return (int)h1.size() - 1; }

    void push(unsigned char c) {
        ensure(size() + 1);
        ll x = (int)c + 1;
        h1.push_back((h1.back() * B1 + x) % M1);
        h2.push_back((h2.back() * B2 + x) % M2);
    }

    // [l, r)，0 <= l <= r <= size()
    H get(int l, int r) const {
        int k = r - l;
        ll x = (h1[r] - h1[l] * p1[k] % M1 + M1) % M1;
        ll y = (h2[r] - h2[l] * p2[k] % M2 + M2) % M2;
        return {x, y};
    }

    // 已知两段 Hash 与右段长度，求拼接 Hash
    static H concat(H left, H right, int right_len) {
        ensure(right_len);
        return {
            (left.first * p1[right_len] + right.first) % M1,
            (left.second * p2[right_len] + right.second) % M2
        };
    }
};
```

**用法**：

```cpp
PolyHash hs(s), ht(t);

bool eq = (r1 - l1 == r2 - l2) &&
          (hs.get(l1, r1) == ht.get(l2, r2));

auto joined = PolyHash::concat(
    hs.get(l1, r1), ht.get(l2, r2), r2 - l2
);
```

**先读懂模板的四个核心接口**：

| 接口 | 它做了什么 | 什么场景会用 |
|---|---|---|
| `PolyHash hs(s)` | 从左到右计算字符串 `s` 的全部前缀 Hash | 预处理一个固定文本 |
| `hs.get(l,r)` | 用 `h[r]-h[l]*pow[r-l]` 得到子串 `s[l,r)` 的双 Hash | 任意子串比较 |
| `hs.push(c)` | 把字符 `c` 加到末尾，并更新新的前缀 Hash | 持续追加字符串 |
| `PolyHash::concat(A,B,lenB)` | 已知两段 Hash 和右段长度，算拼接后的 Hash | 线段树 / 隐式字符串 |

例如：

```cpp
string s = "abcab";
PolyHash hs(s);

// 两段 "ab"：位置虽然不同，但内容一样
assert(hs.get(0, 2) == hs.get(3, 5));

// "abc" + "ab" 的 Hash，应等于整串 "abcab" 的 Hash
auto x = PolyHash::concat(hs.get(0, 3), hs.get(3, 5), 2);
assert(x == hs.get(0, 5));
```

这里的 `h1/h2` 是两个模数下的前缀 Hash，`p1/p2` 是底数幂；**同一个 `PolyHash` 的 `get` 只能访问它实际维护的长度范围**。调用 `push` 后，新字符也进入可查询的范围。

需要注意：所有 `PolyHash` 实例共享两组随机底数；不能把**不同底数**算出来的 Hash 直接比较。

---

## 3. Hash 的四种高频用法

### 3.1 子串相等：先检查长度，再比较 Hash

设要比较 $S[l_1,r_1)$、$S[l_2,r_2)$。如果长度不同，不可能相等；长度相同才比较 Hash：

$$
\operatorname{equal}(l_1,r_1,l_2,r_2)
=[r_1-l_1=r_2-l_2]\land[H_1=H_2].
$$

例如 `abcabd` 中的 $S[0,2)=\texttt{ab}$ 和 $S[3,5)=\texttt{ab}$ 相等，而 $S[0,3)=\texttt{abc}$ 与 $S[3,6)=\texttt{abd}$ 不相等。

这看起来简单，却是后面很多问题的基础：**复杂的匹配条件，先拆成有限次子串相等判断。**

### 3.2 Hash + 二分求 LCP

给原串中两个起点 $i,j$，想求

$$
\operatorname{LCP}(i,j)=\max\{k:S[i,i+k)=S[j,j+k)\}.
$$

朴素做法是从左往右逐个比较字符。若一次查询可能匹配几十万个字符，而且有很多次询问，就太慢了。

**为什么这里能二分？** 固定两个起点，若前 $5$ 个字符都一样，那么前 $1,2,3,4$ 个当然也一样；若前 $5$ 个不一样，更长的前缀也不可能一样。条件

$$
P(k): S[i,i+k)=S[j,j+k)
$$

呈现“前面真、后面假”，因此能二分最大合法长度。

看一个完整例子：

```text
S = abcabxabcaby
    012345678901

从 i=0：abcabxabcaby
从 j=6：abcaby
         abcab ×
```

比较下标 $0$ 和 $6$ 开始的后缀，最大可能长度是 $6$（第二个后缀只有 6 个字符）。

| 询问长度 $k$ | 比较内容 | 结果 |
|---:|---|---|
| 3 | `abc` 与 `abc` | 相等，尝试更长 |
| 5 | `abcab` 与 `abcab` | 相等，尝试更长 |
| 6 | `abcabx` 与 `abcaby` | 不等，缩短 |

因此 $\operatorname{LCP}(0,6)=5$。每次比较都可以调用两次 $O(1)$ 的子串 Hash，二分最多 $O(\log n)$ 次。

```cpp
// 约定 hs 是字符串 S 的静态 Hash，参数 i、j 是 S 中的起点
int lcp(const PolyHash& hs, int i, int j) {
    int n = hs.size();
    int lo = 0, hi = n - max(i, j);
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (hs.get(i, i + mid) == hs.get(j, j + mid))
            lo = mid;
        else
            hi = mid - 1;
    }
    return lo;
}
```

**代码中的上取中点** `mid=(lo+hi+1)/2` 是为了在 `lo+1==hi` 时避免死循环。

两个指定**有限区间**的公共前缀长度还要截断：

$$
\min\bigl(\operatorname{LCP}(l_1,l_2),\ r_1-l_1,\ r_2-l_2\bigr).
$$

> 这是一种“用 Hash 来实现 LCP 查询”的方法，不意味着 LCP 必须依赖 Hash。第 4 讲的 SA + RMQ 也能提供 LCP，并且不依赖随机碰撞。

### 3.3 用 LCP 比较两个子串的字典序

字典序比较的规则其实只有一句：**从左往右找第一个不同字符；谁的这个字符小，谁就小。如果一直没找到，就比较谁先结束。**

比如比较 `abc` 和 `abd`：前两个字符 `ab` 一样，第三个字符 `c < d`，所以 `abc < abd`。

对 $A=S[l_1,r_1)$、$C=S[l_2,r_2)$，先求

$$
k=\min(\operatorname{LCP}(l_1,l_2),|A|,|C|).
$$

然后只有两种情况：

1. $k$ 已等于某个字符串长度：至少一个字符串已经结束，较短者更小；若同长则相等。
2. 两者都没结束：$A[k]$、$C[k]$ 就是**第一个不同字符**，直接比较。

例如在 `abcabd` 中，$S[0,3)=\texttt{abc}$，$S[3,6)=\texttt{abd}$；这两个起点的 LCP 是 2，因此只需比较 `c` 和 `d`。

所以“比较长字符串”被变成了：

$$
\boxed{\text{一次 LCP 查询}+\text{一次字符比较}.}
$$

### 3.4 用 LCP 判断周期、回文与重复

**应用 A：周期。**

例如 `abababa` 长度 $7$，虽然 $7$ 不能被 $2$ 整除，但它有周期 $p=2$：

```text
abababa
  ababa
```

平移 2 位后，重叠的 `ababa` 完全相同。一般地，子串 $S[l,r)$ 长度 $L=r-l$，周期 $p$ 的定义就是

$$
S[l,r-p)=S[l+p,r).
$$

所以只要判定：

$$
\boxed{\operatorname{LCP}(l,l+p)\ge L-p}\quad(1\le p\le L).
$$

特别注意：周期不要求 $p\mid L$；也不需要比较那不重叠的 $p$ 个字符。

**应用 B：回文。**

回文串正着读、反着读一样。例如 `abccba` 是回文，`abca` 不是。令 $R=reverse(S)$、$n=|S|$。原串的一段 $S[l,r)$ 反过来，恰好在 $R$ 的区间 $R[n-r,n-l)$ 中。

例：$S=\texttt{abcde}$，$S[1,3)=\texttt{bc}$；反串 $R=\texttt{edcba}$，$R[2,4)=\texttt{cb}$，恰好是 `bc` 的反转。

因此一段是回文的条件可以通过 Hash 判断：

$$
\boxed{H_S(l,r)=H_R(n-r,n-l).}
$$

当然，这只是在 Hash 不碰撞时给出正确结论；在动态修改的情况下，可以改用线段树维护正向和反向 Hash，见第 5 节。

**应用 C：左右扩展重复。**

如果某两段相同结构从位置 $i,j$ 开始，那么 $\operatorname{LCP}(i,j)$ 给出它们向**右**最长相等多少；反串上的 LCP 给出它们向**左**最长相等多少。把左右两段长度加起来，往往能求出某个重复结构可以扩展到多大的区间。后面的周期理论与 Runs 都会反复使用这个视角。

## 4. 真题精讲 A：CF1200E — Compress Words

**原题**：[Codeforces 1200E](https://codeforces.com/problemset/problem/1200/E)。给定若干个单词，按顺序把它们合并起来；每次尽可能让“当前答案的末尾”和“新单词的开头”重合，然后只追加新单词剩余部分。总输入长度不超过 $10^6$。

### 4.1 先手动合并一次

当前答案 $A=\texttt{sample}$，下一个单词 $T=\texttt{please}$：

```text
A = s a m p l e
          p l e a s e = T
          ↑ ↑ ↑
```

`A` 的末尾 `ple` 与 `T` 的开头 `ple` 相等，这 3 个字符不用写两次。新答案是：

```text
sample + ase = samplease
```

注意，这不是把两个串任意位置的公共子串对齐。**只能取 $A$ 的后缀和 $T$ 的前缀。**

### 4.2 把“重合最多”变成数学式

记 $K=\min(|A|,|T|)$。重合长度 $k$ 满足：

$$
\boxed{A[|A|-k,|A|)=T[0,k).}
$$

目标是在 $0\le k\le K$ 中找最大的合法 $k$。

我们刚学过 Hash：给定一个 $k$，取出左、右两个子串 Hash，在 $O(1)$ 时间内就能判断它是否满足式子。

于是一个很直接的方法是：从 $K$ 开始，$K-1,K-2,\ldots$ 挨个试，找到第一个合法值就停止。

### 4.3 为什么“求最大值”反而不能二分？

这里很容易产生误解：第 3.2 节求 LCP 可以二分，都是“求最大合法长度”，这题能否也二分？

**不能直接二分，因为它不是在比较固定起点的两个前缀。** 当重合长度 $k$ 改变时，$A$ 的后缀**起点也改变了**。

反例：$A=\texttt{aba}$，$T=\texttt{aba}$。

| $k$ | $A$ 的后缀 | $T$ 的前缀 | 可行吗？ |
|---:|---|---|---|
| 1 | `a` | `a` | 是 |
| 2 | `ba` | `ab` | 否 |
| 3 | `aba` | `aba` | 是 |

合法性是“是、否、是”，**没有单调性**，不能二分。

但从大到小枚举 $k$ 仍然很快，因为每轮最多检查 $|T|$ 个候选；所有输入单词长度之和为 $L$，总检查次数至多 $L$，复杂度 $O(L)$（Hash 比较概率正确）。

### 4.4 核心代码

用前面的 `PolyHash`，不仅可以从区间里取 Hash，还可以用 `push` 在末尾追加字符：

```cpp
string ans;
PolyHash ha;

for (int i = 0; i < n; i++) {
    string t;
    cin >> t;
    PolyHash ht(t);

    int k = min((int)ans.size(), (int)t.size());
    while (k > 0 &&
           ha.get((int)ans.size() - k, (int)ans.size()) !=
           ht.get(0, k)) {
        k--;
    }

    // 前 k 个字符已经和 ans 的尾部重合，不用再追加
    for (int j = k; j < (int)t.size(); j++) {
        ans.push_back(t[j]);
        ha.push((unsigned char)t[j]);
    }
}
cout << ans << '\n';
```

最容易造成超时的写法是：每合并一次，就把越来越长的 `ans` 从头重新 Hash 一遍；应使用支持追加的前缀 Hash。

### 4.5 再看一眼 KMP 的解法

只取 $A$ 最后 $K$ 个字符，构造

$$
U=T+\#+\operatorname{suffix}_K(A),
$$

其中 `#` 是不会出现在单词中的分隔符。$U$ 的最长 Border 长度，就是本题的最大重合长度；用 KMP 也能以 $O(|T|)$ 求出。

**这题要带走的模型**：前缀与后缀的相等关系可以用 Hash 检查，也可以交给 KMP；但是否能**二分最大长度**，必须先分析单调性。

## 5. 真题精讲 B：AtCoder ABC331 F — Palindrome Query

**原题**：[ABC331 F](https://atcoder.jp/contests/abc331/tasks/abc331_f)。维护一个字符串，支持两类操作：

1. 把某个位置的字符修改为 $c$；
2. 询问某个区间是否为回文（原题使用 1-based 闭区间）。

官方题解使用 Rolling Hash + 线段树。

### 5.1 静态 Hash 为什么突然不方便？

设 $S=\texttt{abca}$。如果只查询 `S[1,3)` 是否回文，预处理正串、反串的前缀 Hash 就能 $O(1)$ 判断。

但如果把下标 $2$ 的 `c` 改成 `b`，字符串变成 `abba`：

```text
原来：a b c a    不是回文
修改：a b b a    是回文
```

前缀 Hash 是一步步递推出来的；改动一个字符后，后面所有前缀 Hash 值一般都会变化，直接重算需要 $O(n)$。

我们已经知道一个重要性质：**相邻两段的 Hash 可以合并**。因此自然想到用线段树：叶子代表单个字符，父节点代表左右儿子字符串的拼接。

### 5.2 线段树一个节点存什么？

对它所代表的字符串 $X$，存三样信息：

$$
\boxed{(len,fwd,bwd)}
$$

其中：

- `len`：这段字符串长度；
- `fwd`：正着读时的 Hash；
- `bwd`：反过来读时的 Hash。

假设父节点字符串为 $X=A+C$，左右儿子分别代表 $A,C$。

正向自然是：

$$
fwd=H(A)B^{|C|}+H(C).
$$

反向为什么要交换顺序？因为

$$
\operatorname{reverse}(A+C)=\operatorname{reverse}(C)+\operatorname{reverse}(A).
$$

所以：

$$
bwd=H(C^R)B^{|A|}+H(A^R).
$$

**用一个具体数字检查公式。** 假设 $A=\texttt{ab}$、$C=\texttt{ca}$，使用前面 $B=10$ 的玩具 Hash：

```text
父段  = abca    -> fwd = 1231
反串  = acba    -> bwd = 1321
```

按两个儿子合并：

$$
\begin{aligned}
fwd&=12\cdot100+31=1231,\\
bwd&=13\cdot100+21=1321.
\end{aligned}
$$

两份 Hash 不相等，所以 `abca` 不是回文。如果把 `c` 改为 `b`，父段成为 `abba`，正反方向才会一致。

**真正实现时**，上述公式在两个模数下各算一次，不是直接用十进制数字。

### 5.3 修改和查询怎样完成？

- **修改位置 $x$**：沿线段树找到叶子，更新它对应字符的 Hash，再一路重新合并到根。
- **查询区间 $[l,r)$**：按区间查询的方式收集若干节点，严格按字符串原本的**从左到右顺序**合并信息。
- 得到该区间的 `(len,fwd,bwd)` 后，检查 $fwd=bwd$。

每次操作复杂度 $O(\log n)$。

> **推广视角**：这不只是一个“回文线段树模板”。凡是信息能表示一段字符串，且两段信息能在拼接时合并，就可以考虑用线段树、平衡树等数据结构维护它。第 8 讲子序列的转移矩阵也会用到类似思想。

## 6. 真题精讲 C：CF514C — Watto and Mechanism

**原题**：[Codeforces 514C](https://codeforces.com/problemset/problem/514/C)。先存储很多字符串；每次查询一个串 $S$，问是否存在某个存储串 $T$，使得两串**长度相同，并且恰好有一个位置的字符不同**。字符集只有 `a,b,c`。

### 6.1 先想最直接的办法

例如存储了 `abc`，查询 `acc`：第二个字符 `b` 和 `c` 不同，其余位置相同，所以答案应为 YES。

逐个拿查询串与每个存储串比较，显然可能太慢。但字符集只有三个字符，而且要求**恰好改一个位置**：

1. 枚举查询串的某个位置 $i$；
2. 将它改为另外两个可用字符中的一个；
3. 看修改后的整个字符串是否存在于字典中。

每个位置只试两种替换，总共约 $2|S|$ 个候选。

困难在于：每次修改后如果真的复制整个字符串再重新算 Hash，会很慢。能不能直接改 Hash？

### 6.2 为什么“一处修改”只改一个项？

长度为 $m$ 的字符串 Hash 是

$$
H(S)=v(S_0)B^{m-1}+v(S_1)B^{m-2}+\cdots+v(S_{m-1}).
$$

位置 $i$ 的字符从 $a$ 改成 $c$，其余项都不变，只有这一项从 $v(a)B^{m-1-i}$ 变成 $v(c)B^{m-1-i}$。

因此：

$$
\boxed{H(S')=H(S)+\bigl(v(c)-v(a)\bigr)B^{m-1-i}\pmod M.}
$$

还是用玩具 Hash：`abc` 的值是 123；把下标 1 的 `b`(2) 改为 `c`(3)，得到 `acc`：

$$
123+(3-2)\cdot 10^{3-1-1}=123+10=133.
$$

没有重新遍历字符串，就更新了整体 Hash。

### 6.3 如何查询与推广？

将存储串的 **`(长度, 双 Hash)`** 放入集合；查询时枚举一次替换，按上述公式计算两份修改后的 Hash，在集合中查找。

- 为什么必须存长度？因为题目要求长度相同，Hash 值本身不携带长度信息。
- 为什么不能把原字符作为替换候选？因为题目要求**恰好**一处不同。
- 为什么仍要注意碰撞？因为集合里存的是字符串的“特征值”，并非保证唯一的编号。

进一步，如果题目允许至多 $k$ 处失配，而且 $k$ 很小，可以用 **LCP 来跳过一整段相等字符**：

1. 求当前两位置的 LCP，直接跳到第一个不匹配字符；
2. 跳过这个失配点，记录已经用了 1 次修改机会；
3. 重复直到某个字符串结束或失配次数超过 $k$。

这样“比较两个长串是否至多 $k$ 处不同”，就转化成最多 $k+1$ 次 LCP 查询。**关键不是 Hash 本身，而是“快速找到下一个不同位置”这个模型。**

## 7. 进一步的变形与常见陷阱

### 7.1 判断可不可以二分：先证明单调性

- 对固定起点的**公共前缀长度**：可行集合是 $\{0,1,\dots,L\}$，**可以二分**。
- 对**后缀与前缀的重叠长度**：可能是 $\{0,1,3\}$，**不能直接二分**。
- 对“是否存在两个不重叠且相同的长度为 $k$ 的子串”：若长度 $k$ 可行，缩短后仍可行，**可以二分**。

**先弄清 predicate，再决定用不用二分。**

### 7.2 字符串拼接与隐式字符串

若字符串由多段源串的子串拼成：

$$
X=A[l_1,r_1)+B[l_2,r_2)+C[l_3,r_3),
$$

可以由每一段的 `(len,hash)` 逐次合并求得整体 Hash，而不必真的复制。比较两个这样的隐式串时，还需要结合“片段边界 + LCP”定位首次不同之处；**只有整体 Hash 并不能直接求得首次不同的位置**。

### 7.3 进阶预告：2024 ICPC 昆明邀请赛 D — Generated String

**原题**：[2024 ICPC Kunming Invitational D](https://codeforces.com/gym/105386/problem/D)。每个字符串不直接给出，而是由**同一个模板串的多个子串拼接**而成；动态维护这些字符串，询问有多少个字符串同时满足“以 $s$ 为前缀、以 $t$ 为后缀”。

本讲先只关注两步：

1. **隐式字符串比较**：给每个生成串保存各片段的长度、前缀累计长度与累计 Hash；比较两个生成串时，可以通过 Hash 二分 LCP，并通过片段长度前缀和定位第 $k$ 个字符所在的片段。因此无需展开可能很长的生成串。
2. **字符串条件转化**：若字符串按字典序排序，“以 $s$ 为前缀”对应连续的字典序区间；对反串排序，“以 $t$ 为后缀”也对应连续区间。每个字符串于是对应一对排名坐标，后续可转为二维数点，再结合插入、删除时间做离线处理。

> 本题完整正解还涉及 Trie / 排序区间和离线数据结构，难度明显超出第 0 讲。此处把它作为一个贯穿后续章节的例子：**Hash 负责让隐式字符串可比较，字符串排名区间负责把前后缀条件转成几何限制。**

### 7.4 关于碰撞，要有正确认识

多项式 Hash 不是严格意义的“字符串编号”。例如继续使用 `a`→1、`b`→2、`c`→3、$B=10$ 的玩具编码，但这次取模 $M=7$：

$$
H(\texttt{aa})=11\bmod7=4,\qquad H(\texttt{cb})=32\bmod7=4.
$$

`aa` 和 `cb` 明明不同，却得到同一个 Hash。这叫作**碰撞**。真实题目使用大模数、随机底数和双 Hash，是为了尽量降低这种错误概率，并非消除碰撞。


- **Hash 不同** $\Rightarrow$ 内容不同（使用相同参数、同样定义）。
- **Hash 相同** $\nRightarrow$ 内容相同。
- 在素数模数 $M$ 下，对两条固定的不同等长字符串，若底数在有限域中足够随机，碰撞可由多项式根数界估计：长度为 $L$ 时，概率至多约 $(L-1)/M$。这是**随机底数模型下的上界**，不是固定底数的万能保证。
- 大量候选比较、恶意构造的输入会放大风险。双模数与随机底数能明显降低实战风险，但不能使算法严格确定。
- `uint64_t` 自然溢出 Hash 很方便，却存在可构造的碰撞，不宜宣称绝对安全；若题目有确定性方法且复杂度适合，应优先考虑确定性方法。

### 7.5 哪些事情 Hash 很好做，哪些不好做？

| 能力 | Hash 的表现 | 可考虑的替代方案 |
|---|---|---|
| 静态子串相等 | $O(1)$，概率正确 | SA/LCP、直接比较 |
| 任意两后缀 LCP | Hash + 二分 $O(\log n)$ | SA + RMQ $O(1)$ |
| 动态子串相等 | 线段树 $O(\log n)$ | 平衡树上的字符串结构 |
| 一次字符改变后的整体 Hash | $O(1)$ | Trie 等 |
| 一个模式的所有出现位置 | 逐位检查 Hash 或 KMP/Z | KMP/Z 更自然且确定 |
| 字典序比较 | Hash 先求 LCP，再看下一字符 | SA 的 Rank/LCP |
| 所有不同子串计数 | 可 Hash 去重，但候选可达 $O(n^2)$ | SAM / SA |

---

## 8. 练习安排（真题）

建议按顺序做。下列题目均为真实竞赛题；正文保留关键突破口，避免直接给完整代码。

| 题目 | 本讲要训练的模型 | 提示 / 目标复杂度 |
|---|---|---|
| [CF1200E — Compress Words](https://codeforces.com/problemset/problem/1200/E) | 最大前后缀重叠 | Hash 枚举或 KMP，$O(\sum|S_i|)$ |
| [CF514C — Watto and Mechanism](https://codeforces.com/problemset/problem/514/C) | 恰好一处失配 | 枚举修改 + 整串 Hash 更新 |
| [CF271D — Good Substrings](https://codeforces.com/problemset/problem/271/D) | 不同子串去重 | 枚举所有满足条件的子串，用 `(长度,双Hash)` 去重；$n\le1500$ |
| [AtCoder ABC141 E — Who Says a Pun?](https://atcoder.jp/contests/abc141/tasks/abc141_e) | 两次非重叠 Occurrence | 对 $i<j$，最长合法长度 $=\min(\operatorname{LCP}(i,j),j-i)$ |
| [AtCoder ABC331 F — Palindrome Query](https://atcoder.jp/contests/abc331/tasks/abc331_f) | Hash 的区间合并 | 线段树维护正、反向 Hash |
| [2024 昆明邀请赛 D — Generated String](https://codeforces.com/gym/105386/problem/D)（拓展） | 隐式字符串 / 排名区间 | 拼接 Hash + LCP + Trie / 二维数点 |

### 课后思考题

1. 为什么 `ABC141 E` 对两个出现位置 $i<j$ 的答案恰好是 $\min(\operatorname{LCP}(i,j),j-i)$？
2. `CF1200E` 中如果每次对整个答案重新 Hash，最坏复杂度是多少？
3. 如果一个长度为 $L$ 的子串要求周期 $p$，为什么仅需检查长度 $L-p$ 的一对相等区间？
4. Hash 可以做“相等”，但在什么情况下**不适合**直接做“不同子串个数”？第 5 讲的 SAM 会怎样解决？
5. 若查询一个隐式字符串（若干段拼接）的第 $k$ 个字符、或与另一个隐式字符串的 LCP，只有整体 Hash 是否足够？还需要什么结构？

---

## 9. 本讲速查与下一讲的连接

### 常用公式

$$
\begin{aligned}
H(S[l,r))&=h[r]-h[l]B^{r-l},\\
H(A+C)&=H(A)B^{|C|}+H(C),\\
H(\operatorname{reverse}(A+C))&=H(C^R)B^{|A|}+H(A^R),\\
H(\text{修改 }i:a\to c)&=H(S)+(v(c)-v(a))B^{n-1-i}.
\end{aligned}
$$

以上 Hash 运算均按所选模数计算。

### 看到什么想到什么？

- **“两个区间相同吗？”** → Hash / LCP。
- **“最多匹配到哪里？”** → LCP；先考虑是否具有可二分性。
- **“哪些位置出现模式？”** → Occurrence；KMP/Z、SA 区间或 SAM Endpos。
- **“前后缀重叠？”** → 最大 Border / 重叠匹配；注意不一定可二分。
- **“两个串拼起来维护？”** → `(长度, Hash)` + 合并公式。
- **“区间修改后还要比较？”** → 线段树维护 Hash。
- **“回文？”** → 正反 Hash；更专门的算法有 Manacher / PAM。
- **“大量不同子串？”** → 不应停在暴力 Hash 去重；之后学 SA/SAM。

### 下节预告

第 1 讲会用 **KMP、Z Function、Manacher** 为 Occurrence、Border 和回文提供**确定性的线性算法**；第 2 讲再从 Border 深入 Period 和重叠 Occurrence 的结构理论。

---

## 资料与出处

1. [OI Wiki：字符串哈希](https://oi.wiki/string/hash/)：多项式 Hash、碰撞风险和常见应用。
2. [cp-algorithms：String Hashing](https://cp-algorithms.com/string/string-hashing.html)：子串 Hash、去重、双 Hash。
3. [CF1200E 原题](https://codeforces.com/problemset/problem/1200/E)：前后缀重叠拼接。
4. [CF514C 原题](https://codeforces.com/problemset/problem/514/C)：恰好一处不同的模式匹配。
5. [CF271D 原题](https://codeforces.com/problemset/problem/271/D)：满足限制的不同子串。
6. [AtCoder ABC141 E 原题](https://atcoder.jp/contests/abc141/tasks/abc141_e)：两个不重叠的相同子串。
7. [AtCoder ABC331 F 原题](https://atcoder.jp/contests/abc331/tasks/abc331_f) 与 [官方题解](https://atcoder.jp/contests/abc331/editorial/7876?lang=en)：动态回文 + Rolling Hash。
8. [2024 ICPC 昆明邀请赛 D 原题](https://codeforces.com/gym/105386/problem/D)：隐式生成字符串与前后缀限制。

*本讲义为独立编写的学习材料，题目采用概述形式；具体输入输出及限制以原题为准。*
