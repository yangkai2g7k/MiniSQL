//
//  CatalogManager.h
//  
//
//  Created by 杨凯 on 15/10/11.
//
//

#ifndef ____CatalogManager__
#define ____CatalogManager__

#include <stdio.h>//
#include "sqlstruct.h"
#include "sqlparser_driver.hh"
class CatalogManager:public sqlparser_driver{
private:
#define NAME_LENGTH 32
#define HASH_SIZE 102
#define MAX_PRIMARY_COL 10
#define MAXNUM_INDEX 10
#define MAXNUM_COL 10
#define MAXNUM_ATTR 3
#define BLOCKSIZE 4096
#define BLOCKREMAINDER 10000
#define BLOCK_HEAD_SIZE 8
#define STORAGE_START_BLOCK 3
    struct meta_t{
        off_t tablepos;
        off_t indexpos;
        off_t freeblock;
        off_t head,end;
    }meta;
    struct record_t {
        std::string name;
        int datatype;
        std::string attr[MAXNUM_ATTR];
    };
    struct hash_t{
        std::string name;
        off_t pos;
    } tablehash[HASH_SIZE],indexhash[HASH_SIZE];
    struct table_t{
        //sqlstruct::createtable table;
        std::string createstr;
        size_t numofIndex;
        std::string index[MAXNUM_INDEX];
        off_t pos;
    };
    struct index_t{
        std::string name;
        std::string table;
        size_t numofcol;
        std::string col[MAXNUM_COL];
        off_t pos;
    };
    FILE *fp;
    int flevel;
    std::string filename = "/Users/andyyang/Documents/MiniSQL/MiniSQL/test.txt";
    void addIndextoTable(off_t tablepos,std::string name);
    void dropIndextoTable(off_t tablepos,std::string name);
    void map(off_t position,hash_t *hashtable);
    void map(off_t position,table_t *table);
    void map(off_t postion,index_t *index);
    void map();
    void unmap(off_t position,table_t *table);
    void unmap(off_t position,hash_t *hashtable);
    void unmap(off_t position,index_t *index);
    void unmap();
    //BKDR hash
    unsigned int hashFunc(std::string);
    off_t Alloc(size_t size);
    //off_t Alloc(table_t table);
    void Unalloc(off_t pos,size_t size);
    //void Unalloc(table_t table);

    /*
    struct tablelist_t{
        char name[NAME_LENGTH];
        off_t positon;
        off_t next;
    };
    struct indexlist_t{
        char name[NAME_LENGTH];
        char table[NAME_LENGTH];
        char attr[NAME_LENGTH];
        off_t next;
    };
    struct meta_t{
        size_t size;
        off_t firstTable;
        off_t firstIndex;
    } meta;
    struct index_t{
        char indexkey[NAME_LENGTH];
        off_t position;
    };
    struct col_t{
        char name[NAME_LENGTH];
        int datatype;
        int attr;
    };
    struct table_t{
        size_t numofcol;
        size_t sizeofPrimarykey;
        size_t sizeofIndex;
        char (*primaykey)[NAME_LENGTH];
        index_t *index;
        col_t *col;
    };
    bool FindTable(std::string name,off_t &position);
    bool FindIndex(std::string name,off_t &position);
    void map(off_t position,struct tablelist_t &table);
    void map(off_t position,struct indexlist_t &index);
    */
public:
    CatalogManager();
    /*open catalog file*/
    void Openfile();
    /*close catalog file*/
    void Closefile();
    /*add index into catalog, type createindex is define in sqlstruct.h, pos is the addr of head of bpt*/
    bool addIndex(sqlstruct::createindex index,off_t pos);
    /*add table into catalog,name is table name,createstr is the sql cmd that create the table*/
    bool addTable(std::string name,std::string createstr);
    /*find table named name, return exist or not and the addr in catalog file*/
    bool FindTable(std::string name,off_t &position);
    /*find index named name, return exist or not and the addr in catalog file*/
    bool FindIndex(std::string name,off_t &position);
    /*get table info , createtable is define in sqlstruct.h, pos is the addr of catalog that store the table*/
    sqlstruct::createtable GetTableSchema(off_t pos);
    /*drop table named name*/
    bool dropTable(std::string name);
    /*drop table named name*/
    bool dropIndex(std::string name);
    /*do some basic setting, using it when the first time construct db**/
    void InitFromEmpty();
    /*after first time construct db, then every time initialize CatalogManager, call this func*/
    void InitFromFile(){map();};
    sqlstruct::createtable ctable;
    //size_t hashFindName(std::string name);
    //size_t hashFindPos(std::string name);
    void Createtable(sqlstruct::createtable &table);
};
#endif /* defined(____CatalogManager__) */
