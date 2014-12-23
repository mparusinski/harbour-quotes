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
TARGET = PhilosophyQuotes

CONFIG += sailfishapp

SOURCES += src/PhilosophyQuotes.cpp \
    src/quotecontroller.cpp

OTHER_FILES += qml/PhilosophyQuotes.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/content/images/*.png \
    rpm/PhilosophyQuotes.changes.in \
    rpm/PhilosophyQuotes.spec \
    rpm/PhilosophyQuotes.yaml \
    translations/*.ts \
    PhilosophyQuotes.desktop

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/PhilosophyQuotes-de.ts

HEADERS += \
    src/quotecontroller.h


