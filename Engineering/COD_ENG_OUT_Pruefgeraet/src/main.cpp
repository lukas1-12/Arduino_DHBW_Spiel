#include <Arduino.h>

// Pin für den Eingang des Taktsignals
const int inputPin = 2;

// Variable für die Anzahl der Interrupts
volatile unsigned long interruptCount = 0;

// Variable für die Zeitdauer, in der die Interrupts gezählt werden sollen (in
// Millisekunden)
const unsigned long measurementPeriod = 2000; // 2 Sekunden für 1,5 Hz

// Variable für die berechnete Frequenz (mit Nachkommastellen)
volatile double frequency = 0.0;

void countInterrupt();

void setup() {
  // Pin-Modus für den Eingang des Taktsignals einstellen
  pinMode(inputPin, INPUT);

  // Interrupt für steigende Flanke des Taktsignals aktivieren
  attachInterrupt(digitalPinToInterrupt(inputPin), countInterrupt, RISING);

  // Serielle Kommunikation starten
  Serial.begin(9600);

  // Ausgabe eines Header-Titels im Terminal
  Serial.println("Frequency Measurement");
}

void loop() {
  // Interrupts für die Messdauer zählen
  delay(measurementPeriod);

  // Frequenz berechnen (Anzahl der Interrupts pro Messdauer)
  frequency = (double)interruptCount / (measurementPeriod / 1000.0);

  // Ausgabe der Frequenz über die serielle Schnittstelle
  Serial.print("Measured Frequency: ");
  Serial.print(frequency, 3); // Anzeige der Frequenz mit 3 Nachkommastellen
  Serial.println(" Hz");

  // Interrupt-Zähler zurücksetzen
  interruptCount = 0;
}

// Funktion, die bei jedem Interrupt aufgerufen wird
void countInterrupt() { interruptCount++; }
