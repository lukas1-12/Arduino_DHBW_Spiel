# Projektbeschreibung 

## DHBW – Student ärgere dich nicht 

Dieses Projekt befasst sich mit der Wiederauferstehung eines alten Klassikers. Es geht um das alt bekannte Brettspiel „Mensch ärgere dich nicht“. Ein Spiel, dass so ziemlich jeder zu Hause hat, vermutlich aber selten zum Einsatz kommt. Gerade bei den jüngeren Generationen fehlt einfach der Reiz, einen Spieleabend, mit einem etwas in die Jahre gekommenen Brettspiel zu verbringen. Wir von der DHBW – Spielschmiede AG, haben es uns zur Aufgabe gemacht, dieses Spiel neu aufleben zu lassen. Wir vereinigen den alten Charm des Klassikers mit moderner Technik. Ein Mikrocontroller, der den gesamten Spielablauf übernimmt. Einzig die Spieleinstellung, das Würfeln und die Auswahl der Figur, die bewegt werden soll, muss man selbst vornehmen. Schummeln, Meinungsverschiedenheiten oder verlorene Spielfiguren sind somit Geschichte. Auch das Spielen gegen einen Computer ist nun möglich. All das kompakt und praktisch verstaut in einem Gehäuse. 

Mit unserem Produkt schließen wir eine unentdeckte Marktlücke, die nun wirklich ein Spiel für Jung und Alt hervorbringt. 

## Bedienungsanleitung

Die Bedienungsanleitung (Dokument DOC_DED_OUT_Betriebsanleitung.pdf) kann [hier](https://1drv.ms/b/s!AporkiReWFWlqhW5HBnykQcEO_Me?e=MIdUqp) angesehen und heruntergeladen werden.

## Begründung der Hardwareauswahl:

Bei der Hardwareauswahl wurden zunächst verschiedene Ansätze für die Anzeige des Spielfeldes sowie die Auswahl des geeigneten Mikrocontrollers in Betracht gezogen. Es wurde sowohl eine selbstgebaute LED-Anzeige aus einzelnen Leuchtdioden, als auch eine fertige Matrix-LED in Erwägung gezogen. Durch Recherche kristallisierten sich jedoch erhebliche Vorteile der LED-Matrix gegenüber der selbstgebauten Anzeige heraus. Das Team hat gemeinsam beschlossen, aufgrund des hohen Fertigungsaufwands und der hohen Kosten im Vergleich zu einer fertigen Matrix-Anzeige, die im Internet erhältlich ist, auf den eigenen Bau einer Matrix-Anzeige zu verzichten. Die Matrix-Anzeige aus dem Internet bietet zudem einige Vorteile in Bezug auf die Einfachheit der Programmierung sowie die leichte Wiederbeschaffbarkeit.

Bei der Auswahl des Mikrocontrollers wurde zunächst zwischen einem Arduino Mega und einem Arduino Uno geschwankt. Im weiteren Verlauf der Planung stellte sich jedoch heraus, dass der Arduino Uno nicht über ausreichend Timer verfügt, weshalb die Entscheidung auf den Arduino Mega fiel. Ein weiteres entscheidendes Kriterium für den Arduino Mega war die erhöhte Anzahl an Ein- und Ausgangspins, die zukünftige Erweiterungsmöglichkeiten für das Spielgerät ermöglichen.