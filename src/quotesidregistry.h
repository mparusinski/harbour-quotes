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

#ifndef QUOTESIDREGISTRY_H
#define QUOTESIDREGISTRY_H

#include <set>
#include <map>
#include <QSharedPointer>

#include "quote.h"

class Quote;

class QuotesIDRegistry {

public:
    typedef QSharedPointer<Quote> QuotePtr;

    typedef std::set<u_int32_t> UsedIDsSetType;

    typedef std::map<u_int32_t, QuotePtr> QuotesMapType;

    static QuotesIDRegistry* getRegistry();

    u_int32_t registerQuote(const QuotePtr& quote);

    QuotePtr getQuoteWithID(const u_int32_t idNum);

private:
    static QuotesIDRegistry * instance;

    explicit QuotesIDRegistry();

    u_int32_t findValidID();

    u_int32_t m_nextIDToTry;

    UsedIDsSetType m_usedIDs;

    QuotesMapType m_idRegistry;
};

#endif // QUOTESIDREGISTRY_H
