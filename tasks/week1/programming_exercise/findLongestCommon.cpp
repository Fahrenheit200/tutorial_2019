/*****************************************************************************
*  @file     findLongestCommon.cpp                                              
*  @brief    find the longest common suffix of some strings             
*  Details.                                                                  
*                                                                          
*  @author   Jili Liao                                                      
*  @email    915836449@qq.com                                         
*  @version  1.0.0.0                                                 
*  @date     2019/09/16                                                                                                                  
*----------------------------------------------------------------------------
*  Remark         : Description                                              
*----------------------------------------------------------------------------
*  Change History :                                                          
*  <Date>     | <Version> | <Author>       | <Description>                   
*----------------------------------------------------------------------------
*  2019/09/16 | 1.0.0.0   | Jili Liao      | Create file                     
*----------------------------------------------------------------------------
*                                                                            
*****************************************************************************/

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;


/** 
* @brief  find the longest common suffix of some string
* @param[in]  strs  --   a vector of some strings
*
* @return the longest common suffix
*/
string longestCommon(vector<string>& strs);


int main(){
	/* create a empty vector */
	vector<string> strs;
	/* the number of strings */
	int n;
	
	/* add some strings into vector */
	cout << "How many strings do you want to input: ";
	cin >> n;
	cout << "Please input " << n << " strings." << endl;
	for(int i=0; i<n; i++){
		string str;
		cin >> str;
		strs.push_back(str);
	}
	
	/* find and print the longest common suffix of these string */
	cout << endl << "The result is: " << longestCommon(strs) << endl;
	
	return 0;
}


/** 
* @brief  find the longest common suffix of some string
* @param[in]  strs  --   a vevtor of string
*
* @return the longest common suffix
*/
string longestCommon(vector<string>& strs){
	/* the number of strings */
	int n = strs.size();
	/* the index to start get substring */
	int start_index;
	/* the result of this function */
	string return_str = "";
	/* the temporary sample of the result */
	string return_str_tmp;
	/* a flag used to judge if break the loop */
	bool break_flag = false;
	
	/* if there is nothing in the vector, return "" */
	if(n == 0){
		return "";
	}
	
	/* find the minimum length of strings */
	int min_length = strs[0].length();
	for(int i=1; i<n; i++)
		if(strs[i].length() < min_length)
			min_length = strs[i].length();
			
	
	while(return_str.length() < min_length){
		/* update return_str_tmp */
		start_index = strs[0].length() - return_str.length() - 1;
		return_str_tmp = strs[0].substr(start_index, return_str.length() + 1);
		
		/* traverse all the strings */
		for(int i=0; i<n; i++){
			start_index = strs[i].length() - return_str_tmp.length();
			/* if the substring is not equal tp return_str_tmp, break the loop */
			if(return_str_tmp != strs[i].substr(start_index, return_str_tmp.length())){
				break_flag = true;
				break;
			}		
		}
		
		if(break_flag)
			break;
			
		/* update return_str */
		return_str = return_str_tmp;
	}
	
	return return_str;
}
