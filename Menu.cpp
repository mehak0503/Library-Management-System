#include "Menu.h"
#include "db.h"
#include <unistd.h>
//Helper function
bool isNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;

    return true;
}

//Constructor
Menu::Menu()
{
    db_obj = new db();
    db_obj->create_table();
}

//Destructor
Menu::~Menu()
{
    db_obj->~db();
}

//Student Menu
void Menu::student_user()
{
    int choice;
    do{
    system("clear");
    cout<<"\n*********** WELCOME TO USER SECTION ***********\n\n\n";
    cout<<">> Choose operation: \n\n\n";
    cout<<"    1. SEARCH BOOK\n\n";
    cout<<"    2. APPLY FOR MEMBERSHIP\n\n";
    cout<<"    3. BORROW BOOK\n\n";
    cout<<"    4. RETURN BOOK\n\n";
    cout<<"    5. MAIN MENU\n\n";
    cout<<">> Enter your choice: ";
    cin>>choice;
    cin.ignore();
    switch(choice)
    {
        case 1:
            search_book();
            break;
        case 2:
            apply_membership();
            break;
        case 3:
            //borrow_book();
            book_user(0);
            break;
        case 4:
            //return_book();
            book_user(1);
            break;
        case 5:
            return;
        default:
            cout<<"\a";
    }}while(choice!=5);
}

//Staff Menu
void Menu::library_staff()
{
    int choice;
    do{
    system("clear");
    cout<<"\n*********** WELCOME TO STAFF SECTION ***********\n\n\n";
    cout<<">> Choose operation: \n\n\n";
    cout<<"    1. ADD BOOK\n\n";
    cout<<"    2. SEARCH BOOK\n\n";
    cout<<"    3. MARK RESERVED\n\n";
    cout<<"    4. MODIFY BOOK INFO\n\n";
    cout<<"    5. LEND BOOK TO USER\n\n";
    cout<<"    6. TAKE RETURNED BOOK\n\n";
    cout<<"    7. ADD A MEMBER\n\n";
    cout<<"    8. VIEW ALL EVENTS\n\n";
    cout<<"    9. DELETE\n\n";
    cout<<"    10. BUY AND ADD BOOK\n\n";
    cout<<"    11. MAIN MENU\n\n";
    cout<<">> Enter your choice: ";
    cin>>choice;
    cin.ignore();
    switch(choice)
    {
        case 1:
            add_book();
            break;
        case 2:
            search_book();
            break;
        case 3:
            mark_reserved();
            break;
        case 4:
            modify_book();
            break;
        case 5:
            lend_book();
            break;
        case 6:
            get_book();
            break;
        case 7:
            add_member();
            break;
        case 8:
            view_events();
            break;
        case 9:
            delete_operation();
            break;
        case 10:
            buy_book();
            break;
        case 11:
            return;
        default:
            cout<<"\a";
    }}while(choice!=6);
}

//Supplier Menu
void Menu::supplier()
{
    int choice;
    do{
    system("clear");
    cout<<"\n*********** WELCOME TO SUPPLIER SECTION ***********\n\n\n";
    cout<<">> Choose operation: \n\n\n";
    cout<<"    1. SEARCH BOOK\n\n";
    cout<<"    2. APPLY FOR MEMBERSHIP\n\n";
    cout<<"    3. SELL BOOK\n\n";
    cout<<"    4. MAIN MENU\n\n";
    cout<<">> Enter your choice: ";
    cin>>choice;
    cin.ignore();
    switch(choice)
    {
        case 1:
            search_book();
            break;
        case 2:
            apply_membership();
            break;
        case 3:
            sell_book();
            break;
        case 4:
            return;
        default:
            cout<<"\a";
    }}while(choice!=5);
}

//Add book
void Menu::add_book()
{
    try{
    char c;
    do{
    system("clear");
    cout<<"***********ADD BOOK****************\n\n";
    string id,name,author,reserved;
    cout<<"\nEnter ISBN: ";
    getline(cin, id);
    cout<<"\nEnter book title: ";
    getline(cin, name);
    cout<<"\nEnter book author: ";
    getline(cin, author);
    //cout<<"\nEnter number of copies: ";
    //getline(cin, copies);
    cout<<"\nEnter reserved status(0/1): ";
    getline(cin, reserved);
    if (id.empty() || name.empty() || author.empty() \
        || reserved.empty()||(reserved.compare("0") && reserved.compare("1")))
    {
        cout<<"Invalid Input!!";
    }
    else
    {
        string sql = "INSERT INTO BOOKS VALUES ('"+id+"','"+name+"','"+author+"',"+reserved+",NULL,NULL);";
        //cout<<sql;
        db_obj->insert_record(sql);
    }
    cout<<"\nDo you want to continue: (y/n) ";
    cin>>c;
    cin.ignore();
    }while(c!='n');}
    catch(...)
    {
        cout << "An Exception occured\n";
    }
}

//Search book
void Menu::search_book()
{
    try{
    char c;
    do{
    system("clear");
    cout<<"***********SEARCH BOOK****************\n\n";
    string title,author;
    cout<<"\nEnter Title: ";
    getline(cin, title);
    cout<<"\nEnter Author: ";
    getline(cin,author);
    if(title.empty()||author.empty())
    {
        cout<<"Invalid Input!!";
    }
    else{
    string sql = "SELECT * FROM BOOKS WHERE title = '"+title+"' and author = '"+author+"';";
    //cout<<sql;
    int rc = db_obj->fetch_record(sql);}
    cout<<"\n\nDo you want to continue: (y/n) ";
    cin>>c;
    cin.ignore();
    }while(c!='n');}
    catch(...)
    {
        cout << "An Exception occured\n";
    }

}

//Delete Book
void Menu::mark_reserved()
{
 try{
    char c;
    do{
    system("clear");
    cout<<"***********MARK BOOK RESERVED****************\n\n";
    string id,reserved;
    cout<<"\nEnter ISBN: ";
    getline(cin, id);
    cout<<"\nEnter reserved status(0/1): ";
    getline(cin, reserved);
    if (reserved.empty()||(reserved.compare("0") && reserved.compare("1"))||id.empty())
    {
        cout<<"Invalid Input!!";
    }
    else
    {
    string sql = "UPDATE BOOKS set RESERVED ="+reserved+" where ISBN='"+id+"';";
    //cout<<sql;
    db_obj->update_record(sql);
    }
    cout<<"\nDo you want to continue: (y/n) ";
    cin>>c;
    cin.ignore();
    }while(c!='n');}
    catch(...)
    {
        cout << "An Exception occured\n";
    }
}

//Lend book
void Menu::lend_book()
{
 try{
    char c;
    do{
    time_t now = time(0);
    time_t ret = now+1209600;//Divided by 14*24*60*60
    char* dt = ctime(&now);
    char* ret_dt = ctime(&ret);
    system("clear");
    cout<<"*********** LEND BOOK ****************\n\n";
    cout<<"Please write the issued date "<<dt<<" and return within 14 days.\n";
    cout<<"After 14 days, fine of Rs 1 per day will be added to your account.\n\n";
    string sql = "SELECT * FROM BOOK_EVENTS WHERE RQST_TYPE = 0";
    int rc = db_obj->fetch_record(sql);
    if (rc){
    string id;
    cout<<"\nEnter RQST_ID to lend book: ";
    getline(cin, id);
    if (id.empty()||!isNumber(id))
    {
        cout<<"Invalid Input!!";
    }
    else
    {
        string sql1 = "SELECT * FROM BOOKS WHERE (ISSUED_TO IS NOT NULL OR RESERVED=1) AND ISBN = (SELECT isbn FROM BOOK_EVENTS WHERE rqst_id = "+id+");";
    string sql = "UPDATE BOOKS set ISSUED_TO = (SELECT userid FROM BOOK_EVENTS WHERE rqst_id = "+id+"), "\
        "RETURN_DATE = '"+ret_dt+"' where ISSUED_TO IS NULL AND ISBN=(SELECT isbn FROM BOOK_EVENTS WHERE rqst_id = "+id+"); "\
        "DELETE FROM BOOK_EVENTS WHERE rqst_id ="+id+";";
    //cout<<sql<<sql1;
    db_obj->update_delete(sql1,sql);}}
        //cout<<sql;
    cout<<"\nDo you want to continue: (y/n) ";
    cin>>c;
    cin.ignore();
    }while(c!='n');}
    catch(...)
    {
        cout << "An Exception occured\n";
    }
}

//Modify book
void Menu::modify_book()
{
    try{
    char c;
    do{
    system("clear");
    cout<<"***********MODIFY BOOK****************\n\n";
    string id,name,author,reserved;
    cout<<"\nEnter ISBN: ";
    getline(cin, id);
    cout<<"\nEnter modify book title: ";
    getline(cin, name);
    cout<<"\nEnter modify book author: ";
    getline(cin, author);
    //cout<<"\nEnter modify number of copies: ";
    //getline(cin, copies);
    if (id.empty()||name.empty()||author.empty())
    {
        cout<<"Invalid Input!!";
    }
    else
    {
        string sql = "UPDATE BOOKS set title ='"+name+"', author = '"+author+\
                        "' where ISBN='"+id+"';";
        //cout<<sql;
        db_obj->update_record(sql);
    }
    cout<<"\nDo you want to continue: (y/n) ";
    cin>>c;
    cin.ignore();
    }while(c!='n');}
    catch(...)
    {
        cout << "An Exception occured\n";
    }
}


//Get returned book
void Menu::get_book()
{
 try{
    char c;
    do{
    system("clear");
    cout<<"*********** GET RETURN BOOK ****************\n\n";
    string sql = "SELECT * FROM BOOK_EVENTS WHERE RQST_TYPE = 1";
    int rc = db_obj->fetch_record(sql);
    if (rc){
    string id;
    cout<<"\nEnter RQST_ID to get return book: ";
    getline(cin, id);
    
    if (id.empty()||!isNumber(id))
    {
        cout<<"Invalid Input!!";
    }
    else
    {
        string sql = "SELECT return_date from BOOKS where ISBN = (SELECT isbn FROM BOOK_EVENTS WHERE rqst_id = "+id+");";
        db_obj->get_date(sql);

        sql = "UPDATE BOOKS set ISSUED_TO =NULL, RETURN_DATE = NULL"\
                " where isbn = (SELECT isbn FROM BOOK_EVENTS WHERE rqst_id = "+id+"); "\
                "DELETE FROM BOOK_EVENTS WHERE rqst_id ="+id+";";
    db_obj->update_record(sql);}}
    cout<<"\nDo you want to continue: (y/n) ";
    cin>>c;
    cin.ignore();
    }while(c!='n');}
    catch(...)
    {
        cout << "An Exception occured\n";
    }
}

//Add Member
void Menu::add_member()
{
 try{
    char c;
    do{
    system("clear");
    cout<<"***********ADD MEMBER****************\n\n";
    string sql = "SELECT * FROM MEMBER_EVENTS WHERE PHONE NOT IN (SELECT PHONE FROM MEMBERS);";
    int rc = db_obj->fetch_record(sql);
    if (rc){
    string id;
    cout<<"\nEnter user id to add member: ";
    getline(cin, id);
   
    if (id.empty()||!isNumber(id))
    {
        cout<<"Invalid Input!!";
    }
    else
    {
        sql = "INSERT INTO MEMBERS SELECT * FROM MEMBER_EVENTS WHERE USERID = "+id+"; DELETE FROM MEMBER_EVENTS WHERE USERID = "+id+";";
        db_obj->insert_record(sql);
    }}
    cout<<"\nDo you want to continue: (y/n) ";
    cin>>c;
    cin.ignore();
    }while(c!='n');}
    catch(...)
    {
        cout << "An Exception occured\n";
    }
}

//Apply for membership
void Menu::apply_membership()
{
 try{
    char c;
    do{
    system("clear");
    cout<<"***********APPLY FOR MEMBERSHIP****************\n\n";
    string user_type,name,address,phone;
    cout<<"\nEnter UserType (1 for Normal User, 2 for Supplier, 3 for Others): ";
    getline(cin, user_type);
    cout<<"\nEnter user name: ";
    getline(cin, name);
    cout<<"\nEnter address: ";
    getline(cin, address);
    cout<<"\nEnter phone number (only 10 digits): ";
    getline(cin, phone);
    if (user_type.empty()||!isNumber(user_type) || name.empty() || address.empty() || phone.length()!=10 || !isNumber(phone))
    {
        cout<<"Invalid Input!!";
    }
    else
    {
        string sql = "INSERT INTO MEMBER_EVENTS (userid,usertype,name,address,phone) VALUES ((SELECT COALESCE(MAX(userid), 0) FROM MEMBER_EVENTS)+1,"+user_type+",'"+name+"','"+address+"','"+phone+"');";
        //cout<<sql;
        db_obj->insert_member(sql);
    }
    cout<<"\nDo you want to continue: (y/n) ";
    cin>>c;
    cin.ignore();
    }while(c!='n');}
    catch(...)
    {
        cout << "An Exception occured\n";
    }
}

//Borrow or return book
//Request type 0 = borrow and 1 = return
void Menu::book_user(int rqst_type)
{
 try{
    char c;
    do{
    system("clear");
    if(rqst_type)
        cout<<"*********** REQUEST TO RETURN BOOK ****************\n\n";
    else
        cout<<"*********** REQUEST TO BORROW BOOK ****************\n\n";
    cout<<"Please write the issued date and return within 14 days.\n";
    cout<<"After 14 days, fine of Rs 1 per day will be added to your account.\n\n";
    string id,borrower;
    cout<<"\nEnter Borrower Id: ";
    getline(cin, borrower);
    cout<<"\nEnter ISBN: ";
    getline(cin, id);
    if(id.empty()||borrower.empty()||!isNumber(borrower))
    {
        cout<<"Invalid Input!!";
    }
    else{
        string sql1 = "SELECT * FROM BOOK_EVENTS WHERE isbn = '"+id+"' AND rqst_type = "+to_string(rqst_type)+";";
        string sql = "INSERT INTO BOOK_EVENTS (rqst_id,userid,rqst_type,isbn) VALUES"\
        " ((SELECT COALESCE(MAX(rqst_id), 0) FROM BOOK_EVENTS)+1,"+borrower+","+to_string(rqst_type)+",'"+id+"');";
        //cout<<sql;
        db_obj->update_delete(sql1,sql);
    }
    cout<<"\nDo you want to continue: (y/n) ";
    cin>>c;
    cin.ignore();
    }while(c!='n');}
    catch(...)
    {
        cout << "An Exception occured\n";
    }
}


//Sell book
//Request type 2
void Menu::sell_book()
{
 try{
    char c;
    do{
    system("clear");
    cout<<"*********** REQUEST TO SELL BOOK ****************\n\n";
    string id,name,author,price;
    cout<<"\nEnter Id: ";
    getline(cin, id);
    cout<<"\nEnter book title: ";
    getline(cin, name);
    cout<<"\nEnter book author: ";
    getline(cin, author);
    cout<<"\nEnter price: ";
    getline(cin, price);
    if (!isNumber(id)||id.empty()||price.empty()||!isNumber(price) ||name.empty() || author.empty())
    {
        cout<<"Invalid Input!!";
    }
    else{
        string sql = "INSERT INTO BOOK_EVENTS (rqst_id,userid,rqst_type,title,author,price) VALUES"\
        "((SELECT COALESCE(MAX(rqst_id), 0) FROM BOOK_EVENTS)+1, "+id+",2,'"+name+"','"+author+"',"+price+");";
        //cout<<sql;
        db_obj->insert_record(sql);
    }
    cout<<"\nDo you want to continue: (y/n) ";
    cin>>c;
    cin.ignore();
    }while(c!='n');}
    catch(...)
    {
        cout << "An Exception occured\n";
    }
}

//Show requests
void Menu::view_events()
{
    try{
    char c;
    do{
    system("clear");
    cout<<"***********VIEW EVENTS****************\n\n";
    string choice;
    int rc;
    cout<<"\nPress \n1 for book related requests \n2 for membership requests\n3 for books\n4 for members: ";
    getline(cin, choice);
    if(choice.empty()||(choice.compare("1") && choice.compare("2") && choice.compare("3") && choice.compare("4")))
    {
        cout<<"Invalid Input!!";
    }
    else if(!choice.compare("1")){
    string sql = "SELECT * FROM BOOK_EVENTS;";
    //cout<<sql;
    rc = db_obj->fetch_record(sql);}
    else if(!choice.compare("2")){
    string sql = "SELECT * FROM MEMBER_EVENTS;";
    //cout<<sql;
    rc = db_obj->fetch_record(sql);}
    else if(!choice.compare("3")){
    string sql = "SELECT * FROM BOOKS;";
    //cout<<sql;
    rc = db_obj->fetch_record(sql);}
    else if(!choice.compare("4")){
    string sql = "SELECT * FROM MEMBERS;";
    //cout<<sql;
    rc = db_obj->fetch_record(sql);}
    cout<<"\n\nDo you want to continue: (y/n) ";
    cin>>c;
    cin.ignore();
    }while(c!='n');}
    catch(...)
    {
        cout << "An Exception occured\n";
    }
}

//Delete operation
void Menu::delete_operation()
{
    try{
    char c;
    do{
    system("clear");
    cout<<"***********DELETE OPERATIONS****************\n\n";
    string choice;
    cout<<"\nFor deletion, press \n1. books \n2. members ";
    getline(cin, choice);
    if(choice.empty()||(choice.compare("1") && choice.compare("2")))
    {
        cout<<"Invalid Input!!";
    }
    else if(!choice.compare("1")){
    string id;
    cout<<"\nEnter ISBN: ";
    getline(cin, id);
    string sql = "DELETE FROM BOOKS WHERE ISBN = '"+id+"';";
    //cout<<sql;
    db_obj->delete_records(sql);}
    else if(!choice.compare("2")){
    string id;
    cout<<"\nEnter USERID: ";
    getline(cin, id);
    string sql = "DELETE FROM MEMBERS WHERE USERID = "+id+";";
    //cout<<sql;
    db_obj->delete_records(sql);}
    cout<<"\n\nDo you want to continue: (y/n) ";
    cin>>c;
    cin.ignore();
    }while(c!='n');}
    catch(...)
    {
        cout << "An Exception occured\n";
    }
}


//Buy book
void Menu::buy_book()
{
 try{
    char c;
    do{
    system("clear");
    cout<<"***********BUY & ADD BOOK****************\n\n";
    string sql = "SELECT * FROM BOOK_EVENTS WHERE RQST_TYPE = 2";
    int rc = db_obj->fetch_record(sql);
    if (rc){
    string id,isbn;
    cout<<"\nEnter RQST_ID to enter book: ";
    getline(cin, id);
    cout<<"\nEnter ISBN for the book: ";
    getline(cin, isbn);
   
    if (id.empty()||!isNumber(id)||isbn.empty())
    {
        cout<<"Invalid Input!!";
    }
    else
    {
        sql = "INSERT INTO BOOKS (isbn,title,author,reserved) " \
        "SELECT '"+isbn+"', title, author,0 FROM BOOK_EVENTS WHERE RQST_ID = "+id+"; "\
        "DELETE FROM BOOK_EVENTS WHERE RQST_ID = "+id+";"; 
        //cout<<sql;
        db_obj->insert_record(sql);
    }}
    cout<<"\nDo you want to continue: (y/n) ";
    cin>>c;
    cin.ignore();
    }while(c!='n');}
    catch(...)
    {
        cout << "An Exception occured\n";
    }
}

