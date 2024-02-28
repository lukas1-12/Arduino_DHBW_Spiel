## Github Repository 

### Ordner-Struktur

Im Github Repository ist die nachfolgende Ordnerstruktur zu finden.

- Requirements 
- Design_Description
- Management_Development
- Test_Specification_Report
- Engineering

Es ist darauf zu achten, die Dateien im richtigen Ordner abzulegen. Die Ordner ```docs``` und ```.github``` dienen ausschließlich dem Ablegen von Konfigurationsdateien!

### Regeln zur Dateibenennung

Dateien müssen nach den folgenden Schema benannt werden:

```
<Dateityp>_<Ordnerkürzel>_<Kurzname>_<dateiname (individuell)>
```

- Dateityp
  - ```DOC``` für Dokumentation
  - ```COD``` für Code. Bei Code reicht die Anwendung dieses Schemas auf den übergeordneten Ordner.
  - ```PIC``` für Bilder (nur falls zwingend notwendig für die Dokumentation!)
- Ordnerkürzel
  - Requirements: ```REQ```
  - Design_Description: ```DED```
  - Management_Development: ```MAD```
  - Test_Specification_Report: ```TES```
  - Engineering: ```ENG```
- Kurzname: Kurzname, individuell. 2-3 Buchstaben.
- Dateiname: ausgeschriebener Dateiname. Leerzeichen mit Unterstrich.

<div style="background: #8b0000; color: white; padding: 10px; margin: 10px;">
Eine korrekte Benennung der Dateien ist unerlässlich für das automatische Bauen der Projektwebsite.
</div>

### Github Codespace

Für die Programmierung der Spiellogik wurde ein Github Codespace eingerichtet. In diesem sind benötigte Abhängigkeiten für die Entwicklung der Spiellogik Bibliothek bereits vorinstalliert. Für die Programmierung des Gerätecodes eignet sich dieser Codespace jedoch weniger, da eine Anbindung von Hardwarekomponenten (Programmer) an den Codespace konfigurationsbedingt nicht möglich ist. Für diesen Fall empfielt sich die lokale Nutzung von PlatformIO auf einem Rechner mit Linux-basierten Betriebssystem.
  
## Nutzung von PlatformIO für die Mikrocomputerprogrammierung

Für die Programmierung des Arduinos wurde die ```PlatformIO``` Extension für ```VSCode``` verwendet. Dies bietet insbesondere beim Einbinden und Verwalten von Bibliotheken enorme Vorteile gegenüber der ```ArduinoIDE```. PlatformIO bietet dabei eine Grafische Oberfläche zum Kompilieren und Flashen des Codes sowie einen Seriellen Monitor zum Auslesen der Seriellen Schnittstelle.

## Automatisches Bauen der Projektwebsite

Die Gesamte Projektdokumentation ist über eine Projektwebsite einsehbar. Diese Website wird bei jedem Push auf dem Main Branch automatisch neu gebaut. Für das Bauen der Website kommt das Programm ```mkdocs``` zum Einsatz. Dieses wurde so konfiguriert, dass eine Einbindung von in ```Mermaid``` oder ```PlantUML``` gezeichneten Grafiken möglich ist. ```mkdocs``` bezieht den Inhalt der Website aus den in den jeweiligen Ordnern gespeicherten Markdown-Dateien, die die Dokumentation enthalten. Diese werden beim Automatischen Bauen der Website zusammengesucht und für die Veröffentlichung in HTML umgewandelt.

## Onedrive

Da Github für die Verwaltung ausgewählter Dateitypen wie beispielsweise ```.xlsx```-Dateien eher ungeeignet ist, steht für diese Dateien als Ausweich-Option ein Onedrive-Ordner zur Verfügung. In diesem Ordner ist dieselbe Ordnerstruktur vorhanden, wie sie im Kapitel [Ordner-Struktur](#Ordner-Struktur) bereits für das Github-Repository erläutert wurde. 

<div style="background: #8b0000; color: white; padding: 10px; margin: 10px;">
Beim Ablegen einer Datei auf OneDrive ist darauf zu achten, im zugehörigen Teil der Dokumentation auf dem Git-Repository auf die Datei zu verweisen/-linken.
</div>
