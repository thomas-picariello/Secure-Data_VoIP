#ifndef RSAKEYRING_H
#define RSAKEYRING_H

#include <QDebug>
#include <QObject>
#include <QByteArray>
#include <QFile>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDateTime>
#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>
#include <cryptopp/aes.h>

class RsaKeyring : public QObject
{
    Q_OBJECT
public:
    explicit RsaKeyring(QPair<QByteArray,QByteArray> *fileKey,
                        QObject *parent=0);
    ~RsaKeyring();

    void commitToKeystore();
    void exportKeys(QString filePath);
    void exportPublicKey(QString filePath);
    void generateKeypair();
    QByteArray *getPrivateKey();
    QByteArray *getPublicKey();
    void importKeys(QString filePath);
    void importPublicKey(QString filePath);
    void setPrivateKey(QByteArray privateKey);
    void setPublicKey(QByteArray publicKey);
    bool validateKeypair();

signals:
    void keyGenerationFinished();

public slots:
    void onKeyGenJobFinished();

private:
    QPair<QByteArray,QByteArray> *mFileKey;
    QByteArray mPrivateKey;
    QByteArray mPublicKey;
    QFutureWatcher<QPair<QByteArray,QByteArray>> mWatcher;

    QPair<QByteArray, QByteArray> generate();
    void readKeystore();

    Q_DISABLE_COPY(RsaKeyring)
};

#endif //RSAKEYRING_H
