#ifndef MENU_H
#define MENU_H
#include<iostream>
#include <stdlib.h>
#include<string>
#include <ctime>
#include "db.h"
using namespace std;
class Menu{
    db *db_obj;
    void add_book();
    void search_book();
    void mark_reserved();
    void modify_book();
    void lend_book();
    void add_member();
    void apply_membership();
    //void borrow_book();
    //void return_book();
    void book_user(int rqst_type);
    void sell_book();
    void get_book();
    void view_events();
    void delete_operation();
    void buy_book();
    public:
        Menu();
        ~Menu();
        void student_user();
        void library_staff();
        void supplier();

};


#endif // MENU_H
