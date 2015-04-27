# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-quotes

CONFIG += sailfishapp
PKGCONFIG += zlib

SOURCES += \
    src/quote.cpp \
    src/quotedb.cpp \
    src/internalmodelfacade.cpp \
    src/quotesidregistry.cpp \
    src/searchpagelistmodel.cpp \
    src/authorslistmodel.cpp \
    src/harbour-quotes.cpp

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    qml/content/images/*.png \
    translations/*.ts \
    quotesdb/*.json \
    qml/pages/AboutPage.qml \
    qml/pages/QuotePage.qml \
    qml/pages/SearchPage.qml \
    qml/pages/Loading.qml \
    qml/pages/AuthorsPage.qml \
    harbour-quotes.desktop \
    harbour-quotes.png \
    rpm/harbour-quotes.yaml \
    rpm/harbour-quotes.spec \
    rpm/harbour-quotes.changes.in \
    qml/harbour-quotes.qml

harbour-quotes.files = quotesdb/*.json
harbour-quotes.path = /usr/share/$${TARGET}

INSTALLS += harbour-quotes

# to disable building translations every time, comment out the
# following CONFIG line
# CONFIG += sailfishapp_i18n
# TRANSLATIONS += translations/Quotes-de.ts

HEADERS += \
    src/quote.h \
    src/quotedb.h \
    src/internalmodelfacade.h \
    src/quotesidregistry.h \
    src/searchpagelistmodel.h \
    src/authorslistmodel.h

RESOURCES +=


