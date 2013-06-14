#include "CIFIndex.h"

/* read in map buffer from files
 */
void CIFIndex::readIn()
{
    ifstream infile;
    string tmp_str,tmp_dir,tmp_rt,tmp_file_name;
    for(int i=0;i!=m_total_num;++i)
    {
        tmp_dir=m_dir;
        tmp_file_name=i+'0';
        tmp_file_name+=".txt";
        
        tmp_dir+=tmp_file_name;
        
        infile.open(tmp_dir.c_str(),ios::in);

        if(!infile)
        {
            cerr<<"cannot open file: "<<tmp_dir<<endl;
        }
        while(infile>>tmp_str)
        {
            tmp_rt=filter(tmp_str);
            if(!m_map->count(tmp_rt))
            {
                (*m_map)[tmp_rt]=new set<string>();
            }
            (*m_map)[tmp_rt]->insert(tmp_file_name);
        }
        infile.close();
    }
}
void CIFIndex::print()
{
    for(map<string,set<string>* >::iterator ite=m_map->begin();
            ite!=m_map->end();++ite)
    {
        cout<<ite->first<<": "<<endl;
        for(set<string>::iterator set_ite=ite->second->begin();
                set_ite!=ite->second->end();
                ++set_ite)
        {
            cout<<"  ";
            cout<<*set_ite<<" ";
        }
        cout<<endl;
    }
}

const set<string>*CIFIndex::search(const string& in_str)
{
    if(!m_map->count(in_str))
    {
        return NULL;
    }
    else
    {
        return (*m_map)[in_str];
    }
}
