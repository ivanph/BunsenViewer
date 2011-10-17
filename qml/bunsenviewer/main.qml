import QtQuick 1.0
Item {
    width: 800
    height: 480

    Rectangle{
	width: parent.width; height: parent.height

	color: "white"

	Flickable {
	    x:0
	    y:0
	    width: parent.width; height: parent.height
	    contentWidth: image1.width; contentHeight: image1.height


            Image {
		id: image1
		x: 0
		y: 0
		source: CurrentImage

		onStatusChanged: {

		    if (image1.status == Image.Ready){
			imgLoading.opacity = 0
		    }else if (image1.status == Image.Loading){
			imgLoading.opacity = 1
		    }
		}

            }

            MouseArea {
                id: area_mouse
                x: 176
                y: 385
                anchors.fill: parent
                onClicked: btnNext.state.
            }
	}


	Image {
	    id: imgLoading
	    x: 0
	    y: 0
	    width: parent.width
	    height: parent.height
	    source: "loading.png"
            opacity: 0
        }

        Button{
                    id:btnRandom
                    opacity: 0.47
                    x: 360
                    y: 439
                    width: 71
                    height: 41
                    z: 6
                    imgNormal: "random.png"
                    imgPressed: "randomPressed.png"
                    onClicked: {
                        WMain.random()
                        //image1.source = CurrentImage;
                    }
        }

        Button{
            id:btnNext
            opacity: 0.47
            x: 498
                    y: 405
                    z: 5
                    imgNormal: "next.png"
                    imgPressed: "nextPressed.png"
                    onClicked: {
                        WMain.next()
                        //image1.source = CurrentImage;
                    }
        }

        Button{
            id:btnPrevious
            opacity: 0.47
            x: 213
            y: 400
            z: 7
            imgNormal: "previous.png"
            imgPressed: "previousPressed.png"
            onClicked: {
                WMain.previous()
                //image1.source = CurrentImage;
            }
        }

        Item {
            id: botones
            x: 176
            y: 385
            width: 449
            height: 95
            z: -1
        }






    }

}
