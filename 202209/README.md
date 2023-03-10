# 题解记录

C++fw的过渡记录...

## 防疫大数据

在对`stl`更为熟悉以后，再次尝试解决防疫大数据的问题。首先更新一下C++知识：

* `pair`的用法：[stl pair介绍](https://zhuanlan.zhihu.com/p/482540092)，可以用{a,b}来直接赋值pair
* 判断`map`查找失败与否用`count`
* 一些排序、去重的相关操作：[排序函数sort](http://c.biancheng.net/view/7457.html)、[去重（先排序）unique](https://blog.csdn.net/qq_36561697/article/details/82356053)、[unique后续操作erase](https://www.w3schools.cn/cpp_standard_library/cpp_vector_erase_range.asp#:~:text=C%2B%2B%20%E5%87%BD%E6%95%B0,std%3A%3Avector%3A%3Aerase%20%28%29%20%E4%BB%8E%E5%90%91%E9%87%8F%E4%B8%AD%E5%88%A0%E9%99%A4%E5%85%83%E7%B4%A0%E8%8C%83%E5%9B%B4%E3%80%82)

  在这些函数的基础上可以先使用`sort`，再使用`ans.erase(unique(ans.begin(),ans.end()),ans.end());`语句来解决重复的问题
* 在需要导入多个头文件的情况下，可以用`#include<bits/stdc++.h>`来替代，节省时间，不过**在平时的编程中不建议使用**。
* 在循环内重新声明`vector`将其清空

---

在先前的思路设计中，花费了很多的心思在处理存储下每个地区和每个居民当前的状态，由于给出的数据范围是$1\sim 10^9$，于是考虑开一个同样大小的数组，这是不可行的，因此将问题处理得过于复杂了。

以上思路的关键是，不认为可以直接存储下漫游信息，而是想要在读入漫游信息时直接更新用户是否为风险用户的信息。但是这种做法在时间和空间上都是吃力不讨好的，首先需要想办法存储每个用户的信息，此外每次输出答案时都要遍历所有用户的信息，反而在时间上花费过多。这时候顺应题意反而是更好的选择，因为实际上我们**可以存储下所有的漫游信息**，经过计算，在一共1000天的情况下，每天的漫游信息最多1000条，对于内存限制来说，这是可以存下的。

总之不能太钻牛角尖了。在是否要转换题意这一点上，首先脑测一下时间和空间复杂度再做决定，否则很容易在方向选择上就犯错，即使代码逻辑没有问题也不可能做出答案来。

重新整理思路以后可以发现，需要维护的对象主要有两个：地区风险信息（记录开始日期和结束日期），漫游信息记录（全部存储下来）。

**事实证明如果能用一个判断语句解决问题，就不要费尽心思脑测会不会出现意外情况，很容易出错。**
