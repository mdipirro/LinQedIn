#include "gui/loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    LoginWindow* w=new LoginWindow();
    w->show();
    return app.exec();
}//main
