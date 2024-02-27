# Interupt Analyse

Um einen reibungsfreien Programmablauf sicherzustellen, wurde die Dauer aller Interupts gemessen. Darüber hinaus wurde bei durch Timernutzung automatisch wiederholten Interupts die Frequenz aufgezeichnet. Dabei wurden die Taktzyklen gemessen. Anschließend wurde ein Mittelwert ermittelt und daraus die Zeit in Mikrosekunden berechnet. Ebenfalls wurde der Extremfall des Maximalwertes betrachtet, da dieser Wert für den Ablauf des Programms kritisch werden kann.

<iframe width=100% height=300px frameborder="0" scrolling="no" src="https://onedrive.live.com/embed?resid=A555585E24922B9A%215379&authkey=%21AAHF0hk_109KpvE&em=2&wdAllowInteractivity=False&wdHideHeaders=True&wdDownloadButton=True&wdInConfigurator=True&wdInConfigurator=True"></iframe>

Dabei lässt sich festhalten, dass keiner der Werte krtisch groß wird. Der längste Interupt liegt bei 10,31 us, was bei einer Interupt-frequenz von 8 Hz (Taktdauer 0,125 s) 0,0082 % der Taktdauer entspricht.
