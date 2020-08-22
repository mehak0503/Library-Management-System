#ifndef DB_H
#define DB_H
#include "sqlite3.h"
#include<iostream>
#include<string>
using namespace std;
//string db_name = "lms.db";

class db
{
sqlite3 *instance;
//db();
public:
db();
~db();
//db *getInstance();
void create_table();
void execute_query(string sql,string msg);
void execute_param_query(string sql);
void insert_record(string sql);
void insert_member(string sql);
void update_record(string sql);
void update_delete(string sql,string sql1);
void get_date(string sql);
int fetch_record(string sql);
void delete_records(string sql);
};


#endif // DB_H
