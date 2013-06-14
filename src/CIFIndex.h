#ifndef _IFI_H_
#define _IFI_H_



#include<iostream>
#include<set>
#include<map>
#include<string>
#include<fstream>
#include<cctype>

using namespace std;

/* class CIFIndex keep a map with the second parameter: set
 * map method using IFIndex way
 */
class CIFIndex{
	private:
		map<string,set<string>* > *m_map;
		string m_dir;
		int m_total_num;
	public:
        CIFIndex()
        {
            m_map=NULL;
            m_total_num=0;
            m_dir="";
        }
		CIFIndex(string dir,int num)
		{
			m_dir=dir;
			m_total_num=num;	
			m_map=new map<string,set<string> *> ();
		}
        ~CIFIndex(){
			if(m_map!=NULL)
			{
				for(map<string, set<string>* >::iterator ite=m_map->begin();
                        ite!=m_map->end();
                        ++ite)
				{
					if(ite->second!=NULL)
					{
						delete ite->second;
						ite->second=NULL;
					}
				}
				delete m_map;
			}
			m_map=NULL;

		}
		string filter(const string& src)
		{
			string tmp;
			for(int i=0;i!=src.length();++i)
			{
				if(!ispunct(src[i]))
				{
					tmp.push_back(src[i]);

				}	
			}
            
			return tmp;
        }			
    public:
        void readIn();
        void print();
        
        const set<string>* search(const string& in_str);
};

#endif 
