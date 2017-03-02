#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "myserver.h"

class dialog:public QDialog
{
    Q_OBJECT
public:
    dialog();
    QListWidget *ContentListWidget;
    QLabel *PortLabel;
    QLineEdit *PortLineEdit;
    QPushButton *CreateBtn;
    QGridLayout *mainLayout;
    int port;
    MyServer *server;

public slots:
    void slotCreateServer();
    void updateServer(QString,int);
};

#endif // DIALOG_H
