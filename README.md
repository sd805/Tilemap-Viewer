# Tilemap-Viewer
Quickly build a tilemap from a tileset and a CSV file.

## How to use
Create a CSV file with the cells mapping to tile numbers. (0 represents the top-left tile of the tileset)

![tilemap](https://user-images.githubusercontent.com/50186767/114266841-66eafc00-99ad-11eb-932c-fb46bf5ea27f.png)

Then load the tileset image and CSV file into the program. Specify how many pixels wide each tile is and click generate.

![tileoutput](https://user-images.githubusercontent.com/50186767/114266846-6c484680-99ad-11eb-8880-e1ebafb90150.png)

## Building
To build the program, open tilesetWidget.pro in Qt Creator (Qt 5.15.2), run qmake, and build.
