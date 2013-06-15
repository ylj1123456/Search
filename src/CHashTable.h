/* 本文将创建一个hash表程序用于储存所有字符串
 *
 */
#ifndef _HASH_H_
#define _HASH_H_
#include<string>
#include<set>
using namespace std;

const int HASH_OFFSET=0,HASH_A=1,HASH_B=2;
const int TABLE_SIZE=5471;
struct element{
   // unsigned long ix_hash;
    unsigned long ck_hash_a;
    unsigned long ck_hash_b;
    bool bExist;
  //  string words;
    set<string> *pset;
};
class CHashTable{
    private:
        unsigned long cryptTable[0x500];
       // unsigned int table_size;
        struct element* ptable[TABLE_SIZE];
    protected:
        void prepareCryptTable();
    public:
        explicit CHashTable();
        unsigned long getHashString(const string& in_str,unsigned long hash_type);
         int getHashTablePos(string str_sch);
        void insert(const string& in_str,const string& file_name);
        const  element* operator[](const int pos) const
        {
           // return    ptable[pos]->pset;
                   return ptable[pos];
        }
        ~CHashTable();

};
#endif
