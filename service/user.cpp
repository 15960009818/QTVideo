#include "user.h"

User::User()
{

}
User::User(const QString &username, const QString &password)
{
    this->username=username;
    this->password=password;
}
