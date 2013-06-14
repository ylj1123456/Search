#include "CIFIndex.h"
#include<iostream>
using namespace std;

int main(int argc,char **argv)
{
    cout<<"please type in your file path:  and file counts: \n";
    string path;
    int count=0;
    cin>>path;
    cin>>count; 
	CIFIndex ifi(path,count);

ifi.readIn();	
	
string in_str;

cout<<"please cin what you want to search: \n ";
while(cin>>in_str)
{
    if(in_str=="-q")
    {
        return 0;
    }
    else
    {
       const set<string>* pset=ifi.search(in_str);
       cout<<"your search comes here:"<<endl;
       for(set<string>::iterator ite=pset->begin();ite!=pset->end();++ite)
       {
           cout<<*ite<<" ";
       }
       cout<<endl;
    }

cout<<"please cin what you want to search: \n ";
}

}
