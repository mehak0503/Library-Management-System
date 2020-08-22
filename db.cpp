#include "db.h"
#include "sqlite3.h"

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);

   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }

   printf("\n");
   return 0;
}

//Creates a db connection instance
db::db()
{
    int ret_code = sqlite3_open("lms.db",&instance);
    if(ret_code)
    {
        printf("Can't open database: %s\n",sqlite3_errmsg(instance));
    }
}

//Closes a db connection instance
db::~db()
{
    sqlite3_close(instance);
}

//Executes the sql query provided
void db::execute_query(string sql,string msg)
{
    char* msg_err;
    int res = sqlite3_exec(instance,sql.c_str(),NULL,0,&msg_err);
    if (res==SQLITE_CONSTRAINT)
    {
        //printf("%s",msg_err);
      std::cout << msg << std::endl;
    }
    else if (res != SQLITE_OK) {
        std::cout << "\nSomething is wrong!!\n" << std::endl;
        printf("%s",msg_err);
    }
    else
    {
      cout<<"\nOperation successfully done!!\n";
    }
}

//Creates initial database schema
void db::create_table()
{
  string msg = "\nUnknown error!!\n";
  string sql = "PRAGMA foreign_keys = on; CREATE TABLE IF NOT EXISTS MEMBER_EVENTS("  \
      "USERID INT  NOT NULL UNIQUE," \
      "USERTYPE  INT    NOT NULL," \
      "NAME TEXT NOT NULL,"\
      "ADDRESS TEXT NOT NULL,"\
      "PHONE TEXT NOT NULL,"\
      "PRIMARY KEY (PHONE));";
    execute_query(sql,msg);
    sql = "CREATE TABLE IF NOT EXISTS MEMBERS("  \
      "USERID INT  NOT NULL UNIQUE," \
      "USERTYPE  INT    NOT NULL," \
      "NAME      TEXT    NOT NULL," \
      "ADDRESS   TEXT    NOT NULL," \
      "PHONE  TEXT     NOT NULL,"\
      "PRIMARY KEY (PHONE));";
      //"FOREIGN KEY (PHONE) REFERENCES MEMBER_EVENTS(PHONE) ON DELETE CASCADE ON UPDATE CASCADE);";
    execute_query(sql,msg);

    sql = "CREATE TABLE IF NOT EXISTS BOOKS("  \
      "ISBN TEXT PRIMARY KEY  NOT NULL," \
      "TITLE           TEXT    NOT NULL," \
      "AUTHOR         TEXT    NOT NULL," \
      "RESERVED       INT    NOT NULL," \
      "ISSUED_TO      INT,"\
      "RETURN_DATE    TEXT,"\
      "FOREIGN KEY (ISSUED_TO) REFERENCES MEMBERS(USERID) ON DELETE CASCADE ON UPDATE CASCADE);";
    execute_query(sql,msg);
    sql = "CREATE TABLE IF NOT EXISTS BOOK_EVENTS("  \
      "RQST_ID INT NOT NULL UNIQUE, " \
      "USERID INT  NOT NULL," \
      "RQST_TYPE   INT NOT NULL," \
      "ISBN  TEXT,"\
      "TITLE TEXT,"\
      "AUTHOR TEXT,"\
      "PRICE INT,"\
      "PRIMARY KEY (RQST_ID),"\
      "FOREIGN KEY (USERID) REFERENCES MEMBERS(USERID) ON DELETE CASCADE ON UPDATE CASCADE);";
    execute_query(sql,msg);


}

//Insert a new record
void db::insert_record(string sql)
{
    string msg = "\nConstraint violation! Duplicate/No Records Found!!\n";
    execute_query(sql,msg);
}


//Fetch results
int db::fetch_record(string sql)
{
    struct sqlite3_stmt *selectstmt;
    int result = sqlite3_prepare_v2(instance, sql.c_str(), -1, &selectstmt, NULL);
    if(result == SQLITE_OK)
    {
       if (sqlite3_step(selectstmt) == SQLITE_ROW)
       {
        char* msg_err;
        const char* data = "";
        int res = sqlite3_exec(instance, sql.c_str(), callback, (void*)data, &msg_err);
        if( res != SQLITE_OK ) {
          fprintf(stderr, "SQL error: %s\n", msg_err);
          sqlite3_free(msg_err);
        } 
        return 1;
       }
       else
       {
          cout<<"\nNo records found!!\n";
          return 0;
       }
    }
    else{
      cout<<"\nSomething is wrong!!\n";
      return 0;
    }
    sqlite3_finalize(selectstmt);
}

//Update record
void db::update_record(string sql)
{
  struct sqlite3_stmt *selectstmt;
    int result = sqlite3_prepare_v2(instance, sql.c_str(), -1, &selectstmt, NULL);
    if(result == SQLITE_OK)
    {
    int rc = sqlite3_step(selectstmt);
    if (rc == SQLITE_ROW)
    {
      string msg = "\nInvalid USERID!!\n";
      execute_query(sql,msg);
    }
    else if (rc == SQLITE_DONE)
    {
      string msg = "\nWrong operation!!\n";
      execute_query(sql,msg);
    }
    else if (rc == SQLITE_CONSTRAINT)
    {
      cout<<"\nConstraint violation!\n";
    }
    else
       {
          cout<<"\nNo records found!!\n";
       }
    }
    else{
      cout<<"\nSomething is wrong!!\n";
    }
    sqlite3_finalize(selectstmt);

}

//Get return date
void db::get_date(string sql)
{
 struct sqlite3_stmt *selectstmt;
    int result = sqlite3_prepare_v2(instance, sql.c_str(), -1, &selectstmt, NULL);
    if(result == SQLITE_OK)
    {
    int rc = sqlite3_step(selectstmt);
    if (rc == SQLITE_ROW)
    {
      string msg = "\nInvalid ISBN!!\n";
      if (sqlite3_column_type(selectstmt, 0) == SQLITE_NULL)
        cout<<"Book was not issued";
      else
        cout<<"Return date was "<<sqlite3_column_text(selectstmt, 0);
    
    }
    else
       {
          cout<<"\nNo records found!!\n";
       }
    }
    else{
      cout<<"\nSomething is wrong!!\n";
    }
    sqlite3_finalize(selectstmt);

}


//Insert member
void db::insert_member(string sql)
{
    string msg = "\nConstraint violation! Duplicate/No records found!!\n";
    char* msg_err;
    int res = sqlite3_exec(instance,sql.c_str(),NULL,0,&msg_err);
    if (res==SQLITE_CONSTRAINT)
    {
        //printf("%s",msg_err);
      std::cout << msg << std::endl;
    }
    else if (res != SQLITE_OK) {
        std::cout << "\nSomething is wrong!!\n" << std::endl;
        printf("%s",msg_err);
    }
    else
    {
      cout<<"\nOperation successfully done!!\n";
      sql = "SELECT MAX(userid) from member_events";
      struct sqlite3_stmt *selectstmt;
      int result = sqlite3_prepare_v2(instance, sql.c_str(), -1, &selectstmt, NULL);
      if(result == SQLITE_OK)
      {
      int rc = sqlite3_step(selectstmt);
      if (rc == SQLITE_ROW)
      {

        cout<<"\nPlease note your user id is "<<sqlite3_column_text(selectstmt, 0)<<"\n";
      }
      else
        {
            cout<<"\nNo records found!!\n";
        }
      }
      else{
        cout<<"\nSomething is wrong!!\n";
      }
      sqlite3_finalize(selectstmt);

    }
}

//Update and delete event record
void db::update_delete(string sql,string sql1)
{
  struct sqlite3_stmt *selectstmt;
    int result = sqlite3_prepare_v2(instance, sql.c_str(), -1, &selectstmt, NULL);
    if(result == SQLITE_OK)
    {
    int rc = sqlite3_step(selectstmt);
    if (rc == SQLITE_ROW)
    {
      cout<<"\nBook is reserved or already issued to someone!!\n";
      string msg = "\nInvalid USERID!!\n";
      execute_query(sql,msg);
    }
    else if (rc == SQLITE_DONE)
    {
      string msg = "\nWrong operation!!\n";
      execute_query(sql1,msg);
      
    }
    else if (rc == SQLITE_CONSTRAINT)
    {
      cout<<"\nConstraint violation!\n";
    }
    else
       {
          cout<<"\nNo records found!!\n";
       }
    }
    else{
      cout<<"\nSomething is wrong!!\n";
    }
    sqlite3_finalize(selectstmt);

}


//delete records
void db::delete_records(string sql)
{
 string msg = "\nKey Constraints Error!!\n";
    execute_query(sql,msg); 
}

