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

CoverBackground {
    id: coverBackground

        Column {
            height: coverBackground.height
            width: coverBackground.width
            spacing: Theme.paddingSmall
            Image {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Theme.paddingSmall
                source: "../content/images/Cover.png"
                fillMode: Image.Stretch
                height: parent.height - 2 * Theme.fontSizeSmall
                width: parent.width
            }
            Text {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Theme.paddingSmall
                width: parent.width
                horizontalAlignment: Text.Center
                wrapMode: Text.WordWrap
                text: qsTr("<b>Cogito Ergo Sum</b>")
                color: Theme.primaryHighlightColor
                font.pixelSize: Theme.fontSizeSmall
            }
        }

//    CoverActionList {
//        id: coverAction

//        CoverAction {
//            iconSource: "image://theme/icon-cover-next"
//        }

//        CoverAction {
//            iconSource: "image://theme/icon-cover-pause"
//        }
//    }
}
