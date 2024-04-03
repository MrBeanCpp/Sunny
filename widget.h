#ifndef WIDGET_H
#define WIDGET_H

#include <QSystemTrayIcon>
#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setAwake(bool awake = true);

private:
    Ui::Widget* ui;

    QSystemTrayIcon* sysTray = nullptr;
    int runSec = 0;
    bool isAwake = false;
};
#endif // WIDGET_H
