#ifndef GUISTYLE_H
#define GUISTYLE_H

#include<QString>

class QWidget;
class QPushButton;
class QLabel;

class GUIStyle{
private:
    //impedisco la creazione di un oggetto GUIColors
    GUIStyle();
    GUIStyle(const GUIStyle&);
    GUIStyle& operator=(const GUIStyle&);

    static QString _lightBeige;
    static QString _brown;
    static QString _lightGold;
    static QString _darkOrange;
    static QString _redCoral;
    static QString _borderStyle;
    static QString _formBorderStyle;
    static QString _focusedFormBorderStyle;
    static QString _generalStyle;
    static QString _popupButtonStyle;
    static QString _logoPath;
    static QString _iconPath;
    static QString _headerStyle;
    static QString _errorLabelStyle;
    static QString _popupStyle;
    static int _logoWidth;
    static int _logoHeight;

    static void setLogoSize(QWidget*,int,int);

public:
    static QString lightBeige();
    static QString brown();
    static QString lightGold();
    static QString darkOrange();
    static QString redCoral();
    static QString borderStyle();
    static QString formBorderStyle();
    static QString focusedFormBorderStyle();
    static QString generalStyle();
    static QString popupButtonStyle();
    static QString logoPath();
    static QString iconPath();
    static QString headerStyle();
    static QString errorLabelStyle();
    static QString popupStyle();
    static int logoWidth();
    static int logoHeight();
    static void initLogo(QPushButton*,int =_logoWidth,int =_logoHeight);
    static void initLogo(QLabel*,int =_logoWidth,int =_logoHeight);

    virtual ~GUIStyle() =0;
};

#endif // GUISTYLE_H
