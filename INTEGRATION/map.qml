import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

Rectangle{
    property double oldLat:25.6585
    property double oldLng:100.3658
    Plugin{
    id: mapPLugin
     name: "osm"
}
    Map{
        id:mapview
        anchors.fill:parent
        plugin: mapPLugin
        center:QtPositioning.coordinate(oldLat, oldLng);
        zoomLevel: 10
    }
function setCenter(lat,lng){
mapview.pan(oldLat - lat, oldLng - lng)
    oldLat = lat
    oldLng = lng
}

}
