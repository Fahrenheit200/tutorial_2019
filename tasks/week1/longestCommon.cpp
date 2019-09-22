#include<string>
#include<vector>
using std::string;
using std::vector;

string longestCommon(vector<string>& strs)
{
	int vector_size = strs.size();  //得到 strs 长度
	unsigned int num = 0;     //记录相同后缀的数目
	bool flag = true;      //终止条件
    int index1, index2;
	if (strs.empty())    //如vector为空，返回空
		return "";
	if (vector_size == 1)  //如果vector只有一个字符串，返回空
		return "";

	for (int j = 0; flag; j++)
	{
		for (int i = 0; i<vector_size; i++)
			{
				if (num >= strs[i].size())   //判断num是否超过字符串长度
				{
					flag = false;
					break;
				}
			    index1 = strs[0].size() - j - 1;
			    index2 = strs[i].size() - j - 1;
				if (strs[0][index1] != strs[i][index2])//判断尾元素是否相同
				{
					flag = false;
					break;
				}
			}
		if (flag)
			num++;
	}
		string result(strs[0], strs[0].size() - num, num);
		return result;
}

