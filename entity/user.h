ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
    User(const QString &username, const QString &password);

    QString getUsername() const { return username; }
    QString getPassword() const { return password; }
private:

    QString username;
    QString password;
};

#endif // USER_H
