#ifndef LIBRARY_H
#define LIBRARY_H
#include<Book.h>
#include<iostream>

using namespace std;



class Library
{
    public:
        Library();
        Library(int Size);
        bool AddBook(Book b);
        bool RemoveBook(int id);
        void SetSize(int Size);
        void DisplayAllBooks();
        void SetBookBorrowed(int id);
        void SetBookUnborrowed(int id);
        Book* FindByAuthor(string name, int&);
        Book* FindByCategory(string category, int&);
        Book FindByTitle(string title);
        void DisplayBorrorwed();
        void DisplayNonBorrorwed();
        ~Library();
    private:
        int MaxNum = 0;
        Book* Books = nullptr;
        int index=0;
};

#endif // LIBRARY_H
