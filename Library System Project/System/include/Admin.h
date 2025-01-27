#ifndef ADMIN_H
#define ADMIN_H
#include<iostream>
#include<User.h>
using namespace std;

class Admin : public User
{
    public:
        Admin();
        Admin(string name, int id, string username, string password);
        string GetUsername();
        string GetPassword();
        virtual ~Admin();
    private:
        string username = "",password = "";
};

#endif // ADMIN_H
