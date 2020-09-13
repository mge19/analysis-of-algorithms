/*BLG336E-Analysis of Algorithms 2
Project-3
Mehmt Gencay Ertürk - 150130118*/
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#define max 11111;
using namespace std;
#define graph map<int,map<int,int> > //map<from,map<to,weight>>,map[from][to]=weight
/*[0,team-1]:team nodes
team:source
team+1:sink
[team+2,n):match nodes
*/
bool bfs(graph g,int parent[],int team,int n) //Find a flow path
{
	bool visited[n]; 
	fill_n(visited,n,false);
	queue<int> q;
	q.push(team);
	visited[team]=true;
	while(!q.empty())
	{
		int current=q.front();
		q.pop();
		map<int,int>::iterator it;
		if(!g[current].empty())
		{
			for(it=g[current].begin();it!=g[current].end();it++)
			{
				int value=it->first;
				if(!visited[value] && it->second>0)
				{
					visited[value]=true;
					parent[value]=current;
					q.push(value);
				}
			}			
		}
	}
	return visited[team+1]; //If sink is visited, path is found.
}
int maxflow(graph g,int team,int n) //Determine maximum flow
{
	int maxflow=0;
	int parent[n]; //Array to keep the augmenting path
	while(bfs(g,parent,team,n)) //Continue until an augmenting path does not exist
	{
		int flow=max;
		int i=team+1,j;
		while(i!=team) //Determine flow value
		{
			j=parent[i];
			if(flow>g[j][i]){flow=g[j][i];}
			i=j;
		}
		maxflow+=flow;
		i=team+1;
		while(i!=team) //Update the flow graph
		{
			j=parent[i];
			g[j][i]-=flow;
			i=j;
		}
	}
	return maxflow;
}
int main(int argc,char** argv)
{
	ifstream input(argv[1]);
	int team=input.get()-'0'; //Eead number of teams
	input.get();
	int wins[team],remaining[team];
	for(int i=0;i<team;i++) //Read wins of each team
	{
		wins[i]=input.get()-'0';
		input.get();
	}
	int matches[team][team];
	for(int i=0;i<team;i++) //Read matrix of matches
	{
		remaining[i]=0;
		for(int j=0;j<team;j++)
		{
			matches[i][j]=input.get()-'0';
			input.get();
			remaining[i]+=matches[i][j];
		}
	}	
	input.close();
	ofstream output(argv[2]);
	for(int id=0;id<team;id++) //Create flow network for each team
	{
		graph g;
		int gamenode=team+2; //A variable to keep number of nodes
		int maximumflow=0;
		for(int i=0;i<team;i++)
		{
			if(i!=id)
			{
				for(int j=0;j<i;j++)
				{
					if(j!=id && matches[i][j]!=0)
					{
						g[team][gamenode]=matches[i][j]; //Source-match node connection
						g[gamenode][i]=max; //Team node-match node connection
						g[gamenode][j]=max; //Team node-match node connection
						gamenode++;
						maximumflow+=matches[i][j];
					}
				}
				g[i][team+1]=wins[id]+remaining[id]-wins[i]; //Team node-sink connection
			}
		}
		if(maximumflow<=maxflow(g,team,gamenode)){output<<"1 ";} //If maximum flow is greater than or equal to the total number of matches among remaining teams, then it is not eliminated.
		else{output<<"0 ";}
	}
	output.close();
	getchar();
	return 0;
}
