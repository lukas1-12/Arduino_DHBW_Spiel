# Interupt Analyse

Um einen reibungsfreien Programmablauf sicherzustellen, wurde die Dauer aller Interupts gemessen. Darüber hinaus wurde bei durch Timernutzung automatisch wiederholten Interupts die Frequenz aufgezeichnet. Dabei wurden die Taktzyklen gemessen. Anschließend wurde ein Mittelwert ermittelt und daraus die Zeit in Mikrosekunden berechnet. Ebenfalls wurde der Extremfall des Maximalwertes betrachtet, da dieser Wert für den Ablauf des Programms kritisch werden kann.

<div style="background: #AFAFAF; padding: 5px">
<iframe width=100% height=300px frameborder="0" scrolling="no" src="https://onedrive.live.com/embed?resid=A555585E24922B9A%215379&authkey=%21AAHF0hk_109KpvE&em=2&wdAllowInteractivity=False&wdHideHeaders=True&wdDownloadButton=True&wdInConfigurator=True&wdInConfigurator=True"></iframe>
Excel Tabelle: DOC_ENG_TA_Interupt_Messungen.xlsx
</div>

Dabei lässt sich festhalten, dass keiner der Werte krtisch groß wird. Der längste Interupt liegt bei 10,31 us, was bei einer Interupt-frequenz von 8 Hz (Taktdauer 0,125 s) 0,0082 % der Taktdauer entspricht.

In der folgenden Grafik ist die benötigte Zeitdauer der verschiedenen Interupts dargestellt. Dabei wurde ausschließlich beim ISR des Timer 1 (Matrix refresh) die Wiederholung des Interupts eingezeichnet, da bei allen anderen Interupts die Wiederholung eine Skalierung der Zeitachse benötigen würde, bei der die eigentliche Dauer der Interupts nicht mehr erkennbar wäre.

```puml
@startuml
robust "INT4 (Green Button)" as INT4
robust "INT5 (Red Button)" as INT5
robust "ISR Timer 1 (Matrix refresh)" as ISR1
robust "ISR Timer 3 (Debounce)" as ISR3
robust "ISR Timer 4 (Blink starting square)" as ISR4a
robust "ISR Timer 4 (Blink token)" as ISR4b
robust "ISR Timer 4 (Blink Winner)" as ISR4c
robust "ISR Timer 5 (Delay)" as ISR5
scale 25 as 100 pixels

@0
INT4 is inactive 
INT5 is inactive  
ISR3 is inactive 
ISR4a is inactive 
ISR4b is inactive 
ISR4c is inactive
ISR5 is inactive
ISR1 is inactive

@1 
INT4 is active
INT5 is active
ISR3 is active
ISR4a is active
ISR4b is active
ISR4c is active
ISR5 is active
ISR1 is active

@13
ISR5 is inactive

@18
ISR3 is inactive 

@46 
INT4 is inactive 

@53
INT5 is inactive 

@64
ISR4c is inactive

@67
ISR1 is inactive

@135
ISR4b is inactive 
ISR1 is active

@165
ISR4a is inactive 

@enduml
```

Selbstverständlich werden die Interuptroutinen auf dem ATMega2560 nicht gleichzeitig ausgeführt. Dabei unterbricht ein während einer anderen Interuptserviceroutine eintreffender Interupt die laufende Interuptserviceroutine nicht, sondern wird direkt im Anschluss ausgeführt. Entsprechend tritt auch kein Problem bei der Kombination des Matrix-Refresh Interupts mit dem Interupt des Timers 4, welcher für das Blinken des Hauses zuständig ist, auf. Der Matrix Interupt wird einfach im Anschluss ausgeführt, wobei der Jitter des Interupts  für den Benutzer nicht erkennbar ist. Dieser Fall ist in der nächsten Abbildung genauer betrachtet.

```puml
@startuml
robust "ISR Timer 1 (Matrix refresh)" as ISR1
robust "ISR Timer 4 (Blink starting square)" as ISR4a
scale 25 as 50 pixels

@0
ISR1 is inactive
ISR4a is inactive

@1 
ISR1 is active

@30
ISR4a is waiting

@67
ISR1 is inactive
ISR4a is active

@133
ISR1 is waiting

@232
ISR4a is inactive
ISR1 is active

@298
ISR1 is inactive

@364
ISR1 is active

@enduml
```