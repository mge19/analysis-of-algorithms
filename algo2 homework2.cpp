/*BLG336E - Analysis of Algorithms 2
Project - 2
Mehmet Gencay Ertürk - 150130118*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;
typedef unsigned long long int uint64;
int make_equal_length(string &str1,string &str2)
{
	int len1=str1.size(),len2=str2.size();
	if(len1>len2) //If length of str2 is smaller,add zeroes to str2 until sizes will be equal
	{
		for(int i=0;i<len1-len2;i++){str2='0'+str2;}
	}
	if(len1<len2) //If length of str1 is smaller,add zeroes to str1 until sizes will be equal
	{
		for(int i=0;i<len2-len1;i++){str1='0'+str1;}
	}
	return str2.size(); //Return the final size
}
string add(string str1,string str2)
{
	string result; //To store the sum
	int length=make_equal_length(str1,str2),carry=0; //Make string sizes equal,take the string size and initialize carry 
	for(int i=length-1;i>=0;i--) //Add bits from least significant to most significant
	{
		int bit1=str1.at(i)-'0',bit2=str2.at(i)-'0',sum=(bit1^bit2^carry)+'0'; //Calculate sum for every bit.Sum=first XOR second XOR carry
		result=(char)sum+result; 
		carry=((bit1&bit2) | (bit1&carry) | (bit2&carry)); //Calculate carry for each step (Boolean)
	}
	if(carry) {result='1'+result;} //If overflow,add a leading 1
	return result;
}
uint64 multiply(string num1,string num2)
{
	int size=make_equal_length(num1,num2);
	if(size==0) {return 0;}
	if(size==1) {return (num1[0]-'0')*(num2[0]-'0');} //Simply multiply numbers if size is 1 
	int left=size/2,right=size-left; //left and right hand side indexes of integer. Left=floor(n/2),right=ceil(n/2)
	string num1_left=num1.substr(0,left),num1_right=num1.substr(left,right),num2_left=num2.substr(0,left),num2_right=num2.substr(left,right); //Find left and right substrings
	uint64 p1=multiply(num1_left,num2_left),p2=multiply(num1_right,num2_right),p3=multiply(add(num1_left,num1_right),add(num2_left,num2_right)); //Recursive products
	return p1*(1<<(2*right))+(p3-p1-p2)*(1<<right)+p2; //Combine results
}
uint64 multiply_classic(string num1,string num2)
{
	bool zero=true;
	uint64 total=0;
	string result,shifted;
	vector<string> str;
	int size=make_equal_length(num1,num2);
	for(int i=size-1;i>=0;i--)
	{
		if(num1.at(i)=='1') //If any index of first string is 1,shift the second string as the index of digit and add to the list
		{
			zero=false;
			shifted=num2;
			for(int j=0;j<size-i-1;j++){shifted=shifted+"0";}
			str.push_back(shifted);
		}
	}
	if(!zero)
	{
		result=str.at(0);
		for(int i=1;i<str.size();i++) 	{result=add(result,str.at(i));}//Add the list elements and reach to the result.
		for(int i=0;i<result.size();i++) //Convert it to decimal
		{
			if(result[i]=='1'){total+=(1<<(result.size()-i-1));}
		}		
	}
	return total;
}
int main() 
{
	srand(time(NULL));
	ofstream output("output.txt");
	output<<"Bit number\tAlgorithm 1 Result\tClassical Algorithm Result\n";
	string str1,str2;
	for(int i=2;i<=8;i*=2) //Generate random strings from 2 till 8 bits.
	{		
		for(int j=0;j<i;j++) 
		{
			str1.push_back((rand()%2)+'0');
			str2.push_back((rand()%2)+'0');
		}
		output<<i<<'\t'<<multiply(str1,str2)<<'\t'<<multiply_classic(str1,str2)<<endl; //Print out the results.
		str1.clear();
		str2.clear();		
	}
	output<<"Bit number\tAlgorithm 1 Runtime(ms)\tClassical Algorithm Runtime(ms)\n";
	for(int i=512;i<=4096;i*=2) //Generate random strings from 512 till 4096 bits.
	{		
		for(int j=0;j<i;j++) 
		{
			str1.push_back((rand()%2)+'0');
			str2.push_back((rand()%2)+'0');
		}
		clock_t start=clock();
		uint64 x=multiply(str1,str2);
		clock_t end=clock();
		output<<i<<'\t'<<1000*((double)end-(double)start)/CLOCKS_PER_SEC<<'\t'; //Print out the runtimes.
		clock_t start2=clock();
		x=multiply_classic(str1,str2);
		clock_t end2=clock();
		output<<1000*((double)end2-(double)start2)/CLOCKS_PER_SEC<<endl; //Print out the runtimes.		
		str1.clear();
		str2.clear();
	}	
	output.close();
	return 0;
}
