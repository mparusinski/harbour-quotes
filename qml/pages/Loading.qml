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

import QtQuick 2.0
import Sailfish.Silica 1.0

import com.parusinskimichal.quotes.engine 1.0

Page {
    backNavigation: false

    Column {
        id: loadingPage
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 20

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Loading Quotes..."
        }

        BusyIndicator {
            id: busyIndicator
            anchors.horizontalCenter: parent.horizontalCenter
            size: BusyIndicatorSize.Large
            running: true
        }

        Component.onCompleted: {
            internalModel.setupSearchPageListModel();
            internalModel.aynscReadQuotesDB();
        }

        InternalModelWindow {
            onDoneReadingQuotes: {
                busyIndicator.running = false;
                pageStack.replace(Qt.resolvedUrl('SearchPage.qml'), {}, PageStackAction.Immediate);
            }
        }

    }
}
