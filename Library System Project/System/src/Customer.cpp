#include "Customer.h"
#include<Library.h>
#include <iostream>
Customer::Customer()
{
}

Customer::Customer(string name, int id) : User(name,id)
{
}

bool Customer::borrowBook(Book &b, bool borrowanyway)
{

    if (b.isBorrowed() == 0 || borrowanyway)
    {

        for (int i = 0; i < 5; i++)
        {
            if (book[i].GetId() == 0)
            {
                book[i] = b;
                index++;
                b.setBorrowed(1);
                return true;
            }
        }
    }

    return false;
}

bool Customer::returnBook(int book_id)
{
    for(int i = 0;i<index;i++){
        if(book[i].GetId() == book_id){
            book[i] = book[index-1];
            index--;
            return true;
        }
    }
    return false;
}

int Customer::getNumberOfBooks() { return index; }

Book *Customer::returnBooks()
{
    Book *b = book;
    return b;
}

void Customer::displayInfo()
{
    User::displayinfo();
    for (int i = 0; i < index; i++)
    {
        cout << "The " << i + 1 << " Book title is: " << book[i].getTitle() << "\n";
        cout << "Its ID is: " << book[i].GetId() << "\n";
        cout << "Its category: " << book[i].getCategory() << "\n";
        cout << "Its author: " << book[i].getAuthor() << "\n\n";
    }
}
