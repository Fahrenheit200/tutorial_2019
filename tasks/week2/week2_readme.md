## 基础考核-第二周
- 作者：彭学斌
- 日期：2019-10-01
- 版本：1.0.0
- 摘要：完成第二周任务

### 功能：
     使用opencv还原背景；实现链表加法。
### 接口：
#### opencv 还原背景
/// *读入视频，参数为视频固定路径*
`void readVideo(string filePath)`
/// *处理视频*
`void process()`
/// *显示结果*
`void showResult`
#### 链表加法
/// *两个链表分别代表一个整数，现实现两个链表的相加*
`ListNode* addTwoNumbers(LisNode* l1, ListNode* l2)`
### 依赖库：
- 依赖opencv

### 编译提示
```
$cd recovery
$make
$./recovery "filepath"
```

