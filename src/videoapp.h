#ifndef VIDEOAPP_H
#define VIDEOAPP_H



#include <contact.h>
#include <QDebug>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDeclarativeContext>
#include <QtGui>
#include <QVideoFrame>

#include "typesenums.h"
#include "abstractapp.h"
#include "viewfinderwrapper.h"



namespace Ui{
class VideoApp;

}

class VideoApp : public AbstractApp
{
    Q_OBJECT

public:
    static const AppType APPTYPE = VideoStreamer;

    explicit VideoApp(Contact *contact, QWidget *parent = 0);
    virtual ~VideoApp();

    void addContact();
    void updateDisplay();

public slots :
    virtual void readIncommingData(QByteArray &data);
    void drawFrame(QVideoFrame frame);

signals :
    void error();



private slots:
    void senddata();

private:
    Ui::VideoApp *ui;
    ViewFinderWrapper *wrapper;







};

#endif // VIDEOAPP_H
