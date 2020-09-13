/*********************************
*BLG335E-Analysis of Algorithms  *
*Assignment-1                    *
*Mehmet Gencay Ertürk - 150130118*
**********************************/
#include <bits/stdc++.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
class Sort{ //Defining class variables and functions.
	private:
		long int size,*numbers;
	public:
		~Sort();
		Sort(char*,int);
		void mergesort();
		void merge(long int l,long int m,long int r);
		void bubblesort();
};
void Sort::bubblesort() //Bubblesort algorithm in homework document.
{
	bool sorted=false;
	clock_t t=clock();
	for(long int i=size;i>1 && sorted==false;i--)
	{
		sorted=true;
		for(long int j=1;j<i;j++)
		{
			if(numbers[j]<numbers[j-1])
			{
				long int temp=numbers[j];
				numbers[j]=numbers[j-1];
				numbers[j-1]=temp;
				sorted=false;
			}
		}
	}
	t=clock()-t;
	cout<<1000*(((double)t)/CLOCKS_PER_SEC)<<endl;	
}
void Sort::mergesort() //Divide part of mergesort algorithms in iterative format.Determines start,middle and end points for each execution.
{
	vector<long int> v;
	v.push_back(size);
	int i=0;
	long int l=0,m,r;
	clock_t t=clock();
	while(v[i]>1)
	{
		long int div=v[i]/2;
		v.push_back(div);
		v.push_back(v[i]-div);
		i++;
	}
	for(int j=v.size()-1;j>=0;j--)
	{
		if(v[j]!=1)
		{
			if(v[j]%2!=0){m=l+((v[j]+1)/2);}
			else{m=l+(v[j]/2);}
			r=l+v[j]-1;
			merge(l,m,r);
		}
		if(l+v[j]>size-1){l=0;}
		else{l+=v[j];}
	}
	t=clock()-t;
	cout<<1000*(((double)t)/CLOCKS_PER_SEC)<<endl;
}
void Sort::merge(long int l,long int m,long int r) //Conquer part of mergesort algorithm.
{
	long int i=0,j=0,k=l,a=m-l,b=r-m+1,left[a],right[b];
	while(i<a || j<b)
	{
		if(i<a)
		{
			left[i]=numbers[l+i];
			i++;
		}
		if(j<b)
		{
			right[j]=numbers[m+j];
			j++;
		}
	}
	i=0,j=0;
	while(i<a || j<b)
	{
		if(i<a && j<b)
		{
			if(left[i]<right[j])
			{
				numbers[k]=left[i];
				i++;
			}
			else
			{
				numbers[k]=right[j];
				j++;
			}
		}
		else if(i<a)
		{
			numbers[k]=left[i];
			i++;
		}
		else
		{
			numbers[k]=right[j];
			j++;
		}
		k++;
	}
}
Sort::~Sort() //Destructor function is also prints the output array.
{
	ofstream file("output.txt");
	for(int i=0;i<size;i++)
	{
		file<<numbers[i]<<endl;
	}
	file.close();
	delete numbers;
}
Sort::Sort(char* filename,int n){ //Constructor function is also reads lines from file
	size=n;
	numbers=new long int[size];
	ifstream file(filename);
	for(int i=0;i<size;i++)
	{
		string str;
		file>>str;
		istringstream(str)>>numbers[i];
	}
	file.close();
}
int main(int argc,char** argv)
{
	if(argc==4) //Check the number of arguments for correctness
	{
		long int size=atoi(argv[2]); //Take array size
		if(0<size<=1000000 && (strcmp(argv[1],"b")==0 || strcmp(argv[1],"m")==0)) //Check array size and algorithm type for correctness
		{
			Sort Data(argv[3],size); //Create array and read data from given text file
			if(strcmp(argv[1],"m")==0){Data.mergesort();} //If first argument is m,perform mergesort
			else if(strcmp(argv[1],"b")==0){Data.bubblesort();} //Otherwise perform bubblesort
		}
		else{cerr<<"Invalid command.";}		//Send error message and exit.
	}
	else{cerr<<"Invalid command.";}
	return 0;
}
