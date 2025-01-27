#ifndef DESKTOP_CUSTOMER_H
#define DESKTOP_CUSTOMER_H
#include "Book.h"
#include "User.h"
#include <string>
using namespace std;

class Customer: public User
{
private:
    Book book[5];
    int index = 0;

public:
    Customer();

    Customer(string, int);
    bool borrowBook(Book &,bool= 0);
    bool returnBook(int);
    int getNumberOfBooks();
    Book *returnBooks();
    void displayInfo();
};

#endif
