#include "User.h"

User::User(string name, int id):name(name),id(id)
{
}
User::User()
{
    name = "";
    id = 0;
}
void User::displayinfo(){
    cout<<"Student's id: "<<id<<", student's name: "<<name<<endl;
}
int User::GetId(){
    return id;
};
string User::GetName(){
    return name;
}
User::~User()
{
}
