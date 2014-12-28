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
    function quoteText() {
        return "\t\"" + quoteController.getQuoteText() + "\"";
    }

    function philosopherText() {
        return "<i>" + quoteController.getPhilosopherText() + "</i>"
    }

    id: page

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Search")
                // onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
            }
            MenuItem {
                text: qsTr("Next quote")
                onClicked: {
                    quoteController.updateQuote()
                    quoteField.text = quoteText()
                    philosopherField.text = philosopherText()
                }
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column
            width: page.width
            height: page.height
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("Philosophy Quotes")
            }
            Column {
                anchors.verticalCenter: parent.verticalCenter
                spacing: Theme.paddingLarge
                width: page.width

                Text {
                    id: quoteField
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: Theme.paddingLarge
                    width: parent.width
                    horizontalAlignment: Text.AlignJustify
                    wrapMode: Text.WordWrap
//                    text: "\t\"That which does not kill you makes you stronger\""
                    text: quoteText()
                    color: Theme.primaryColor
                    font.pixelSize: Theme.fontSizeLarge
                }
                Text {
                    id: philosopherField
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: Theme.paddingLarge
                    width: parent.width
                    horizontalAlignment: Text.AlignRight
                    wrapMode: Text.WordWrap
//                    text: "<i>Frederich Nietszche</i>"
                    text: philosopherText()
                    color: Theme.secondaryHighlightColor
                    font.pixelSize: Theme.fontSizeMedium
                }
            }
        }
    }
}
