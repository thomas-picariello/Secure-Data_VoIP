#ifndef ROOTAPP_H
#define ROOTAPP_H

#include "abstractapp.h"
#include "typesenums.h"
#include "contact.h"
#include "contactdb.h"

class RootApp : public AbstractApp
{
    Q_OBJECT
public:
    static const AppType APPTYPE = Root;

    explicit RootApp(ContactDB *contactDB, QWidget *parent = 0);
    explicit RootApp(QList<Contact*> contactList, ContactDB *contactDB, QWidget *parent = 0);
    virtual ~RootApp();

public slots:
    virtual void dataToRead(QByteArray data);

};

#endif // ROOTAPP_H
