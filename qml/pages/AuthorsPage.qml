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

Page {
    SilicaListView {
        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
        }

        id: listView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.fill: parent

        // prevent newly added list delegates from stealing focus away from the search field
        currentIndex: -1

        delegate: Column {
            spacing: Theme.paddingLarge
            height: authorText.height + Theme.paddingLarge * 2
            width: parent.width
            Text {
                id: authorText
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Theme.paddingLarge
                horizontalAlignment: Text.AlignLeft
                color: Theme.primaryColor
                text: author
                font.pixelSize: Theme.fontSizeMedium
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        internalModel.loadAuthor(author);
                        pageStack.push(Qt.resolvedUrl("SearchPage.qml"))
                    }
                }
            }
        }

        header: Column {
            height: authorsHeader.height
            width: parent.width
            PageHeader {
                id: authorsHeader
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Theme.paddingLarge
                title: "Authors"
            }
        }

        model: authorsPageListModel


        VerticalScrollDecorator {

        }

        Component.onCompleted: {
            internalModel.buildAuthorsPageListModel();
        }
    }
}
