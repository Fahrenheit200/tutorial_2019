## 读写线程调度

- Author: bbpumpkin
- Revised: bbpumpkin
- Date: 2018-10-19
- Version: 1.0.0
- Abstract: 调度多个读写线程

### Functions:
	无
### Interfaces:
	详见注释
### Depend Libraries:
	无

源代码已做好注释，可以使用Doxygen生成文档（为避免提交内容过大没有提供生成好的文档）
---
### 项目使用说明
运行示例
```
bin/RWDispatch TEST_FILES/test_1.txt
```
若对于同一时刻不同线程都进行输出，则输出的顺序是未知的，我并未做额外处理（我认为这是合理的行为）
TEST_FILES里面有三组自用过的三组数据，完整测试数据请自行准备
test里面有一个我自己测试用的Python脚本，项目已经通过了这个测试，一并提交仅供测试者批阅指正
