//BLG335E-Analysis of Algorithms
//Project-2
//Mehmet Gencay Ertürk - 150130118
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
class data{
	public:
		int id,rec,pos,neg;
};
class heap{
	private:
		data *unsorted,*sorted;
		bool call=false;
		int length=0,day=1;
	public:
		void max_heapify(int i,int cur);
		void min_heapify(int i,int cur);
		void build_min_heap();
		void build_max_heap();
		void insert(int* arr);
		void heapsort(bool max);
		void extract_max();
		void swap(int i,int j);
		heap();
		void extract_min();
		void increase_key(int* arr);
		~heap();
};
void heap::swap(int i,int j)
{
	int temp=sorted[i].id;
	sorted[i].id=sorted[j].id;
	sorted[j].id=temp;
	temp=sorted[i].rec;
	sorted[i].rec=sorted[j].rec;
	sorted[j].rec=temp;
	temp=sorted[i].pos;
	sorted[i].pos=sorted[j].pos;
	sorted[j].pos=temp;
	temp=sorted[i].neg;
	sorted[i].neg=sorted[j].neg;
	sorted[j].neg=temp;
}
void heap::max_heapify(int i,int cur)
{
	int left=2*i+1,right=2*i+2,max=i,score_cur=2*sorted[i].rec+sorted[i].pos-sorted[i].neg,score_max=score_cur;
	if(left<cur)
	{
		int score_left=2*sorted[left].rec+sorted[left].pos-sorted[left].neg;
		if((!call && score_left>score_max) || (call && sorted[left].rec>sorted[i].rec))
		{
			max=left;
			score_max=score_left;
		}
	}
	if(right<cur)
	{
		int score_right=2*sorted[right].rec+sorted[right].pos-sorted[right].neg;
		if((!call && score_right>score_max) || (call && sorted[right].rec>sorted[max].rec)){max=right;}		
	}
	if(max!=i)
	{
		swap(i,max);
		max_heapify(max,cur);
	}
}
void heap::min_heapify(int i,int cur)
{
	int left=2*i+1,right=2*i+2,min=i,score_cur=2*sorted[i].rec+sorted[i].pos-sorted[i].neg,score_min=score_cur;
	if(left<cur)
	{
		int score_left=2*sorted[left].rec+sorted[left].pos-sorted[left].neg;
		if((!call && score_left<score_cur) || (call && sorted[left].rec<sorted[i].rec))
		{
			min=left;
			score_min=score_left;
		}
	}
	if(right<cur)
	{
		int score_right=2*sorted[right].rec+sorted[right].pos-sorted[right].neg;
		if((!call && score_right<score_min) || (call && sorted[right].rec<sorted[min].rec))
		{
			min=right;
			score_min=score_right;
		}		
	}
	if(min!=i)
	{
		swap(i,min);
		min_heapify(min,cur);
	}	
}
void heap::build_max_heap()
{
	for(int i=(length/2)-1;i>=0;i--){max_heapify(i,length);}
}
void heap::build_min_heap()
{
	for(int i=(length/2)-1;i>=0;i--){min_heapify(i,length);}	
}
void heap::insert(int* arr)
{
	unsorted[arr[0]-100].id=arr[0];
	unsorted[arr[0]-100].neg=arr[3];
	unsorted[arr[0]-100].pos=arr[2];
	unsorted[arr[0]-100].rec=arr[1];
	sorted[arr[0]-100].id=arr[0];
	sorted[arr[0]-100].neg=arr[3];
	sorted[arr[0]-100].pos=arr[2];
	sorted[arr[0]-100].rec=arr[1];
}
void heap::increase_key(int* arr)
{
	unsorted[arr[0]-100].id=arr[0];
	unsorted[arr[0]-100].rec+=arr[1];
	unsorted[arr[0]-100].neg+=arr[3];
	unsorted[arr[0]-100].pos+=arr[2];
	sorted[arr[0]-100].id=unsorted[arr[0]-100].id;
	sorted[arr[0]-100].pos=unsorted[arr[0]-100].pos;
	sorted[arr[0]-100].rec=unsorted[arr[0]-100].rec;
	sorted[arr[0]-100].neg=unsorted[arr[0]-100].neg;
}
void heap::extract_max()
{
	if(!call)
	{
		int score1=2*sorted[length-1].rec+sorted[length-1].pos-sorted[length-1].neg;
		int score2=2*sorted[length-2].rec+sorted[length-2].pos-sorted[length-2].neg;
		int score3=2*sorted[length-3].rec+sorted[length-3].pos-sorted[length-3].neg;
		cout<<"AFTER DAY-"<<day<<"\nBEST PERFORMANCES:\n1.ID: "<<sorted[length-1].id<<" SCORE: "<<score1<<endl;
		cout<<"2.ID: "<<sorted[length-2].id<<" SCORE: "<<score2<<endl;
		cout<<"3.ID: "<<sorted[length-3].id<<" SCORE: "<<score3<<endl;
	}
	else
	{
		cout<<"MAXIMUM CALLS:\n1.ID: "<<sorted[length-1].id<<" CALLS: "<<sorted[length-1].rec<<endl;
		cout<<"2.ID: "<<sorted[length-2].id<<" CALLS: "<<sorted[length-2].rec<<endl;
		cout<<"3.ID: "<<sorted[length-3].id<<" CALLS: "<<sorted[length-3].rec<<endl;		
	}
}
void heap::heapsort(bool max)
{
	if(!max){build_min_heap();}
	else{build_max_heap();}
	for(int cur=length-1;cur>=0;cur--)
	{
		swap(0,cur);
		if(!max){min_heapify(0,cur);}
		else{max_heapify(0,cur);}
	}
	if(!max){extract_min();}
	else{extract_max();}
}
void heap::extract_min()
{
	int i=1;
	while(sorted[length-i].id==0){i++;}
	if(!call)
	{
		int score1=2*sorted[length-i].rec+sorted[length-i].pos-sorted[length-i].neg;
		int score2=2*sorted[length-i-1].rec+sorted[length-i-1].pos-sorted[length-i-1].neg;
		int score3=2*sorted[length-i-2].rec+sorted[length-i-2].pos-sorted[length-i-2].neg;
		cout<<"WORST PERFORMANCES:\n1.ID: "<<sorted[length-i].id<<" SCORE: "<<score1<<endl;
		cout<<"2.ID: "<<sorted[length-i-1].id<<" SCORE: "<<score2<<endl;
		cout<<"3.ID: "<<sorted[length-i-2].id<<" SCORE: "<<score3<<endl;
	}
	else
	{
		cout<<"MINIMUM CALLS:\n1.ID: "<<sorted[length-i].id<<" CALLS: "<<sorted[length-i].rec<<endl;
		cout<<"2.ID: "<<sorted[length-i-1].id<<" CALLS: "<<sorted[length-i-1].rec<<endl;
		cout<<"3.ID: "<<sorted[length-i-2].id<<" CALLS: "<<sorted[length-i-2].rec<<endl;		
	}
}
heap::heap()
{
	unsorted=new data[890];
	sorted=new data[890];
	char* str=new char[9];
	char* str2=new char[2];
	int* arr=new int[4];
	while(day<=10)
	{
		strcpy(str,"day");
		sprintf(str2,"%d",day);
		strcat(str,str2);
		strcat(str,".csv");
		FILE* fp=fopen(str,"r");
		if(fp==NULL)
		{
			cout<<"File not found";
			exit(1);
		}
		else
		{
			while(!feof(fp))
			{
				fscanf(fp,"%d,%d,%d,%d\n",&arr[0],&arr[1],&arr[2],&arr[3]);
				if(arr[0]-100>=length)
				{
					if(day<10){length++;}
					else{length=arr[0]-99;}					
					insert(arr);
				}
				else{increase_key(arr);}
			}
			heapsort(1);
			call=true;
			heapsort(1);
			call=false;
			if(day==10)
			{
				heapsort(0);
				call=true;
				heapsort(0);
				call=false;
			}
			fclose(fp);
			day++;
		}
	}
	delete str;
	delete str2;
	delete arr;
}
heap::~heap()
{
	delete unsorted;
	delete sorted;
}
int main()
{
	heap h;
	getchar();
	return 0;
}
