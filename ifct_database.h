#ifndef ifct_database_h
#define ifct_database_h


int ifctdb_addTail(void* obj);
int ifctdb_deleteData(int index);
int ifctdb_len(void);
void* ifctdb_getData(int index);

#endif
