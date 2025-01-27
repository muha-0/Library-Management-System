#include "Library.h"


string tosmall(string s){
    string res = "";
    int sz = s.size();
    for(int i = 0;i<sz;i++){
        res+=tolower(s[i]);
    }
    return res;
}

bool IsSubStr(const string &s, const string &t)
{
    // Checks if s is a substring of t or not
    int sz1 = s.size(), sz2 = t.size();
    if (sz1 > sz2)
    {
        return false;
    }
    for (int i = 0; i < sz2 - sz1 + 1; i++)
    {
        if (t[i] == s[0])
        {
            bool match = true;
            for (int j = 0; j < sz1; j++)
            {
                if (s[j] != t[j + i])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                return true;
            }
        }
    }
    return false;
}

Library::Library()
{
}
Library::Library(int Size)
{
    if(Size<0){Size = 0;}
    MaxNum = Size;
    Books = new Book[MaxNum];
}
bool Library::AddBook(Book b){
    if(index >= MaxNum){
        return false;
    }
    Books[index++] = b;
    return true;
}
bool Library::RemoveBook(int id){
    if(id<=0 || MaxNum == 0){
        return false;
    }
    for(int i = 0;i<MaxNum;i++){
        if(id == Books[i].GetId()){
            Books[i] = Books[MaxNum-1];
            Books[MaxNum-1].zeroId();
            index--;
            return true;
        }
    }
    return false;
}
void Library::DisplayAllBooks(){
    for(int i = 0;i<index;i++){
        Books[i].displayInfo();
    }
}
Book* Library::FindByAuthor(string name, int &cnt){
    int counter = 0;
    for(int i = 0;i<index;i++){
        if(IsSubStr(tosmall(name),tosmall(Books[i].getAuthor()))){
            counter++;
        }
    }
    if(!counter){
        return nullptr;
    }
    Book* arr = new Book[counter];
    int j = 0;
    for(int i = 0;i<index;i++){
        if(IsSubStr(tosmall(name),tosmall(Books[i].getAuthor()))){
            arr[j++] = Books[i];
        }
    }
    cnt = counter;
    return arr;
}
Book* Library::FindByCategory(string category, int &cnt){
    int counter = 0;
    for(int i = 0;i<index;i++){
        if(IsSubStr(tosmall(category),tosmall(Books[i].getCategory()))){
            counter++;
        }
    }
    if(!counter){
        return nullptr;
    }
    Book* arr = new Book[counter];
    int j = 0;
    for(int i = 0;i<index;i++){
        if(IsSubStr(tosmall(category),tosmall(Books[i].getCategory()))){
            arr[j++] = Books[i];
        }
    }
    cnt = counter;
    return arr;
}
Book Library::FindByTitle(string title){
    for(int i = 0;i<index;i++){
        if(tosmall(Books[i].getTitle()) == tosmall(title)){
            return Books[i];
        }
    }
    return Book();
}
void Library::DisplayBorrorwed(){
    for(int i = 0;i<index;i++){
        if(Books[i].isBorrowed()){
            Books[i].displayInfo();
        }
    }
}
void Library::SetBookBorrowed(int id){
    for(int i = 0;i<index;i++){
        if(Books[i].GetId() == id){
            Books[i].setBorrowed(1);
            return;
        }
    }
}
void Library::SetSize(int Size){
    MaxNum = Size;
    delete[] Books;
    Books = new Book[MaxNum];
}
void Library::SetBookUnborrowed(int id){
    for(int i = 0;i<index;i++){
        if(Books[i].GetId() == id){
            Books[i].setBorrowed(0);
        }
    }
}
void Library::DisplayNonBorrorwed(){
    for(int i = 0;i<index;i++){
        if(!Books[i].isBorrowed()){
            Books[i].displayInfo();
        }
    }
}
Library::~Library()
{
    delete[] Books;
    Books = nullptr;
}
