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

    SilicaListView {
        id: listView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.fill: parent
        anchors.margins: Theme.paddingLarge

        // prevent newly added list delegates from stealing focus away from the search field
        currentIndex: -1

        delegate: ListItem {
            Text {
                anchors {
                    left: parent.left
                    right: parent.right
                }
                color: Theme.secondaryHighlightColor
                text: quote.substring(0, 30) + "..." + " - <i>" + philosopher + "</i>"
                wrapMode: Text.WordWrap
                font.pixelSize: Theme.fontSizeMedium
            }
        }

        header: Column {
            height: searchField.height
            width: parent.width
            anchors.margins: parent.margins
            SearchField {
                id: searchField
                width: parent.width
                placeholderText: "Search"

    //            onTextChanged: {
    //                listModel.update()
    //            }
            }
        }

        model: quoteModel

        VerticalScrollDecorator { }
    }
}
