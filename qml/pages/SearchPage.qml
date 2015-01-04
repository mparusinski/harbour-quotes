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

    Column {
        id: searchFieldContainer
        anchors.left: parent.left
        anchors.right: parent.right

        SearchField {
            id: searchField
            width: parent.width
            placeholderText: "Search"

            onTextChanged: {
                listModel.update()
            }
        }
    }

    SilicaListView {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        // anchors.fill: parent
        anchors.top: searchFieldContainer.bottom

        // prevent newly added list delegates from stealing focus away from the search field
        currentIndex: -1

        model: ListModel {
            id: listModel
            property var quotes: ["Nietzsche", "Proudhon", "Plato", "Descartes", "Sartre"]

            function update() {
                clear()
                for (var i=0; i<quotes.length; i++) {
                    if (searchField.text == "" || quotes[i].indexOf(searchField.text) >= 0) {
                        append({"name": quotes[i]})
                    }
                }
            }

            Component.onCompleted: update()
        }

        delegate: ListItem {
            Label {
                anchors {
                    left: parent.left
                    leftMargin: searchField.textLeftMargin
                    verticalCenter: parent.verticalCenter
                }
                text: name
            }
        }
    }
}
