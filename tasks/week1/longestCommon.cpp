#include <algorithm>
string longestCommon(vector <string>& s)
{
	if(s.size()==1) {return *s.begin();}
	else
	{
	    int i=0;
	    int x=0;
            string s1=*s.begin();          
	    string s2=*(s.begin()+1);
            reverse(s1.begin(),s1.end());
            reverse(s2.begin(),s2.end());
            char a=s1[0];
            while(i<s1.size()&&i<s2.size())
            {
    		    if(s1[i]==s2[i]&&s2[i]==a)
                    {
			    x+=1;
                            i++;
                     }

                    else {break;}
             }
   	    if(x==0) {return "";}
	    else
       	    {
	  	    s.erase(s.begin());
                    s.erase(s.begin());
                    s.insert(s.begin(),string(x,a));
                    return longestCommon(s);
            }
        }
}


-- VISUAL --                                       1         35,0-1        Bot

