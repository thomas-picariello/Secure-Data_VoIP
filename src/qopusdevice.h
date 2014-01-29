#ifndef QOPUSENCODER_H
#define QOPUSENCODER_H

#include <QDebug>
#include <QObject>
#include <QIODevice>
#include <QBuffer>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QByteArray>
#include <opus/opus.h>

class QOpusDevice : public QIODevice
{
    Q_OBJECT
public:
    explicit QOpusDevice(QIODevice *deviceToUse,
                         int frameSizeInMicrosecs = 0,
                         QObject* parent = 0);
    bool open(OpenMode mode);
    void close();
    bool isSequential() const;

    int getFrameSize() const;
    void setFrameSize(int frameSizeInMicrosecs);
    int getEncoderApplication() const;
    void setEncoderApplication(int application);
    quint64 getBitrate() const;
    void setBitrate(quint64 bitrate);

    static QString getOpusErrorDesc(int errorCode);

    ~QOpusDevice();

signals:
    void error(const int err);

protected:
    qint64 readData(char * data, qint64 maxSize);
    qint64 writeData(const char * data, qint64 maxSize);

private:
    OpusEncoder *mEncoder;
    OpusDecoder *mDecoder;
    QIODevice *mUnderlyingDevice;
    QByteArray mBuffer;
    QAudioFormat mAudioFormat;
    int mError;
    int mOpusFrameSize;
    int mApplication;


    Q_DISABLE_COPY(QOpusDevice)
};

#endif // QOPUSENCODER_H
