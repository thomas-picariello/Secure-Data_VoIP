#include "messengerwindow.h"
#include "ui_messengerwindow.h"

MessengerWindow::MessengerWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MessengerWindow){
    ui->setupUi(this);
    msglist = new QStringList;

    connect(ui->send, SIGNAL(clicked()),
            this, SLOT(onSend()));
    connect(ui->input,SIGNAL(returnPressed()),
            this,SLOT(onSend()));
}

void MessengerWindow::displayMessage(QString msg){
    msglist->append(msg);
    ui->chat->setText(msglist->join("\n"));
    this->show();
}
void MessengerWindow::onSend(){
    QByteArray msg = ui->input->text().toUtf8();

    /****AES encryption in CFB mode***/
    QByteArray key(16, 0x0); //16 byte = 128 bits, filled with 0x0.
    qDebug()<<"AES key:"<<key.toHex();

    QByteArray iv(CryptoPP::AES::BLOCKSIZE, 0x0); //filled with 0x0.
    qDebug()<<"AES iv:"<<iv.toHex();

    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cfbEnc;
    cfbEnc.SetKeyWithIV((byte*)key.data(), key.size(), (byte*)iv.data());
    cfbEnc.ProcessData((byte*)msg.data(), (byte*)msg.data(), msg.size());

    emit sendMessage(msg);
    ui->input->clear();
}

MessengerWindow::~MessengerWindow(){
    delete ui;
}