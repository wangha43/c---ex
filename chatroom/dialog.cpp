#include "dialog.h"

dialog::dialog()
{
    setWindowTitle(tr("TCP Server"));

       ContentListWidget = new QListWidget;

       PortLabel = new QLabel(tr("端口："));
       PortLineEdit = new QLineEdit;

       CreateBtn = new QPushButton(tr("创建聊天室"));

       mainLayout = new QGridLayout(this);
       mainLayout->addWidget(ContentListWidget,0,0,1,2);
       mainLayout->addWidget(PortLabel,1,0);
       mainLayout->addWidget(PortLineEdit,1,1);
       mainLayout->addWidget(CreateBtn,2,0,1,2);

       port=1234;
       PortLineEdit->setText(QString::number(port));

       connect(CreateBtn, SIGNAL(clicked()), this, SLOT(slotCreateServer()));
}

void dialog::slotCreateServer()
{
    server = new MyServer();
    server->StartServer();
    CreateBtn->setEnabled(false);
}

void dialog::updateServer(QString msg, int length)
{
    ContentListWidget->addItem(msg.left(length));
}
