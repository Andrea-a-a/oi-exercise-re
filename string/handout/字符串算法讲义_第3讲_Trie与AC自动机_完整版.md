# 第 3 讲　Trie 与 AC 自动机：前缀树模型、分组与贡献、Occurrence 与 Fail Tree

> **课程定位**：面向具有基础算法知识、正在系统学习字符串算法的 ICPC / CCPC / OI 选手。本讲会认真解释 Trie、Fail 指针和 AC 自动机为什么这样设计，但不会花大量篇幅证明复杂度；更多篇幅留给 **Occurrence、树上统计、动态模式串与状态 DP**。  
> **先修**：第 0 讲的前缀、子串与 Occurrence；第 1 讲 KMP 的失配跳转；第 2 讲 Border 和 Fail Tree。  
> **约定**：字符串下标从 **0** 开始，区间统一使用左闭右开 `S[l,r)`；模式串均为**非空串**。`go[u][c]` 表示自动机的转移，`fail[u]` 表示失配链接；本讲用 **LCP** 表示最长公共前缀。  
> **本讲目标**：先将 Trie 作为一类独立的竞赛模型，掌握 **公共前缀、子树、路径计数、前缀贡献、分组、动态约束、Trie DP、正反 Trie**；再理解 AC 自动机的 Fail 转移、Occurrence 统计、Fail Tree 和自动机 DP。

---

## 0. 从问题出发：一个文本里有很多模式串

第 1 讲的 KMP 解决的是：给定一个模式串 `P` 和一个文本 `T`，找 `P` 在 `T` 中的 Occurrence。

现在模式串不是一个，而是很多个：

```text
模式串：he, she, hers, his
文本串：ushers
```

如果对四个模式分别运行 KMP，当然可以；但是模式串可能有 $10^5$ 个，而文本也很长。**能否只扫描文本一遍，同时知道哪些模式串结束于当前位置？**

先手动看看答案：

```text
T = u s h e r s
      s h e        she，结束于下标 3
        h e        he，也结束于下标 3
        h e r s    hers，结束于下标 5
```

这里有两个容易被忽略的事实。

1. **一个位置可能同时结束多个模式串**：在下标 $3$，`she` 和 `he` 都出现了。
2. **即使不能继续匹配当前较长的模式，也不代表要从头开始**：如果刚匹配到 `sh`，它的后缀 `h` 可能是另一个模式串的前缀。

这是本讲两种结构的分工：

- **Trie** 本身就是一棵可以做统计、贪心、DP、区间化的**字符串集合树**，不只是建 AC 的准备步骤；
- **Fail** 告诉我们当前匹配失败后，还有哪个**最长的、有用的后缀**可以继续；
- **AC 自动机** 把二者合在一起，使文本扫描变成状态转移。

| 题目真正问什么 | 第一反应 | 后续常见转化 |
|---|---|---|
| 大量字符串的前缀关系 | Trie | 子树、字典序、前缀统计 |
| 多模式的全部 Occurrence | AC 自动机 | 结束位置、Fail 链 |
| 每个模式出现多少次 | AC 自动机 | Fail Tree 子树求和 |
| 模式串可以启用/禁用 | AC + Fail Tree | 子树加、单点查 |
| 模式出现于哪些文本 | AC + 离线 | 扫描线、BIT |
| 构造满足/避免某些模式的字符串 | AC + DP | 状压、计数、最优化 |

---

# 一、Trie：不仅是存储字符串，更是“前缀形成的树”

> 本章前半部分与 AC 自动机无关：**即使题目完全没有模式串匹配，Trie 也可能是正解的核心**。例如把全部字符串的 LCP 统计成节点贡献，把按 LCP 分组的最优化问题变成树上贪心，把禁止前缀变成子树删除。

## 1.1 一个 Trie 节点到底代表什么？

考虑四个字符串（其中 `ab` 可以是另一字符串的前缀）：

```text
ab, aba, ba, b

(root) ""
  ├── a
  │    └── b       [end: ab]
  │         └── a  [end: aba]
  └── b           [end: b]
       └── a      [end: ba]
```

**节点 $u$ 代表从根到 $u$ 的字符序列 $P_u$。** 深度 $dep[u]$ 就是 $|P_u|$。一条边相当于在某个前缀后面再加一个字符。

Trie 上最重要的对应关系如下：

| 字符串语言 | Trie 里的语言 |
|---|---|
| $p$ 是 $s$ 的前缀 | $node(p)$ 是 $node(s)$ 的祖先 |
| 以 $p$ 为前缀的所有已插入字符串 | $node(p)$ 的子树中的**终点及其重数** |
| 两字符串的 LCP | 它们终点的 LCA 的深度 |
| 为所有字符串的每个非空前缀加一 | 从根的儿子到终点的**路径加一** |
| 按字典序排列字符串 | 按字符升序 DFS，先处理终点再处理儿子 |

不能将“有终点”和“没有孩子”混淆：例如 `ab` 是一个完整输入串，但 `ab` 节点还有 `aba` 这个后代。输入允许相同字符串重复时，还要记录终点的出现**重数**。

一般建议每个节点至少认识这几种量：

- `end[u]`：**恰好等于** $P_u$ 的输入字符串有几个；
- `pass[u]`：有几个输入字符串**经过**节点 $u$，即以 $P_u$ 为前缀；
- `dep[u]`：前缀长度；
- `parent[u]`：删掉最后一个字符后的前缀节点；
- `tin/tout`：该节点子树的 DFS 序区间。

其中，`pass[u]` 不一定等于 `end[u]`，但有：

$$
pass[u]=end[u]+\sum_{v\text{ 是 }u\text{ 的 Trie 儿子}}pass[v].
$$

例如插入 `ab, aba, ba, b` 后，`a` 的 `pass` 为 $2$；`ab` 的 `pass` 为 $2$、`end` 为 $1$；`b` 的 `pass` 为 $2$、`end` 为 $1$。

### Trie 的树形结构为什么有用？

并不是为了节省一点存储空间，而是因为：**字符串的前缀关系被变成了普通树上的祖先关系**。于是很多本来要逐字符串判断的条件，转成了子树求和、沿路径更新、树上 DP、DFS 序、区间数据结构。

---

## 1.2 Trie 与 LCP：两个字符串相似到哪一步？

考虑：

```text
abca
abde
ax
```

`abca` 和 `abde` 在 Trie 中先共同经过 `a`、`ab` 两个节点，然后分别走向 `abc` 与 `abd`。

所以：

$$
\boxed{LCP(s,t)=dep[LCA(node(s),node(t))]}.
$$

这条性质本身很简单，但十分有用。

再进一步，两字符串 LCP 的长度不仅是一个数，还可以这样理解：

> **两个字符串共同经过了多少个非根节点，它们的 LCP 就有多长。**

若 $LCP(s,t)=d$，那它们共同拥有长度 $1,2,\ldots,d$ 的非空前缀，正好 $d$ 个。这种“每经过一个节点就贡献 $1$”的转换，是下一道题的关键。

### 所有字符串两两 LCP 之和

设 `pass[u]` 为经过节点 $u$ 的字符串数（包含重复字符串的重数）。

对于每个非根节点 $u$，从 `pass[u]` 个字符串中任取两个，它们都至少共有前缀 $P_u$，因此该节点向总 LCP 和贡献：

$$
\binom{pass[u]}{2}.
$$

故：

$$
\boxed{\sum_{i<j}LCP(s_i,s_j)
=\sum_{u\ne root}\binom{pass[u]}2}.
$$

注意我们没有对每一对字符串求 LCP，而是反过来**按公共前缀枚举贡献**。

### 2024 AtCoder ABC353 E — Yet Another Sigma Problem

[题目](https://atcoder.jp/contests/abc353/tasks/abc353_e) · [官方题解](https://atcoder.jp/contests/abc353/editorial/10110)

给 $n$ 个字符串，求所有无序对的 LCP 长度之和。总长度不超过 $3\times10^5$。

例如：

```text
ab
abc
arc
```

- `ab` 与 `abc`：LCP 为 $2$；
- `ab` 与 `arc`：LCP 为 $1$；
- `abc` 与 `arc`：LCP 为 $1$。

答案是 $4$。用 Trie 看，前缀 `a` 的 `pass=3`，贡献 $\binom32=3$；前缀 `ab` 的 `pass=2`，贡献 $\binom22=1$；其余节点贡献 $0$，总和正好 $4$。

也可以**在线算贡献**：插入一个新串时，依次经过路径上的节点 $u$。如果已有 `pass[u]=c` 个旧串经过这里，新串与这 $c$ 个串的共同前缀都多了 $1$，所以立即给答案加 $c$，再把 `pass[u]` 加一。

```cpp
// 假设已有 Trie，next[u][c] 为 Trie 儿子，-1 表示不存在。
// Node 中有 int pass = 0;
long long answer = 0;

void add_string(const string& s) {
    int u = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (tr[u].next[c] == -1) {
            int v = (int)tr.size();
            tr[u].next[c] = v;
            tr.emplace_back();
        }
        u = tr[u].next[c];
        answer += tr[u].pass;
        ++tr[u].pass;
    }
}
```

这里的代码是**算法片段**，节点定义放在下一节的可复用框架中。核心在于 `answer += old_pass`，不是代码细节。

**遇题信号**：$\sum LCP$、所有字符串两两公共前缀、按公共前缀长度计分。优先考虑按 Trie 节点分摊贡献，而不是枚举字符串对。

---

## 1.3 Trie 的两类基本更新：路径加与子树查询

先不要急着写复杂代码。观察插入字符串 `abc`：

```text
root -> a -> ab -> abc
```

每一个非根节点都代表 `abc` 的一个非空前缀，因此：

$$
\boxed{\text{插入一个串}=\text{从根到终点的路径上 }pass+1}.
$$

询问“有多少字符串以 `ab` 为前缀”，只需要读取 `pass[node(ab)]`。

但是如果输入是一批固定字符串，在 Trie 上枚举所有节点，又能使用后序累加：

$$
\boxed{pass[u]=end[u]+\sum pass[child]}.
$$

注意这两种统计方式是等价的，只是前者天然支持在线插入，后者适合一次性建树后做 DP。

如果操作不是简单插入，而是维护一个**已插入字符串集合上的任意节点权值**，可以进一步在 Trie 上做 DFS 序：

$$
\boxed{\operatorname{subtree}(u)\leftrightarrow[tin[u],tout[u])}.
$$

于是“以 $p$ 为前缀的字符串集合”可以变成一个连续区间，在区间中做求和、计数、最值，或者点更新。

**重要边界**：如果 Trie 还在在线创建新节点，原先计算好的 DFS 序可能失效。常见做法是先离线收集全部会出现的字符串建好 Trie，再按操作时间逐次更新节点权值。

### 可复用的 Trie 节点框架（不包含 AC）

```cpp
struct Trie {
    struct Node {
        array<int, 26> next;
        int parent = -1;
        int depth = 0;
        int pass = 0;
        int end = 0;
        Node() { next.fill(-1); }
    };

    vector<Node> tr;
    Trie() { tr.emplace_back(); } // 0 是根

    int insert(const string& s) {
        int u = 0;
        ++tr[u].pass;
        for (char ch : s) {
            int c = ch - 'a';
            if (tr[u].next[c] == -1) {
                int v = (int)tr.size();
                tr[u].next[c] = v;
                tr.emplace_back();
                tr[v].parent = u;
                tr[v].depth = tr[u].depth + 1;
            }
            u = tr[u].next[c];
            ++tr[u].pass;
        }
        ++tr[u].end;
        return u;
    }

    // 若字符串尚不存在，返回 -1。
    int locate(const string& s) const {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            u = tr[u].next[c];
            if (u == -1) return -1;
        }
        return u;
    }
};
```

这里为每个节点保存了 `parent/depth/pass/end`。编写复杂应用时，你可以删掉不需要的字段。**注意若用 `vector` 扩容，不能在 `emplace_back()` 前后一直持有指向旧元素的引用。**

---

## 1.4 核心真题：2024 ICPC 香港 G — Yelkrab

[题目（QOJ #9921）](https://qoj.ac/problem/9921/statement/zh_cn) · [官方分析（Hong Kong Regional Analysis，G）](https://qoj.ac/download.php?id=1885&r=1&type=attachments)

这道题建议放在 Trie 部分的**主讲位置**。它极好地体现了：

$$
\boxed{\text{最长公共前缀计分}}
\longrightarrow
\boxed{\text{Trie 子树分组}}
\longrightarrow
\boxed{\text{整除关系与增量维护}}.
$$

### 题意简化

依次加入 $n$ 个字符串。给定一个固定的队伍人数 $k$，每队恰好 $k$ 个字符串，同一个字符串最多用一次；某队得分等于所有成员字符串的 LCP 长度。不必用完所有字符串。

令 $f(i,k)$ 为只使用前 $i$ 个字符串时能得到的**最大总得分**。对每个 $i$，输出：

$$
\boxed{ans_i=\bigoplus_{k=1}^{i}\left(k\cdot f(i,k)\right)}.
$$

题目总字符串长度不超过 $10^6$，$n$ 的总和不超过 $5\times10^5$。

### 第一步：为什么想到 Trie？

先只考虑一个 $k$。如果一组字符串想得到较高分数，它们必须共享更长的前缀。

例如：

```text
aa, ab, ab, ac, d
```

当 $k=2$，一种最优分法：

```text
ab + ab -> LCP = 2
 aa + ac -> LCP = 1
 d 单独剩下
总分 = 3
```

为什么 `ab + ab` 比 `ab + d` 更值得优先分组？因为更深的 Trie 节点代表更长公共前缀，因此**尽量在更深的节点内部凑够一组**不会比向上合并更差。

### 第二步：把组的得分分摊到 Trie 的边

如果一组字符串的共同前缀长度为 $d$，那么在 Trie 中，从根向下有 $d$ 条共同经过的边。可以看成：这组每在一个非根节点的子树内全部出现，就为这个节点贡献 $1$ 分。

记：

$$
\boxed{cnt_i[u]=\text{前 }i\text{ 个字符串中经过 }u\text{ 的数量}}.
$$

对于任意节点 $u$，若要组内所有 $k$ 个字符串都位于它的子树，最多能够组成：

$$
\left\lfloor\frac{cnt_i[u]}{k}\right\rfloor
$$

组。

从深节点往上贪心合并，先让能在深处形成的组形成，再把无法凑足 $k$ 个的剩余字符串交给父亲；同一组在 Trie 中每向上共享一条边，就有一次单位贡献。这一贪心可达到每个节点的上界，官方题解给出了交换论证。故：

$$
\boxed{f(i,k)=\sum_{u\ne root}\left\lfloor\frac{cnt_i[u]}{k}\right\rfloor}.
$$

#### 为什么这个上界真的可以同时达到？

先想一个**上界**。固定某个非根节点 $u$：一支队伍的 $k$ 个字符串如果全部位于 $u$ 的子树，那么它们至少共享前缀 $P_u$，于是这支队伍给节点 $u$ 贡献 $1$ 分。但子树里只有 $cnt[u]$ 个字符串，所以这样的队伍最多 $\lfloor cnt[u]/k\rfloor$ 支。把所有节点上界加起来，得到上面的求和式。

再想**构造**。我们从 Trie 的叶子往根处理：

1. 先把每个儿子的子树内能组成的 $k$ 人队伍全部组成，这些队伍不用拆开；
2. 每个儿子把凑不够一支队伍的剩余字符串交给当前节点，另外加上直接在当前节点结束的字符串；
3. 把这些剩余字符串继续每 $k$ 个组成一队，多出来的不足 $k$ 个交给父亲。

这样，节点 $u$ 的整个子树内最终恰好包含 $\lfloor cnt[u]/k\rfloor$ 支**在此节点或更深处已经形成的队伍**；因而对每个 $u$ 都达到了刚才的单位贡献上界。注意不是说每个节点都要重新使用同一个字符串组队，而是一个已经在深处形成的队伍，会沿着所有公共祖先各贡献 $1$ 分。

例如 $k=2$，输入 `aa, ab, ab, ac, d`：

```text
ab 这个节点：ab, ab 先组成一队，贡献深度 2
 a 这个节点：剩余 aa, ac 组成一队，贡献深度 1
根节点：剩下 d，无法组成一队；根深度 0 也不计分
```

这比直接宣称“贪心最优”更容易理解，也说明**Trie 的每条公共边就是一单位得分**。

注意**根不计入**，因为根对应空串，深度为 $0$，对 LCP 分数没有贡献。

### 第三步：拿刚才的五个字符串检查公式

以 `aa, ab, ab, ac, d` 为例，相关非根节点计数：

| 前缀节点 | `a` | `aa` | `ab` | `ac` | `d` |
|---|---:|---:|---:|---:|---:|
| $cnt[u]$ | 4 | 1 | 2 | 1 | 1 |

因此 $k=2$：

$$
f(5,2)=\lfloor4/2\rfloor+\lfloor1/2\rfloor+\lfloor2/2\rfloor
+\lfloor1/2\rfloor+\lfloor1/2\rfloor=3.
$$

同理：

$$
f(5,1)=9,\quad f(5,2)=3,\quad f(5,3)=1,\quad f(5,4)=1,\quad f(5,5)=0.
$$

最终：

$$
ans_5=(1\cdot9)\oplus(2\cdot3)\oplus(3\cdot1)\oplus(4\cdot1)=8.
$$

与题目样例对应。

### 第四步：如何同时维护所有 $k$？

如果每加一个字符串都遍历所有 Trie 节点、所有 $k$，太慢。我们只需注意每个路径节点 $u$ 的计数增加了 $1$：

$$
cnt[u]:c-1\longrightarrow c.
$$

此时：

$$
\left\lfloor\frac{c}{k}\right\rfloor
-\left\lfloor\frac{c-1}{k}\right\rfloor
=\begin{cases}1,&k\mid c,\\0,&k\nmid c.\end{cases}
$$

所以只对 $c$ 的约数 $k$ 有影响！

定义：

$$
F_k=k\cdot f(i,k).
$$

每当路径节点的计数从 $c-1$ 增加为 $c$，对所有 $k\mid c$：

$$
F_k\gets F_k+k.
$$

而题目维护的是 XOR：

$$
ans=F_1\oplus F_2\oplus\cdots\oplus F_i.
$$

改变某个 $F_k$ 时，先用 XOR 删除它的旧值，再加入新值：

```cpp
ans ^= F[k];
F[k] += k;
ans ^= F[k];
```

把所有整数 $1\ldots n$ 的约数预处理好，就可以高效更新。虽然单次数的约数数量不恒为 $O(\log n)$，但对每个 Trie 节点，其计数会从 $1$ 依次增加到最终 `pass[u]`，因而总更新次数可以用 $\sum_{c\le m}\tau(c)=O(m\log m)$ 控制，最终整体为：

$$
O\left(\sum_i|s_i|\log n\right)
$$

数量级。这里 $\tau(c)$ 是 $c$ 的正约数个数。

### 可运行的 C++20 核心实现

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Solver {
    struct Node {
        array<int, 26> next;
        int cnt = 0;
        Node() { next.fill(-1); }
    };

    vector<Node> tr;
    vector<vector<int>> divisors;
    vector<long long> F; // F[k] = k * f(current_size, k)
    long long answer = 0;

    explicit Solver(int n) : divisors(n + 1), F(n + 1, 0) {
        tr.emplace_back(); // 根节点 0；根不计分
        for (int d = 1; d <= n; ++d)
            for (int multiple = d; multiple <= n; multiple += d)
                divisors[multiple].push_back(d);
    }

    long long insert(const string& s) {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (tr[u].next[c] == -1) {
                int v = (int)tr.size();
                tr[u].next[c] = v;
                tr.emplace_back();
            }
            u = tr[u].next[c];
            int now = ++tr[u].cnt;
            for (int k : divisors[now]) {
                answer ^= F[k];
                F[k] += k;
                answer ^= F[k];
            }
        }
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        Solver solver(n);
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            cout << solver.insert(s) << (i + 1 == n ? '\n' : ' ');
        }
    }
}
```

**课堂建议**：先暂停在 $\sum\lfloor cnt/k\rfloor$，让学生自己猜“加一个字符串后哪些 $k$ 的答案会变”，再揭晓约数条件。这样比直接给整段代码更有收获。

---

## 1.5 Trie 上的前缀 DP / 最优值：2024 ABC377 G

[题目 — Edit to Match](https://atcoder.jp/contests/abc377/tasks/abc377_g) · [官方题解](https://atcoder.jp/contests/abc377/editorial/11245)

这题允许对当前字符串 $S$ 做两种操作：**删掉末尾字符**，或者**在末尾添加一个字符**，每次花费 $1$。询问把它变成之前某个输入字符串（或空串）的最少花费。

例如把 `abca` 变成 `abde`，最合理的做法是：

```text
abca -> abc -> ab -> abd -> abde
        删    删    加     加
```

共 $4$ 步，而不是任意位置编辑距离。因为只能在末尾操作，所以必须先保留一个共同前缀。若两个字符串的 LCP 长为 $d$，最少操作次数：

$$
\boxed{cost(S,T)=|S|+|T|-2LCP(S,T)}.
$$

如何在很多旧字符串中找最优的 $T$？

固定当前串的一个前缀 $p=S[0,d)$。所有具有前缀 $p$ 的旧字符串，都在 Trie 的 $node(p)$ 子树中。只需知道它们的最短长度：

$$
best[u]=\min\{|T|:T\text{ 是已插入字符串且经过 }u\}.
$$

答案为：

$$
\boxed{\min_{p\text{ 是 }S\text{ 的前缀}}
\bigl(|S|+best[node(p)]-2|p|\bigr)}.
$$

根节点代表允许变为空串，初始化 $best[root]=0$，因此初始答案是 $|S|$。

实现时，从根沿 $S$ 的路径走一遍：先用该节点**旧的** `best` 更新答案，再把 `best` 更新为 $\min(best,|S|)$，就能在线处理。每次 $O(|S|)$，所有字符串合计线性。

这里的关键思想是：

> **一个前缀代表一整个候选子树；对子树取最小长度可以压缩所有候选字符串。**

这类题常见于“只允许删除后缀 / 添加后缀”的编辑操作、最小代价转换、公共前缀附近的优化。

---

## 1.6 Trie 上的禁止前缀与动态子树：2025 ABC403 E

[题目 — Forbidden Prefix](https://atcoder.jp/contests/abc403/tasks/abc403_e) · [官方题解](https://atcoder.jp/contests/abc403/editorial/12832)

维护两个字符串多重集合 $X,Y$，每次向其中一个集合插入一个串。每次输出：

> 有多少个 $Y$ 中的字符串，**不存在任何** $X$ 中的字符串是它的前缀？

例如：

```text
X = {at}
Y = {watcoder, atcoder}
```

`atcoder` 被 `at` 禁止，但 `watcoder` 尚未被禁止。如果随后将 `wa` 加入 $X$，则 `watcoder` 也被禁止。

观察：

$$
\boxed{x\text{ 是 }y\text{ 的前缀}
\iff node(y)\text{ 在 }node(x)\text{ 的子树内}}.
$$

所以每个 $x\in X$ 都会覆盖它的整个 Trie 子树。随着 $X$ 只增加、从不删除，被禁止的 $Y$ **永远不会重新合法**，这使问题有单调性。

一种在线维护方法：

- 在每个 Trie 节点维护 `blocked`，表示有某个禁止前缀恰好在此结束；
- 维护 `cnt[u]`，表示当前**未被禁止**且位于 $u$ 子树内的 $Y$ 字符串数；
- 插入 $Y$：若沿路径遇到已禁止前缀，什么都不做；否则将其从根到终点路径上的 `cnt` 全部加一；
- 插入 $X$：若路径上已有被禁止的祖先，无须处理；否则令 $z=cnt[node(x)]$，从根到 `node(x)` 的整条路径上的 `cnt` 都减去 $z$，并在终点打上 `blocked`；
- 答案始终是 `cnt[root]`。

为什么只需减去 $z$？因为此前合法、现在被 $x$ 禁止的，恰好是这个节点子树中尚未被覆盖的 $Y$；它们均在每个祖先的计数里出现一次。即便 $x$ 的某些后代已被其他 $X$ 禁止，也不会重复扣除，因为那些 $Y$ 早已不计入 `cnt`。

整道题只需要沿每个输入字符串路径走有限次，整体 $O(\sum|s_i|)$。这是 **Trie 前缀集合的单调覆盖 / 删除** 模型，不需要 AC 自动机。

---

## 1.7 Trie 的 DFS 序、字典序与正反 Trie

Trie 能把一个前缀 $p$ 对应的全部字符串看成一个子树。若先收集所有可能用到的字符串，按 Trie 的 DFS 序给终点编号，那么：

$$
\boxed{\text{“以 }p\text{ 为前缀”}\longrightarrow
\text{一段连续编号}}.
$$

假如需要同时限制：

> 有多少个字符串以 $p$ 为前缀、又以 $q$ 为后缀？

一棵正向 Trie 处理前缀；将每个字符串反转后，再建一棵反向 Trie 处理后缀。原串 $s$ 对应两棵树中的两个终点编号：

$$
\boxed{s\longrightarrow(x_s,y_s)}.
$$

前缀条件给出区间 $x_s\in[L_p,R_p]$，后缀条件给出区间 $y_s\in[L'_q,R'_q]$，于是原题变成：

$$
\boxed{\text{二维矩形数点}}.
$$

可用扫描线 + BIT、离线 CDQ、主席树等数据结构处理。

### 2024 ICPC 昆明邀请赛 D — Generated String

[题目与分析](https://www.luogu.com/article/68qflomx)

题目动态维护字符串集合，询问“同时以 $s$ 为前缀、以 $t$ 为后缀”的字符串个数。字符串甚至是若干**基础串子串拼接**得到的，未必适合显式展开。

核心的第一步仍是：**正 Trie 子树 + 反 Trie 子树 = 二维点矩形**；进一步加入时间维度处理动态存在性。字符串比较则用 Hash / LCP 处理隐式表示。我们不在这一讲推完完整 CDQ，只强调关键的模型识别。

这也解释了为什么“Trie 子树”值得单独学：它常是把复杂字符串条件交给普通数据结构处理的桥梁。

---

## 1.8 Trie 上的博弈 / 树形 DP

假设有若干字符串，两个人轮流在当前串末尾添加一个字符，但添加后必须仍然是某个输入串的前缀。不能操作的人输。

字符串看似在逐字符变化，其实所有合法状态就是 Trie 的节点，所有可行操作就是沿 Trie **向儿子走一条边**。

定义 `win[u]`：从 $u$ 开始轮到当前玩家，是否能取胜。则：

$$
\boxed{win[u]=\bigvee_{v\in child(u)}\neg win[v]}.
$$

如果没有儿子，`win[u]=false`。

这就是普通树上博弈 DP。若题目是很多轮、存在特殊结束规则，可能需要同时维护“能否强制赢 / 能否强制输”等状态。

典型题：[CF455B — A Lot of Games](https://codeforces.com/problemset/problem/455/B)。这题并非靠模式匹配解决，而是把**字符串前缀接龙**转成 Trie 上的博弈。

---

## 1.9 01 Trie：把整数二进制前缀也当作字符串

Trie 的边不一定是字母。把整数看成固定长度的二进制串，也可以建二叉 Trie。

典型题：[CF706D — Vasiliy's Multiset](https://codeforces.com/problemset/problem/706/D)，动态维护整数多重集，支持：

- 插入整数；
- 删除一份整数；
- 查询给定 $x$ 与集合中某个 $y$ 的最大 $x\oplus y$。

从高位到低位走：如果 $x$ 当前位为 $b$，优先走 $1-b$ 的边，因为更高一位的 XOR 为 $1$ 比后面所有位的收益都重要；若该边不存在或有效元素数量为 $0$，再走 $b$。删除时沿路径减少经过计数，而不是简单删除节点。

这仍然是 Trie 的同一套思维：**状态是前缀；路径表示完整对象；节点计数支持动态集合；贪心由字典序/位权决定。**

---

## 1.10 什么时候用 Trie，什么时候该换 AC 自动机？

| 题目关注的关系 | 更自然的结构 |
|---|---|
| 两个输入字符串共享多少开头 | Trie / LCP |
| 某串是否是另一个串的**前缀** | Trie 祖先/子树 |
| 多个输入串按公共前缀分组 | Trie 树上贪心、贡献 |
| 动态加入字符串，维护前缀计数/最优值 | Trie 路径维护 |
| 限制一个集合里哪些串具有指定前缀 | Trie 子树、DFS 序 |
| 一个模式串出现在长文本的**任意位置** | KMP / Z |
| 多个模式同时出现在文本的**任意位置** | **AC 自动机** |
| 后缀、子串出现关系 | AC、SA、SAM 等，视询问而定 |

**分界线在于：** Trie 只会沿字符串的**开头**向下走；要在文本任意位置寻找所有模式，必须在无法继续向下走时，找到当前已读字符的最长可用后缀。这就是下一部分的 Fail 指针。

举例：

```text
模式：he, she, hers, his
文本：ushers
```

扫描到 `sh` 后，如果下一字符不再能沿当前 Trie 路径走，直接回根会丢掉其后缀 `h`（这也是一个模式前缀）。AC 自动机会把这个“有用的后缀”保留下来。

---

# 二、Fail：多模式匹配中的“可保留后缀”

## 2.1 Fail 指针的准确含义

设 Trie 节点 $u$ 代表字符串 $P_u$。

$fail[u]$ 指向一个节点 $v$，使得：

1. $P_v$ 是 $P_u$ 的**真后缀**；
2. $P_v$ 在 Trie 中出现，也就是它是**某个模式串的前缀**；
3. 在满足前两条的节点中，$P_v$ 最长。

如果不存在非空的这样的后缀，就指向根节点。

例如有模式：

```text
he, she, hers, his
```

可以得到：

```text
fail(sh)   = h
fail(she)  = he
fail(hers) = s
fail(his)  = s
```

为什么 `fail(she)=he`？因为 `she` 的后缀是 `he`、`e`，其中 `he` 是 Trie 中的一个节点，而且最长。

为什么 `fail(hers)=s`？因为 `hers` 末尾的 `s` 是模式 `she` 的前缀，而 `ers`、`rs` 等都不是 Trie 中的前缀。

### 和 KMP 的联系

| KMP | AC 自动机 |
|---|---|
| 一个模式串的前缀 | **所有模式串**组成的 Trie 前缀 |
| 失配后跳最长 Border | 失配后跳最长**可用后缀** |
| 只需维护匹配长度 | 需要维护 Trie 节点编号 |
| 找一个模式的 Occurrence | 同时找许多模式的 Occurrence |

可以把 AC 看成：**KMP 的失败跳转思想，搬到了 Trie 上。**

## 2.2 如何求 Fail？为什么需要 BFS？

设节点 $v$ 是节点 $u$ 经过字符 `c` 的 **Trie 儿子**：

$$
P_v=P_u+c.
$$

要找 $P_v$ 的最长可用真后缀，可以先考虑 $P_u$ 的最长可用真后缀 $P_{fail[u]}$，再接字符 `c`。

若存在这样的转移，那么候选就是：

$$
\boxed{fail[v]=go[fail[u]][c]}
$$

这里的 `go` 必须已经能处理“不存在 Trie 儿子时继续沿 Fail 寻找”的情况。

为什么可以直接用它？因为比 $P_{fail[u]}$ 更长的可用真后缀若存在，就会违背 $fail[u]$ 的最长性。BFS 保证处理 $v$ 时，$fail[u]$ 对应的转移已经准备好了。

根节点及其第一层儿子的 Fail 都指向根。按照 Trie 深度从小到大 BFS，就能构造全部 Fail。

> **关键提醒**：`fail[v]` 不一定是 Trie 中 $v$ 的父亲或祖先；Trie 是**前缀树**，Fail 是**后缀关系**。这是两棵不同的树。

## 2.3 补全转移：让 Fail 跳转成为一次查表

定义：

$$
\boxed{go[u][c]=\text{在状态 }u\text{ 后读入字符 }c\text{ 应到达的状态}}
$$

具体规则：

- 如果 $u$ 在 Trie 中确实有 `c` 儿子，就沿这条边前进；
- 否则，先尝试 $fail[u]$ 的 `c` 转移；
- 最终退到根也找不到时，仍留在根。

即：

$$
go[u][c]=
\begin{cases}
\text{TrieChild}(u,c),&\text{若存在};\\
go[fail[u]][c],&\text{否则}.
\end{cases}
$$

根节点不存在的转移直接指向根。

因此 AC 构建完以后，文本匹配核心只有一行：

```cpp
u = ac.go[u][c];
```

虽然代码很短，但背后实际上完成了“失败后沿 Fail 链寻找可用后缀”的过程。

**重要区别：构建完成后的 `go` 已不再只保存 Trie 边。** 其中很多转移是“补全”的自动机边。若后续想再向 Trie 插入模式串，不能直接在这个补全表上继续插入；通常需要重建，或者单独保存原 Trie 边。

---

# 三、AC 的状态究竟表示什么？

扫描文本 $T$ 的前 $i$ 个字符后，设当前 AC 状态为 $u$。

它的准确含义是：

> $P_u$ 是已扫描文本的某个后缀，并且是**所有 Trie 前缀中最长的那个**。

例如：

```text
模式：he, she, hers, his
文本：u s h e r s
```

依次扫描：

| 刚读入字符 | 当前位置 | 当前状态代表的字符串 | 本位置结束的模式 |
|---|---:|---|---|
| `u` | 0 | 空串 | 无 |
| `s` | 1 | `s` | 无 |
| `h` | 2 | `sh` | 无 |
| `e` | 3 | `she` | `she`、`he` |
| `r` | 4 | `her` | 无 |
| `s` | 5 | `hers` | `hers` |

在读到下标 $3$ 的 `e` 时，状态是 `she`。为什么 `he` 也出现了？

因为：

```text
she -> fail -> he
```

`he` 是当前已扫描文本的后缀，且它是一个完整模式。

**因此本讲最关键的匹配性质是：**

$$
\boxed{
\text{模式 }P\text{ 在当前位置结束}
\iff
\text{模式终点节点在当前状态的 Fail 祖先链上}
}
$$

注意这个性质可以转化为两种截然不同的算法：

- **在线逐个输出匹配**：沿 Fail 链找所有终点（可以用 Output Link 加速）；
- **离线统计很多匹配**：把每个文本位置只记录到它的当前状态，最后通过 Fail Tree 汇总，避免每次沿链跳。

后面一半的竞赛应用，都从这句话出发。

---

# 四、可以直接复用的 C++20 AC 自动机

下面给出一种便于课堂使用的版本：字母表为小写英文字母，所有模式先插入，再 `build()`，最后可扫描文本、统计每个模式的出现次数。节点 `0` 是根。

```cpp
#include <bits/stdc++.h>
using namespace std;

struct ACAutomaton {
    struct Node {
        array<int, 26> go{};    // build 后为完整转移
        int fail = 0;
        int terminal = 0;       // 有多少模式以此节点结尾（可重复）
        int outMask = 0;        // 供少量模式的状压题使用
    };

    vector<Node> tr{Node{}};
    vector<int> order;          // BFS 顺序（不包含根）

    // 返回该模式的终点节点编号
    int insert(const string& s) {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (tr[u].go[c] == 0) {
                int v = (int)tr.size();
                tr[u].go[c] = v;
                tr.emplace_back();
            }
            u = tr[u].go[c];
        }
        tr[u].terminal++;
        return u;
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < 26; c++) {
            int v = tr[0].go[c];
            if (v) q.push(v); // fail[v] = 0
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            order.push_back(u);
            int f = tr[u].fail;

            // 所有“以当前状态结尾”的模式，包含 Fail 祖先上的终点
            tr[u].outMask |= tr[f].outMask;

            for (int c = 0; c < 26; c++) {
                int v = tr[u].go[c];
                if (v) {
                    tr[v].fail = tr[f].go[c];
                    q.push(v);
                } else {
                    tr[u].go[c] = tr[f].go[c];
                }
            }
        }
    }

    // 每个节点 v 在 Fail Tree 子树上的访问次数总和
    vector<long long> count_nodes(const string& text) const {
        vector<long long> cnt(tr.size(), 0);
        int u = 0;
        for (char ch : text) {
            u = tr[u].go[ch - 'a'];
            cnt[u]++;
        }
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int v = order[i];
            cnt[tr[v].fail] += cnt[v];
        }
        return cnt;
    }
};
```

使用方法：

```cpp
vector<string> patterns = {"he", "she", "hers", "his"};
ACAutomaton ac;
vector<int> endNode;

for (auto& s : patterns)
    endNode.push_back(ac.insert(s));

ac.build();
auto cnt = ac.count_nodes("ushers");

for (int v : endNode)
    cout << cnt[v] << " ";  // 1 1 1 0
```

几个容易出错的地方：

1. `insert` 必须在 `build` **之前**调用。
2. **重复模式**会得到相同终点；按输入下标查询同一终点即可。若计算“模式总权值”，则重复模式应作为多个模式贡献，而不是去重。
3. `count_nodes` 对每个文本位置只打一次标记，不能在扫描时就对整条 Fail 链打标记后又逆序上传，否则会重复计数。
4. `outMask` 仅适用于模式数较少的场景（如 $N\le 8$），使用前先给每个模式的终点置相应 bit；普通出现次数统计不需要它。
5. 当前版本是静态自动机。如需在线新增模式，通常使用“重建 / 二进制分组”，后面会讲。

---

# 五、Fail Tree：把“某模式在当前位置结束”变成树上祖先

## 5.1 为什么 Fail 边会形成树？

每个非根节点都恰好有一个 Fail 父亲，且 Fail 指向更短的字符串，因此不会成环；所有节点最终都会指向根。

只保留 Fail 边，就得到一棵以根为根的 **Fail Tree**。

节点在 Trie 中的父亲和在 Fail Tree 中的父亲可以完全不同。例如模式集合 `he,she`：

- Trie 中，`she` 的父亲是 `sh`；
- Fail Tree 中，`she` 的父亲是 `he`。

这两个方向分别对应：

- Trie 父边：**删去最后一个字符**，得到前缀；
- Fail 父边：**删去若干开头字符**，得到最长可用后缀。

## 5.2 最核心的子树公式

设某个模式 $P$ 的终点节点为 $v$，扫描文本 $T$ 时每个结束位置对应的自动机状态为 $u_i$。

刚才的性质说：

$$
P\text{ 在位置 }i\text{ 结束}
\iff v\text{ 是 }u_i\text{ 的 Fail 祖先}.
$$

换一个方向，就得到：

$$
\boxed{
\#\operatorname{Occ}_T(P)
=
\#\{i:u_i\in\operatorname{subtree}_{fail}(v)\}
}
$$

所以，**统计模式出现次数 = 在 Fail Tree 中求对应终点的子树访问次数**。

### 具体例子：`a`、`aa`、`aaa`

模式：

```text
a
 aa
 aaa
```

自动机有这些状态：

```text
root ← a ← aa ← aaa    （箭头表示 fail 指向左边）
```

扫描文本：

```text
T = a a a a a
```

每个位置的最终状态为：

```text
a, aa, aaa, aaa, aaa
```

如果仅仅统计“直接到达某个状态的次数”，有：

```text
状态 a   ：1 次
状态 aa  ：1 次
状态 aaa ：3 次
```

但真正的模式出现次数应该是：

```text
"a"   ：5 次
"aa"  ：4 次
"aaa" ：3 次
```

原因是：到达 `aaa` 的位置，也一定同时结束一个 `aa` 和一个 `a`。

因此把子节点的次数沿 Fail 边往上累加：

```text
aaa: 3
 ↓
aa : 1 + 3 = 4
 ↓
a  : 1 + 4 = 5
```

这就是上面模板中“倒序 BFS 累加”的全部含义。

### 两种方向要分清

| 想计算什么 | 树上的操作 |
|---|---|
| 一个**固定模式**在所有扫描位置出现多少次 | **对子树求和** |
| 在一个**固定扫描状态**结束了多少模式 | **对祖先链求和** |

这是后面两道动态题的核心：原问题看似都在统计 Occurrence，但一个要子树求和，另一个要路径/祖先求和。

## 5.3 DFS 序：把 Fail Tree 子树变成区间

对 Fail Tree 做 DFS，记录：

$$
\operatorname{tin}[v],\quad\operatorname{tout}[v].
$$

定义区间为半开：

$$
\boxed{\operatorname{subtree}(v)\longleftrightarrow [tin[v],tout[v])}
$$

于是可以方便地用树状数组或线段树做：

- **单点加、子树求和**：某个文本位置访问了状态 $u$，对 `tin[u]` 加 $1$；查询模式 $v$ 的 Occurrence，就是区间和。
- **子树加、单点查询**：某模式 $v$ 启用/禁用，给 `[tin[v],tout[v])` 加上 $\pm1$；扫描文本到状态 $u$ 时，点查询 `tin[u]` 得到当前匹配的活跃模式数。

**这两种操作是反向的，务必要记清楚。**

---
## 5.4 如果题目要输出每一次匹配：Output Link

前面的“扫描一次后在 Fail Tree 上传”很适合**统计次数**，但如果题目要输出每个匹配的具体结束位置，就不能只留一个总数。

最直接的方法是：扫描到状态 $u$，沿 Fail 一直跳到根，把遇到的全部模式终点输出。问题是 Fail 链上可能有很多**不是终点**的节点，每次都遍历它们会浪费时间。

可以只保留指向下一个**模式终点**的 `outputLink`：

- `outputLink[u]` = `u` 的 Fail 祖先中，最近的一个模式终点；
- 如果没有这样的祖先，就记成根节点 `0`；
- 如果 `u` 本身就是模式终点，报告时先报告 `u`，然后再走 `outputLink[u]`。

由于 Fail 父节点总是先于儿子处理，`outputLink` 可以按 BFS 顺序计算：

```cpp
vector<int> outputLink(ac.tr.size(), 0);
for (int u : ac.order) {
    int f = ac.tr[u].fail;
    outputLink[u] = ac.tr[f].terminal ? f : outputLink[f];
}

int u = 0;
for (int i = 0; i < (int)T.size(); i++) {
    u = ac.tr[u].go[T[i] - 'a'];
    int v = ac.tr[u].terminal ? u : outputLink[u];
    for (; v != 0; v = outputLink[v]) {
        // 节点 v 代表的模式在文本下标 i 结束
        // 若同一终点有多个输入模式编号，逐个报告即可
    }
}
```

在 `ushers` 中，读到 `e` 后当前状态是 `she`，先报告 `she`，`outputLink[she]` 会直接指向 `he`，于是再报告 `he`，不用经过中间的非终点节点。

这一做法的耗时与**文本长度 + 实际输出的匹配数量**相关。如果输出本身就有很多条，无法指望花比输出量更少的时间。

---

# 六、真题 1：CF1202E — You Are Given Some Strings...

**题目**：[Codeforces 1202E](https://codeforces.com/problemset/problem/1202/E)

给定文本 $T$ 和 $n$ 个模式串 $s_1,s_2,\ldots,s_n$，求：

$$
\boxed{\sum_{i=1}^{n}\sum_{j=1}^{n} \#\operatorname{Occ}_T(s_i+s_j)}
$$

注意 $(i,j)$ 是**有序对**。如果不同下标对应相同字符串，也要分别计入贡献。

## 6.1 为什么直接枚举模式对不可行？

如果 $n=2\times 10^5$，有 $n^2$ 个有序对，根本无法枚举。即使我们可以快速检查某个 `s_i+s_j` 是否出现，也没有用。

遇到这种题，先不枚举字符串对，而是问：

> `s_i+s_j` 出现在文本中时，中间必然有一个**拼接分界线**。能否枚举分界线？

假设分界线在下标 $k$，也就是：

```text
T[0..k) | T[k..m)
          ^ 分界线
```

左边必须有一个模式 $s_i$ **恰好在 $k-1$ 结束**；右边必须有一个模式 $s_j$ **恰好从 $k$ 开始**。

于是定义：

$$
L[k]=\#\{i:s_i\text{ 在 }k-1\text{ 结束}\},
$$

$$
R[k]=\#\{j:s_j\text{ 在 }k\text{ 开始}\}.
$$

在分界线 $k$ 处，合法的左右模式可以任意组合，贡献就是：

$$
L[k]R[k].
$$

每次完整出现恰好对应一个分界线，因此：

$$
\boxed{\text{答案}=\sum_{k=1}^{|T|-1}L[k]R[k]}
$$

## 6.2 用具体例子看为什么是乘法

取：

```text
T = ababa
模式：a, ba
```

不同分界线：

```text
k=1 : a|baba
       左边结尾 a（1种）
       右边开头 ba（1种）
       贡献 1

k=2 : ab|aba
       左边没有模式在 b 结尾
       贡献 0

k=3 : aba|ba
       左边结尾 a 或 ba（2种）
       右边开头 ba（1种）
       贡献 2

k=4 : abab|a
       左边没有模式在 b 结尾
       贡献 0
```

总答案是 $1+0+2+0=3$，对应 `aba` 两次、`baba` 一次。

## 6.3 AC 自动机怎样求 $L$ 和 $R$？

我们把每个模式的终点记作一个权重 $1$。对任意状态 $u$，定义：

$$
\operatorname{out}[u]
=\sum_{v\text{ 是 }u\text{ 的 Fail 祖先（含 }u\text{）}} terminal[v].
$$

这就是：**扫描到状态 $u$ 时，有多少模式刚刚结束**。

它可以按 BFS 顺序计算：

```cpp
// ac.build() 后，ac.order 是 BFS 顺序
vector<long long> out(ac.tr.size());
for (int u = 0; u < (int)ac.tr.size(); u++)
    out[u] = ac.tr[u].terminal;
for (int u : ac.order)
    out[u] += out[ac.tr[u].fail];
```

正向扫描文本，令 `endCnt[i]` 为在文本下标 $i$ 结束的模式数量：

```cpp
int u = 0;
for (int i = 0; i < (int)T.size(); i++) {
    u = ac.tr[u].go[T[i] - 'a'];
    endCnt[i] = out[u];
}
```

于是：

$$
L[k]=endCnt[k-1].
$$

求 $R[k]$ 呢？把所有模式反转，并把文本反转。**原串在 $k$ 开始**，就等价于**反串在 $|T|-1-k$ 结束**。

所以构造反串 AC，得到 `revEndCnt` 后：

$$
R[k]=revEndCnt[|T|-1-k].
$$

最后按分界线求和。

### 这道题真正值得学的部分

不是“使用了两遍 AC 自动机”，而是：

$$
\boxed{\text{字符串对的拼接计数}\longrightarrow
\text{枚举分界线}\longrightarrow
\text{左端匹配数}\times\text{右端匹配数}}
$$

**遇到“前半段满足 A，后半段满足 B”的题，往往应当先想分界线与正反字符串扫描。**

---

# 七、真题 2：CF547E — Mike and Friends

**题目**：[Codeforces 547E](https://codeforces.com/problemset/problem/547/E)

给定 $n$ 个字符串 $s_1,\ldots,s_n$。每次询问 $(l,r,k)$：

> 模式串 $s_k$ 在 $s_l,s_{l+1},\ldots,s_r$ 中**总共出现多少次**？

也就是：

$$
\boxed{\sum_{i=l}^{r} \#\operatorname{Occ}_{s_i}(s_k)}
$$

这一题非常经典，因为它把“每个模式的 Occurrence”变成了“按字符串编号的区间求和”。

## 7.1 如果每次查询都跑 KMP？

一次查询需要扫描 $s_l$ 到 $s_r$，多次询问可能反复扫描大量文本。模式数、询问数都很大，这样做不行。

从另一方向想：**先处理好所有模式，并把每个字符串编号看成时间。**

1. 所有 $s_i$ 都先插入 AC 自动机；`end[k]` 表示模式 $s_k$ 的终点节点。
2. 从 $i=1$ 到 $n$，依次把 $s_i$ 当成文本扫描一遍。扫描新字符串时，**从根重新开始**，不能把相邻字符串错误地拼接起来。
3. 每读入一个字符，当前 AC 状态为 $u$，就对 Fail Tree 的 `tin[u]` 加 $1$。
4. 扫描完前 $r$ 个字符串后，`end[k]` 的 Fail 子树上累积的访问次数，恰好是 $s_k$ 在 $s_1,\ldots,s_r$ 中的总出现次数。

记：

$$
F(r,k)=\sum_{i=1}^{r}\#\operatorname{Occ}_{s_i}(s_k).
$$

那么所求就是：

$$
\boxed{F(r,k)-F(l-1,k)}.
$$

这就是典型的离线前缀差分。

## 7.2 一次扫描时，到底往哪里加？

假设模式为：

```text
a, aa
```

扫描文本 `aaa`，自动机经历：

```text
a, aa, aa
```

我们**只在实际到达的状态**打点：

```text
访问次数：a 有 1 次；aa 有 2 次
```

然后查询模式 `a` 的终点 `a` 所在的 Fail 子树，其中包括 `a` 和 `aa`，得到 $1+2=3$；查 `aa` 的子树，只得到 $2$。

所以不要每次扫描时就沿 Fail 链给所有祖先加值，否则可能变慢；把统计工作转交给子树查询更合适。

## 7.3 离线处理的完整模型

把每个询问 $(l,r,k)$ 拆成两个事件：

- 在扫描完 $r$ 个字符串时，贡献 $+\operatorname{query}(end[k])$；
- 在扫描完 $l-1$ 个字符串时，贡献 $-\operatorname{query}(end[k])$。

维护一个 BIT：

```cpp
// 每扫描到一个文本字符：
bit.add(tin[state], 1);

// 在扫到时间 r 的查询事件：
long long value = bit.sum(tout[end[k]] - 1)
                - bit.sum(tin[end[k]] - 1);
```

这里只展示含义：上述 `bit.sum(pos)` 是包含 `pos` 的前缀和，`tin/tout` 为半开 DFS 序。实际实现时保持 BIT 下标与 DFS 序的 $0/1$ 起点一致即可。

最终复杂度大约是：

$$
O\big((\sum |s_i|+q)\log M+26M\big),
$$

其中 $M$ 为 Trie 节点数。精确的建图与常数依实现而异。

### 这一题的可迁移结论

$$
\boxed{\text{模式匹配 + 按文本编号的区间限制}}
$$

$$
\Downarrow
$$

$$
\boxed{\text{Fail 子树计数 + 离线扫描线 + 前缀差分}}
$$

第 4 讲学习 SA 后，我们还会发现同一题可以转成**后缀排名区间 + 二维数点**。这很适合用来对比：相同的 Occurrence 问题，不同字符串结构提供了不同坐标系。

---

# 八、真题 3：CF163E — e-Government

**题目**：[Codeforces 163E](https://codeforces.com/problemset/problem/163/E)

先给定一组互不相同的模式串。所有模式最初启用，支持：

- `+ i`：启用第 $i$ 个模式；
- `- i`：禁用第 $i$ 个模式；
- `? T`：询问当前启用的所有模式在文本 $T$ 中的出现次数之和（允许重叠）。

与上一题不同：**模式串的集合不会新增字符串，只是每个模式的权值在 $0$ 与 $1$ 之间变化。**

## 8.1 先想暴力模型

扫描文本 $T$ 的某个位置时，状态为 $u$。所有在这个位置结束的模式，其终点节点都在 $u$ 的 Fail 祖先链上。

所以当前位置的贡献是：

$$
\boxed{\sum_{v\text{ 是 }u\text{ 的 Fail 祖先}} active[v]}.
$$

其中 `active[v]` 是终点 $v$ 对应模式的当前启用权值。

如果对每个文本位置都沿 Fail 链累加，最坏可能很慢；例如一大堆 `a,aa,aaa,...`，每读一个 `a` 都要跳很多层。

## 8.2 从“祖先路径求和”转成“子树加、点查询”

如果启用一个模式，其终点为 $v$：

> 哪些自动机状态 $u$ 会因此在扫描时多产生一次贡献？

答案：**所有以 $v$ 为 Fail 祖先的 $u$**，也就是 Fail Tree 中 $v$ 的**整个子树**。

因此：

- 启用模式 $v$：对 Fail Tree 子树 $v$ 加 $1$；
- 禁用模式 $v$：对子树 $v$ 加 $-1$；
- 扫描文本到状态 $u$：查询点 `tin[u]` 当前的权值。

有 DFS 序以后：

$$
\operatorname{subtree}(v)=[tin[v],tout[v]).
$$

就变成常见的“区间加、单点查”，可以用 BIT 维护差分数组。

### 用 `a`、`aa` 看状态变化

```text
模式：a, aa
文本：aaa
```

开始都启用。Fail Tree 为：

```text
root
 └─ a
     └─ aa
```

把 `a` 启用，相当于对 `a` 的整个子树加 $1$；把 `aa` 启用，又对 `aa` 子树加 $1$。

扫描 `aaa` 的三个状态：

```text
a   -> 查询值 1（匹配 a）
aa  -> 查询值 2（匹配 a、aa）
aa  -> 查询值 2（匹配 a、aa）
```

总贡献：$1+2+2=5$。

若禁用 `aa`，则其子树减 $1$，三个扫描位置都只贡献一个 `a`，答案变为 $3$。

## 8.3 为什么它和 CF547E 方向相反？

这是一组特别值得对比的模型：

| 问题 | 更新 | 查询 |
|---|---|---|
| CF547E：固定模式，文本一个个加入 | 访问状态 $u$：**单点加** | 模式终点 $v$：**子树求和** |
| CF163E：模式启停，文本不断来 | 模式终点 $v$：**子树加** | 扫描状态 $u$：**单点查** |

**一个匹配关系，在“以模式为中心”或“以扫描状态为中心”时，数据结构的操作方向会反过来。**

实际写代码时还要用 `bool enabled[i]` 保存模式当前是否启用。题目允许重复启用已经启用的模式、或重复禁用已经禁用的模式，这两种操作不能重复加减。

---

# 九、从匹配算法到自动机 DP

到目前为止，我们一直在扫描**给定文本**。接下来换一个问题：

> 如果文本本身需要我们构造，怎样保证它包含（或不包含）某些模式串？

一旦建立 AC 自动机，无论读入哪个字符，都有确定的下一状态：

$$
\boxed{u\xrightarrow{c}go[u][c]}.
$$

因此**构造一个字符串**，就等价于**从根状态出发，在这个有向图上走若干步**。

在这个过程中，我们通常只需要记：

- 已构造长度 $i$；
- 当前自动机状态 $u$；
- 已经满足了哪些额外条件（例如哪些模式曾出现过）。

## 9.1 禁止出现某些模式：把“坏状态”删掉

例如模式为 `ab`，想统计长度为 $L$ 的小写字母串中，不包含 `ab` 的数量。

当扫描状态 $u$ 对应的 Fail 链上存在模式终点，就说明**某个被禁用的模式已经出现**。因此这种状态不能继续作为合法 DP 状态。

定义 `bad[u]`：

$$
bad[u]=terminal[u]>0\ \text{或}\ bad[fail[u]].
$$

这个性质可以按 BFS 顺序计算。

令：

$$
dp[i][u]=\text{长度为 }i\text{，尚未出现禁用模式，当前状态为 }u\text{ 的字符串数}.
$$

转移：

$$
\boxed{
 dp[i+1][go[u][c]]\mathrel{+}=dp[i][u],
 \quad \text{仅当 }bad[go[u][c]]=false
}
$$

扫完所有 $L$ 个字符，把所有合法状态相加，就是答案。

**这里最重要的思考方式是：把一个全局条件“从头到尾不能出现模式”转成局部条件“每一步不能进入坏状态”。**

## 9.2 要求所有模式都出现：额外维护 bitmask

如果模式只有 $N\le8$ 个，可以用一个 $N$ 位二进制数记录哪些模式已经出现。

令：

$$
mask=\text{已经出现过的模式编号集合}.
$$

再定义：

$$
outMask[u]=\text{在状态 }u\text{ 结束的全部模式编号集合}.
$$

要注意：`outMask[u]` 不是仅仅存储 Trie 节点 $u$ 自己是哪些模式终点，还要合并 Fail 祖先上的模式。

因此：

$$
\boxed{outMask[u]=terminalMask[u]\ \mathrm{OR}\ outMask[fail[u]]}.
$$

那么加入一个字符 $c$ 后：

$$
v=go[u][c],\qquad newMask=mask\;\mathrm{OR}\;outMask[v].
$$

这就得到经典的：

$$
\boxed{dp[i][u][mask]}
$$

即自动机状态 + 状压 DP。

---

# 十、2025 年真题：AtCoder ABC419 F — All Included

**题目**：[AtCoder ABC419 F](https://atcoder.jp/contests/abc419/tasks/abc419_f)　｜　[官方题解](https://atcoder.jp/contests/abc419/editorial/13661)

给定 $N$ 个模式串与整数 $L$，问有多少长度恰好为 $L$ 的小写英文字母串，**包含所有给定模式作为子串**。对 $998244353$ 取模。

限制：

$$
N\le8,\quad L\le100,\quad |s_i|\le10.
$$

这道 2025 年的题很适合作为“AC 自动机本身只负责记录匹配状态，其他条件交给 DP”的教学例子。

## 10.1 为什么不能直接暴力构造？

有 $26^L$ 个候选字符串。即使 $L$ 很小，也完全枚举不了。

但“已经构造的整个前缀”其实包含大量对未来无关的信息。

考虑我们构造到：

```text
...abc
```

假设模式只有 `ab`、`bc`、`cde`。将来接一个字符时，我们只关心：

- 当前结尾是否能继续构成某个模式的前缀；
- 哪些模式以前已经完整出现。

因此历史可以压缩成两个量：

```text
AC 状态：u
出现集合：mask
```

例如模式 `ab` 与 `c`：

```text
当前构造：abc
```

扫描时：

- 读 `a`：状态 `a`，`mask=00`；
- 读 `b`：状态 `ab`，匹配 `ab`，`mask=01`；
- 读 `c`：状态 `c`，匹配 `c`，`mask=11`。

之后无论再接什么字符，`mask=11` 都不会失效，因为**某个模式“曾经出现过”是不可逆的事实**。

## 10.2 状态和转移

定义：

$$
 dp[i][mask][u]
 =\text{长度为 }i\text{，已出现模式集合为 }mask\text{，AC 状态为 }u\text{ 的方案数}.
$$

初始：

$$
 dp[0][0][root]=1.
$$

枚举下一个字符 $c$：

$$
v=go[u][c],\quad mask'=mask\;|\;outMask[v].
$$

因此：

$$
\boxed{dp[i+1][mask'][v]\mathrel{+}=dp[i][mask][u]}.
$$

最后答案：

$$
\boxed{\sum_u dp[L][(1\ll N)-1][u]\pmod{998244353}}.
$$

因为所有 $N$ 个模式都出现过，说明 `mask` 的 $N$ 位全为 $1$。

## 10.3 和前面的 AC 模板如何拼接？

插入第 $i$ 个模式之后，在它的终点节点设置第 $i$ 位：

```cpp
int endpoint = ac.insert(s[i]);
ac.tr[endpoint].outMask |= 1 << i;
```

`build()` 中的这一句：

```cpp
tr[u].outMask |= tr[tr[u].fail].outMask;
```

会把“同时在本位置结束”的其他模式也算进去。

下面是主 DP 部分（假定已按上述方式建好 `ac`）：

```cpp
constexpr int MOD = 998244353;
int M = (int)ac.tr.size();
int ALL = 1 << N;
vector<vector<int>> dp(ALL, vector<int>(M, 0));
dp[0][0] = 1;

for (int pos = 0; pos < L; pos++) {
    vector<vector<int>> ndp(ALL, vector<int>(M, 0));
    for (int mask = 0; mask < ALL; mask++) {
        for (int u = 0; u < M; u++) {
            int ways = dp[mask][u];
            if (!ways) continue;
            for (int c = 0; c < 26; c++) {
                int v = ac.tr[u].go[c];
                int nmask = mask | ac.tr[v].outMask;
                int &target = ndp[nmask][v];
                target += ways;
                if (target >= MOD) target -= MOD;
            }
        }
    }
    dp.swap(ndp);
}

int ans = 0;
for (int ways : dp[ALL - 1]) {
    ans += ways;
    if (ans >= MOD) ans -= MOD;
}
cout << ans << '\n';
```

这里对同一个状态枚举的不同字符，即使它们转移到相同节点，也必须各自计数，因为构造出的文本字符串不同。

官方样例 `N=2, L=4, {ab,c}` 的答案是 **153**；这不是“有 153 种拼接方法”，而是**153 个不同的长度为 4 的字符串**。

## 10.4 这类题的一般模型

$$
\boxed{\text{字符串的全局模式约束}}
\longrightarrow
\boxed{\text{AC 状态 + 一个很小的额外记忆量}}
$$

额外记忆量可以是：

- 已出现模式集合 `mask`；
- 是否进入过禁用状态；
- 已匹配模式数是否达到 $k$；
- 当前获得的权值；
- 模某个整数的余数。

注意：AC 自动机只负责“下一字符之后，后缀匹配状态是什么”。**具体计数/最优值/限制条件通常都在 DP 那一层。**

---

# 十一、进阶：动态新增/删除模式与自动机上的矩阵

## 11.1 CF710F — String Set Queries：模式真的发生增删怎么办？

**题目**：[Codeforces 710F](https://codeforces.com/problemset/problem/710/F)

与 CF163E 不同，这题的模式集合会**在线新增、删除字符串**，新模式不一定事先给出。此时不能简单把一个模式的终点权值改掉：新模式可能需要给 Trie 增加大量新节点，已有 Fail 和转移都会受影响。

一种常见方法叫**二进制分组重建**：

- 把当前加入过的模式分成若干组，每组包含 $2^k$ 个模式；
- 每一组单独构建一台 AC 自动机；
- 新增一个模式时，像二进制加法一样，把同大小的组不断合并并重建；
- 每个模式在它的生命周期中被合并/重建 $O(\log n)$ 次。

若要支持删除，可维护两套集合：

$$
\boxed{\text{答案}=\text{历史加入模式的总贡献}-\text{历史删除模式的总贡献}}.
$$

两套集合都只做“新增”，因此均可使用二进制分组。查询文本时扫描所有非空组的 AC，然后相加/相减。

这里最有价值的不是记住某份动态 AC 模板，而是：

> **静态结构难以直接支持插入时，可以把在线更新改造成少量静态结构的定期重建。**

同样的思想也用于动态凸包、分块维护等场景。

## 11.2 若长度极大：AC 状态上的矩阵快速幂

假设要构造长度 $L$ 的文本，$L$ 可能达到 $10^{12}$，每次加字符得到的收益只取决于当前状态和下一状态。

设进入状态 $v$ 时，本位置结束的所有模式权值之和是 $w[v]$。

普通最优化 DP 是：

$$
dp[i+1][go[u][c]]
=\max\big(dp[i+1][go[u][c]],\ dp[i][u]+w[go[u][c]]\big).
$$

这就是自动机图上走恰好 $L$ 步的最长路（允许重复访问状态）。

可以定义 max-plus 矩阵：

$$
A_{u,v}=\max_{c:\ go[u][c]=v} w[v],
$$

不存在转移则是 $-\infty$，矩阵乘法定义为：

$$
(C=A\otimes B)_{i,j}=\max_k\{A_{i,k}+B_{k,j}\}.
$$

再对 $A$ 做快速幂就能处理极长的 $L$。经典练习是 [CF696D — Legen...](https://codeforces.com/problemset/problem/696/D)。

如果问的是**方案数**，矩阵里的运算就换回普通的加法和乘法，并且如果多个字符有相同的 $u\to v$ 转移，矩阵元素应当记录这个转移的**字符数量**，不能只设成 $1$。

---

# 十二、容易混淆的几个问题

## 12.1 `terminal[u]` 与 `out[u]` 不一样

- `terminal[u]`：恰好以 Trie 节点 $u$ 结束的模式数量；
- `out[u]`：以当前扫描状态 $u$ 结尾的**所有**模式数量（包括 Fail 链上的终点）。

例如模式 `he, she`，当前状态 `she`：

```text
terminal[she] = 1
out[she]      = 2
```

因为 `he` 也刚刚结束了。

## 12.2 扫描时直接跳 Fail，还是构建时补全转移？

二者描述的是同一件事：

- 未补全的 Trie：当前字符没有对应儿子，就沿 Fail 链退；
- 补全后的 `go`：这件事预先做成表，扫描时一次查表。

但补全转移之后，**不能再把 `go` 当作原始 Trie 儿子关系**。这一点对后续变形尤其重要。

## 12.3 “存在一次”与“出现多少次”不能乱用同一份代码

- **统计每个模式的出现次数**：扫描状态计数 + Fail 逆序上传；
- **寻找所有匹配的具体位置**：沿 Output Link 列举终点，代价与实际输出量有关；
- **判断是否至少出现一次**：计数是否大于 $0$，或者用布尔信息上传；
- **统计有多少个不同模式至少出现一次**：对终点做去重，不要把多次 Occurrence 当成多个模式。

## 12.4 重复模式与相同字符串下标

若输入：

```text
a
 a
 aa
```

前两个模式是**不同编号**，但对应同一 Trie 终点。若题目要求按模式编号回答，两个答案相同；若要求“所有模式匹配贡献之和”，这个终点的重数应是 $2$。

## 12.5 为什么有人说“Fail Tree”，有人说“字典图”？

它们是不同视角：

- Trie：表示**字符串集合的前缀**；
- 完整 AC 转移图：表示**读一个字符后该去哪里**；
- Fail Tree：表示**最长可用后缀的包含关系**。

解题时常需要先把 Trie 转成完整转移图扫描，再把统计量放到 Fail Tree 上处理。它们不是三种不同算法，而是同一个 AC 自动机的三种用法。

---

# 十三、练习路线

建议先做 Trie 独立题，再做 AC 的 Occurrence / Fail Tree 题。下表按“模型”而不是按模板分类：

| 难度 | 题目 | 重点训练 |
|---|---|---|
| 基础 | [ABC353 E — Yet Another Sigma Problem（2024）](https://atcoder.jp/contests/abc353/tasks/abc353_e) | Trie 节点贡献与两两 LCP |
| 中档 | [ABC377 G — Edit to Match（2024）](https://atcoder.jp/contests/abc377/tasks/abc377_g) | Trie 上维护前缀子树最优值 |
| 中档 | [ABC403 E — Forbidden Prefix（2025）](https://atcoder.jp/contests/abc403/tasks/abc403_e) | 动态禁止前缀、单调覆盖 |
| 提高 | [2024 ICPC 香港 G — Yelkrab](https://qoj.ac/problem/9921/statement/zh_cn) | Trie 深度优先分组 + 整除增量维护 |
| 提高 | [CF455B — A Lot of Games](https://codeforces.com/problemset/problem/455/B) | Trie 上博弈 DP |
| 提高 | [2024 ICPC 昆明邀请赛 D — Generated String](https://www.luogu.com/article/68qflomx) | 正反 Trie → 二维区间、隐式字符串比较 |
| 选讲 | [CF706D — Vasiliy's Multiset](https://codeforces.com/problemset/problem/706/D) | 01 Trie 动态维护与按位贪心 |
| 入门 | [洛谷 P5357 — AC 自动机（二次加强版）](https://www.luogu.com.cn/problem/P5357) | 多模式出现次数；逆序 Fail 上传 |
| 入门 | [CSES — Counting Patterns](https://cses.fi/problemset/task/2103) | Occurrence 数量与 Fail Tree |
| 基础 | [CSES — Word Combinations](https://cses.fi/problemset/task/1731) | AC 匹配 + 字典分词 DP |
| 提高 | [CF1202E — You Are Given Some Strings...](https://codeforces.com/problemset/problem/1202/E) | 正反 AC + 拼接分界线 |
| 提高 | [CF547E — Mike and Friends](https://codeforces.com/problemset/problem/547/E) | Fail Tree + 扫描线 + BIT |
| 提高 | [ABC419F — All Included（2025）](https://atcoder.jp/contests/abc419/tasks/abc419_f) | AC 状态 + bitmask DP |
| 进阶 | [CF163E — e-Government](https://codeforces.com/problemset/problem/163/E) | 模式启停 + 子树加、单点查 |
| 进阶 | [CF710F — String Set Queries](https://codeforces.com/problemset/problem/710/F) | 动态插入/删除 + 二进制分组 |
| 进阶 | [CF696D — Legen...](https://codeforces.com/problemset/problem/696/D) | AC 上最优路径 + max-plus 矩阵 |

建议课堂精讲 **ABC353E、Yelkrab、ABC403E、CF547E**：分别代表“LCP 转节点贡献”“Trie 分组 + 约数更新”“前缀子树的单调覆盖”“AC 的 Occurrence 转树上查询”。时间允许再补 ABC377G 与 CF1202E / ABC419F。

---

# 十四、看到什么想到什么？

| 题目中的描述 | 优先考虑 |
|---|---|
| 两两 LCP 之和 | Trie 节点对数贡献 $\sum\binom{pass[u]}2$ |
| 按 LCP 最优分组 | Trie 子树从深到浅贪心 |
| 字符串插入后所有前缀贡献变化 | Trie 路径 `pass` 增量 |
| 某个前缀禁止所有以它开头的串 | Trie 子树覆盖 / 单调维护 |
| 前缀、后缀同时受约束 | 正反 Trie + 二维数点 |
| 一个串通过删尾、加尾变为另一串 | LCP + Trie 子树最优值 |
| 字符串接龙和轮流补字符 | Trie 树上博弈 DP |
| 动态整数最大 XOR | 01 Trie + 按位贪心 |
| 给很多模式串，一段文本，要找匹配 | AC 自动机 |
| 模式共享前缀、按字典序维护 | Trie |
| 多模式 Occurrence 的**总次数** | AC + Fail Tree 计数上传 |
| 同一位置可能匹配多个模式 | Fail 祖先链 / Output Link |
| 某模式在一段文本内出现多少次 | 终点节点的 Fail 子树计数 |
| 询问文本编号区间 $[l,r]$ 中的模式出现次数 | 离线扫描 + 前缀差分 + BIT |
| 已知全部模式，支持启用/禁用 | Fail Tree 子树加、单点查 |
| 模式真的在线新增/删除 | 多个静态 AC + 二进制分组重建 |
| 模式不能出现 | AC + bad 状态 + DP |
| 所有模式都要出现，模式数小 | AC + bitmask DP |
| 模式出现次数可以计分，构造极长文本 | AC + 最优化 DP / 矩阵 |
| 左模式与右模式拼接后出现 | 正反 AC + 枚举分界线 |
| 出现位置要求具体输出 | Output Link，注意输出规模 |

---

# 十五、本讲速查

**0. Trie 的几条核心转换**

$$
\boxed{\text{前缀}\leftrightarrow\text{祖先/子树}}\qquad
\boxed{LCP(s,t)=dep[LCA(s,t)]}
$$

$$
\boxed{\sum_{i<j}LCP(s_i,s_j)=\sum_{u\ne root}\binom{pass[u]}2}
$$

$$
\boxed{f_{Yelkrab}(i,k)=\sum_{u\ne root}\left\lfloor\frac{cnt_i[u]}k\right\rfloor}
$$

$$
\boxed{\Delta\lfloor c/k\rfloor=[k\mid c]}
$$


**1. Fail 的语义**

$$
\boxed{fail[u]=\text{当前 Trie 字符串的最长真后缀，且仍是某模式的前缀}}
$$

**2. 转移补全**

$$
\boxed{go[u][c]=\text{Trie 儿子（若存在），否则 }go[fail[u]][c]}
$$

**3. 匹配条件**

$$
\boxed{P\text{ 在文本当前位置结束}\iff end(P)\text{ 是当前状态的 Fail 祖先}}
$$

**4. Occurrence 计数**

$$
\boxed{\#\operatorname{Occ}_T(P)=\sum_{u\in subtree_{fail}(end(P))} cnt[u]}
$$

其中 $cnt[u]$ 是扫描文本时直接到达状态 $u$ 的次数。

**5. Fail Tree DFS 序**

$$
\boxed{\operatorname{subtree}(u)\leftrightarrow[tin[u],tout[u])}
$$

**6. 动态模式启停**

$$
\boxed{\text{模式终点的子树加权}\Longleftrightarrow\text{扫描状态的祖先链权值和}}
$$

**7. 自动机 DP 的基本套路**

$$
\boxed{dp[\text{长度}][\text{AC 状态}][\text{额外记忆}]}.
$$

**最想让读者带走的两句话：**

> Trie 不是 AC 的附属模板。它把“字符串的公共前缀”变成**一棵可以统计、贪心、做 DP、做子树操作的树**。

> 当匹配从“从头开始的前缀关系”推广成“文本任意位置的模式出现”时，才需要借助 Fail 把 Trie 变成 AC 自动机；而 Fail Tree 负责把 Occurrence 再转回树上统计。

---

## 资料与出处

**Trie 专题真题与官方解析**

- [2024 ICPC 香港 G — Yelkrab（题面）](https://qoj.ac/problem/9921/statement/zh_cn)；[官方分析（PDF）](https://qoj.ac/download.php?id=1885&r=1&type=attachments)
- [ABC353 E — Yet Another Sigma Problem（2024）](https://atcoder.jp/contests/abc353/tasks/abc353_e)；[官方题解](https://atcoder.jp/contests/abc353/editorial/10110)
- [ABC377 G — Edit to Match（2024）](https://atcoder.jp/contests/abc377/tasks/abc377_g)；[官方题解](https://atcoder.jp/contests/abc377/editorial/11245)
- [ABC403 E — Forbidden Prefix（2025）](https://atcoder.jp/contests/abc403/tasks/abc403_e)；[官方题解](https://atcoder.jp/contests/abc403/editorial/12832)
- [2024 ICPC 昆明邀请赛 D — Generated String](https://www.luogu.com/article/68qflomx)
- [CF455B — A Lot of Games](https://codeforces.com/problemset/problem/455/B)；[CF706D — Vasiliy's Multiset](https://codeforces.com/problemset/problem/706/D)

**基础原理**

1. [OI Wiki：AC 自动机](https://oi.wiki/string/ac-automaton/)：Trie、Fail、字典图、Fail Tree、拓扑上传和 AC 上 DP。
2. [cp-algorithms：Aho–Corasick algorithm](https://cp-algorithms.com/string/aho_corasick.html)：自动机定义、Fail 和转移补全。

**题目与进一步阅读**

3. [洛谷 P5357：AC 自动机（二次加强版）](https://www.luogu.com.cn/problem/P5357)
4. [CF1202E：You Are Given Some Strings...](https://codeforces.com/problemset/problem/1202/E)
5. [CF547E：Mike and Friends](https://codeforces.com/problemset/problem/547/E)
6. [CF163E：e-Government](https://codeforces.com/problemset/problem/163/E)
7. [ABC419F：All Included（2025）](https://atcoder.jp/contests/abc419/tasks/abc419_f) 和 [官方题解](https://atcoder.jp/contests/abc419/editorial/13661)
8. [CF710F：String Set Queries](https://codeforces.com/problemset/problem/710/F)
9. [CF696D：Legen...](https://codeforces.com/problemset/problem/696/D)
10. [CSES：Word Combinations](https://cses.fi/problemset/task/1731)

> **下节预告**：第 4 讲进入后缀数组与后缀树。它将进一步推广本章的“前缀对应连续子树/区间”视角：**所有以同一个串为前缀的后缀，在 SA 中占据连续排名区间**。而 AC 的 Fail Tree 则从后缀匹配关系的另一侧表示 Occurrence。
