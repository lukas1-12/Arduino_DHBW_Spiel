## Test Cases

### Unittests mit dem Catch2 Framework
Die in der Spiellogik implementierten Funktionen werden durch einzelne Unittests auf fehlerfreie Funktionalität getestet. Diese Art von Test ermöglicht es, nicht funktionsfähige Codeabschnitte bereits während der Programmierung zu erkennen und frühzeitig einzugreifen. Ein wesentlicher Vorteil besteht darin, dass keine dedizierte Hardware für die Tests erforderlich ist. Dadurch kann jeder Programmierer unabhängig von der Verfügbarkeit spezifischer Hardware mit diesen Tests arbeiten.

### Test über die Debugging Schnittstelle
Um das Nachstellen von Szenarien auf dem Spielfeld zu vereinfachen und Zeit zu sparen, wurde eine externe Debugging-Schnittstelle für Tests entwickelt. Diese Schnittstelle ermöglicht es, Würfelwerte festzulegen, indem 3 Bits über Leitungen nach außen geführt werden. Durch die korrekte Schalterstellung können Würfelwerte zwischen 1 und 6 eingestellt werden. Hierfür muss der DICE_MODE in der defines.hpp auf den Wert 1 gesetzt werden. Zusätzlich bietet ein anderer Modus die Möglichkeit, verschiedene Zahlenwerte zwischen 1 und 6 in einem Array zu speichern. Anhand dieser Werte können Spiele und verschiedene Szenarien nachgestellt und getestet werden. Hierfür muss der DICE_MODE auf den Wert 2 gestellt werden.
Die Debugging-Schnittstelle zeigt zusätzlich den aktuellen Status des Zustandsgraphen auf den ersten 4 Bits an. Danach folgen zwei Bits für die Anzahl der Spieler und zwei Bits für die Anzahl der Computerspieler, die mithilfe von LEDs dargestellt werden. Im Spielmodus werden die ausgewählte Spielernummer und die ausgewählte Tokennummer auf den letzten 4 Bits angezeigt.

### Prüfgerät
Um die Blinkfrequenz des schnellen und langsamen Blinkens zu messen, wurde ein zusätzlicher Arduino als Messeinrichtung verwendet. Auf diesem Arduino wurde ein Code geschrieben, der die Zeiten zwischen den Flankenwechseln an seinem Eingang misst und daraus die Frequenz berechnet. Die Zeiten sowie die entsprechenden Frequenzen, in denen der Eingang High bzw. Low war, werden im Serial Monitor ausgegeben. Bei der Erstellung des Programmcodes lag der Fokus mehr auf der Lesbarkeit als auf der Effizienz, da dieser Code ausschließlich für das Prüfgerät und nicht in einem Serienprodukt verwendet wird.

### Testdokumentation

Die untenstehende Excel-Tabelle wurde verwendet, um die Testfälle zu strukturieren und zu dokumentieren. Die zu testenden Requirements wurden in verschiedene Testfälle aufgeteilt, die als Registerkarten im Excel-Fenster angezeigt werden. Darüber hinaus wurde ein Verification Control Document erstellt, in dem aufgeführt ist, welches Requirement in welchem Testfall getestet wurde.


<iframe width=100% height="600px" frameborder="0" scrolling="no" src="https://onedrive.live.com/embed?resid=A555585E24922B9A%215374&authkey=%21AAeusmggII6N7WQ&em=2&wdAllowInteractivity=False&wdDownloadButton=True&wdInConfigurator=True&wdInConfigurator=True"></iframe>