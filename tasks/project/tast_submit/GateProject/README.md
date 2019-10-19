## 门电路模拟器

- Author: bbpumpkin
- Revised: bbpumpkin
- Date: 2018-10-14
- Version: 1.0.0
- Abstract: 模拟连接逻辑门构成电路图

### Functions:
	无
### Interfaces:
	详见注释
### Depend Libraries:
	无

源代码已做好注释，可以使用Doxygen生成文档（为避免提交内容过大没有提供生成好的文档）
---
### 模拟器使用说明
该模拟器提供一个控制台，运行bin/GSConsole启动控制台

命令列表：
- help 
- create 
- setInput 
- setOutput 
- connect 
- list
- exec
- print
- clear
命令具体用法请使用help *cmd*查询

名词解释：
- gid： 门的id，一个整数，一个逻辑门在board上的唯一表示符
- bmask： 输入端口，表示在输入时给定值绑定到逻辑门的哪一个入口，对于二元运算的门可以指定为0或1
- 输出集合： 一个gid集合，board会从给定的门上收集输入值并缓存

测试输入：
模拟4位全加器，有两组数据，分别存放在a.txt和b.txt中
a.txt只有一组输入
b.txt有全部的4位全加器256组的可能的输入
将文件内容全部粘贴到控制台即可运行即可

---
关于找环：使用BFS
伪(P)代(y)码：
```
opens = [start_node]
closes = []
while opens:
	node = opens.pop(0)
	if not node in closes:
		visit(node)
		children = expand(node)
		opens.extend(children)
		closes.append(node)
```
若原图无环可以直接以新加入的节点为源点开始跑BFS，若此过程中多次访问到源点，则表示有环
此外，Floyd最小环算法可以找到图中的最小环，且可以找出对应的具体路径，时间复杂度O(n^3)
