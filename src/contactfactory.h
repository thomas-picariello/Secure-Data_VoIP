/**
 * @brief ContactFactory retrieves contact informations from the storage and returns filled Contact objects.
 *
 * Each contact should be stored to be retrieved by the **QSettings** class according to the following path pattern:
 *
 * ~~~~~~~~~~
 * /"Contacts"/id/("name", "host", "port" or "key")
 * ~~~~~~~~~~
 */

#ifndef CONTACTFACTORY_H
#define CONTACTFACTORY_H

#include <QSettings>
#include <QList>
#include "contact.h"

class ContactFactory
{
public:
    /**
     * @brief Retrievs a contact by searching his *id*.
     *
     * @param id the ID of the contact to find
     * @param parent the parent **QObject**
     *
     * @return A Contact object or a *NULL* pointer if the contact does not exist
     */
    static Contact* findById(int id, QObject *parent = 0);

    /**
     * @brief Retrievs a contact by searching his *host* (hostname or IP).
     *
     * @param host the hostname or IP of the contact to find
     * @param parent the parent **QObject**
     *
     * @return A **QList** of Contact pointers or an empty **QList** if no contact has the searched host
     */
    static QList<Contact*> findByHost(QString host, QObject *parent = 0);

    /**
     * @brief Retrievs a contact by searching his *key*.
     *
     * @param key the key of the contact to find
     * @param parent the parent **QObject**
     *
     * @return A Contact object or a *NULL* pointer if the contact does not exist
     */
    static Contact* findByKey(QByteArray key, QObject *parent = 0);

    /**
     * @brief Retrievs a contact by searching his *name*.
     *
     * @param name the name of the contact to find
     * @param parent the parent **QObject**
     *
     * @return A **QList** of Contact pointers or an empty **QList** if no contact has the searched key
     */
    static QList<Contact*> findByName(QString name, QObject *parent = 0);

    /**
     * @brief Returns a list of all existing contacts.
     *
     * @param parent the parent **QObject**
     *
     * @return A **QList** of Contact pointers or an empty **QList** if there is no contact stored
     */
    static QList<Contact*> getContactList(QObject *parent = 0);
};

#endif // CONTACTFACTORY_H