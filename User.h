#pragma once
using namespace std;
#include <string>
class User
{
    std::string login_;
    std::string name_;
    std::string password_;
    

public:
    User(const std::string &login,  const std::string &name,const std::string &password) : login_(login), name_(name) ,password_(password) {}
    const std::string &getUserLogin() const { return login_; }
    void setUserLogin(const std::string &login) { login_= login; }
    const std::string &getUserName() const { return name_; }
    void setUserName(const std::string &name) { name_ = name; }
    const std::string &getUserPassword() const { return password_; }
    void setUserPassword(const std::string &password) { password_ = password; }
 
};