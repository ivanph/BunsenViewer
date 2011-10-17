import QtQuick 1.0

Item {
    id: symbolContainer
    property bool disabled: false
    property alias imgNormal: imgNormal.source
    property alias imgPressed: imgPressed.source
    signal clicked

    width: 80
    height: 80

    Rectangle {
	id: normal
 color: "#00000000"
	anchors.fill: parent
	smooth: true
	/*gradient: Gradient {
	    GradientStop { position: 0.0; color: "#DDDDDD" }
	    GradientStop { position: 1.0; color: "#AAAAAA" }
	}*/

	Image {
	    id: imgNormal
	    anchors.fill: parent
	}
    }

    Rectangle {
	id: pressed
 color: "#00000000"
	anchors.fill: parent
	smooth: true
	opacity: 0
	/*gradient: Gradient {
	    GradientStop { position: 0.0; color: "#666666" }
	    GradientStop { position: 1.0; color: "#AAAAAA" }
	}*/

	Image {
	    id: imgPressed
	    anchors.fill: parent
	}
    }

    MouseArea {
	anchors.fill: parent
	onClicked: {
	    if (!symbolContainer.disabled)
		symbolContainer.clicked()
	}
	onPressed: {
	    if (!symbolContainer.disabled)
		symbolContainer.state = "Pressed"
	}
	onReleased: {
	    if (!symbolContainer.disabled)
		symbolContainer.state = ""
	}
    }

    states: [
	State {
	    name: "Pressed"
	    PropertyChanges { target: pressed; opacity: 1 }
	}
    ]
    transitions: Transition {
	NumberAnimation { properties: "opacity"; duration:500 }
    }
}
