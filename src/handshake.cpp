#include "handshake.h"

Handshake::Handshake(QTcpSocket *socket,  QObject *parent): QObject(parent)
{
    //responder

    m_Socket = new QTcpSocket;
    m_Socket = socket;



}

Handshake::Handshake(QTcpSocket *socket,Contact contact,  QObject *parent): QObject(parent)
{
    //starter
    m_Socket = new QTcpSocket;
    m_Socket = socket;




}
void Handshake::startCheckKey(){
emit handshakeSuccessfull();
}
void Handshake::startCheckCompatibility(){

}
void Handshake::respondCheckKey(){

}
void Handshake::respondCheckCompatbility(){

}

Handshake::~Handshake()
{

}