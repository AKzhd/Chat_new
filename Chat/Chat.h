#pragma once
using namespace std;
#include <string>
#include <exception>
#include <memory>
#include <vector>
#include "Message.h"
struct UserLoginExp : public std::exception
{
    const char *what() const noexcept override { return "error: user login is bysy"; }
};
struct UserNameExp : public std::exception
{
    const char *what() const noexcept override { return "error: user name is bysy"; }
};

class Chat
{

private:
    bool isChatWork_ = false;
    std::vector<User> userList_;
    std::vector<Message> messageList_;
    std::shared_ptr<User> currentUser_ = nullptr;
    void login();
    void signUp();
    void showChat() const;
    void ShowAllUsersName() const;
    void addMessage();
    std::vector<User> &getAllUsers() { return userList_; }
    std::vector<Message> &getAllMessages() { return messageList_; }
    std::shared_ptr<User> getUserByLogin(const std::string &login) const;
    std::shared_ptr<User> getUserByName(const std::string &name) const;

public:
    void start();
    bool isChatWork() const { return isChatWork_; }
    std::shared_ptr<User> getCurrentUser() const { return currentUser_; }
    void ShowLoginMenu();
    void ShowUserMenu();
};