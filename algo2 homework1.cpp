/*BLG336E - Analysis of Algorithms
  Project - 1
  Mehmet Gencay Ertürk - 150130118*/
#include <iostream>
#include <ctime>
#include <list>
#include <deque>
#include <cstdlib>
#include <cstring>
using namespace std;
class Coordinate
{
	public:
		int x,y;
		bool placed;
		Coordinate(int i,int j);
};
Coordinate::Coordinate(int i,int j)
{
	x=i;
	y=j;
	placed=false;
}
class Table{
	public:
		Table(char* str);
		bool can_place_miner(int i,int j);
		void place_miner(int i,int j);
		void find_solution(char* str1,char* str2);
		char** table;
		list<Coordinate> sites; 
		~Table();
		int row,col,*row_max,*col_max,number_of_miners;
};
Table::Table(char* str)
{
	FILE* input=fopen(str,"r+");
	if(input==NULL)
	{
		cerr<<"Error opening file.";
		exit(1);
	}
	fscanf(input,"%d\t%d\n\t",&col,&row);
	col_max=new int[col];
	row_max=new int[row];
	table=new char*[row];
	for(int i=0;i<=row;i++)
	{
		if(i<row){table[i]=new char[col];}
		for(int j=0;j<=col;j++)
		{
			char x;
			if(j==col && i<row){fscanf(input,"%c\n",&x);}
			else if(!(i==0 && j==0)){fscanf(input,"%c\t",&x);}
			else if(j==col && i==row){fscanf(input,"%c",&x);}
			if(i==0)
			{
				if(j>0){col_max[j-1]=x-48;}
			}
			else if(j==0){row_max[i-1]=x-48;}
			else 
			{
				table[i-1][j-1]=x;
				if(x=='s'){sites.push_back(Coordinate(i-1,j-1));}
			}
			cout<<x<<endl;
		}
	}
	fclose(input);
}
bool Table::can_place_miner(int i,int j)
{
	if(i<0 || j<0 || i>=row || j>=col){return false;}
	if(table[i][j]=='s' || table[i][j]=='m'){return false;}
	if(row_max[i]<0 || col_max[j]<0){return false;}
	if(i>0 && table[i-1][j]=='m'){return false;}
	if(j>0 && table[i][j-1]=='m'){return false;}
	if(i<row-1 && table[i+1][j]=='m'){return false;}
	if(j<col-1 && table[i][j+1]=='m'){return false;}	
	return true;
}
void Table::place_miner(int i,int j)
{
	table[i][j]='m';
	row_max[i]--;
	col_max[j]--;
	number_of_miners++;
}
void Table::find_solution(char* str1,char* str2)
{
	int maximum_nodes_kept_in_stack=1,number_of_visited_nodes=1;
	Table t=*this;
	deque<Table> d;
	clock_t time_start=clock();
	d.push_back(t);
	while(t.number_of_miners!=sites.size())
	{
		if(strcmp(str1,"bfs")==0)
		{
			t=d.front();
			d.pop_front();	
		}
		else
		{
			t=d.back();
			d.pop_back();
		}
		list<Coordinate>::iterator it;
		for(it=t.sites.begin();it!=t.sites.end();++it)
		{
			if(t.can_place_miner((it->x)-1,it->y))
			{
				Table a=t;
				a.place_miner((it->x)-1,it->y);
				number_of_visited_nodes++;
				
				d.push_back(a);
			}
			if(t.can_place_miner((it->x)+1,it->y))
			{
				cout<<"x"<<endl;
				Table a=t;
				cout<<"x"<<endl;
				a.place_miner((it->x)+1,it->y);
				cout<<"x"<<endl;
				number_of_visited_nodes++;
				cout<<"x"<<endl;
			}
			if(t.can_place_miner(it->x,(it->y)-1))
			{
				Table a=t;
				a.place_miner(it->x,(it->y)-1);
				number_of_visited_nodes++;
				d.push_back(a);
			}
			if(t.can_place_miner(it->x,(it->y)+1))
			{
				Table a=t;
				a.place_miner(it->x,(it->y)+1);
				number_of_visited_nodes++;
				d.push_back(a);
			}
		}
		if(d.size()>maximum_nodes_kept_in_stack){maximum_nodes_kept_in_stack=d.size();}		
	}
	clock_t time_end=(double)(clock()-time_start)/CLOCKS_PER_SEC;
	cout<<"Algorithm: "<<str1<<endl<<"Number of visited nodes: "<<number_of_visited_nodes<<endl<<"Maximum number of nodes kept in memory: "<<maximum_nodes_kept_in_stack<<endl<<"Running time: "<<time_end<<"seconds"<<endl;
	FILE* output=fopen(str2,"w+");
	if(output==NULL)
	{
		cerr<<"Error opening file";
		exit(1);
	}
	fprintf(output,"%d\t%d\n\t",col,row);
	for(int i=0;i<=row;i++)
	{
		for(int j=0;i<=col;j++)
		{
			if(i==0)
			{
				if(j>0)
				{
					if(j==t.col){fprintf(output,"%d\n",col_max[j-1]);}
					else{fprintf(output,"%d\t",col_max[j-1]);}					
				}
			}
			else if(j==0){fprintf(output,"%d\t",row_max[i-1]);}
			else if(j==t.col){fprintf(output,"%c\n",t.table[i-1][j-1]);}
			else{fprintf(output,"%c\t",t.table[i-1][j-1]);}
		}
	}
	cout<<"Solution is written to the file";
	fclose(output);
}
Table::~Table()
{
	delete row_max;
	delete col_max;
	delete* table;
}
int main(int argc,char** argv)
{
	if(argc==4 && (strcmp(argv[1],"bfs")==0 || strcmp(argv[1],"dfs")==0))
	{
		Table t(argv[2]);
		t.find_solution(argv[1],argv[3]);
	}
	else
	{
		cerr<<"Invalid command";
		exit(1);
	}
	system("pause");
	return 0;
}
