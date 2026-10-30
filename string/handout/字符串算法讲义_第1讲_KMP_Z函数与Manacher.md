# 第 1 讲　线性字符串算法：KMP、Z 函数与 Manacher

> **课程定位**：面向有基础算法知识、但可能第一次系统学习字符串算法的 ICPC / CCPC / OI 选手。重点不是背代码，而是弄清楚**每个数组记录了什么、算法为什么能复用已经比较过的字符、实际做题怎样转化**。  
> **先修**：第 0 讲的前缀、后缀、子串、Occurrence、LCP 与 Hash。  
> **约定**：下标从 **0** 开始，子串用半开区间 `S[l,r)`；`n=|S|`。除特别说明外，讨论非空模式串。  
> **本讲目标**：会调用并理解 `pi / z / d1 / d2`；看到匹配、前缀重叠、非重叠重复、回文区间等条件，能判断该用哪个数组、如何转化。Border 的周期引理和等差数列分解留到第 2 讲。

---

## 0. 三种算法究竟在解决什么问题？

先想三个问题：

1. 模式串 `aba` 在文本 `ababa` 的哪些位置出现？
2. `abacaba` 从每个位置开始，与**整个串的前缀**能连续相同多长？
3. `abacaba` 以每个位置为中心，最长的回文子串有多长？

它们的朴素做法很像：从一个位置开始，不断比较两个字符，直到不相同。但如果每个位置都重新开始比较，在 `aaaaaaaa...` 这样的字符串上就容易退化到平方复杂度。

这三种线性算法的共同点是：**前面已经比较出的相等关系，不应该浪费。**

| 算法 | 输出的核心信息 | 最典型的问题 | 复用什么信息 |
|---|---|---|---|
| **KMP / Prefix Function** | 每个前缀的最长真 Border 长度 `pi[i]` | 找 Occurrence、前后缀关系 | 已匹配部分的 Border |
| **Z Function** | `z[i]=LCP(S[0,n),S[i,n))` | 前缀与每个后缀的 LCP、匹配、重叠 | 已知的 Z-Box |
| **Manacher** | 每个中心的最大奇/偶回文半径 | 回文区间、最长回文、回文计数 | 回文区间内的镜像对称 |

**课堂要反复强调的区分：** KMP 和 Z 主要处理**相同字符顺序的匹配**；Manacher 主要处理**左右反向的对称**。不要因为三者都叫“线性字符串算法”，就把它们看成同一种题。

---

# 一、KMP：失配时，已经匹配的部分不必全部丢掉

## 1.1 从最朴素的模式匹配开始

设模式串 `P=ababaca`，文本串 `T=abababaca`。

如果从文本第 0 个字符开始比较：

```text
T:  a b a b a b a c a
P:  a b a b a c a
    ✓ ✓ ✓ ✓ ✓ ×
```

前五个字符 `ababa` 都匹配成功，直到文本的第 5 个字符 `b`，才发现它与模式第 5 个字符 `c` 不相同。

最朴素的想法是：把模式串整体往右挪 1 位，从头重比。这会浪费刚刚已经知道的五个相等关系。

但是注意，已匹配部分是 `ababa`。它的**前缀** `aba`，恰好也等于它的**后缀** `aba`：

```text
已经匹配： a b a b a
前缀 aba ： a b a
后缀 aba ：     a b a
```

所以即使这一次完整匹配失败，我们仍知道文本刚扫过的最后三个字符是 `aba`。完全可以把它当作下一次匹配的开头，接着比较当前位置的 `b`。

```text
T:    a b a b a b a c a
P:        a b a b a c a
          ✓ ✓ ✓ ✓ ✓ ✓ ✓
```

最终在下标 **2** 找到完整的 `ababaca`。

**KMP 的核心不是“巧妙地挪动模式串”，而是：**

> 我们已经匹配了一段前缀，失配时，要保留它**仍有可能作为模式串前缀**的最长后缀。

---

## 1.2 Prefix Function `pi[i]` 的意义

定义：

$$
\pi[i]=\max\{k:0<k<i+1,\; S[0,k)=S[i-k+1,i+1)\}.
$$

即：**前缀 `S[0,i+1)` 的最长真 Border 长度**。所谓真 Border，是不把整个字符串本身算进去。

例如：

```text
S:        a b a b a c a
下标:     0 1 2 3 4 5 6
pi:       0 0 1 2 3 0 1
```

我们挑三个位置手动理解：

- `i=2`：当前前缀是 `aba`，开头和结尾都是 `a`，所以 `pi[2]=1`。
- `i=4`：当前前缀是 `ababa`，前后都能取出 `aba`，所以 `pi[4]=3`。
- `i=5`：当前前缀是 `ababac`，没有非空前缀能同时做后缀，所以 `pi[5]=0`。

可以这样理解 `pi[i]`：当你读完整个 `S[0,i+1)` 后，**如果还想把它的末尾当作下一轮匹配的开头，最多能保留多少字符？**

---

## 1.3 `pi` 为什么能在线性扫描中计算出来？

已经知道 `pi[0],...,pi[i-1]`，现在想算 `pi[i]`。

令：

$$
j=\pi[i-1].
$$

这意味着 `S[0,j)` 已经等于 `S[0,i)` 的长度为 `j` 的后缀。我们只需要尝试把新字符 `S[i]` 接在后面。

- 如果 `S[j]==S[i]`，那么相等的前后缀可以一起延长 1，答案为 `j+1`。
- 如果不等，长度 `j` 不可行；下一个候选也不能随便猜，它必然是 **`S[0,j)` 的 Border**，所以让 `j=pi[j-1]`。
- 一直跳到某个长度可以接上当前字符，或跳到 `0`。

以 `S=ababaca` 计算 `pi[5]` 为例：

```text
当前前缀：a b a b a c
前 5 位 ：a b a b a       pi[4] = 3
                        尝试延长 aba

j = 3：S[3] = b，S[5] = c，不等
j = 1：S[1] = b，S[5] = c，不等
j = 0：S[0] = a，S[5] = c，不等
所以 pi[5] = 0
```

为什么从 `3` 直接跳到 `1`，而不用检查 `2`？因为 `ababa` 的后缀如果还要等于整个模式的某个前缀，那么它必须沿着 Border 链依次变短；`2` 根本不可能是候选。

**最值得掌握的结构性结论：**

$$
\boxed{\text{一个前缀的所有真 Border 长度}=\pi[i],\pi[\pi[i]-1],\ldots}
$$

下一讲会专门把这条链组织成 Fail Tree，再研究周期结构。

### KMP / Prefix Function 模板（可用于字符串和整型序列）

```cpp
// a 支持 size()、operator[] 和元素相等比较。
template<class Seq>
vector<int> prefix_function(const Seq& a){
    int n=a.size();
    vector<int> pi(n);

    for(int i=1;i<n;i++){
        int j=pi[i-1];
        while(j>0&&a[i]!=a[j])
            j=pi[j-1];
        if(a[i]==a[j]) j++;
        pi[i]=j;
    }
    return pi;
}
```

这里不展开冗长的摊还证明，只需直观理解：`i` 一直向右走；`j` 成功时逐次增长，失配时只能沿 `pi` 严格变小，整体不会反复扫描已经处理过的字符。构造时间为 **`O(n)`**。

---

## 1.4 用 KMP 找到全部 Occurrence

扫描文本时维护 `j`：**模式串已经有多少个开头字符匹配成功**。

遇到文本字符 `c`：

1. 若它不能接到当前长度 `j` 的匹配后面，沿 `pi[j-1]` 回退。
2. 若可以接，就令 `j++`。
3. 若 `j==|P|`，说明模式完整出现，输出起点；之后仍沿 `pi` 回退，而不是把 `j` 清零。

为什么匹配成功后也不能清零？

```text
文本： a b a b a
模式： a b a
          a b a
```

`aba` 在下标 `0` 和 `2` 都出现。第一次匹配成功时，模式的末尾 `a` 也可能是下一次出现的开头。清零会漏掉这种**重叠匹配**。

```cpp
template<class Seq>
vector<int> find_occurrences(const Seq& text,const Seq& pat){
    int n=text.size(),m=pat.size();
    if(m==0) return {}; // 这里约定不处理空模式

    auto pi=prefix_function(pat);
    vector<int> ans;
    int j=0;

    for(int i=0;i<n;i++){
        while(j>0&&text[i]!=pat[j])
            j=pi[j-1];
        if(text[i]==pat[j]) j++;

        if(j==m){
            ans.push_back(i-m+1);
            j=pi[j-1];
        }
    }
    return ans;
}
```

接口示例：

```cpp
find_occurrences(string("ababa"),string("aba"));
// 得到 {0,2}
```

**何时优先用 KMP？** 当模式串固定、文本从左到右流式扫描，或者对象不是字符而是整数差分、状态序列时，KMP 很自然。

---

## 1.5 不只找匹配：KMP 还可以统计“每个前缀出现了几次”

先看：

```text
S = ABACABA
```

前缀 `A` 出现 4 次；前缀 `ABA` 出现 2 次；整个串出现 1 次。

为什么可以只用 `pi` 统计？

每一个出现都可以看作：**某个前缀恰好在位置 `i` 结尾**。

若长度 `k` 的前缀在这里出现，那么 `k` 就是前缀 `S[0,i+1)` 的一个 Border，或者 `k=i+1`（整个前缀本身）。

因此先让每个前缀长度 `i` 给自己贡献 `1`，再把这个贡献沿“最长 Border”逐步传给更短的 Border：

```cpp
// pi = prefix_function(s)
int n=s.size();
vector<long long> cnt(n+1,0);

for(int i=1;i<=n;i++) cnt[i]=1;
for(int i=n;i>=1;i--){
    int p=pi[i-1];
    if(p>0) cnt[p]+=cnt[i];
}
// cnt[k] = 长度 k 的前缀在整个 s 中出现的次数
```

它并没有真的“枚举所有出现位置”，而是将出现关系转成了**一条条 Border 的祖先关系**。这也是第 2 讲 Fail Tree 的直观起点。

---

# 二、Z 函数：把“与整个串的前缀比较”一次算完

## 2.1 Z 数组恰好就是一类特殊 LCP

第 0 讲已经定义：`LCP(A,B)` 是两串从开头连续相同的最大长度。

Z 函数只是固定比较对象为整个串自身：

$$
\boxed{z[i]=LCP(S[0,n),S[i,n))},\quad i>0.
$$

约定 `z[0]=0`，因为 `S` 与自身的 LCP 虽然是 `n`，但这个值对算法没有帮助。**部分资料约定 `z[0]=n`，调用模板时要知道差别。**

例子：

```text
S:        a b a c a b a
下标:     0 1 2 3 4 5 6
z:        0 0 1 0 3 0 1
```

重点看 `z[4]=3`：

```text
整个 S：a b a c a b a
从 4 起：        a b a
                 ✓ ✓ ✓
```

从位置 `4` 开始的后缀 `aba` 与整个串的前缀 `aba` 相同，长度就是 `3`。

可见：

- `pi` 关注**每个前缀的末尾**还能与开头相同多长。
- `z` 关注**从每个位置向右**还能与开头相同多长。

两者都编码了前缀匹配信息，但查询方式完全不同。

---

## 2.2 为什么不能从每个位置暴力求 LCP？

若 `S=aaaaab`：

```text
z[1] = 4  (aaaa)
z[2] = 3  (aaa)
z[3] = 2  (aa)
z[4] = 1  (a)
z[5] = 0
```

朴素求每一个 `z[i]`，总共会做很多重复字符比较。

但注意：**如果已经知道某一大段与前缀相同，那么这段里面的字符关系其实也已知。**

这就引出 Z-Box。

---

## 2.3 Z-Box：维护一个已经验证过的匹配区间

维护 `[l,r)`，它满足：

$$
S[l,r)=S[0,r-l),
$$

并且 `r` 是当前已经得到的匹配区间中最靠右的右端点。直观上，把 `[l,r)` 想成：**我们已经验证过，这段与字符串开头一模一样。**

现在要求 `z[i]`：

**情况 A：`i>=r`。** 当前位置不在已知的匹配区间里，只能从 `0` 开始向右比较。

**情况 B：`i<r`。** 当前下标落在 Z-Box 内。因为

$$
S[l,r)=S[0,r-l),
$$

所以 `i` 处字符的相对位置，对应前缀中的 `i-l`。我们已经知道 `z[i-l]`，因此可以先得到一个无需重新比较的长度：

$$
\boxed{z[i]\ge \min(z[i-l],r-i)}.
$$

这里只能取 `min`：`z[i-l]` 可能比 Z-Box 中剩下的部分更长；**超出 `r` 的字符还没有验证过，不能直接相信。**

然后才从已知的长度继续向右暴力扩展，并更新 Z-Box。

用 `S=aaaaab` 看 `i=2`：

```text
下标： 0 1 2 3 4 5
字符： a a a a a b

已知 z[1]=4，所以 [l,r)=[1,5) 与前缀 aaaa 相同。
现在 i=2 位于 Z-Box 中。

前缀对应位置 i-l=1，z[1]=4
但 [2,5) 只有 3 个字符。
所以先确定 z[2] 至少为 min(4,3)=3。
再比较下一个字符：S[3]=a 与 S[5]=b，不相等。
最终 z[2]=3。
```

**Z 算法真正节约的是：已知匹配盒子内部的字符不重新比较。**

### Z 函数模板

```cpp
template<class Seq>
vector<int> z_function(const Seq& s){
    int n=s.size();
    vector<int> z(n);
    int l=0,r=0;  // 已验证区间 [l,r)

    for(int i=1;i<n;i++){
        if(i<r)
            z[i]=min(r-i,z[i-l]);

        while(i+z[i]<n&&s[z[i]]==s[i+z[i]])
            z[i]++;

        if(i+z[i]>r){
            l=i;
            r=i+z[i];
        }
    }
    return z;
}
```

复杂度为 `O(n)`。直观理由：每次真正扩展匹配、突破旧的右端点时，`r` 都只会向右移动，至多到 `n`。

---

## 2.4 用 Z 找模式串的全部 Occurrence

若模式 `P=aba`，文本 `T=ababa`，拼接：

```text
U = aba#ababa
    ^^^ ^^^^^
     P    T
```

这里的 `#` 是输入中不会出现的分隔符。

计算 `z(U)`。文本的下标 `0` 对应 `U` 的位置 `|P|+1=4`；文本下标 `2` 对应 `U` 的位置 `6`。

这两个位置都与模式前缀 `aba` 匹配至少 `3` 位，因此就是两个出现位置。

公式：

$$
\boxed{P\text{ 在 }T\text{ 的位置 }i\text{ 出现}\iff z_{P+\#+T}[|P|+1+i]\ge |P|}.
$$

```cpp
vector<int> find_occurrences_z(const string& text,const string& pat){
    int m=pat.size();
    if(m==0) return {};
    string u=pat+'#'+text;  // 假设输入不包含 '#'
    auto z=z_function(u);

    vector<int> ans;
    for(int i=0;i+(int)pat.size()<=(int)text.size();i++){
        if(z[m+1+i]>=m) ans.push_back(i);
    }
    return ans;
}
```

这也说明，**KMP 和 Z 都能做单模式匹配**。区别往往在于后续题目究竟需要 `pi` 的 Border 链，还是 `z` 给出的“每个位置与前缀的 LCP”。

---

## 2.5 Z 的另一个重要用法：判断前后缀是否重叠

给两个串 `X` 与 `Y`，要找最大 `k`：

$$
X[|X|-k,|X|)=Y[0,k).
$$

就是说，把 `Y` 接到 `X` 后面时，最多能复用多少字符？例如：

```text
X = cababa
Y = abac

X 的后缀 aba = Y 的前缀 aba
所以可以拼成 cababac
```

可以构造 `Y + '#' + X` 并计算 Z。若 X 中某位置开始的后缀，能**完整地与 Y 的前缀匹配到 X 末尾**，那就是一种合法重叠。

```cpp
int overlap(const string& X,const string& Y){
    string u=Y+'#'+X;  // 输入不包含 '#'
    auto z=z_function(u);
    int ans=0;
    int n=u.size();

    for(int i=(int)Y.size()+1;i<n;i++){
        if(i+z[i]==n)
            ans=max(ans,z[i]);
    }
    return ans;
}
```

注意：**合法的重叠长度不一定具有单调性，不能因为求最大 `k` 就直接二分。** 第 0 讲 CF1200E 已经见过这个陷阱。

---

# 三、Manacher：每个回文中心可以扩张多远？

## 3.1 为什么回文不能只按“一个中心”统一处理？

回文串从左到右和从右到左一样。它们有两种中心：

```text
奇数回文：a b a
            ↑
           中心 b

偶数回文：a b b a
            ↑
        中心在两个 b 之间
```

因此我们用两个数组：

- `d1[i]`：以字符 `i` 为中心的**奇数长度回文半径**（包含中心本身）。
- `d2[i]`：以字符 `i-1` 与 `i` 的缝隙为中心的**偶数长度回文半径**。

它们不是“回文长度”本身。具体对应：

$$
\begin{aligned}
\text{奇回文区间}&=[i-d1[i]+1,\ i+d1[i]),\\
\text{长度}&=2d1[i]-1;\\
\text{偶回文区间}&=[i-d2[i],\ i+d2[i]),\\
\text{长度}&=2d2[i].
\end{aligned}
$$

例子一：

```text
S:     a b a c a b a
下标:  0 1 2 3 4 5 6
d1:    1 2 1 4 1 2 1
```

中心 `3` 是 `c`，最大奇回文是整个 `abacaba`，所以 `d1[3]=4`，长度 `2*4-1=7`。

例子二：

```text
S:     a b b a
下标:  0 1 2 3
d2:    0 0 2 0
```

`d2[2]=2` 表示中心在下标 `1` 和 `2` 的两个 `b` 之间，向左右各覆盖两个字符，最大回文 `abba`，长度为 `4`。

---

## 3.2 朴素做法为什么会慢？

我们可以枚举每个中心，不断比较左右两个字符：

```text
abacaba
   ↑
从 c 向两侧扩张：a=a，b=b，a=a
```

单个中心可能扩张 `O(n)` 次，总体可能达到 `O(n^2)`。如一长串 `aaaaaaaa...`，几乎每个中心都可以向两侧扩很多层。

Manacher 的思路与 Z 类似：**如果已经求出一段很长的回文，它内部的镜像位置的信息就可以复用。**

---

## 3.3 回文区间和镜像位置

先只看奇回文。

维护目前右端点最靠右的回文区间 `[L,R]`（**这里用闭区间**，与本讲的子串 `[l,r)` 约定不同，仅用于解释 Manacher 模板）。

假设当前要计算中心 `i`，并且它已经落在 `[L,R]` 中。

它关于大回文中心的镜像位置为：

$$
\boxed{j=L+R-i}.
$$

因为大区间 `[L,R]` 是回文，所以 `i` 附近的一部分字符关系，和镜像中心 `j` 附近是一样的。我们至少能直接得到：

$$
\boxed{d1[i]\ge\min(d1[j],R-i+1)}.
$$

为什么还要取最小值？

- `d1[j]` 说明镜像中心有多大的回文。
- `R-i+1` 说明当前中心右侧**还有多少个位置在已知大回文内**。
- 若镜像回文伸出了大回文的边界，外面的字符还不知道是否相等，不能直接复制。

复用已知的那部分后，再尝试向左右扩张，得到真正的 `d1[i]`。这和 Z 函数的 `min(已知匹配长度,距离右边界)` 几乎一模一样。

例如 `abacaba`，中心 `3` 求出半径 `4`、覆盖 `[0,6]` 后，计算中心 `5` 时镜像位置是 `1`：

```text
S:   a b a c a b a
idx: 0 1 2 3 4 5 6
             ^   ^
             3   5
镜像中心 j = 0+6-5 = 1
已知 d1[1]=2
边界内最多 R-i+1=2
所以 d1[5] 至少为 2；实际上恰好为 2（对应 aba）。
```

---

## 3.4 奇偶两种半径的模板

```cpp
struct Manacher{
    vector<int> d1,d2;

    Manacher(const string& s){
        int n=s.size();
        d1.assign(n,0);
        d2.assign(n,0);

        // 奇数回文：d1[i] >= 1
        for(int i=0,l=0,r=-1;i<n;i++){
            int k=(i>r ? 1 : min(d1[l+r-i],r-i+1));
            while(i-k>=0&&i+k<n&&s[i-k]==s[i+k])
                k++;
            d1[i]=k;
            if(i+k-1>r){
                l=i-k+1;
                r=i+k-1;
            }
        }

        // 偶数回文：中心在 i-1 与 i 之间，d2[i] 可以为 0
        for(int i=0,l=0,r=-1;i<n;i++){
            int k=(i>r ? 0 : min(d2[l+r-i+1],r-i+1));
            while(i-k-1>=0&&i+k<n&&s[i-k-1]==s[i+k])
                k++;
            d2[i]=k;
            if(i+k-1>r){
                l=i-k;
                r=i+k-1;
            }
        }
    }

    // 判断 [l,r) 是否回文，O(1)，包含空串的情况
    bool is_pal(int l,int r)const{
        int len=r-l;
        if(len<=1) return true;
        if(len&1){
            int c=(l+r-1)/2;
            return d1[c]>=(len+1)/2;
        }
        else{
            int c=(l+r)/2;
            return d2[c]>=len/2;
        }
    }
};
```

模板中有两个最容易写错的地方：

1. 奇数回文包含中心，所以初始半径是 `1`；偶数回文没有中心字符，所以初始半径是 `0`。
2. 偶数回文以两个字符的**缝隙**为中心，因此镜像公式与向左扩张的下标都比奇数情况偏一位。

整个算法时间为 `O(n)`；大致理由同样是维护最靠右的已知回文边界，每次真正越过边界都会推进右端点。

---

## 3.5 Manacher 数组不仅能求最长回文

### 应用 1：求整个串的最长回文子串

答案是：

$$
\boxed{\max_i\{2d1[i]-1,\ 2d2[i]\}}.
$$

只需记下中心与半径，就能还原子串的 `[l,r)` 区间。

### 应用 2：统计所有回文子串（按出现位置计数）

对一个奇数中心，半径为 `d1[i]`，表示有这么多个奇数回文：长度 `1,3,...,2d1[i]-1`。

对一个偶数中心，半径为 `d2[i]`，表示有这么多个非空偶数回文：长度 `2,4,...,2d2[i]`。

所以：

$$
\boxed{\text{回文子串出现总数}=\sum_i(d1[i]+d2[i])}.
$$

例如 `aaa` 有 `a` 三次、`aa` 两次、`aaa` 一次，共 `6` 次。

**注意：这是按位置统计，不是统计“不同回文串”的个数。** 不同回文串会在第 7 讲用 PAM 解决。

### 应用 3：任意静态区间的回文判定

不必每次重新比较或使用 Hash：已经有 `d1/d2` 后，`is_pal(l,r)` 可以 `O(1)` 回答。

但如果题目允许**修改原字符串**，Manacher 的半径不能简单局部更新，此时更适合第 0 讲的正反 Hash + 线段树。

### 应用 4：以某个端点结尾的回文约束

一个回文中心及半径，等价于一段可选择的回文区间。

很多题在确定回文半径后，会继续把它转成：

- 按左端点 / 右端点统计；
- 扫描线中的区间增减；
- 差分、树状数组或 DP 转移。

Manacher 输出的是**所有回文中心的几何信息**，后续是否要加数据结构取决于题目，而不是一拿到 `d1/d2` 就结束。

---

# 四、真题精讲：如何从题目看出数组的用途？

## 4.1 CF432D — Prefixes and Suffixes：`pi` 还是出现次数工具

**题目**：[Codeforces 432D](https://codeforces.com/problemset/problem/432/D)。给一个字符串 `S`，找出所有既是前缀又是后缀的非空字符串，并统计它们分别在 `S` 中作为子串出现的次数。

输入示例：

```text
ABACABA
```

对应结果：

| 前缀长度 | 字符串 | 出现次数 |
|---:|---|---:|
| 1 | `A` | 4 |
| 3 | `ABA` | 2 |
| 7 | `ABACABA` | 1 |

**朴素思路**：枚举前缀长度 `k`，检查是否也是后缀，再枚举所有位置统计出现次数。这明显有大量重复匹配。

**第一层转化：筛选合法长度。** “既是前缀又是后缀”就是 Border。由最长 Border 沿 `pi` 不断跳转，就能取出所有合法长度。为了把整个串也算进去，从长度 `n` 开始：

$$
n\to \pi[n-1]\to \pi[\pi[n-1]-1]\to\cdots.
$$

**第二层转化：统计出现次数。** 使用第 1.5 节的 `cnt` 数组，把每个长前缀的贡献往它的最长 Border 上传。最后对所有合法 `k` 输出 `(k,cnt[k])`。

**整题的核心不是扫描文本，而是：**

$$
\boxed{\text{Occurrence 计数}\longrightarrow\text{Border 链上的贡献汇总}}.
$$

这是一道适合引出 **Fail Tree** 的例题：`pi` 不只是匹配时的回退位置，也编码了整个字符串的前后缀层次结构。

---

## 4.2 CF2010C2 — Message Transmission Error（2024）：重复拼接变成 Border 长度限制

**题目**：[Codeforces 2010C2](https://codeforces.com/problemset/problem/2010/C2)。原本发送的是同一个字符串 `P` 连续两遍，但两个副本的尾部和头部有一段**非空、且不是整个 P 的重叠**，结果接收到了字符串 `T`。给定 `T`，问能否反推出一种可能的 `P`。

例如：

```text
P = abca
两次发送：abca + abca
重叠一个 a：abcabca
T = abcabca
```

这题最有价值的是如何翻译“两个相同副本发生重叠”。

令 `n=|T|`，`m=|P|`，副本起点之间的距离为：

$$
d=n-m.
$$

第一个副本就是 `T[0,m)`，第二个副本就是 `T[n-m,n)`，因此必须：

$$
T[0,m)=T[n-m,n).
$$

也就是说，**`m` 必须是 `T` 的 Border 长度**。

另外，重叠长度：

$$
k=2m-n.
$$

题目要求 `0<k<m`，等价于：

$$
\boxed{n/2<m<n}.
$$

于是题目转化成：

> `T` 是否存在一个长度严格大于 `n/2` 的真 Border？

直接求最大真 Border：

$$
b=\pi[n-1].
$$

如果 `2*b>n`，输出 `YES`，并令 `P=T[0,b)`；否则输出 `NO`。

例如 `abcabc` 的最长真 Border 长度为 `3`，刚好是总长度 `6` 的一半：那只是**不重叠的两次拼接**，题目明确不算错误，因此答案 `NO`。

**可迁移的套路：**

$$
\boxed{\text{相同串的两次拼接}\to\text{前后缀相等}\to\text{Border}}.
$$

下一讲会进一步把两个 occurrence 的起点差转成 Period。

---

## 4.3 AtCoder ABC141 E — Who Says a Pun?：Z + “不重叠”限制

**题目**：[ABC141 E](https://atcoder.jp/contests/abc141/tasks/abc141_e?lang=en)。给一个串 `S`，找最长的非空子串，使它至少出现两次，并且**这两次出现不能重叠**。`n<=5000`。

先看例子：

```text
S = ababa
```

`aba` 从下标 `0` 和 `2` 出现，但长度为 `3`，而两次起点只相距 `2`，所以它们重叠了，不能选。`ab` 可以从位置 `0` 和 `2` 出现，长度为 `2`，恰好不重叠，答案是 `2`。

**把问题写成 LCP。**

假设两次出现的起点为 `i<j`。两处实际能匹配的最大长度是：

$$
LCP(S[i,n),S[j,n)).
$$

但为了不重叠，选择的长度还必须：

$$
len\le j-i.
$$

因此这一对起点能贡献：

$$
\boxed{\min(LCP(i,j),\;j-i)}.
$$

如果使用第 0 讲的 Hash 求 LCP，要二分；但这里可以利用 Z 函数把固定 `i` 后的全部 LCP 一次算完。

对每个起点 `i`：

1. 取后缀 `U=S[i,n)`。
2. 计算 `z(U)`。
3. 对 `d=1,2,...,|U|-1`，`z[d]` 正是 `LCP(i,i+d)`。
4. 更新答案 `max(ans, min(z[d],d))`。

```cpp
int longest_nonoverlap(const string& s){
    int n=s.size(),ans=0;
    for(int i=0;i<n;i++){
        string u=s.substr(i);
        auto z=z_function(u);
        for(int d=1;d<(int)u.size();d++)
            ans=max(ans,min(z[d],d));
    }
    return ans;
}
```

每个后缀求 Z 为线性，一共 `O(n^2)`，满足本题范围。

**这题教会我们：** 不要把 Z 只当成“模式匹配工具”。它更重要的身份是**批量 LCP**：对一个固定起点，批量查询它和后面每个起点的最长匹配长度。

---

## 4.4 AtCoder ABC343 G — Compress Strings（2024）：Z + 重叠图 + 状压 DP

**题目**：[ABC343 G](https://atcoder.jp/contests/abc343/tasks/abc343_g?lang=en)；[官方题解](https://atcoder.jp/contests/abc343/editorial/9447?lang=en)。给 `N<=20` 个字符串，总长度不超过 `2×10^5`，构造一个**最短的字符串**，使每个给定串都作为它的子串出现。

与第 0 讲 CF1200E 不同：这里**字符串的放置顺序也可以改变**。

例如：

```text
S1 = abc
S2 = bcd
S3 = cde

按 S1 -> S2 -> S3 拼：
abc
 bcd
  cde
得到 abcde，长度 5。
```

### 第一步：先删掉“被其他字符串完整包含”的串

例如 `abcde` 已经包含 `bcd`。只要结果包含 `abcde`，就自动满足对 `bcd` 的要求，所以可以删掉 `bcd`。

还要处理完全重复的输入串；去重后再按“被包含”关系删除。

这一步为什么重要？因为后面打算每个串只选择一次并按某种顺序拼接，如果不删包含关系，会破坏这种“逐个放置”的简化。

### 第二步：把相邻两个串的拼接费用算出来

定义：

$$
overlap(i,j)=\max\{k:\text{suffix}_k(S_i)=\text{prefix}_k(S_j)\}.
$$

若已经放完 `S_i`，接着放 `S_j`，新增长度是：

$$
\boxed{cost(i,j)=|S_j|-overlap(i,j)}.
$$

这就是第 2.5 节的 Z 前后缀重叠操作。

### 第三步：字符串问题转成“访问所有点的最短路径”

把每个字符串看成一个点，从 `i` 到 `j` 的边权为 `cost(i,j)`。

只要确定串的放置顺序，结果长度就能算出来。因此用状压 DP：

$$
\begin{aligned}
dp[mask][i]=&\text{已经安排了 }mask\text{ 中的串，}\\
&\text{最后一个是 }i\text{ 的最小总长度}.
\end{aligned}
$$

初始化：

$$
dp[1\ll i][i]=|S_i|.
$$

转移：

$$
\boxed{dp[mask\cup\{j\}][j]=\min\big(dp[mask\cup\{j\}][j],\;dp[mask][i]+cost(i,j)\big)}.
$$

最终答案是 `min(dp[(1<<N)-1][i])`。

整体时间约为：

$$
O\left(N\sum|S_i|+2^N N^2\right).
$$

这里需要的字符串知识只有两件：**判断子串包含**、**求有向的前后缀最大重叠**。真正的优化部分是状压 DP。

**本题最值得模仿的转化：**

$$
\boxed{\text{最短公共包含串}\to\text{相邻重叠长度}\to\text{带权完全有向图上的状压 DP}}.
$$

*补充提醒*：`overlap(i,j)` 通常**不等于** `overlap(j,i)`；这是一个有向关系。

---

## 4.5 CF1326D2 — Prefix-Suffix Palindrome：先处理两端，再用 Manacher

**题目**：[Codeforces 1326D2](https://codeforces.com/problemset/problem/1326/D2)。给一个字符串 `S`，可以选它的一个前缀 `A` 和一个后缀 `B`，拼成 `A+B`（允许其中之一为空），要求结果是回文，且长度最大。

**这不是“求原串最长回文子串”。** 因为我们允许从中间丢掉一大段，只留下两端拼接。

先看：

```text
S = abaxyzaba
```

两端能直接配对的字符是：

```text
左：a b a | x y z | a b a：右
      三对可以保留
```

于是先保留 `aba` 和末尾 `aba`，剩下中间串 `xyz`。

此时中间最多还能选择一个**回文前缀**或**回文后缀**。如选 `x`：

```text
aba + x + aba = abaxaba
```

这就是合法回文。

### 为什么中间部分只能选回文前缀或回文后缀？

设两端已经剥离了最长一段逐字符相同的外壳，长度为 `k`，剩下：

$$
S = A + M + A^R,
$$

而 `M` 的首尾字符若仍都存在，已经不相同了，否则还可以继续剥离一层。我们要找的答案可以保留共同外壳 `A, A^R`；剩下的中间选取部分，如果又同时从 `M` 的两端各取非空字符，就会要求最外层这两个字符相等，与“已经不能继续剥离”矛盾。

因此剩下的选择只能全部来自 `M` 的一侧：

$$
\boxed{\text{取 }M\text{ 的最长回文前缀，或最长回文后缀}}.
$$

这两种候选用 Manacher 都可以线性求出。

### 怎么用半径数组找最长回文前缀 / 后缀？

对 `M` 做 Manacher。枚举每个中心，由半径算出它的最大回文区间 `[l,r)`：

- 如果 `l==0`，它是一个回文前缀，长度 `r`。
- 如果 `r==|M|`，它是一个回文后缀，长度 `|M|-l`。

枚举奇偶回文中心，找到两种候选中较长的一种。

```cpp
string solve_cf1326d2(string s){
    int n=s.size(),k=0;
    while(k<n-1-k&&s[k]==s[n-1-k]) k++;

    string mid=s.substr(k,n-2*k);
    if(mid.empty()) return s;

    Manacher ma(mid);
    int m=mid.size();
    int pref=0,suff=0;

    auto check=[&](int l,int r){
        if(l==0) pref=max(pref,r);
        if(r==m) suff=max(suff,m-l);
    };

    for(int i=0;i<m;i++){
        check(i-ma.d1[i]+1,i+ma.d1[i]);
        check(i-ma.d2[i],i+ma.d2[i]);
    }

    string keep;
    if(pref>=suff) keep=mid.substr(0,pref);
    else keep=mid.substr(m-suff,suff);

    return s.substr(0,k)+keep+s.substr(n-k,k);
}
```

复杂度 `O(n)`。本题展现的不是 Manacher 的特殊构造，而是：

$$
\boxed{\text{两端对称约束}\to\text{剥离可贪心保留的外壳}\to\text{剩余串的回文前/后缀}}.
$$

---

# 五、理解了原理以后，哪些变形最常出现？

## 5.1 匹配对象不一定是字符：序列差分后再 KMP

真实竞赛中的模式匹配经常“允许整体平移数值”。

例如：

```text
文本数列：10 13 15 18 20
模式数列： 1  4  6
```

虽然数值不相等，但文本前三项与模式的相邻差都为：

```text
差分(文本前三项)：3 2
差分(模式)      ：3 2
```

所以模式加上常数 `9` 后，恰好和文本前三项一致。

**关键等价**：如果两段等长数列只相差同一个加法常数，那么它们的相邻差分数组必然相同；反过来也成立。

因此：

$$
\boxed{\text{匹配允许整体平移}\to\text{对相邻差分做 KMP}}.
$$

典型题：[CF471D — MUH and Cube Walls](https://codeforces.com/problemset/problem/471/D)。注意模式长度为 `1` 时，差分为空，所有文本单个位置都合法，要单独处理。

这个技巧还能推广到：

- 只关心相邻字符间的关系；
- 相邻大小比较形成 `<,=,>` 的关系序列；
- 某些几何路径中，比较相邻移动向量。

不要机械地把每个变形都当成“字符串匹配”，先看看能否通过**不变量**把它转换成普通相等比较。

---

## 5.2 KMP / Z 都能匹配，什么时候选哪一个？

| 任务特征 | 更自然的选择 | 原因 |
|---|---|---|
| 固定模式，文本连续输入 / 在线扫描 | KMP | `j` 就是当前匹配进度 |
| 只需要某模式在某文本中的全部位置 | 都可以 | 都是线性，按个人模板习惯 |
| 研究每个前缀的前后缀关系 | KMP | `pi` / Border 链天然存在 |
| 给定一个前缀，求它与所有后缀的 LCP | Z | 直接就是 `z[i]` |
| 枚举后缀或固定起点的重复长度 | Z | 可对每个后缀批量预处理 |
| 处理一组整数元素的平移匹配 | KMP / Z | 两者都可用于一般可比较序列 |
| 研究一个模式串的整个前后缀重叠集合 | KMP / Z | 可以互相转换，有不同思考习惯 |

**不要误解**：Z 不是“无碰撞的 Hash”，它只能直接快速回答“**某个串前缀**与其各个后缀的 LCP”，并不能预处理一次后就 `O(1)` 回答任意 `(i,j)` 的 LCP。任意下标 LCP 要用第 0 讲 Hash + 二分，或后续的 SA + RMQ 等结构。

---

## 5.3 回文区间很容易转换成“中心半径条件”

给一个静态字符串，询问 `S[l,r)` 是否回文。

**奇数长度** `len=r-l`，中心：

$$
c=(l+r-1)/2.
$$

当且仅当：

$$
\boxed{d1[c]\ge (len+1)/2}.
$$

**偶数长度**，缝隙中心：

$$
c=(l+r)/2.
$$

当且仅当：

$$
\boxed{d2[c]\ge len/2}.
$$

因此 Manacher 的一个直接应用是：**把看似要比较两段字符的回文条件，压缩成一个整数不等式**。

类似地，判断一个区间里有多少种**位置不同**的回文、哪些位置可能是回文起点 / 终点，通常可以从中心半径生成的区间约束继续推导。

---

## 5.4 三个数组的共同思想：已知信息的边界

把代码放到一起看，会发现同一种设计：

- **KMP**：已有一段匹配成功；失败后沿较短 Border 回退，保留仍有用的相等部分。
- **Z**：已有 Z-Box；盒内先复用，超出右端点后才做真实比较。
- **Manacher**：已有回文区间；利用镜像中心先复用，超出边界后才做真实比较。

所以本讲不要求学生记住三段复杂度证明，但至少要理解：

$$
\boxed{\text{先维护一种“已知相等结构”，只为新信息进行比较。}}
$$

这也是理解后续 SA、SAM、ACAM 的一个切入点：算法维护的结构可能更复杂，但都在避免对相同关系反复计算。

---

# 六、常见错误与易混概念

| 容易写错 / 想错的地方 | 正确认识 |
|---|---|
| `pi[i]` 是最长匹配子串长度 | **不是**。是前缀 `S[0,i+1)` 的最长真 Border 长度 |
| KMP 找到一次匹配后把 `j=0` | 会漏掉**重叠**出现，应设 `j=pi[m-1]` |
| KMP 失配就直接减 `j--` | 应跳到 `pi[j-1]`，否则既慢又不体现 Border 结构 |
| `z[i]` 是任意两个后缀的 LCP | 不是，它只比较整个串的前缀和位置 `i` 的后缀 |
| `z[0]` 必然是 0 | 常见有 0 或 `n` 两种约定，注意模板 |
| `P+'#'+T` 中 `#` 也可能出现于输入 | 分隔符必须是保证不会出现的字符；一般整型序列可选独立哨兵值 |
| “最大重叠长度”天然可以二分 | 不对，长度为 `k` 的前后缀相等不一定推出长度 `k-1` 也相等 |
| `d1[i]` / `d2[i]` 是回文长度 | 它们存的是**半径**，奇长 `2*d1-1`，偶长 `2*d2` |
| Manacher 只用奇回文就够 | 原串有偶回文，需要 `d2` 或插入哨兵统一处理 |
| `sum(d1+d2)` 等于不同回文子串数量 | 这是**按出现位置**统计，去重需要别的结构 |
| Manacher 可以直接支持频繁改单字符 | 不适合；动态回文考虑第 0 讲的 Hash + 线段树 |

---

# 七、练习安排：先掌握接口，再学模型转化

下面尽量按解题思维而不是模板难度来排序。

| 题目 | 重点训练 | 参考难度定位 |
|---|---|---|
| [CSES — String Matching](https://cses.fi/problemset/task/1753) | KMP / Z，全部 Occurrence | 入门 |
| [CSES — Finding Borders](https://cses.fi/problemset/task/1732) | `pi` 跳 Border 链 | 入门 |
| [CF432D — Prefixes and Suffixes](https://codeforces.com/problemset/problem/432/D) | Border 链 + 出现次数贡献 | 基础～中档 |
| [CF471D — MUH and Cube Walls](https://codeforces.com/problemset/problem/471/D) | 差分不变量 + KMP | 中档 |
| [CF2010C2 — Message Transmission Error](https://codeforces.com/problemset/problem/2010/C2) | 两次相同串重叠 → Border | 中档（2024） |
| [ABC141 E — Who Says a Pun?](https://atcoder.jp/contests/abc141/tasks/abc141_e?lang=en) | 从每个起点批量求 LCP、非重叠限制 | 中档 |
| [CSES — Longest Palindrome](https://cses.fi/problemset/task/1111) | Manacher 半径与原串下标 | 入门 |
| [CF1326D2 — Prefix-Suffix Palindrome](https://codeforces.com/problemset/problem/1326/D2) | 两端贪心 + Manacher | 中档 |
| [ABC343 G — Compress Strings](https://atcoder.jp/contests/abc343/tasks/abc343_g?lang=en) | 字符串重叠 + 状压 DP | 较难（2024） |

### 课后思考（很适合作为课堂讨论）

1. 设某个模式在位置 `2` 和 `5` 出现，长度为 `7`。为什么它的起点差 `3` 必然与周期相关？
2. 为什么 `z[i]` 可以直接做 `S[0,n)` 与 `S[i,n)` 的 LCP，却不能直接做 `S[2,n)` 与 `S[5,n)` 的 LCP？
3. `S=aaaa` 的回文子串总出现次数是多少？不同回文子串个数又是多少？
4. 你能把 KMP、Z、Manacher 各自维护的“已经知道”的信息用一句话描述出来吗？
5. 对字符串集合求最短包含串时，为什么要先删除那些已经被别的字符串包含的串？

---

# 八、本讲速查与下一讲连接

## 8.1 四种数组定义

$$
\boxed{\pi[i]=\text{前缀 }S[0,i+1)\text{ 的最长真 Border 长度}}
$$

$$
\boxed{z[i]=LCP(S[0,n),S[i,n)),\quad z[0]=0}
$$

$$
\boxed{d1[i]=\text{以字符 }i\text{ 为中心的最长奇回文半径}}
$$

$$
\boxed{d2[i]=\text{以 }i-1,i\text{ 缝隙为中心的最长偶回文半径}}
$$

## 8.2 看到什么想到什么？

| 题目中出现的条件 | 首先尝试的转化 |
|---|---|
| 固定模式在文本中出现 | KMP / Z → Occurrence |
| 数列允许整体加常数后匹配 | 差分 → KMP / Z |
| 一个前缀也是后缀 | `pi` → Border 链 |
| 同一串两份重叠拼接 | Border 或 Period |
| 比较“整个串前缀”与每个后缀 | Z → 批量 LCP |
| 两次出现不能重叠 | `min(LCP(i,j),j-i)` |
| 两串拼接要求省字符 | 最大后缀/前缀重叠 → Z / KMP |
| 每个中心最长回文 | Manacher `d1/d2` |
| 静态区间是否回文 | `d1/d2` → 半径条件 |
| 最长回文前缀 / 后缀 | 检查最大回文区间是否接触两端 |
| 一次出现的数量和不同串的数量 | 先区分按位置计数还是去重计数 |

## 8.3 下一讲：为什么 Border 链值得单独讲？

本讲中 `pi[i]` 只是一个长度，但是我们已经三次利用到了它：

- 失配时保留可用的前后缀；
- 统计某个前缀出现次数；
- 把“两次相同串重叠”转成前后缀长度条件。

下一讲继续研究：

$$
\boxed{\text{Border 长度 }b\iff\text{周期 }p=n-b}
$$

进而介绍**周期引理、gcd、短周期整除、全部 Border 的 `O(log n)` 段等差数列结构**，解释为什么很多重叠匹配问题最终会出现数论和等差数列。

---

## 资料与出处

**算法基础**

- [cp-algorithms：Prefix Function / KMP](https://cp-algorithms.com/string/prefix-function.html)
- [cp-algorithms：Z-function](https://cp-algorithms.com/string/z-function.html)
- [cp-algorithms：Manacher's Algorithm](https://cp-algorithms.com/string/manacher.html)

**题目与官方资料**

- [Codeforces 432D — Prefixes and Suffixes](https://codeforces.com/problemset/problem/432/D)
- [Codeforces 471D — MUH and Cube Walls](https://codeforces.com/problemset/problem/471/D)
- [Codeforces 2010C2 — Message Transmission Error](https://codeforces.com/problemset/problem/2010/C2)
- [AtCoder ABC141 E — Who Says a Pun?](https://atcoder.jp/contests/abc141/tasks/abc141_e?lang=en)
- [AtCoder ABC343 G — Compress Strings](https://atcoder.jp/contests/abc343/tasks/abc343_g?lang=en)
- [AtCoder ABC343 G — 官方题解](https://atcoder.jp/contests/abc343/editorial/9447?lang=en)
- [Codeforces 1326D2 — Prefix-Suffix Palindrome](https://codeforces.com/problemset/problem/1326/D2)
- [CSES — Longest Palindrome](https://cses.fi/problemset/task/1111)

> **授课建议**：讲 KMP 时先手动演示一次失配与跳 Border；讲 Z 时在 `aaaaab` 上画出 `[l,r)`；讲 Manacher 时在 `abacaba` 上标镜像中心。每个算法随后立即做一道能让读者看到“数组含义 → 题意转化”的题，效果通常比先连续讲完三份模板更好。
