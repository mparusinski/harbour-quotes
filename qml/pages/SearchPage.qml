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
import QtGraphicalEffects 1.0
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
            height: quoteText.height + philosopherText.height
            width: parent.width
            Text {
                id: quoteText
                // color: Theme.primaryColor
                // height: Theme.fontSizeMedium
                width: parent.width
                maximumLineCount: 2
                // elide: Text.ElideRight
                wrapMode: Text.WrapAnywhere
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: Theme.paddingLarge
                anchors.rightMargin: Theme.paddingLarge
                text: "<p>" + quote + "</p>"
                font.pixelSize: Theme.fontSizeMedium
                visible: false
                clip: true
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        internalModel.loadQuote(quoteID);
                        pageStack.push(Qt.resolvedUrl("QuotePage.qml"))
                    }
                }
            }
            LinearGradient  {
                    anchors.fill: quoteText
                    source: quoteText
                    start: Qt.point(0, 0)
                    end: Qt.point(quoteText.width, 0)
                    gradient: Gradient {
                        GradientStop { position: 0; color: Theme.primaryColor }
                        GradientStop { position: 0.7; color: Theme.primaryColor }
                        GradientStop { position: 1; color: "transparent" }
                    }
                }
            Text {
                id: philosopherText
                anchors.top: quoteText.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: Theme.paddingLarge
                horizontalAlignment: Text.AlignRight
                color: Theme.secondaryHighlightColor
                text: "<i>" + philosopher + "</i>"
                font.pixelSize: Theme.fontSizeSmall
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        internalModel.loadQuote(quoteID);
                        pageStack.push(Qt.resolvedUrl("QuotePage.qml"))
                    }
                }
            }
        }

        header: Column {
            height: searchField.height
            width: parent.width
            SearchField {
                id: searchField
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Theme.paddingLarge
                placeholderText: "Search"

                onTextChanged: {
                    internalModel.filterSearchPageUsingSearchString(text);
                }

                Keys.onReturnPressed: {
                    Qt.inputMethod.hide()
                }
            }
        }

        model: searchPageListModel

        onFlickStarted: {
            Qt.inputMethod.hide()
        }

        VerticalScrollDecorator {

        }

        Component.onCompleted: {
            internalModel.buildSearchPageListModel();
        }
    }
}
