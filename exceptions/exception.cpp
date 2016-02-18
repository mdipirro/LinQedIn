#include "exception.h"

Exception::Exception(const QString& m):msg(m){}

Exception::~Exception(){}

QString Exception::what() const{return msg;}
