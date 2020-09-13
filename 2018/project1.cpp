/*********************************
*BLG335E-Analysis of Algorithms  *
*Project-1                       *
*Mehmet Gencay Ertürk - 150130118*
**********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <ctime>
#define length 251
#define length2 743
using namespace std;
class data{
	private:
		long int arraysize;
		char algo,feature,**array,firstline[length2];
		double* numbers; 
	public:
		data(char c1,char c2,int n);
		~data();
		void determine_sort();
		void insertion_sort();
		void read();
		void write();
		void merge_sort();	
		void merge(long int l,long int m,long int r);	
};
data::data(char c1,char c2,int n)
{
	algo=c1;
	feature=c2;
	arraysize=n;
	array=new char*[arraysize];
	numbers=new double[arraysize];
	for(int i=0;i<arraysize;i++){array[i]=new char[length];}
}
data::~data()
{
	delete numbers;
	delete* array;
}
void data::determine_sort()
{
	if(algo=='i'){insertion_sort();}
	else {merge_sort();}
}
void data::insertion_sort()
{
	double temp;
	char* tempstr=new char[length];
	clock_t t=clock();
	for(long int i=0;i<arraysize;i++)
	{
		long int j=i-1;
		while(j>=0 && numbers[j]>numbers[j+1])
		{
			temp=numbers[j+1];
			numbers[j+1]=numbers[j];
			numbers[j]=temp;
			strcpy(tempstr,array[j+1]);
			strcpy(array[j+1],array[j]);
			strcpy(array[j],tempstr);
			j--;
		}
	}
	t=clock()-t;
	cout<<((double)t)/CLOCKS_PER_SEC<<endl;
	delete tempstr;
}
void data::read()
{
	FILE* fp=fopen("log_inf.csv","r+");
	if(fp==NULL)
	{
		printf("File not found.\n");
		exit(1);
	}
	else
	{
		char** newarray=new char*[arraysize],*str;
		fgets(firstline,length2,fp);
		for(int i=0;i<arraysize;i++)
		{
			newarray[i]=new char[length];
			int j=0;
			char x;
			do{
				x=fgetc(fp);
				array[i][j]=x;
				newarray[i][j]=x;
				j++;
			}while(x!='\n');
			for(j=0,str=strtok(newarray[i],",");(j<2 && feature=='p') || (j<7 && feature=='t');str=strtok(NULL,","),j++){}	
			numbers[i]=atof(str);
		}
		delete* newarray;
		fclose(fp);
	}
}
void data::merge(long int l,long int m,long int r)
{
	long int i=0,j=0,k=l,a=m-l,b=r-m+1;
	double left[a],right[b];
	char** leftarray=new char*[a],**rightarray=new char*[b];
	while(i<a || j<b)
	{
		if(i<a)
		{
			leftarray[i]=new char[length];
			strcpy(leftarray[i],array[l+i]);
			left[i]=numbers[l+i];
			i++;
		}
		if(j<b)
		{
			rightarray[j]=new char[length];
			strcpy(rightarray[j],array[m+j]);
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
				strcpy(array[k],leftarray[i]);
				i++;
			}
			else
			{
				numbers[k]=right[j];
				strcpy(array[k],rightarray[j]);
				j++;
			}
		}
		else if(i<a)
		{
			numbers[k]=left[i];
			strcpy(array[k],leftarray[i]);
			i++;
		}
		else
		{
			numbers[k]=right[j];
			strcpy(array[k],rightarray[j]);
			j++;
		}
		k++;
	}
	delete* leftarray;
	delete* rightarray;
}
void data::write()
{
	FILE *gp=fopen("sorted.csv","w+");
	fputs(firstline,gp);
	for(int i=0;i<arraysize;i++){fputs(array[i],gp);}
	fclose(gp);
}
void data::merge_sort()
{
	vector<long int> v;
	v.push_back(arraysize);
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
		if(l+v[j]>arraysize-1){l=0;}
		else{l+=v[j];}
	}
	t=clock()-t;
	cout<<((double)t)/CLOCKS_PER_SEC<<endl;
}
int main(int argc,char** argv)
{
	if(argc==7 && strcmp(argv[1],"-algo")==0 && strcmp(argv[3],"-feature")==0 && strcmp(argv[5],"-size")==0)
	{
		long int size=atoi(argv[6]);
		if(0<size<916723 && (strcmp(argv[4],"p")==0 || strcmp(argv[4],"t")==0) && (strcmp(argv[2],"m")==0 || strcmp(argv[2],"i")==0))
	 	{
			data d(argv[2][0],argv[4][0],size);
			d.read();
			d.determine_sort();
			d.write();
		}
		else {cout<<"Invalid command"<<endl;}
	}
	else {cout<<"Invalid command"<<endl;}
	return 0;
}
