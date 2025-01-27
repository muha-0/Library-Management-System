#ifndef DESKTOP_BOOK_H
#define DESKTOP_BOOK_H
#include <string>
#include <iostream>
using namespace std;

class Book
{
private:
    int ID;
    string title, author, category;
    bool borrowed;

public:
    Book();
    Book(int id, string title, string author, string category, bool borrowed);
    void setTitle(string);
    void setAuthor(string);
    void setCategory(string);
    void setBorrowed(bool);
    void zeroId();
    void displayInfo();
    string getTitle();
    int GetId();
    string getAuthor();
    string getCategory();
    bool isBorrowed();
};

#endif
