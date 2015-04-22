/*
  Copyright 2015 Michal Parusinski <mparusinski@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include "quotesidregistry.h"
#include <QDebug>

QuotesIDRegistry* QuotesIDRegistry::instance = NULL;

QuotesIDRegistry::QuotesIDRegistry() {
    m_nextIDToTry = 1;
}

QuotesIDRegistry * QuotesIDRegistry::getRegistry() {
    if (instance == NULL) {
        instance = new QuotesIDRegistry;
    }
    return instance;
}

u_int32_t QuotesIDRegistry::registerQuote(const QuotesIDRegistry::QuotePtr& quote) {
    u_int32_t validID = findValidID();
    m_usedIDs.insert(validID);
    m_idRegistry[validID] = quote;
    return validID;
}

u_int32_t QuotesIDRegistry::findValidID() {
    if (m_nextIDToTry == UINT_MAX) {
        qCritical() << "UNABLE TO FIND AN ID";
        return 0;
    }
    m_nextIDToTry++;
    return m_nextIDToTry;
}

QuotesIDRegistry::QuotePtr QuotesIDRegistry::getQuoteWithID(const u_int32_t idNum) {
    return m_idRegistry[idNum];
}
