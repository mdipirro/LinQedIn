#ifndef SMARTUSER_H
#define SMARTUSER_H

class User;

class SmartUser{
    friend class Database;
private:
    User* user;

    void setReferences(int);

public:
    SmartUser(User* const =0);
    SmartUser(const SmartUser&);
    SmartUser& operator=(const SmartUser&);
    ~SmartUser();
    bool operator==(const SmartUser&) const;
    bool operator!=(const SmartUser&) const;
    bool operator<(const SmartUser&) const;
    User& operator*() const;
    User* operator->() const;
    operator bool() const;
};

#endif // SMARTUSER_H
