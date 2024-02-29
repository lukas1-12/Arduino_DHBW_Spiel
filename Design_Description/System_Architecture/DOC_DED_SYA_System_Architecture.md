# Systemarchitektur:
Der grundlegende Gedanke unser Projekt aufzubauen war der, dass wir die Spielelogik und das Anzeigen auf der LED-Matrix jeweils in einer Bibliothek implementieren. Dadurch kam für uns das MVC-Modell für unsere Systemarchitektur infrage. 


### Modell View Controller:
- 1 - Modell (Model):
Die Bibliothek für die Spielelogik könnte als das "Modell" betrachtet werden. Sie enthält die grundlegenden Regeln und Zustände des Spiels, wie die Spiellogik, Spielzustände, Spielerpositionen usw.

- 2 - Ansicht (View):
Die Bibliothek für die Anzeige auf der LED-Matrix könnte als die "Ansicht" betrachtet werden. Sie ist verantwortlich für die Darstellung des aktuellen Zustands des Spiels auf der Benutzeroberfläche (in diesem Fall auf der LED-Matrix). Sie kümmert sich um die visuelle Darstellung des Spielbretts, Spielerfiguren und anderer Spielinformationen.

- 3 - Controller:
Die main.cpp könnte als der "Controller" betrachtet werden. Er handelt die Benutzereingaben ab, koordiniert die Interaktion zwischen Modell und Ansicht und aktualisiert den Spielzustand entsprechend. Der Controller entscheidet, welche Aktionen basierend auf Benutzereingaben oder dem aktuellen Zustand des Spiels ausgeführt werden sollen, und ruft entsprechende Funktionen im Modell auf, um den Zustand des Spiels zu ändern. Er kann auch die Ansicht aktualisieren, um Änderungen im Spielzustand widerzuspiegeln.


In diesem Sinne ähnelt undere Systemarchitektur dem MVC-Muster, wobei die Spielelogik das Modell darstellt, die Bibliothek für die Anzeige die Ansicht und die main.cpp den Controller. Es ist jedoch wichtig anzumerken, dass diese Analogie möglicherweise nicht perfekt passt, da das MVC-Muster hauptsächlich für die Entwicklung von Benutzeroberflächen in herkömmlichen Anwendungen konzipiert ist, während unser System auf die Steuerung eines physischen Spiels abzielt. Dennoch bietet das MVC-Muster eine nützliche Struktur, um die Verantwortlichkeiten der Komponenten zu organisieren.