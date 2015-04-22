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

#include <QtQuick>

#include <sailfishapp.h>
#include "internalmodelfacade.h"
#include "quotedb.h"

int main(int argc, char *argv[]) {
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    qmlRegisterType<InternalModelWindow>("com.parusinskimichal.quotes.engine", 1, 0, "InternalModelWindow");
    QSharedPointer<QQuickView> view(SailfishApp::createView());
    InternalModelFacade::getInternalModelFacade()->setMainView(view);

    view->rootContext()->setContextProperty("internalModel", InternalModelFacade::getInternalModelFacade());
    view->setSource(SailfishApp::pathTo("qml/Quotes.qml"));
    view->show();

    return app->exec();
}
