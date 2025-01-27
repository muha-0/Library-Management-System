#include "Admin.h"
Admin::Admin()
{
}
Admin::Admin(string name, int id, string username, string password):User(name,id),username(username),password(password){

}
string Admin::GetPassword(){
    return password;
}
string Admin::GetUsername(){
    return username;
}
Admin::~Admin()
{
}
