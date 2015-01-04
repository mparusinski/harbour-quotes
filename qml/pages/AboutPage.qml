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
    id: page

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

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
                title: qsTr("About")
            }

            Text {
                id: description
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Theme.paddingLarge
                width: parent.width
                horizontalAlignment: Text.AlignJustify
                wrapMode: Text.WordWrap
                text: "\t<b>Philosophy Quotes</b> helps you discover famous quotes from famous people."
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
            }

//            Image {
//                anchors.left: parent.left
//                anchors.right: parent.right
//                anchors.margins: Theme.paddingSmall
//                source: "../../PhilosophyQuotes.png"
//                fillMode: Image.PreserveAspectFit
//                // height: parent.height - 2 * Theme.fontSizeSmall
//                // width: parent.width
//            }

            Text {
                id: copyright
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Theme.paddingLarge
                width: parent.width
                horizontalAlignment: Text.AlignJustify
                wrapMode: Text.WordWrap
                text: "\t<b>Philosophy Quotes</b> is licensed under the terms of the General Public License version 2, the source code can be found on <a href=\"https://github.com/mparusinski/PhilosophyQuotes\">here</a>."
                color: Theme.primaryColor
                onLinkActivated: Qt.openUrlExternally("https://github.com/mparusinski/PhilosophyQuotes")
                font.pixelSize: Theme.fontSizeSmall
            }
        }
    }
}
