import QtQuick 1.0

Item {
    id: symbolContainer
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
	    source: "quit.png"
	}
    }


    MouseArea {
	anchors.fill: parent
	onClicked: {
	    if (!symbolContainer.disabled)
		symbolContainer.clicked()
	}
    }

}
