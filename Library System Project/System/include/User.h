#ifndef USER_H
#define USER_H
#include<iostream>

using namespace std;

class User
{
private:
        string name;
        int id;
public:
        User();
        User(string ,int );
        void displayinfo();
        int GetId();
        string GetName();
        ~User();


};

#endif // USER_H
