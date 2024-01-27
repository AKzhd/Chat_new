#include <iostream>
#include "Chat.h"
#include "Message.h"
#include "User.h"

using namespace std;

    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
 

void Chat::start()
{
    isChatWork_ = true;
    chat_work();
}

void Chat::test_msql_descriptor(MYSQL &mysql)
{

    if (&mysql == NULL)
    {
        std::cout << " Error: can't create MySQL-descriptor" << std::endl;
        exit(1);
    };
    std::cout << " MySQL-descriptor created" << std::endl;
}

void Chat::create_database(MYSQL &mysql)
{
    if (!mysql_real_connect(&mysql, "localhost", username_db.c_str(), password_db.c_str(), NULL, 0, NULL, 0))
        std::cout << " Error: don't connect to server MySQL" << mysql_error(&mysql) << std::endl;
    else
        std::cout << " Connected to server MySQL" << std::endl;

    if (!mysql_query(&mysql, "CREATE DATABASE chat"))
        std::cout << " Created database chat" << std::endl;
    else
        std::cout << " Error: don't create database chat" << std::endl;

    if (!mysql_query(&mysql, "USE chat"))
        std::cout << " use chat applied" << std::endl;
    else
        std::cout << " Error: don't use database chat" << std::endl;
}

void Chat::create_table(MYSQL &ms)
{
    if (!mysql_query(&ms, "CREATE TABLE users(id INT AUTO_INCREMENT PRIMARY KEY, login VARCHAR(255) NOT NULL UNIQUE, name VARCHAR(255), password VARCHAR(255))"))
        std::cout << " Table " << table_users << " created" << std::endl;
    else
        std::cout << " Error: don't created table " << table_users << mysql_error(&ms) << std::endl;

    add_user(ms, table_users, "test2", "all", "changemy");
    add_user(ms, table_users, "test", "test", "eudcyugdy3e4767");

    if (!mysql_query(&ms, "CREATE TABLE messages(id INT AUTO_INCREMENT PRIMARY KEY, sender VARCHAR(255), name VARCHAR(255), recipient VARCHAR(255), mess TEXT)"))
        std::cout << " Table " << table_mess << " created" << std::endl;
    else
        std::cout << " Error: don't created table " << table_mess << mysql_error(&ms) << std::endl;

    insert_into_message(ms, table_mess, "ALL USERS", "Общий чат", "ALL USERS", "Вы в общем чате");
}

bool Chat::connect_to_db(MYSQL &ms)
{
    while (true)
    {
        if (!mysql_real_connect(&ms, "localhost", username_db.c_str(), password_db.c_str(), database_chat.c_str(), 0, NULL, 0))
        {
            std::cout << "Error: can't connect to database " << mysql_error(&ms) << std::endl;
            if (mysql_errno(&ms) == not_db)
            {
                std::cout << " No database " << database_chat << std::endl;
                std::cout << " need for create database" << std::endl;
                return false;
                break;
            }
            else
                std::cout << " Invalid username or password" << std::endl;
            continue;
        }
        else
        {
            std::cout << "\n Success!" << std::endl;
            return true;
            break;
        }
    }
}
void Chat::add_user(MYSQL&mysql, std::string tbl ,std::string login, std::string name, std::string password){
	std::string ins = "INSERT INTO " + tbl + "(id,login, name, password) VALUES (default,'"+login+"', '"+name+"', '"+password+"')";
    cout<< ins.c_str();
    	if (!mysql_query(&mysql,&ins[0]))
		std::cout << login << " is added "<< std::endl;
		else std::cout << "User is not added" << std::endl << mysql_error(&mysql) << std::endl;
}

void Chat::insert_into_message(MYSQL &mysql, std::string table, std::string send, std::string name, std::string rec, std::string mess)
{
    std::string str = "INSERT INTO " + table + "(id, sender, name, recipient, mess) VALUES (default, \'" + send + "\', \'" + name + "\', \'" + rec + "\' ,\'" + mess + "\')";
    if (!mysql_query(&mysql, str.c_str()))
        std::cout << " Сообщение от " << send << " добавлено в таблицу" << std::endl;
    else
        std::cout << " Error: сообщение от " << send << " не добавлено в таблицу" << std::endl
                  << mysql_error(&mysql) << std::endl;
}

bool Chat::check_login_table(MYSQL &mysql, MYSQL_RES *res, MYSQL_ROW &row, std::string table, std::string log)
{
    std::string str = "SELECT * FROM " + table + " WHERE login = \'" + log + "\'";
    if (mysql_query(&mysql, str.c_str()))
        std::cout << " Erorr: сбой проверки логина " << std::endl
                  << mysql_error(&mysql) << std::endl;
    else
    {
        res = mysql_use_result(&mysql);
        if (res)
        {
            if (row = mysql_fetch_row(res))
            {
                int count = std::stoi(row[0]);
                mysql_free_result(res);
                if (count > 0)
                    return false;
                else
                    return true;
            }
        }
        mysql_free_result(res);
    }
    return -1;
}
// void Chat::registration(char menu, bool* check_user, MYSQL& ms, MYSQL_RES* res, MYSQL_ROW& row) {
// 	User user;

// 	// *check_user = false;
// 	// // Вход в чат
// 	// if (menu == '1') {
// 	// 	exchange(" Введите логин(латинский алфавит, цифры, символы): ");
// 	// 	user.get_user_login(message());
// 	// 	exchange(" Введите пароль(латинский алфавит, цифры, символы): ");
// 	// 	user.get_user_password(message());
// 	// 	int counter = 0;
// 	// 	if (!check_pass_table(ms, res, row, table_users, user.user_login(), user.user_password())) {
// 	// 		user.get_user_name(name_user(ms, res, row, table_users, user.user_login()));
// 	// 		get_user(user.user_login(), user.user_name());
// 	// 		transmitting(user.user_name());
// 	// 		*check_user = true;
// 	// 	}
// 	// 	else {
// 	// 		transmitting("false");
// 	// 		return;
// 	// 	}
// 	// }

// 	// регистрация нового пользователя

// 		*check_user = true;
// 		user.getUserName();
// 		exchange(user.user_name());
// 		exchange(" Введите логин (латинский алфавит, цифры, символы): ");
// 		bool check_login;
// 		do {
// 			user.get_user_login(message());
// 			check_login = check_login_table(ms, res, row, table_users, user.user_login());
// 			if (check_login == false) {
// 				user.clear_login();
// 				exchange("false");
// 			}
// 		} while (!check_login);
// 		exchange(" логин принят");
// 		exchange( " Введите пароль (латинский алфавит, цифры, символы): ");
// 		user.get_user_password(message());
// 		std::cout << message() << std::endl;
// 		insert_into_users(ms, table_users, user.user_login(), user.user_name(), user.user_password());
// 		if(check_login_table(ms, res, row, table_users, user.user_login())){
// 			*check_user = false;
// 			return;
// 		}
// 		show_table(ms, res, row, table_users);
// 		exchange("reg ok");
// 	}
// }

void Chat::chat_work()
{
    mysql_init(&mysql);
    test_msql_descriptor(mysql);
   if (!connect_to_db(mysql))
    {
        create_database(mysql);
        create_table(mysql);
    }
  
}

string cyan_begin = "\x1B[36m", cyan_end = "\033[0m\t\t";
string yellow_begin = "\x1B[33m", yellow_end = "\033[0m\t\t";
string red_begin = "\x1B[31m", red_end = "\033[0m\t\t";
string green_begin = "\x1B[32m", green_end = "\033[0m\t\t";
string line = "\x1B[36m============================================================\033[0m\t\t";

std::shared_ptr<User> Chat::getUserByLogin(const std::string &login) const
{
    for (auto &user : userList_)
    {
        if (login == user.User::getUserLogin())
            return std::make_shared<User>(user);
    }
    return nullptr;
}

std::shared_ptr<User> Chat::getUserByName(const std::string &name) const
{
    for (auto &user : userList_)
    {
        if (name == user.User::getUserName())
            return std::make_shared<User>(user);
    }
    return nullptr;
}

void Chat::login()
{
    std::string login, name, password;
    User user = User(login, name, password);
   
    char operation;
    do
    {
        std::cout << line << std::endl;
        std::cout << "login: ";
        std::cin >> login;
        std::cout << "password: ";
        std::cin >> password;
        std::cout << line << std::endl;

        currentUser_ = user.getUserLogin();
        char operation;
        if (currentUser_ == nullptr || (password != currentUser_->getUserPassword())) // Проверка на наличие пользователя и правильности пароля
        {
            currentUser_ = nullptr;
            std::cout << red_begin << "Неверный логин!!!, для повторения нажмите любую клавищу. Для выхода нажмите 0(ноль) " << red_end << std::endl;

            std::cin >> operation;
            if (operation == '0')
                break;
        }
    } while (!currentUser_);
}

void Chat::signUp()

{
    std::string login, name, password;
    User user = User(login, name, password);
    std::cout << green_begin << "login: " << green_end;
    std::cin >> login;
    user.setUserLogin(login);
    std::cout << green_begin << "Name: " << green_end;
    std::cin >> name;
    user.setUserName(name);
    std::cout << green_begin << "password: " << green_end;
    std::cin >> password;
    user.setUserPassword(password);
    bool check_login;
		do {
			check_login = check_login_table(mysql, res, row, table_users, user.getUserLogin());
			if (check_login == false) {
                std::cout << "Пользователь c логином: " <<login << "  уже существует" << std::endl;
				return;
			}
		} while (!check_login);
  
            add_user(mysql, table_users, user.getUserLogin(), user.getUserName(), user.getUserPassword());
            std::cout << "Пользователь c логином: " <<login << " создан" << std::endl;
}

void Chat::show_table(MYSQL &ms, MYSQL_RES *res, MYSQL_ROW &row, std::string table)
{
    std::string str = "SELECT * FROM " + table;
    if (!mysql_query(&ms, str.c_str()))
    {
        std::cout << " Таблица " << table << ":" << std::endl;
        if (res = mysql_store_result(&ms))
        {
            while (row = mysql_fetch_row(res))
            {
                for (int i = 0; i < mysql_num_fields(res); i++)
                {
                    std::cout << "| " << row[i] << " |";
                }
                std::cout << std::endl;
            }
        }
        else
            std::cout << " Ошибка mysql: " << mysql_error(&ms) << std::endl;
        mysql_free_result(res);
    }
    else
        std::cout << " Error: таблица не выведена " << std::endl
                  << mysql_error(&ms) << std::endl;
}

void Chat::ShowAllUsersName() const
{
    cout << "Пользователи" << endl;
    for (auto &User : userList_) // цикл на основе диапазона
    {
        cout << User.getUserName();
        cout << endl;
        if (currentUser_->getUserLogin() == User.getUserLogin())
        {
            cout << "(Я)";
            cout << endl;
        }
        cout << endl;
    }
}
void Chat::ShowLoginMenu()
{
    setlocale(LC_ALL, "");
    //currentUser_ = nullptr;
    char operation;
    do
    {
        std::cout << line << std::endl;
        std::cout << cyan_begin << " Добро пожаловать в консольный чат " << cyan_end << std::endl;
        std::cout << line << std::endl;
        std::cout << yellow_begin << " Ввести логин       - введите 1" << yellow_end << std::endl;
        std::cout << yellow_begin << " Зарегистрироваться - введите 2" << yellow_end << std::endl;
        std::cout << yellow_begin << " Выход              - введите q" << yellow_end << std::endl;

        std::cin >> operation;

        switch (operation)
        {
        case '1':
            login();

            break;
        case '2':
            try
            {
                signUp();
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
            break;
        case 'q':
            isChatWork_ = false;
            break;
        default:
            std::cout << "1 or 2..." << std::endl;
            break;
        }
    } while (isChatWork_);        // (!currentUser_ && isChatWork_);
}

void Chat::ShowUserMenu()
{
    char operation;
    ;
    std::cout << " Привет, " << currentUser_->getUserName() << std::endl;
    std::cout << line << std::endl;
    while (currentUser_)
    {
        std::cout << yellow_begin << " Просмотр зарегистрированных пользователей в чате - введите 1 " << yellow_end << std::endl;
        std::cout << yellow_begin << " Отправить сообщение                              - введите 2 " << yellow_end << std::endl;
        std::cout << yellow_begin << " Просмотр сообщений в чате                        - введите 3 " << yellow_end << std::endl;
        std::cout << yellow_begin << " Выход                                            - введите q " << yellow_end << std::endl;
        std::cout << line << std::endl;

        std::cout << std::endl;
        cout << ">>";
        std::cin >> operation;
        switch (operation)
        {
        case '1':
            ShowAllUsersName();
            break;
        case '2':
            addMessage();
            break;
        case '3':
            showChat();
            break;
        case 'q':
            currentUser_ = nullptr;
            break;
        default:
            std::cout << " Неверный выбор ..." << std::endl;
            break;
        }
    }
}

void Chat::addMessage()
{
    std::string to, text;
    std::cout << "Отправить кому (Логин или Отправить всем(введите all)):                  ";
    std::cin >> to;
    std::cout << "Текст:                  ";
    std::cin.ignore();
    getline(std::cin, text); // getline предназначена для ввода данных из потока до строкового разделителя.

    if (!(to == "all" || Chat::getUserByName(to)))
    {
        std::cout << red_begin << "Ошибка отправки сообщения: Не найден получатель !" << red_end << to << std::endl;
        return;
    }
    if (to == "all")
    {
        messageList_.push_back(Message(currentUser_->getUserLogin(), "all", text));
    }
    else
    {
        messageList_.push_back(Message(currentUser_->getUserLogin(), getUserByName(to)->getUserLogin(), text));
    }
}

void Chat::showChat() const
{
    std::string from, to;
    std::cout << line << std::endl;
    for (auto &mess : messageList_)
    {
        if (currentUser_->getUserLogin() == mess.getFrom() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
        {
            from = (currentUser_->getUserLogin() == mess.getFrom()) ? "Я" : getUserByLogin(mess.getFrom())->getUserName();
        }
        if (mess.getTo() == "all")
        {
            to = "(all)";
        }
        else
        {
            to = (currentUser_->getUserLogin() == mess.getTo()) ? "Я" : getUserByLogin(mess.getTo())->getUserName();
        }
        std::cout << green_begin << "Сообщение от: " << green_end << from << "\n"
                  << green_begin << "Кому: " << green_end << to << "\n"
                  << std::endl;
        std::cout << green_begin << "Техт сообщения: " << green_end << mess.getText() << std::endl;
    }
    std::cout << line << std::endl;
}

// bool Chat::check_login_table(MYSQL& ms, MYSQL_RES* res, MYSQL_ROW& row, std::string table, std::string log){
// 	std::string str = "SELECT COUNT(*) FROM " + table + " WHERE login = \'" + log + "\'";
// 	if(mysql_query(&ms, str.c_str()))
// 		std::cout << " Erorr: сбой проверки логина " << std::endl
// 			<< mysql_error(&ms) << std::endl;
// 	else{
// 			res = mysql_use_result(&ms);
// 			if(res){
// 				if (row = mysql_fetch_row(res)){
// 					int count = std::stoi(row[0]);
// 					mysql_free_result(res);
// 					if(count > 0) return false;
// 					else return true;
// 				}
// 			}
// 			mysql_free_result(res);
// 	}
// 	return -1;
// }
// bool Chat::check_pass_table(MYSQL &ms, MYSQL_RES *res, MYSQL_ROW &row, std::string table, std::string log, std::string pass)
// {
// std::string str = "SELECT COUNT(*) FROM " + table + " WHERE login = \'" + log + "\' AND hash = \'" + pass + "\'";
// 	if(mysql_query(&ms, str.c_str()))
// 		std::cout << " Erorr: сбой проверки пароля " << std::endl
// 			<< mysql_error(&ms) << std::endl;
// 	else{
// 			res = mysql_use_result(&ms);
// 			if(res){
// 				if (row = mysql_fetch_row(res)){
// 					int count = std::stoi(row[0]);
// 					mysql_free_result(res);
// 					if(count == 1) return false;
// 					else return true;
// 				}
// 			}
// 			mysql_free_result(res);
// 	}
// 	return false;
// }

// //--------------- Вход и регистрация ----------------------------------------------------
// void Chat::registration(char menu, bool* check_user, MYSQL& ms, MYSQL_RES* res, MYSQL_ROW& row) {
// 	User user;

// 	*check_user = false;
// 	// Вход в чат
// 	if (menu == '1') {
// 		exchange(" Введите логин(латинский алфавит, цифры, символы): ");
// 		user.get_user_login(message());
// 		exchange(" Введите пароль(латинский алфавит, цифры, символы): ");
// 		user.get_user_password(message());
// 		int counter = 0;
// 		if (!check_pass_table(ms, res, row, table_users, user.user_login(), user.user_password())) {
// 			user.get_user_name(name_user(ms, res, row, table_users, user.user_login()));
// 			get_user(user.user_login(), user.user_name());
// 			transmitting(user.user_name());
// 			*check_user = true;
// 		}
// 		else {
// 			transmitting("false");
// 			return;
// 		}
// 	}

// 	// регистрация нового пользователя
// 	else {
// 		*check_user = true;
// 		user.get_user_name(message());
// 		exchange(user.user_name());
// 		exchange(" Введите логин (латинский алфавит, цифры, символы): ");
// 		bool check_login;
// 		do {
// 			user.get_user_login(message());
// 			check_login = check_login_table(ms, res, row, table_users, user.user_login());
// 			if (check_login == false) {
// 				user.clear_login();
// 				exchange("false");
// 			}
// 		} while (!check_login);
// 		exchange(" логин принят");
// 		exchange( " Введите пароль (латинский алфавит, цифры, символы): ");
// 		user.get_user_password(message());
// 		std::cout << message() << std::endl;
// 		insert_into_users(ms, table_users, user.user_login(), user.user_name(), user.user_password());
// 		if(check_login_table(ms, res, row, table_users, user.user_login())){
// 			*check_user = false;
// 			return;
// 		}
// 		show_table(ms, res, row, table_users);
// 		exchange("reg ok");
// 	}
// }
