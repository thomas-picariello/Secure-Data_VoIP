#include "networkmanager.h"

NetworkManager::NetworkManager(QTcpSocket *socket, QObject *parent): QObject(parent)
{
    m_Socket = new QTcpSocket;
    m_Socket = socket;

    hs = new Handshake(m_Socket);
    connect(hs,SIGNAL(handshakeSuccessfull()),this,SLOT(onIdentified()));
    hs->startCheckKey();


}
NetworkManager::NetworkManager(Contact c, QObject *parent): QObject(parent)
{
    m_Socket = new QTcpSocket;
    Contact contact = c;

    QString ip  = contact.getIp();
    quint16 port = contact.getPort().toInt();

    //Close previous connection if already connected with this socket
    if(m_Socket->state() == QAbstractSocket::ConnectedState ||
       m_Socket->state() == QAbstractSocket::ConnectingState)
        m_Socket->abort();

    m_Socket->connectToHost(ip, port);

    connect(m_Socket, SIGNAL(connected()),
            this, SLOT(onConnect()));

}
void NetworkManager::onConnect(){

    hs = new Handshake(m_Socket,contact);
    connect(hs,SIGNAL(handshakeSuccessfull()),this,SLOT(onIdentified()));
    hs->startCheckKey();


}
void NetworkManager::onIdentified(){

    m_settings = new QSettings;
    voip = new VoIP;

    mAesKey = QByteArray(16, 0x0); //16 byte = 128 bits, filled with 0x0.
    mAesIv = QByteArray(AES::BLOCKSIZE, 0x0); //filled with 0x0.
    mCfbAesEnc.SetKeyWithIV((byte*)mAesKey.data(), mAesKey.size(), (byte*)mAesIv.data());
    mCfbAesDec.SetKeyWithIV((byte*)mAesKey.data(), mAesKey.size(), (byte*)mAesIv.data());

     m_MessengerWindow = new MessengerWindow;
     QString ip = m_Socket->peerAddress().toString();
     qDebug()<<ip;

     m_MessengerWindow->displayMessage(Message("Connected to : "+ip, Message::SERVICE));

     connect(m_MessengerWindow,SIGNAL(callContact()),
             this, SLOT(voipCall()));
     connect(m_Socket, SIGNAL(readyRead()),
             this, SLOT(readIncomingData()));
     connect(m_MessengerWindow,SIGNAL(sendMessage(QByteArray)),
                     this, SLOT(sendData(QByteArray)));
}

void NetworkManager::voipCall()
{

    if(voip->getCallState() == VoIP::OFFLINE){
        m_MessengerWindow->changeButtonState(false);
        voip->call(Contact());
    }
    else if (voip->getCallState() == VoIP::ONLINE){
        m_MessengerWindow->changeButtonState(true);
        voip->endCall();
    }

}
void NetworkManager::readIncomingData()
{
    QByteArray data = m_Socket->readAll();
    //decrypt AES
    mCfbAesDec.ProcessString((byte*)data.data(), data.length());

    m_MessengerWindow->displayMessage(Message(QString(data), Message::RECIEVED));


}

void NetworkManager::sendData(QByteArray data)
{
    if(m_Socket->state() == QAbstractSocket::ConnectedState){
        m_MessengerWindow->displayMessage(Message(QString(data), Message::SENT));
        //encrypt AES
        mCfbAesEnc.ProcessString((byte*)data.data(), data.length());

        m_Socket->write(data);
    }
    else m_MessengerWindow->displayMessage(Message("Couldn't send message : Not connected.", Message::ERR));

}
void NetworkManager::error(QAbstractSocket::SocketError error)
{
    qDebug()<<error;

    if(error == QAbstractSocket::RemoteHostClosedError){
        m_MessengerWindow->displayMessage(Message("The server has disconnected...", Message::ERR));
    }
}

NetworkManager::~NetworkManager()
{


}