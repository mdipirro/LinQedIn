#include "guistyle.h"
#include <QPushButton>
#include <QLabel>
#include <QWidget>

QString GUIStyle::_lightBeige="#e1ba8a";
QString GUIStyle::_brown="#422d06";
QString GUIStyle::_lightGold="#e1ba70";
QString GUIStyle::_darkOrange="#e19600";
QString GUIStyle::_redCoral="#ff4040";
QString GUIStyle::_borderStyle="border:4px solid "+_brown+";border-radius:40px;";
QString GUIStyle::_formBorderStyle="border:3px solid "+_brown+";";
QString GUIStyle::_focusedFormBorderStyle="border:3px solid "+_darkOrange+";";
QString GUIStyle::_generalStyle="QLineEdit{"+_formBorderStyle+"color:black;}" //stile caselle di testo
                                    "QLineEdit:focus{"+_focusedFormBorderStyle+"}" //stile caselle di testo con focus
                                    "QFrame, QFrame * {font:14px;background:"+_lightBeige+";}" //stile generale
                                    "QPushButton{font:15px;background:"+_lightGold+";font-weight:bold;padding:5px;color:black;}"
                                    "QPushButton:pressed{font:15px;background:"+_darkOrange+";border:2px solid"+_brown+";"
                                                        "font-weight:bold;padding:5px;color:black;}"
                                     "QLabel{color:black;}";
QString GUIStyle::_popupButtonStyle="QPushButton{background:"+_lightBeige+";color:black;}"
                                    "QPushButton:pressed{background:"+_darkOrange+";border:2px solid"+_brown+";color:black;}";
QString GUIStyle::_logoPath="images/logo.png";
QString GUIStyle::_iconPath="images/icon.png";
QString GUIStyle::_headerStyle="font:30px;font-weight:bold;";
QString GUIStyle::_errorLabelStyle="color:"+_redCoral+";font-weight:bold;";
QString GUIStyle::_popupStyle="QMessageBox{background:"+_lightGold+";font-size:13px;color:black;}"+_popupButtonStyle;
int GUIStyle::_logoWidth=350;
int GUIStyle::_logoHeight=100;

void GUIStyle::setLogoSize(QWidget* logo,int width,int height){
    logo->setMaximumSize(width,height);
    logo->setMinimumSize(width,height);
}//setLogoSize

QString GUIStyle::lightBeige(){return _lightBeige;}
QString GUIStyle::brown(){return _brown;}
QString GUIStyle::lightGold(){return _lightGold;}
QString GUIStyle::darkOrange(){return _darkOrange;}
QString GUIStyle::redCoral(){return _redCoral;}
QString GUIStyle::borderStyle(){return _borderStyle;}
QString GUIStyle::formBorderStyle(){return _formBorderStyle;}
QString GUIStyle::focusedFormBorderStyle(){return _focusedFormBorderStyle;}
QString GUIStyle::generalStyle(){return _generalStyle;}
QString GUIStyle::popupButtonStyle(){return _popupButtonStyle;}
QString GUIStyle::logoPath(){return _logoPath;}
QString GUIStyle::iconPath(){return _iconPath;}
QString GUIStyle::headerStyle(){return _headerStyle;}
QString GUIStyle::errorLabelStyle(){return _errorLabelStyle;}
QString GUIStyle::popupStyle(){return _popupStyle;}
int GUIStyle::logoWidth(){return _logoWidth;}
int GUIStyle::logoHeight(){return _logoHeight;}

void GUIStyle::initLogo(QPushButton* button,int width,int height){
    button->setStyleSheet("border-image:url("+_logoPath+");");
    button->setFlat(true);
    button->setCursor(QCursor(Qt::PointingHandCursor));
    setLogoSize(button,width,height);
}//initLogo

void GUIStyle::initLogo(QLabel* label,int width,int height){
    label->setPixmap(QPixmap(_logoPath));
    label->setScaledContents(true);
    setLogoSize(label,width,height);
}//initLogo

GUIStyle::~GUIStyle(){}
