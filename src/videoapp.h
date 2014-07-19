#ifndef VIDEOAPP_H
#define VIDEOAPP_H



#include <contact.h>
#include <QDebug>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDeclarativeContext>
#include <QtGui>
#include <QVideoFrame>
#include <QCamera>
#include <QBuffer>

#include "typesenums.h"
#include "abstractapp.h"

#include "qglcanvas.h"
#include "videoencoder.h"
#include "videosurface.h"



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
    virtual void readIncommingData(const QByteArray &data);
    void drawFrame(QImage frame);
    void onDataToSend(QByteArray data);

signals :
    void error();

private:
    Ui::VideoApp *ui;

    QGLCanvas *m_Canvas;
    QGLCanvas *m_Canvas2;

    VideoEncoder *m_encoder;

    QCamera* m_camera;

    VideoSurface *m_surface;




};

#endif // VIDEOAPP_H
