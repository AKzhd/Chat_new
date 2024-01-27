#pragma once
using namespace std;
#include <string>
#include <exception>
#include <memory>
#include <vector>
#include "Message.h"
#include "User.h"
#include <mariadb/mysql.h>

struct UserLoginExp : public std::exception
{
    const char *what() const noexcept override { return "error: user login is busy"; }
};
struct UserNameExp : public std::exception
{
    const char *what() const noexcept override { return "error: user name is busy"; } };

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
    int not_db = 1049;
	std::string username_db = "user1" ;
	std::string password_db = "Pa$$wd";
	std::string database_chat = "chat";
	std::string table_users = "chat.users";
	std::string table_mess = "messages";

public:
    void start();
    bool isChatWork() const { return isChatWork_; }
    std::shared_ptr<User> getCurrentUser() const { return currentUser_; }
    void ShowLoginMenu();
    void ShowUserMenu();
    bool check_login_table(MYSQL& ms, MYSQL_RES* res, MYSQL_ROW& row, std::string table, std::string log);
	bool check_pass_table(MYSQL& ms, MYSQL_RES* res, MYSQL_ROW& row, std::string table, std::string log, std::string pass); 
    void registration(char, bool*, MYSQL& ms, MYSQL_RES* res, MYSQL_ROW& row);
    void show_table(MYSQL& ms, MYSQL_RES* res, MYSQL_ROW& row, std::string table); 
    void exchange(const std::string& mess);
    void test_msql_descriptor(MYSQL& ms);
	bool connect_to_db(MYSQL& ms);
    void create_database(MYSQL& ms);
	void create_table(MYSQL& ms); 
	void add_user(MYSQL& ms, std::string tbl, std::string login, std::string name, std::string password); 
	void insert_into_message(MYSQL& ms, std::string table, std::string send, std::string name, std::string rec, std::string mess);
    void chat_work();
};