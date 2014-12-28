/*
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

#include "quote.h"

Quote::Quote(QObject *parent) :
    QObject(parent)
{
}

Quote::Quote(QString philosopher, QString quoteText)
{
    m_philosopher = philosopher;
    m_quoteText = quoteText;
}

QString Quote::getPhilosopher() const {
    return m_philosopher;
}

QString Quote::getQuoteText() const {
    return m_quoteText;
}
