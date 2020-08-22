#include <iostream>
#include <stdlib.h>
#include "Menu.h"
using namespace std;


int main()
{
    system("clear");
    int choice;
    string password;
    cout<<"\n\n***************LIBRARY MANAGEMENT SYSTEM**************\n\n\n\n";
    cout<<"\n\nPassword: ";

    cin>>password;
    if(password=="admin")
    {
        Menu menu;

        do{
            system("clear");
    cout<<">> Choose user type:\n\n";
    cout<<"   1. Library Staff\n\n";
    cout<<"   2. User\n\n";
    cout<<"   3. Supplier\n\n";
    cout<<"   4. Exit\n\n";
    cout<<">> Enter your choice: ";
    cin>>choice;
    switch(choice)
    {
        case 1:
            menu.library_staff();
            break;
        case 2:
            menu.student_user();
            break;
        case 3:
            menu.supplier();
            break;
        case 4:
            exit(0);
        default:
            cout<<"\a";
    }}while(choice!=4);}
    else
    {
        cout<<"\n\nINCORRECT PASSWORD\n\n";
        exit(0);
    }
    return 0;
}
