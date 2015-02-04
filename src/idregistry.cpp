#include "idregistry.h"
#include <QDebug>

IDRegistry* IDRegistry::instance = NULL;

IDRegistry::IDRegistry(QObject *parent) :
    QObject(parent)
{
}

IDRegistry * IDRegistry::getRegistry()
{
    if (instance == NULL) {
        instance = new IDRegistry;
    }
    return instance;
}

u_int32_t IDRegistry::getNextID() {
    for (u_int32_t id = 0;  id < UINT_MAX; id++) {
        if (!m_usedIDs.contains(id)) {
            m_usedIDs.insert(id);
            return id;
        }
    }

    qCritical() << "UNABLE TO FIND AN ID";
    return 0;
}
