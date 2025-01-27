#include <iostream>
#include<User.h>
#include<Book.h>
#include<Customer.h>
#include<Admin.h>
#include<Library.h>
#include<string>
#include<fstream>
using namespace std;

struct Sizes{
    int admins_size;
    int customers_size;
    int books_size;
    Sizes(int admins_size,int customers_size, int books_size):admins_size(admins_size),customers_size(customers_size),books_size(books_size)
    {}
};
template<typename T>
int autoid(T* &arr, int sz){
    if(sz == 0){
        return ((rand()%9 + 1) + (rand()%9 + 1)*10 + (rand()%9 + 1)*100);
    }
    int maxid = -1;
    for(int i = 0;i<sz;i++){
        if(arr[i].GetId()>maxid){
            maxid = arr[i].GetId();
        }
    }
    return maxid+1;

}

int stringtoint(string num){
    int res = 0;
    int unit = 1;
    for(int i = num.size()-1;i>=0;i--){
        res+=unit*(num[i]-'0');
        unit*=10;
    }
    return res;
}
string inttostring(int num){
    string res = "";
    while(num){
        int digit = num%10;
        num/=10;
        res = (char)(digit+'0') + res;
    }
    return res;
}
string lowerit(string s){
    string res = "";
    int sz = s.size();
    for(int i = 0;i<sz;i++){
        res+=tolower(s[i]);
    }
    return res;
}
string* split(string text, char seperator){
    int counter {0};
    int sz = text.size();
    for(int i = 0;i<sz;i++){
        if(text[i] == seperator){
            counter++;
        }
    }
    string* arr = new string[counter+1];
    int index = 0;
    string tmp = "";
    for(int i = 0;i<sz;i++){
        if(text[i] == ','){
            arr[index++] = tmp;
            tmp = "";
        }
        else{
            tmp += text[i];
        }
    }
    arr[index] = tmp;
    return arr;
}



int* read(Admin* &admins, Customer* &customers, Book* &books, int &LMaxSize){ //for files
    ifstream admn("admins.txt");
    int*  sizes = new int[3];
    string text;
    getline(admn,text);
    sizes[0] = stringtoint(text);
    admins = new Admin[stringtoint(text)];
    int i =0;
    while(getline(admn,text)){
        string* arr = split(text,',');
        string name = arr[0];
        string id = arr[1];
        string username = arr[2];
        string pass = arr[3];
        admins[i++] = Admin(name,stringtoint(id),username,pass);
    }
    admn.close();
    ifstream bks("books.txt");
    getline(bks,text);
    LMaxSize= stringtoint(text);
    getline(bks,text);
    sizes[1] = stringtoint(text);
    books = new Book[stringtoint(text)];
    i = 0;
    while(getline(bks,text)){
        string* arr = split(text,',');
        int id = stringtoint(arr[0]);
        string title = arr[1];
        string author = arr[2];
        string category = arr[3];
        bool borrowed = stringtoint(arr[4]);
        books[i++] = Book(id,title,author,category,borrowed);
    }
    bks.close();
    ifstream cstmr("customers.txt");
    getline(cstmr,text);
    sizes[2] = stringtoint(text);
    customers = new Customer[stringtoint(text)];
    i = 0;
    while(getline(cstmr,text)){
        string* arr = split(text,',');
        string name = arr[0];
        string id = arr[1];
        int num = stringtoint(arr[2]);
        customers[i] = Customer(name,stringtoint(id));
        for(int j = 0;j<num;j++){
            int book_id = stringtoint(arr[j+3]);
            for(int k= 0;k<sizes[1];k++){
                if(book_id == books[k].GetId()){
                    customers[i].borrowBook(books[k],1);
                }
            }
        }
        i++;
    }
    cstmr.close();
    return sizes;
}
void write(Admin* admins, Customer* customers, Book* books, Sizes sizes, int LMaxSize){ //for files
    ofstream admn("admins.txt");
    admn<<sizes.admins_size<<endl;
    for(int i = 0;i<sizes.admins_size;i++){
        admn<<admins[i].GetName()<<","<<admins[i].GetId()<<","<<admins[i].GetUsername()<<","<<admins[i].GetPassword()<<endl;
    }
    admn.close();
    ofstream bks("books.txt");
    bks<<(LMaxSize)<<endl;
    bks<<sizes.books_size<<endl;
    for(int i = 0;i<sizes.books_size;i++){
        bks<<books[i].GetId()<<","<<books[i].getTitle()<<","<<books[i].getAuthor()<<","<<books[i].getCategory()<<",";
        if(books[i].isBorrowed()){
            bks<<"1"<<endl;
        }
        else{
            bks<<"0"<<endl;
        }
    }
    bks.close();
    ofstream cstmr("customers.txt");
    cstmr<<sizes.customers_size<<endl;
    for(int i = 0;i<sizes.customers_size;i++){
        cstmr<<customers[i].GetName()<<","<<customers[i].GetId()<<","<<customers[i].getNumberOfBooks()<<",";
        Book* customers_books = customers[i].returnBooks();
        for(int j = 0;j<customers[i].getNumberOfBooks();j++){
            cstmr<<inttostring(customers_books[j].GetId());
            if(j!=customers[i].getNumberOfBooks()-1){cstmr<<",";}
        }
        cstmr<<endl;
    }
}
void welcome(){
    cout<<"-------------------------------------\n";
    cout<<"-------------------------------------\n";
    cout<<"----Welcome To Our Library System----\n";
    cout<<"-------------------------------------\n";
    cout<<"-------------------------------------\n";
}
bool load(){

    string ans;
    cout<<"Do you want to load from the existing files?(y/n): ";
    cin>>ans;
    while(lowerit(ans) != "y" && lowerit(ans) != "n"){
        cout<<"Enter a valid answer: ";
        cin>>ans;
    }
    if(lowerit(ans) == "y"){
        return true;
    }
    return false;
}
template<typename T>
void Add(T* &arr, int Size, T obj){
    if(!arr){
        arr = new T[1];
        arr[0] = obj;
        return;
    }
    T* newarr = new T[Size+1];
    for(int i = 0;i<Size;i++){
        newarr[i] = arr[i];
    }
    newarr[Size] = obj;
    delete[] arr;
    arr = newarr;
}

template<typename T>
bool Remove(T* &arr, int Size, int id){
    int index = -1;
    for(int i = 0;i<Size;i++){
        if(id == arr[i].GetId()){
            index = i;
            break;
        }
    }
    if(index == -1){return false;}
    if(Size == 1){arr = nullptr;}
    else{
        arr[index] = arr[Size-1];
    }
    return true;

}

void menu(){
    cout<<"-------------------------------------\n";
    cout<<"1.Create new user\n";
    cout<<"2.Display All Users\n";
    cout<<"3.Remove a customer\n";
    cout<<"4.Add a book\n";
    cout<<"5.Remove a book\n";
    cout<<"6.Allow customer to borrow a book\n";
    cout<<"7.Allow customer to return a book\n";
    cout<<"8.Display all books\n";
    cout<<"9.Search a book by title\n";
    cout<<"10.Search a book by category\n";
    cout<<"11.Search a book by author\n";
    cout<<"12.Exit\n";
    cout<<"-------------------------------------\n";
}

int main()
{
    welcome();
    Admin* admins = nullptr;
    Customer* customers = nullptr;
    Book* books = nullptr;
    Library library(0);
    int LMaxSize;
    Sizes sizes(0,0,0);
    if(load()){
        int* tmp = read(admins,customers,books,LMaxSize);
        sizes.admins_size = tmp[0];
        sizes.customers_size = tmp[2];
        sizes.books_size = tmp[1];
        library.SetSize(LMaxSize);
        for(int i = 0;i<sizes.books_size;i++){
            library.AddBook(books[i]);
        }
        string username, password;
        while(true){
        cout<<"Enter your username: ";
        cin>>username;
        cout<<"Enter password: ";
        cin>>password;
        bool found = false;
        for(int i = 0;i<sizes.admins_size;i++){
            if(admins[i].GetUsername() == username && admins[i].GetPassword() == password){
                cout<<"-------------------------------------\n";
                cout<<"Welcome "<<username<<"\n";
                cout<<"-------------------------------------\n";
                found = true;
                break;
            }
            }
        if(found){break;}
        else{
            cout<<"No matching username or password, please try again\n";
        }
        }
    }
    else{
        cout<<"Your files will be overwritten...\n";
        cout<<"-------------------------------------\n";
        cout<<"Creating new admin\n";
        cout<<"-------------------------------------\n";
        string name,username,password;
        cout<<"Enter name: ";
        cin>>name;
        cout<<"Enter username: ";
        cin>>username;
        cout<<"Enter password: ";
        cin>>password;
        Add(admins, sizes.admins_size++, Admin(name,autoid(admins,sizes.admins_size),username,password));
        cout<<"Welcome "<<name<<endl;
        cout<<"Enter the size of the library: ";
        cin>>LMaxSize;
        library.SetSize(LMaxSize);
    }
    while(true){
        menu();
        int choice;
        cout<<"Enter your choice: ";
        cin>>choice;
        while(choice > 12 || choice < 1){
            cout<<"Enter a valid choice: ";
            cin>>choice;
        }
        if(choice == 1){
            string ans;
            cout<<"Add an admin or a customer(a,c): ";
            cin>>ans;
            while(lowerit(ans)!="c" && lowerit(ans) != "a"){
                cout<<"Enter a valid choice: ";
                cin>>ans;
            }
            if(ans == "a"){
                string name,username,password;
                cout<<"Enter name: ";
                cin>>name;
                cout<<"Enter username: ";
                cin>>username;
                cout<<"Enter password: ";
                cin>>password;
                Add(admins, sizes.admins_size++, Admin(name,autoid(admins,sizes.admins_size),username,password));
                cout<<"Admin added successfully\n";
            }
            else{
                string name;
                cout<<"Enter name: ";
                cin>>name;
                Add(customers,sizes.customers_size++, Customer(name,autoid(customers,sizes.customers_size)));
                cout<<"Customer added successfully\n";
            }
        }
        else if(choice == 2){
            for(int i = 0;i<sizes.admins_size;i++){
                cout<<"Admin's name:"<<admins[i].GetName()<<", id:"<<admins[i].GetId()<<endl;
            }
            for(int i = 0;i<sizes.customers_size;i++){
                cout<<"Customer's name:"<<customers[i].GetName()<<", id:"<<customers[i].GetId()<<endl;
            }
        }
        else if(choice == 3){
            cout<<"Displaying all customers...\n";
            for(int i = 0;i<sizes.customers_size;i++){
                cout<<"Customer's name:"<<customers[i].GetName()<<", id:"<<customers[i].GetId()<<endl;
            }
            int id;
            cout<<"Enter customer's id to be removed: ";
            cin>>id;
            if(Remove(customers,sizes.customers_size,id)){
                cout<<"Customer removed succesfully\n";
                sizes.customers_size--;
            }
            else{
                cout<<"Failed...Invalid id\n";
            }
        }
        else if(choice == 4){
            int id = autoid(books, sizes.books_size);
            string title,author,category;
            cout<<"Enter title: ";
            cin>>title;
            cout<<"Enter author's name: ";
            cin>>author;
            cout<<"Enter category: ";
            cin>>category;
            if(library.AddBook(Book(id,title,author,category,0))){
                cout<<"Book added succesfully\n";
                Add(books,sizes.books_size++,Book(id,title,author,category,0));
            }
            else{
                cout<<"Sorry, can't add more books to the library\n";
            }
        }
        else if(choice == 5){
            for(int i = 0;i<sizes.books_size;i++){
                cout<<"Book title: "<<books[i].getTitle()<<", book id: "<<books[i].GetId()<<endl;
            }
            int id;
            cout<<"Enter id of the book to be removed: ";
            cin>>id;
            bool found = false;
            for(int i = 0;i<sizes.books_size;i++){
                if(id == books[i].GetId()){
                    Remove(books,sizes.books_size--,id);
                    library.RemoveBook(id);
                    cout<<"Book removed succesfully\n";
                    found = true;
                    break;
                }
            }
            if(!found){
                cout<<"Failed...No matching id\n";
            }
        }
        else if(choice == 6){
            cout<<"The non borrowed books: \n";
            library.DisplayNonBorrorwed();
            int bid;
            cout<<"Enter id of the book to be borrowed: ";
            cin>>bid;
            int bindex = -1;
            for(int i = 0;i<sizes.books_size;i++){
                if(bid == books[i].GetId()){
                    bindex = i;
                }
            }
            cout<<"Customers ids: \n";
            for(int i = 0;i<sizes.customers_size;i++){
                cout<<"Customer's name:"<<customers[i].GetName()<<", id:"<<customers[i].GetId()<<endl;
            }
            int cid,cindex = -1;
            cout<<"Enter customer's id: ";
            cin>>cid;
            for(int i = 0;i<sizes.customers_size;i++){
                if(cid == customers[i].GetId()){
                    cindex = i;
                }
            }
            if(bindex == -1){
                cout<<"Invalid Book id\n";
            }
            else if(cindex == -1){
                cout<<"Invalid Customer id\n";
            }
            else{
                if(customers[cindex].borrowBook(books[bindex])){
                    cout<<"Book borrowed succesfully\n";
                    library.SetBookBorrowed(bid);
                }
                else{
                    cout<<"Failed...Customer has 5 borrowed books or book is already borrowed\n";
                }
            }
        }
        else if(choice == 7){
            cout<<"Customers ids: \n";
            for(int i = 0;i<sizes.customers_size;i++){
                cout<<"Customer's name:"<<customers[i].GetName()<<", id:"<<customers[i].GetId()<<endl;
            }
            int cid,cindex = -1;
            cout<<"Enter customer's id: ";
            cin>>cid;
            for(int i = 0;i<sizes.customers_size;i++){
                if(cid == customers[i].GetId()){
                    cindex = i;
                }
            }
            if(cindex == -1){
                cout<<"Invalid id\n";
            }
            else{
                if(customers[cindex].getNumberOfBooks()==0){
                    cout<<"Customer has no borrowed books to return\n";
                }
                else{
                    cout<<"Customer's info:\n";
                    customers[cindex].displayInfo();
                    int id;
                    cout<<"Enter book id to return: ";
                    cin>>id;
                    if(customers[cindex].returnBook(id)){
                        cout<<"Book returned to library\n";
                        library.SetBookUnborrowed(id);
                    }
                    else{
                        cout<<"Invalid Id\n";
                    }
                }
            }
        }
        else if(choice == 8){
            cout<<"----------------------------------------------------\n";
            cout<<"BOOKS AVAILABLE IN THE LIBRARY SYSTEM\n";
            cout<<"----------------------------------------------------\n";
            library.DisplayAllBooks();
        }
        else if(choice == 9){
            string title;
            cout<<"Enter book title to search for: ";
            cin>>title;
            Book b = library.FindByTitle(title);
            if(b.GetId() == 0){
                cout<<"No book found with this title\n";
            }
            else{
                b.displayInfo();
            }
        }
        else if(choice == 10){
            string category;
            cout<<"Enter category: ";
            cin>>category;
            int counter;
            Book* matching = library.FindByCategory(category,counter);
            if(matching == nullptr){
                cout<<"No matching books found\n";
            }
            else{
                for(int i = 0;i<counter;i++){
                    matching[i].displayInfo();
                }
            }
        }
        else if(choice == 11){
            string author;
            cout<<"Enter author's name: ";
            cin>>author;
            int counter;
            Book* matching = library.FindByAuthor(author,counter);
            if(matching == nullptr){
                cout<<"No matching books found\n";
            }
            else{
                for(int i = 0;i<counter;i++){
                    matching[i].displayInfo();
                }
            }
        }
        else{
            cout<<"Thanks for using our system (;\n";
            write(admins,customers,books,sizes,LMaxSize);
            delete[] books;
            delete[] customers;
            delete[] admins;
            return 0;
        }
    }

}
