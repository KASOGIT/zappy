/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0

Rectangle {
    id: root
    anchors.fill: parent
    color: "black"

    property string source1
    property string source2
    property color bgColor: "black"
    property real volume: 0.25
    property bool perfMonitorsLogging: false
    property bool perfMonitorsVisible: false

    QtObject {
        id: d
        property int itemHeight: root.height > root.width ? root.width / 10 : root.height / 10
        property int buttonHeight: 0.8 * itemHeight
        property int margins: 5
    }

    Loader {
        id: performanceLoader

        Connections {
            target: inner
            onVisibleChanged:
                if (performanceLoader.item)
                    performanceLoader.item.enabled = !inner.visible
            ignoreUnknownSignals: true
        }

        function init() {
            var enabled = root.perfMonitorsLogging || root.perfMonitorsVisible
            source = enabled ? "../performancemonitor/PerformanceItem.qml" : ""
        }

        onLoaded: {
            item.parent = root
            item.anchors.fill = root
            item.logging = root.perfMonitorsLogging
            item.displayed = root.perfMonitorsVisible
            item.enabled = false
            item.init()
        }
    }

    Rectangle {
        id: inner
        anchors.fill: parent
        color: root.bgColor

        Button {
            id: openFile1Button
            anchors {
                top: parent.top
                left: parent.left
                right: exitButton.left
                margins: d.margins
            }
            bgColor: "#212121"
            bgColorSelected: "#757575"
            textColorSelected: "white"
            height: d.buttonHeight
            text: (root.source1 == "") ? "Select file 1" : root.source1
            onClicked: fileBrowser1.show()
        }

        Button {
            id: openFile2Button
            anchors {
                top: openFile1Button.bottom
                left: parent.left
                right: exitButton.left
                margins: d.margins
            }
            bgColor: "#212121"
            bgColorSelected: "#757575"
            textColorSelected: "white"
            height: d.buttonHeight
            text: (root.source2 == "") ? "Select file 2" : root.source2
            onClicked: fileBrowser2.show()
        }

        Button {
            id: exitButton
            anchors {
                top: parent.top
                right: parent.right
                margins: d.margins
            }
            bgColor: "#212121"
            bgColorSelected: "#757575"
            textColorSelected: "white"
            width: parent.width / 10
            height: d.buttonHeight
            text: "Exit"
            onClicked: Qt.quit()
        }

        Row {
            id: modes
            anchors.top: openFile2Button.bottom
            anchors.margins: 0
            anchors.topMargin: 5
            Button {
                width: root.width / 2
                height: 0.8 * d.itemHeight
                bgColor: "#212121"
                radius: 0
                text: "Video Modes"
                enabled: false
            }
            Button {
                width: root.width / 2
                height: 0.8 * d.itemHeight
                bgColor: "#212121"
                radius: 0
                text: "Camera Modes"
                enabled: false
            }
        }

        Rectangle {
            id: divider
            height: 1
            width: parent.width
            color: "black"
            anchors.top: modes.bottom
        }

        SceneSelectionPanel {
            id: sceneSelectionPanel
            itemHeight: d.itemHeight
            color: "#212121"
            anchors {
                top: divider.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            radius: 0
            onSceneSourceChanged: {
                sceneLoader.source = sceneSource
                var scene = null
                var innerVisible = true
                if (sceneSource == "") {
                    if (performanceLoader.item)
                        performanceLoader.item.videoActive = false
                } else {
                    scene = sceneLoader.item
                    if (scene) {
                        if (scene.contentType === "video" && source1 === "") {
                            errorDialog.show("You must first select a video file")
                            sceneSource = ""
                        } else {
                            scene.parent = root
                            scene.color = root.bgColor
                            scene.buttonHeight = d.buttonHeight
                            scene.source1 = source1
                            scene.source2 = source2
                            scene.volume = volume
                            scene.anchors.fill = root
                            scene.close.connect(closeScene)
                            scene.content.initialize()
                            innerVisible = false
                        }
                    }
                }
                videoFramePaintedConnection.target = scene
                inner.visible = innerVisible
            }
        }
    }

    Loader {
        id: sceneLoader
    }

    Connections {
        id: videoFramePaintedConnection
        onVideoFramePainted: {
            if (performanceLoader.item)
                performanceLoader.item.videoFramePainted()
        }
        ignoreUnknownSignals: true
    }

    FileBrowser {
        id: fileBrowser1
        anchors.fill: root
        onFolderChanged: fileBrowser2.folder = folder
        Component.onCompleted: fileSelected.connect(root.openFile1)
    }

    FileBrowser {
        id: fileBrowser2
        anchors.fill: root
        onFolderChanged: fileBrowser1.folder = folder
        Component.onCompleted: fileSelected.connect(root.openFile2)
    }

    function openFile1(path) {
        root.source1 = path
    }

    function openFile2(path) {
        root.source2 = path
    }

    ErrorDialog {
        id: errorDialog
        anchors.fill: root
        dialogWidth: d.itemHeight * 5
        dialogHeight: d.itemHeight * 3
        enabled: false
    }

    // Called from main() once root properties have been set
    function init() {
        performanceLoader.init()
        fileBrowser1.folder = videoPath
        fileBrowser2.folder = videoPath
    }

    function qmlFramePainted() {
        if (performanceLoader.item)
            performanceLoader.item.qmlFramePainted()
    }

    function closeScene() {
        sceneSelectionPanel.sceneSource = ""
    }
}
