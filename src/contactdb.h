/**
 * @brief ContactDB Stores Contact data and makes it availlable.
 */

#ifndef CONTACTDB_H
#define CONTACTDB_H

#include <QtSql/QtSql>
#include <QList>
#include <QByteArray>
#include <cryptopp/sha.h>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/base64.h>
#include "contact.h"

class ContactDB: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief The Event enum describs the events that can happen to a Contact.
     */
    enum Event{
        ContactAdded,
        ContactEdited,
        ContactDeleted
    };

    /**
     * @brief The Action enum describs the actions that can done on a Contact.
     */
    enum Action{
        Add,
        Edit,
        Delete
    };

    explicit ContactDB(QPair<QByteArray, QByteArray> *fileKey, QObject *parent = 0);
    ~ContactDB();

    void erase(int id);
    Contact* const findById(int id);
    Contact* const findByKey(QByteArray key);
    QList<Contact*> getAllContacts() const;
    uint save(Contact *contact);
    void updateFileKey();

signals:
    void contactEvent(int id, Event);
    void error(QString err);

private:
    QMap<uint,Contact*> m_contactList;
    QSqlDatabase m_database;
    QPair<QByteArray, QByteArray> *m_fileKey;

    void commitToDatabase();
    QByteArray generateHash();
    void importDatabase();
    void initDbTables();
    uint getNextAvailableId();
    QByteArray serializeStringList(QStringList list);
    QStringList deserializeStringList(QByteArray byteArray);
    void openDB();

    Q_DISABLE_COPY(ContactDB)
};

#endif // CONTACTDB_H
