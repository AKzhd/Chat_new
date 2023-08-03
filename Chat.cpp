#include <iostream>
#include "Chat.h"
#include "Message.h"
#include "User.h"

using namespace std;

void Chat::start()
{
    isChatWork_ = true;
}

string cyan_begin = "\x1B[36m",cyan_end = "\033[0m\t\t";
string yellow_begin = "\x1B[33m",yellow_end = "\033[0m\t\t";
string red_begin = "\x1B[31m",red_end = "\033[0m\t\t";

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
    std::string login, password;
    char operation;
    do
    {
        std::cout << "login: ";
        std::cin >> login;
        std::cout << "password: ";
        std::cin >> password;

        currentUser_ = getUserByLogin(login);
        char operation;
        if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
        {
            currentUser_ = nullptr;
            std::cout << red_begin<<"Неверный логин!!!, для повторения нажмите любую клавищу. Для выхода нажмите 0(ноль) "<<red_end<< std::endl;
           
            std::cin >> operation;
            if (operation == '0')
                break;
        }
    } while (!currentUser_);
}

void Chat::signUp()
{
    std::string login, password, name;
    std::cout << "login:               ";
    std::cin >> login;
    std::cout << "password: ";
    std::cin >> password;
    std::cout << "Name: ";
    std::cin >> name;
    if (getUserByLogin(login) || login == "all")
    {
        throw UserLoginExp();
    }
    if (getUserByName(name) || name == "all")
    {
        throw UserNameExp();
    }
    User user = User(login, password, name);
    userList_.push_back(user);
    currentUser_ = std::make_shared<User>(user);
}

void Chat::ShowAllUsersName() const
{
    cout << "Пользователи" << endl;
    for (auto &User : userList_)
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
    currentUser_ = nullptr;
    char operation;
    do
    {
        std::cout << cyan_begin<<" Добро пожаловать в консольный чат "<<cyan_end << std::endl;
        std::cout << "----------------------------------" << std::endl;
        std::cout << yellow_begin<<" Ввести логин       - введите 1" <<yellow_end<< std::endl;
        std::cout << yellow_begin<<" Зарегистрироваться - введите 2" <<yellow_end<<std::endl;
        std::cout << yellow_begin<<" Выход              - введите q" <<yellow_end<< std::endl;

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
    } while (!currentUser_ && isChatWork_);
}

void Chat::ShowUserMenu()
{
    char operation;
    ;
    std::cout << " Привет, " << currentUser_->getUserName() << std::endl;
    while (currentUser_)
    {
        std::cout << yellow_begin<< " Просмотр зарегистрированных пользователей в чате - введите 1 "<< yellow_end<< std::endl;
        std::cout << yellow_begin<< " Отправить сообщение                              - введите 2 "<< yellow_end<< std::endl;
        std::cout << yellow_begin<< " Просмотр сообщений в чате                        - введите 3 "<< yellow_end<< std::endl;
        std::cout << yellow_begin<< " Выход                                            - введите q "<< yellow_end<< std::endl;


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
    getline(std::cin, text);           //getline предназначена для ввода данных из потока до строкового разделителя.
    
    if (!(to == "all" || Chat::getUserByName(to)))
    {
        std::cout << red_begin<<"Ошибка отправки сообщения: Не найден получатель !" <<red_end<< to << std::endl;
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
    std::cout << "\x1B[36m============================================================\033[0m\t\t" << std::endl;
    for (auto &mess : messageList_)
    {
        if (currentUser_->getUserLogin() == mess.getFrom() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
        {
            from = (currentUser_->getUserLogin() == mess.getFrom()) ? "me" : getUserByLogin(mess.getFrom())->getUserName();
        }
        if (mess.getTo() == "all")
        {
            to = "(all)";
        }
        else
        {
            to = (currentUser_->getUserLogin() == mess.getTo()) ? "me" : getUserByLogin(mess.getTo())->getUserName();
        }
        std::cout << "Сообщение от: " << from << "\n" << "Кому: " << to<<"\n"<< std::endl;
        std::cout << "Техт сообщения: " << mess.getText() << std::endl;
    }
    std::cout << "\x1B[36m============================================================\033[0m\t\t" << std::endl;
}
