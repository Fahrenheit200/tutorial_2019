#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* This function is to find the longest common suffix of the words */
string longestCommon(vector<string>& strs);

int main()
{

	int N; // The number of the words

	cout << "Please enter the number of words: ";
	cin >> N;

	vector<string> Suffix(N); // The string vector to store the words

	for (int i = 0; i < N; i++) // Enter the words
	{
		cout << "Please enter the suffix " << i + 1 << ": ";
		cin >> Suffix[i];
	}

	string LongestCommon = longestCommon(Suffix); // Get the longest common suffix of the words
	
	// Estimate whether the word have common suffix
	if(LongestCommon.empty())
		cout<< "The words don't have any common suffix!";
	else
		cout<< "The longest common suffix is: " << LongestCommon;

	return 0;
}

string longestCommon(vector<string>& strs) {
	int n = strs.size(); // Get the number of the words
	int i = 1; // The length of the suffix
	bool item = true; // Estimate the longest common suffix
	string longestcommon; // The longest common suffix

	while(item) // Compare the suffix of all  the words
	{
		for (int a = 0; a < n-1; a++)
		{
			for(int b = 1; b < n; b++)
			{
				// If they will not be common when the length increasing, get the current suffix and break 
				if(strs[a].substr(strs[a].size() - i) != strs[b].substr(strs[b].size() -i)) 
				{
					longestcommon = strs[a].substr(strs[a].size() - i + 1);
					item = false;
				}
			}
		}

		i++; // If they are still common, increase the length of the suffix
	}
	
	return longestcommon; // Return the longest common suffix
}
