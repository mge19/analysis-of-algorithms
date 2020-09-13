//BLG335E-Analysis of Algorithms
//Homework-2
//Mehmet Gencay Ertürk - 150130118
#include <bits/stdc++.h>
#include <ctime>
using namespace std;
class Event{
	public:
		string event_name;
		int event_time;
		bool start;
		Event(string str,int time,bool isstart);
};
Event::Event(string str,int time,bool isstart)
{
	event_name=str;
	event_time=time;
	start=isstart;
}
vector<Event> events;
void read_file(const char* filename)
{
	ifstream file(filename);
	if(!file.is_open())
	{
		cerr<<"Error! File is unavailable.";
		exit(1);
	}
	else
	{
		while(!file.eof())
		{
			string str;
			int start_time=0,end_time=0;
			char x;
			while(true) //Take event name
			{
				x=file.get();
				if(x=='\t'){break;} //Finish taking event name
				else{str.push_back(x);}
			}
			while(true) //Take start time
			{
				x=file.get();
				if(x=='\t'){break;} //Finish taking start time
				else
				{
					start_time+=x-'0';
					start_time*=10;
				}
			}			
			start_time/=10;
			while(true) //Take end time
			{
				x=file.get();
				if(x=='\n' || file.eof()){break;} //Finish taking end time
				else
				{
					end_time+=x-'0';
					end_time*=10;
				}
			}
			end_time/=10;
			if(end_time<start_time) //Error handling
			{
				cout<<"Error! End time cannot be less than start time."<<endl;
				exit(1);
			}
			events.push_back(Event(str,start_time,true)); //Create start event and push it to the vector
			events.push_back(Event(str,end_time,false)); //Create end event and push it to the vector
		}
		file.close();
	}
}
void heapify(int size,int i) //First part of the heapsort algorithm
{
	int min=i,l=2*i+1,r=2*i+2; //Take child node indexes and initialize the minimum node
	if(l<size && events[l].event_time<events[min].event_time){min=l;} //Check left child node if exists
	if(r<size && events[r].event_time<events[min].event_time){min=r;} //Check right child node if exists
	if(min!=i) //If minimum node is one of the child nodes.
	{
		swap(events[i],events[min]); //Swap nodes
		heapify(size,min); //Execute heapify for minimum child node
	}
}
void heapsort() //Last part of the heapsort algorithm
{
	int size=events.size(),maxtime=0; //Calculate size and initialize the maximum time
	for(int i=size/2-1;i>=0;i--){heapify(size,i);} //Build min heap
	for(int i=size/2;i<size;i++){maxtime=(events[i].event_time>maxtime)?events[i].event_time:maxtime;} //Find maximum time around leaf nodes
	for(int clock=0;clock<=maxtime;clock++) //Clock increments
	{
		if(events[0].event_time>clock){cout<<"TIME "<<clock<<": NO EVENTS"<<endl;} //Report if no events
		else
		{
			while(size>0 && events[0].event_time==clock) //Execute the algorithm for nodes has same value with clock
			{
				cout<<"TIME "<<clock<<": "<<events[0].event_name;
				if(events[0].start){cout<<" STARTED"<<endl;} //Print for start event
				else{cout<<" ENDED"<<endl;} //Print for end event
				swap(events[0],events[size-1]); //Swap minimum and maximum elements
				heapify(--size,0); //Decrement heap size and heapify to make next node with minimum time root
			}
		}
	}
}
int main(int argc,char** argv)
{
	if(argc==2) //If only parameter is filename
	{
		read_file(argv[1]);
		clock_t start=clock();
		heapsort();	
		clock_t end=clock();
		cout<<"Total execution time:"<<(double)((end-start)/CLOCKS_PER_SEC); //Print out total execution time	
	}
	else{cerr<<"Error! Invalid command.";}
	return 0;
}
