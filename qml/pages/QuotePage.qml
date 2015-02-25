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
        return "\t" + quoteController.getQuote();
    }

    function philosopherText() {
        return "<i>" + quoteController.getPhilosopher() + "</i>"
    }

    id: page

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            id: dropdown
            visible: quoteController.quoteNumber() > 1
            MenuItem {
                text: qsTr("Previous quote")
                onClicked: {
                    quoteController.prevQuote()
                    quoteField.text = quoteText()
                    philosopherField.text = philosopherText()
                }
            }

            MenuItem {
                text: qsTr("Next quote")
                onClicked: {
                    quoteController.nextQuote()
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
            height: pageHeader.height + column.spacing + subColumn.height
            spacing: Theme.paddingLarge
            PageHeader {
                id: pageHeader
                title: qsTr("Quote")
            }
            Column {
                id: subColumn
                anchors.verticalCenter: parent.verticalCenter
                anchors.top: pageHeader.bottom
                spacing: Theme.paddingLarge
                width: page.width
                height: quoteField.height + 5 * subColumn.spacing + philosopherField.height

                Text {
                    id: quoteField
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: Theme.paddingLarge
                    width: parent.width
                    horizontalAlignment: Text.AlignJustify
                    wrapMode: Text.WordWrap
                    text: quoteText()
                    color: Theme.primaryColor
                    font.pixelSize: Theme.fontSizeLarge
                }
                Text {
                    id: philosopherField
                    anchors.top: quoteField.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: Theme.paddingLarge
                    width: parent.width
                    horizontalAlignment: Text.AlignRight
                    wrapMode: Text.WordWrap
                    text: philosopherText()
                    color: Theme.secondaryHighlightColor
                    font.pixelSize: Theme.fontSizeMedium
                }
            }
        }

        VerticalScrollDecorator { }
    }
}
