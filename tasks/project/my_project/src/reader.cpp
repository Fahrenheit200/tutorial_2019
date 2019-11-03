#include<iostream>
#include<thread>
#include<mutex>
#include<fstream>
#include<algorithm>
#include<deque>
#include<sstream>
using namespace std;
//	this_thread::sleep_for(chrono::milliseconds(1)); 
mutex mu;
mutex r;
deque <int> w_head;
int w_doing=0;
int head=0;
int rate=1;
int lock_status=0;
void lockIt(int);
void unlockIt();
int reading_count=0;
struct th{
	int num;
	char type;
	int come;
	int last;
};
th p[1000001];
int n;
int T=0;
int reader_time=0;
bool compare(th a,th b)//to sort data
{
	return a.come<b.come;
}
int transf(string a)
{
	stringstream ss;
	int temp_n;
	ss<<a;
	ss>>temp_n;
	return temp_n;
}
void write(int num,int come,int last);
void read(int num,int come,int last);
int main(int argc,char** argv)
{
	if(argc!=2)
	{
		cout<<"[main] fail to open test file"<<endl;
		return 0;
	}
	cout<<"[main] start"<<endl;
	cout<<"[main] try open "<<argv[1]<<endl;
	freopen(argv[1],"r",stdin);
	string temp;
	int i=0;
	int o=0;//record to transf num or come or last
	int i_temp=0;
	string s_temp="";
	while(getline(cin,temp))
	{
//		cout<<"temp"<<i<<"  "<<temp<<endl;
		o=0;
		i_temp=0;
		while(i_temp<temp.size())
		 {
			// cout<<i_temp<<' ';
			 s_temp="";
			if(temp[i_temp]==' ') i_temp++;
			else if(temp[i_temp]>57){ p[i].type=temp[i_temp];i_temp++; }
		       		else {
				while(temp[i_temp]!=' ')
				{	
					s_temp=s_temp+temp[i_temp];
					i_temp++;
					if(i_temp>=temp.size()) break;
				
				}

				if(o==0){ p[i].num=transf(s_temp); o=1; }
				else if(o==1){ p[i].come=transf(s_temp);o=2; }
				else if(o==2){ p[i].last=transf(s_temp);o=0; }
				//cout<<i_temp<<" o:"<<o<<"s:"<<s_temp<<endl;
				i_temp++;
				}
		}

			//	cout<<p[i].num<<' '<<p[i].type<<' '<<p[i].come<<' '<<p[i].last<<endl;
		i++;
	}
	/********test*/
	sort(p,p+i,compare);
//	for(int k=0;k<i;k++) cout<<p[k].num<<' '<<p[k].type<<' '<<p[k].come<<' '<<p[k].last<<endl;
//	return 0;
	/********test*/
	T=p[0].come;
	cout<<"[main] open "<<argv[1]<<" succcess"<<endl;
	n=i;
	thread t[100001];
	int writer_number=0,reader_number=0;
	for(i=0;i<n;i++)
	{
		if(p[i].type=='W')
		{
			writer_number++;
			t[i]=thread(write,writer_number,p[i].come,p[i].last);
		}
		else 
		{
			reader_number++;
			t[i]=thread(read,reader_number,p[i].come,p[i].last);
		}
	}



	for(i=0;i<n;i++)
	{
		t[i].join();
	}


	fclose(stdin);
	return 0;

}

void write(int num,int come ,int last)
{
	  this_thread::sleep_for(chrono::milliseconds(rate*come));
	  head++;//using variable head to record the number of writer in the waiting line
	  w_head.push_back(num);
	  lockIt(num);
          head--;
	  w_doing=1;//to check if writer is visiting
	  cout<<"[writer"<<num<<"] "<<T<<"s: Keep for "<<last<<"s"<<endl;
	  T+=last; 
	  this_thread::sleep_for(chrono::milliseconds(last*rate));
	    cout<<"[writer"<<num<<"] "<<T<<"s: exit"<<endl;

	  w_head.pop_front();
	    w_doing=0;
	  unlockIt();
}


void read(int num,int come,int last)
{
	bool f=0;
	bool f2=0;//to check if it has waited head
	  this_thread::sleep_for(chrono::milliseconds(rate*come));
	  while(head||w_doing)
		  f2=1;
	if(f2) come=T;//if it has waited,reset the time it comes
	  r.lock();
	  reading_count++;//record the number readers
	  if(reading_count==1)
	  {lockIt(0);
	   cout<<"[reader"<<num<<"] "<<T<<"s: Keep for "<<last<<"s"<<endl;//如果写者在写，输出当前时刻，否则输出到来时刻
                 f=1;
		  reader_time=0;
	  }
	  else cout<<"[reader"<<num<<"] "<<come<<"s: Keep for "<<last<<"s"<<endl;
	  r.unlock();
	if(come+last>reader_time) reader_time=come+last;//the time readers have used depends on the last-leaving reader
	    this_thread::sleep_for(chrono::milliseconds(rate*last));   
//	    cout<<"[test] reader"<<num<<endl;
	  //  T+=last;
	  // cout<<"[reader"<<num<<"] "<<T<<"s: exit"<<endl;
	    r.lock();
	    reading_count--;
	    if(reading_count==0) {
		    unlockIt();
		    T=reader_time;
		      cout<<"[reader"<<num<<"] "<<T<<"s: exit"<<endl;
		     r.unlock();
		     return;
	    }
	    else 
	    {if(f)   cout<<"[reader"<<num<<"] "<<T+last<<"s: exit"<<endl; 
	    else   cout<<"[reader"<<num<<"] "<<come+last<<"s: exit"<<endl; 
	    }
	    r.unlock();
}



void lockIt(int num)
{
	int front=0;
	if(num==0) front=0;
	else front=w_head.front();
	if(lock_status==0&&num==front) lock_status=1;//获取锁
	else
	while(lock_status==1||num!=front)//如果被锁上了或者前面有写者
	{
		front=w_head.front();
		if(lock_status==0&&num==front)
		{
			lock_status=1;
			break;
		}
	}
}

void unlockIt()
{
	lock_status=0;
}

