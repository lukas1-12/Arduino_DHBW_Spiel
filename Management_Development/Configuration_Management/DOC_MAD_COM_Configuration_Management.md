## Github Repository 

### Ordner-Struktur

Im Github Repository ist die nachfolgende Ordnerstruktur zu finden.

- Requirements 
- Design_Description
- Management_Development
- Test_Specification_Report
- Engineering

Es ist darauf zu achten, die Dateien im richtigen Ordner abzulegen. Die Ordner ```docs```, ```.devcontainer``` und ```.github``` dienen ausschließlich dem Ablegen von Konfigurationsdateien!

### Regeln zur Dateibenennung

Dateien müssen nach den folgenden Schema benannt werden:

```
<Dateityp>_<Ordnerkürzel>_<Kurzname>_<dateiname (individuell)>.<Dateiendung>
```

Dateityp:

  - ```DOC``` für Dokumentation
  - ```COD``` für Code. Bei Code reicht die Anwendung dieses Schemas auf den übergeordneten Ordner.
  - ```PIC``` für Bilder (nur falls zwingend notwendig für die Dokumentation!)
  - ```CAD``` für CAD-Dateien.

Ordnerkürzel:

  - Requirements: ```REQ```
  - Design_Description: ```DED```
  - Management_Development: ```MAD```
  - Test_Specification_Report: ```TES```
  - Engineering: ```ENG```

Kurzname: Kurzname, individuell. 2-3 Buchstaben.

Dateiname: ausgeschriebener Dateiname. Leerzeichen mit Unterstrich.

<div style="background: #8b0000; color: white; padding: 10px; margin: 10px;">
Eine korrekte Benennung der Dateien ist unerlässlich für das automatische Bauen der Projektwebsite.
</div>

### Github Codespace

Für die Programmierung der Spiellogik wurde ein Github Codespace eingerichtet. In diesem sind benötigte Abhängigkeiten für die Entwicklung der Spiellogik Bibliothek bereits vorinstalliert. Für die Programmierung des Gerätecodes eignet sich dieser Codespace jedoch weniger, da eine Anbindung von Hardwarekomponenten (Programmer) an den Codespace konfigurationsbedingt nicht möglich ist. Für diesen Fall empfielt sich die lokale Nutzung von PlatformIO auf einem Rechner mit Linux-basierten Betriebssystem.

Der Github Codespace verwendet die in der Datei ```.devcontainer/Dockerfile``` enthaltene Docker-Konfiguration. Diese kann alternativ zur Nutzung mit dem Github-Codespace auch als lokaler Docker-Container genutzt werden.

### CMake Organisation

Um die Spielelogik zu entwickeln und testen wird CMake verwendet. Die Header und Source Files der Logik befinden sich in einem Unterordner im lib-Verzeichnes (```Game_Logic```). Im gleichem Pfad befindet sich die erste von 2 CMakeLists.txt, diese gibt vor wie das Projekt gebaut werden muss und wo der Code der Logik und der Tests zu finden sind.
Die Logik wird mittels Catch2 Tests im Test-Verzeichnis auf Funktionsfähigkeit geprüft. In diesem Pfad befindet sich die zweite CMakeLists.txt, diese dient zur Konfiguration der Catch2-Tests. 
Das ganze Projekt kann durch den Befehl ```./runcmake.sh``` in der Kommandozeile gebaut werden. Dabei werden auch im Anschluss die erstellten Testdateien ausgeführt.

## Nutzung von PlatformIO für die Mikrocomputerprogrammierung

Für die Programmierung des Arduinos wurde die ```PlatformIO``` Extension für ```VSCode``` verwendet. Dies bietet insbesondere beim Einbinden und Verwalten von Bibliotheken enorme Vorteile gegenüber der ```ArduinoIDE```. PlatformIO bietet dabei eine Grafische Oberfläche zum Kompilieren und Flashen des Codes sowie einen Seriellen Monitor zum Auslesen der Seriellen Schnittstelle.

## Automatisches Bauen der Projektwebsite

Die Gesamte Projektdokumentation ist über eine Projektwebsite einsehbar. Diese Website wird bei jedem Push auf dem Main Branch automatisch neu gebaut. Für das Bauen der Website kommt das Programm ```mkdocs``` zum Einsatz. Dieses wurde so konfiguriert, dass eine Einbindung von in ```Mermaid``` oder ```PlantUML``` gezeichneten Grafiken möglich ist. ```mkdocs``` bezieht den Inhalt der Website aus den in den jeweiligen Ordnern gespeicherten Markdown-Dateien, die die Dokumentation enthalten. Diese werden beim Automatischen Bauen der Website zusammengesucht und für die Veröffentlichung in HTML umgewandelt. Darüber hinaus wird mit Doxygen eine Code-Dokumentation erzeugt, die dann ebenfalls über die Website einsehbar ist.

## Lokales Hosten der Projektwebsite

Zu Testzwecken kann es durchaus sinnvoll sein, die Projektwebsite temporär lokal zu Hosten, z.B. um die korrekte Einbindung von Grafiken zu testen. Im folgenden wird Schritt für Schritt erklärt, wie die Website lokal gehostet werden kann.

Die folgende Anleitung erklärt das Vorgehen bei der Verwendung von Linux oder MacOS. Für Windows-Nutzer empfielt sich die Nutzung des Windows Subsystem for Linux (WSL) oder des in der Datei ```.devcontainer/Dockerfile``` konfigurierten Docker-Containers.

In den folgenden Schritten wird davon ausgegangen, das ein Terminal-Fenster in der obersten Ebene der Ordnerstruktur des Projektes geöffnet wurde. Eventuell müssen Shell-Skripte mittels 
```bash
chmod +x <Pfad/Dateiname.sh>
```
ausführbar gemacht werden. Der Teil ```<Pfad/Dateiname.sh>``` ist dabei durch den Pfad und Dateinamen des betroffenen Shell-Skriptes zu ersetzen.

### Schritt 1: Installation von Doxygen

Mkdocs benötigt doxygen für das Bauen der Website. Mit 

```bash
doxygen --version
```

kann geprüft werden, ob doxygen bereits installiert ist. Sollte dies nicht der Fall sein, kann doxygen mit den Befehlen

```bash
sudo apt-get update
sudo apt-get install -y doxygen # Linux
```

installiert werden. Bei der Nutzung von MacOS empfielt sich die Nutzung von Homebrew, falls dieses bereits installiert ist:

```bash
brew install doxygen # MacOS
```

### Schritt 2: Erstellen eines Python Environments

Für das Erstellen eines Python Environments wurde ein Shell-Skript geschrieben, mit dem das Environment automatisch erstellt und konfiguriert wird. Dazu ist der folgende Befehl im Terminal einzugeben:

```bash
./docs/env_setup.sh
```

### Schritt 3: Erstellen und Hosten der Seite

Mit dem Skript

```bash
./docs/launch_site.sh
```

wird das soeben erstellte Python-environment automatisch gestartet und der Befehl ```mkdocs serve``` ausgeführt, welcher die Website unter ```http://127.0.0.1:8000/``` verfügbar macht.

Mit der Tastenkombination ```Strg```+ ```C``` (```control``` + ```C``` unter MacOS) kann Mkdocs wieder beendet werden. Zum erneuten Starten kann direkt bei Schritt 3 eingestiegen werden.

Darüber hinaus kann die Website mit 

```bash
./docs/copy_docs.sh
```

aktualisiert werden.

```bash
./docs/remove_docs.sh
```

räumt den ```docs/docs```-Ordner auf. Die Verwendung des Skriptes empfielt sich nach dem Abschluss der Arbeiten mit MkDocs.

<div style="background: #E0FFE0; padding: 10px; margin: 10px;">
<b>Tipp:</b> Alternativ zum Hosten der Seite kann auch der Quellcode erzeugt werden. Dazu muss zuerst das Python-Environment mittels <code>source docs/env/bin/activate</code> aktiviert werden. Anschließend kann durch Ausführen des Befehls <code>mkdocs build</code> im <code>docs/</code>-Ordner die Seite gebaut werden. Der Quellcode ist dann im Ordner <code>docs/site</code> zu finden.<br>
Diese Möglichkeit eignet sich zu Untersuchen der Dateistruktur und des Websiteaufbaus, ist aber zum Betrachten der Seite eher ungeeignet, da CSS-Stylesheets eventuell nicht korrekt verlinkt werden.
</div>

<div style="background: #8b0000; color: white; padding: 10px; margin: 10px;">
Automatisch generierte Ordner dürfen nicht auf das Repository gepusht werden!
</div>

## Onedrive

Da Github für die Verwaltung ausgewählter Dateitypen wie beispielsweise ```.xlsx```-Dateien eher ungeeignet ist, steht für diese Dateien als Ausweich-Option ein Onedrive-Ordner zur Verfügung. In diesem Ordner ist dieselbe Ordnerstruktur vorhanden, wie sie im Kapitel [Ordner-Struktur](#Ordner-Struktur) bereits für das Github-Repository erläutert wurde. 

<div style="background: #8b0000; color: white; padding: 10px; margin: 10px;">
Beim Ablegen einer Datei auf OneDrive ist darauf zu achten, im zugehörigen Teil der Dokumentation auf dem Git-Repository auf die Datei zu verweisen/-linken.
</div>
