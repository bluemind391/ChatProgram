import QtQuick 2.9
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import ChatClient 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Chat Client")
 
    function qmlFuncPrintMessage(stringValue) {
        showMessage.text += stringValue + qsTr("\n");
    }

    ChatClient {
        id: chatClient
    }

    Column {
        anchors.fill: parent
        Rectangle {
            id: rect1
            width: parent.width
            height: 60
            RowLayout {
                anchors.fill: parent
                Rectangle {
                    width: 350
                    height: 50
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    border.color: "black"
                    TextField {
                        id: ipPort                        
                        placeholderText: qsTr("ip:port")
                        text: qsTr("127.0.0.1:8080")
                        validator: RegExpValidator {
                            regExp:  /^((?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){0,3}(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\:(?:[0-5]?[0-9]?[0-9]?[0-9]?[0-9]|6[0-4][0-9][0-9][0-9]|65[0-4][0-9][0-9]|655[0-2][0-9]|6553[0-5])$/
                       }
                        anchors.fill: parent
                        font.pointSize: 20
                        padding: 10
                        focus: true
                    }
                }
                Button {
                    id: connectButton
                    text: qsTr("Connect")
                    onClicked: chatClient.cppFuncConnect(ipPort.text)
                }
                Button {
                    id: disconnectButton
                    text: qsTr("Disconnect")
                    onClicked: chatClient.cppFuncDisconnect()
                }
            }
        }
        Rectangle {
            id: rect2
            width: parent.width
            height: parent.height - rect1.height - rect3.height
            border.color: "black"
            TextArea {
                id: showMessage
                anchors.fill: parent
                readOnly: true
                font.pointSize: 15
                padding: 10
                wrapMode: TextArea.Wrap
            }
        }
        Rectangle {
            id: rect3
            width: parent.width
            height: 60
            RowLayout {
                anchors.fill: parent
                Rectangle {
                    width: 100
                    height: 50
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    border.color: "black"
                    TextField {
                        id: name
                        anchors.fill: parent
                        font.pointSize: 20
                        padding: 10
                        placeholderText: qsTr("name")
                        focus: true
                    }
                }
                Rectangle {
                    width: 350
                    height: 50
                    border.color: "black"
                    TextField {
                        id: message
                        anchors.fill: parent
                        font.pointSize: 20
                        padding: 10
                        placeholderText: qsTr("message")
                        focus: true
                    }
                }
                Button {
                    id: sendButton
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    text: qsTr("Send")
                    onClicked: {
                        chatClient.cppFuncSend(name.text + qsTr(" : ") + message.text)
                        message.text = qsTr("")
                    }
                }
            }
        }
    }
}
