#include "LCS.h"

string longestCommon(vector<string> &strs)
{
    int strs_vector_length = strs.size();
    int shortest_str_length = INT32_MAX;
    int common_part_length, common_str_length;
    string shortest_string = "", common_string = "";
    if (strs_vector_length == 0)
        return "";
    for (int index = 0; index < strs_vector_length; index++)
    {
        if (strs[index].length() < shortest_str_length)
        {
            shortest_str_length = strs[index].length();
            shortest_string = strs[index];
        }
    }
    common_string = shortest_string;
    common_str_length = common_string.length();
    for (int index = 0; index < strs_vector_length; index++)
    {
        int current_str_length = strs[index].length();
        if (common_str_length < current_str_length)
        {
            common_part_length = common_str_length;
        }
        else
        {
            common_part_length = current_str_length;
        }
        for (int offset = 0; offset < common_str_length; offset++)
        {
            if (strs[index][current_str_length - 1 - offset] != common_string[common_str_length - 1 - offset])
            {
                common_str_length = offset;
                break;
            }
        }
        if (common_str_length == 0)
        {
            common_string = "";
            break;
        }
        common_string = common_string.substr(common_string.length() - common_str_length, common_str_length);
        common_str_length = common_string.length();
    }
    return common_string;
}
