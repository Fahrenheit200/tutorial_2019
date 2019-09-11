## 程序设计能力练习题

- 请使用C++和g++。
- 开设此题的目的只是想让你熟悉基本的C++和程序设计，多动动脑筋。
- 只要简单测试Accepted就可以得分，代码简洁可得满分。请独立认真完成。
- 可能需要先了解的知识：std::string、二进制与十进制、IPv4与子网掩码。

## 第一周题目 —— Palindromes

### Description

编写一个函数来查找字符串数组中的最长公共后缀。

如果不存在公共前缀，返回空字符串 ""。

### Input
编写一个函数，接口如下:
```
string longestCommonPrefix(vector<string>& strs) {

}
```

### Output
返回最长的公共后缀

### Sample Input
```
ppp
pplpp
lpp
```

### Sample Output
```
pp
```


## 第二周题目 —— IP Networks

### Description

Alex is administrator of IP networks. His clients have a bunch of individual IP addresses and he decided to group all those IP addresses into the smallest possible IP network.  

Each IP address is a 4-byte number that is written byte-by-byte in a decimal dot-separated notation "byte0.byte1.byte2.byte3" (quotes are added for clarity). Each byte is written as a decimal number from 0 to 255 (inclusive) without extra leading zeroes.  

IP network is described by two 4-byte numbers - network address and network mask. Both network address and network mask are written in the same notation as IP addresses.  

In order to understand the meaning of network address and network mask you have to consider their binary representation. Binary representation of IP address, network address, and network mask consists of 32 bits: 8 bits for byte0 (most significant to least significant), followed by 8 bits for byte1, followed by 8 bits for byte2, and followed by 8 bits for byte3.  

IP network contains a range of 2n IP addresses where 0<=n<=32 . Network mask always has 32 - n first bits set to one, and n last bits set to zero in its binary representation. Network address has arbitrary 32 - n first bits, and n last bits set to zero in its binary representation. IP network contains all IP addresses whose 32 - n first bits are equal to 32 - n first bits of network address with arbitrary n last bits. We say that one IP network is smaller than the other IP network if it contains fewer IP addresses.  

For example, IP network with network address 194.85.160.176 and network mask 255.255.255.248 contains 8 IP addresses from 194.85.160.176 to 194.85.160.183 (inclusive).  

### Input

The input file will contain several test cases, each of them as described below.  

The first line of the input file contains a single integer number m (1<=m<=1000) . The following m lines contain IP addresses, one address on a line. Each IP address may appear more than once in the input file.  

### Output

For each test case, write to the output file two lines that describe the smallest possible IP network that contains all IP addresses from the input file. Write network address on the first line and network mask on the second line.  

### Sample Input
```
3
194.85.160.177
194.85.160.183
194.85.160.178

```

### Sample Output
```
194.85.160.176
255.255.255.248

```
