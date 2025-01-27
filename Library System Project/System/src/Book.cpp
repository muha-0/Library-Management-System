#include "Book.h"

Book::Book()
{
    ID = 0;
    title = "";
    author = "";
    category = "";
    borrowed = 0;
}

Book::Book(int i, string t, string a, string c, bool b)
{
    ID = i;
    title = t;
    author = a;
    category = c;
    borrowed = b;
}

void Book::setTitle(string t) { title = t; }

void Book::setAuthor(string a) { author = a; }

void Book::setCategory(string c) { category = c; }

void Book::setBorrowed(bool b) { borrowed = b; }

void Book::zeroId() { ID = 0; }

void Book::displayInfo()
{
    cout << "The book title is: " << title <<"\nAuthor: " << author << "\nCategory: " << category << "\n";
    cout<<"Book id: "<<ID<<endl;

    if (borrowed)
        cout << "The book is currently borrowed\n\n";

    else
        cout << "The book is currently not borrowed\n\n";
    cout<<"----------------------------------------------------\n";
}

// getters functions:
string Book::getTitle() { return title; }
int Book::GetId() { return ID; }
string Book::getAuthor() { return author; }
string Book::getCategory() { return category; }
bool Book::isBorrowed() { return borrowed; }
