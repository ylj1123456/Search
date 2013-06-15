#include "CHashTable.h"
#include<cctype>
#include<iostream>
/*
CHashTable::CHashTable()
{
    table_size=0;
    cryptTable=NULL;
    prepareCryptTable();
}*/
CHashTable::CHashTable()
{
    prepareCryptTable();
    //ptable=new element*[table_size];
    for(int i=0;i!=TABLE_SIZE;++i)
    {
        ptable[i]=new element();
       // ptable[i]->ix_hash=-1;
        ptable[i]->ck_hash_a=-1;
        ptable[i]->ck_hash_b=-1;
        ptable[i]->bExist=false;
    //    ptable[i]->words="";
        ptable[i]->pset=NULL;
    }
    cout<<"here!"<<endl;
        
}
void CHashTable::prepareCryptTable()
{
    unsigned long seed=0x00100001,index1=0,index2=0,i;
    for(index1=0;index1<0x100;index1++)
    {
        for(index2=index1,i=0;i<5;i++,index2+=0x100)
        {
            unsigned long tmp1,tmp2;

            seed=(seed*125+3)%0x2AAAAB;
            tmp1=(seed&0xFFFF)<<0x10;
            seed=(seed*125+3)%0x2AAAAB;
            tmp2=(seed&0xFFFF);

            cryptTable[index2]=(tmp1|tmp2);
        }
    }
   /* cout<<"prepare success!"<<endl;
    for(i=0;i!=0x500;++i)
    {
        cout<<cryptTable[i]<<" "<<cryptTable[1]<<endl;
    }
    */
}
unsigned long CHashTable::getHashString(const string& in_str,unsigned long hash_type)
{
    unsigned long seed1=0x7FED7FED;
    unsigned long seed2=0xEEEEEEEE;
    int ch;

    for(int i=0;i!=in_str.length();++i)
    {
        ch=toupper(in_str[i]);
        seed1=cryptTable[(hash_type<<8)+ch]^(seed1+seed2);
        seed2=ch+seed1+seed2+(seed2<<5)+3;
    }
   // cout<<"seed1"<<seed1<<endl;
    return seed1;
}
 int CHashTable::getHashTablePos(string str_sch)
{
   unsigned long nHash=getHashString(str_sch,HASH_OFFSET);
   unsigned long nHashA=getHashString(str_sch,HASH_A);
   unsigned long nHashB=getHashString(str_sch,HASH_B);
   int nHashStart=nHash%TABLE_SIZE;
   int nHashPos=nHashStart; 
   cout<<"search string: "<<str_sch<<" hash: "<<nHash<<"hash_pos: "<<nHashPos<<" hash_a: "<<nHashA<<" hash_b "<<nHashB<<endl;
   while(ptable[nHashPos]->bExist)
   {
       cout<<" hasha: "<<ptable[nHashPos]->ck_hash_a<<endl;
       if((ptable[nHashPos]->ck_hash_a==nHashA)
               &&(ptable[nHashPos]->ck_hash_b==nHashB))
       {
           cout<<"true"<<endl;
           return nHashPos;
       }
       else
       {
           nHashPos=(nHashPos+1)%TABLE_SIZE;
       }
       if(nHashPos==nHashStart)
           break;
   }
   return -1;

}
void CHashTable::insert(const string& in_str,const string& file_name)
{
    
   unsigned long nHash=getHashString(in_str,HASH_OFFSET);
   unsigned long nHashA=getHashString(in_str,HASH_A);
   unsigned long nHashB=getHashString(in_str,HASH_B);
   int nHashStart=nHash%TABLE_SIZE;
   int nHashPos=nHashStart;

   cout<<"insert string: "<<in_str<<" hash: "<<nHash<<"nHashPos: "<<nHashPos<<" hash_a:"<<nHashA<<" hash_b "<<nHashB<<endl;
   while(ptable[nHashPos]->bExist)
   {
       if((ptable[nHashPos]->ck_hash_a==nHashA)
               &&(ptable[nHashPos]->ck_hash_b==nHashB))
       {
           break;
       }
       else
       {
           nHashPos=(nHashPos+1)%TABLE_SIZE;
       }
       if(nHashPos==nHashStart)
       {
           cerr<<"error! hashtable is full!";
           return;
       }
   }
   if(!ptable[nHashPos]->bExist)
   {
      // ptable[nHashPos]->ix_hash=nHash;
       ptable[nHashPos]->ck_hash_a=nHashA;
       ptable[nHashPos]->ck_hash_b=nHashB;
       ptable[nHashPos]->pset=new set<string>();
       ptable[nHashPos]->bExist=true;
   }
   ptable[nHashPos]->pset->insert(file_name);
}
CHashTable::~CHashTable()
{
        for(int i=0;i!=TABLE_SIZE;++i)
        {
            if(ptable[i]!=NULL)
            {

                delete ptable[i];
                ptable[i]=NULL;
            }

        }

}
