# Binary Search
Ein kleines Programm, dass die folgende Aufgabenstellung loesen soll.

**Aufgabenstellung**:
Eine Stadtbibliothek verwaltet ein großes Archiv an Büchern. Jedes Buch in der
Bibliothek ist durch eine eindeutige ISBN (International Standard Book Number)
identifizierbar, die immer in aufsteigender Reihenfolge in der Datenbank gespeichert
ist. Die Bibliothekssoftware soll es den Mitarbeitern und Besuchern ermöglichen, ein
bestimmtes Buch effizient zu finden, indem sie nur die ISBN eingeben. Da die
Datenbank sehr groß ist und neue Bücher ständig hinzugefügt werden, muss der
Suchalgorithmus so effizient wie möglich gestaltet sein


## Nr. 1
*Implementiere einen Binary-Search-Algorithmus in C oder Java, um die ISBN eines
bestimmten Buches in einer sortierten Liste von ISBNs zu finden. Der
Algorithmus soll den Index der gesuchten ISBN zurückgeben, falls sie in der
Liste vorhanden ist, oder -1, falls das Buch nicht gefunden wurde.*

Testweise habe ich dafuer die Funktion `binary_search` in *main.c* geschrieben,
um erstmal die konkrete Logik hinter dem Algorithmus aufgeschrieben zu haben.
Anschliessend habe ich eine `struct Book` definiert, die sowohl Author, den
Title des Buches als auch die ISBN in form eines 64 bit integers beinhaltet.
Diese befindet sich in der Datei *book.c*. 
Die Array-Liste in *array_list.c* sollte sich dann um das Hinzufuegen der
einzelnen Buecher kuemmern, sowie eine Moeglichkeit die Elemente
allgemeingueltig in ihr sortieren zu lassen. Je nach dem, welche
*Vergleichsfunktion* man einsetzt, konnte man die Liste entsprechend sortieren
und auch nach Werten suchen (siehe `do_sort_array` `do_search_array`).
Mittlerweile habe ich wieder vergessen, warum ich dafuer eine eigene Array-List
implementiert habe, aber sie scheint in gewissem Masse zu funktionieren (wenn
auch sehr inneffizient!).
Durch das abstrakte design kann ich nun flexible auswaehlen, nach welchen
Kriterien ich die Liste durchsuchen und sortieren kann.

## Nr. 2
*Erkläre, warum der Binary-Search-Algorithmus für diese Aufgabe besser geeignet
ist als eine lineare Suche. Gehe hierbei auf die Zeitkomplexität des
Algorithmus ein und vergleiche sie mit der Zeitkomplexität einer linearen
Suche.*

Der *Binary Search* Algorithmus ist bei weitem der schnellste der
Such-Algorithmen. Der einzige Nachteil ist, dass die Liste, in der man etwas
sucht, sortiert sein muss. Fuer eine Buecherdatenbank empfiehlt es sich, da man
die zeitlichen Ressourcen hat, die es benoetigt um die Liste vorzusortieren.
Gerade bei grossen Datensammlungen koennten andere Suchalgorithmen weitaus
langsamer und grosse Mengen an Zeit verbrauchen, bis sie ein Ergebnis haben. Im
Vergleich zu einer Linearen-Suche beispielsweise, deren Zeitkomplexitaet bei
O(n) liegt (n ist die Anzahl der Elemente in der Liste), liegt die
Zeitkomplexitaet bei der Binary Search bei O(log n). Dadurch faellt diese
wesentlich geringer aus.

## Nr. 3
*Die Bibliothek möchte auch nach Büchern suchen, die bestimmten anderen
Kriterien entsprechen, z.B. nach einem bestimmten Autor oder Titel.
Diskutiert, wie der Binary-Search-Algorithmus modifiziert oder mit anderen
Algorithmen kombiniert werden könnte, um solche Suchen effizient zu
unterstützen.*

Wie bereits erwaehnt habe ich die Array-Liste und den Sortier- und
Suchmechanismus moeglichst flexibel und modular zu gestalten, sodass man
lediglich eine Vergleichsfunktion angeben muss, die die Art und Weise wie etwas
sortiert wird aendert. So kann man fuer jede Option (Autor, Titel, ISBN)
einfach eine gewuenschte Funktion uebergeben, die eben nach diesen Werten
optimiert und schliesslich eine, die nach diesen Werten sucht. Fuer den
Binary-Search Algorithmus ist es essentiel, dass die Liste sortiert ist,
weshalb man vor einer Suche unbedingt einen Sortieralgorithmus laufen lassen
muss, um ein schnelles und vor allem richtiges Ergebnis erzielen zu koennen.

## Nr. 4
Hierzu habe ich 100.000 Mal die `add_array` Funktion eines frisch initialisiertem
Array aufgerufen und eine instanziierte Book struct uerbergeben, die jeweils eine
zufaellige ISBN zugeteilt bekommen. Anschliessend wird das Array dementsprechend
sortiert und der Index der ISBN 12345678 gesucht. 
Auch hier gehort dazu gesagt, dass man das so in der Form niemals machen sollte. 
Um das zu erreichen alloziiert man nun den benoetigten Platz fuer die 100.000
(in `init_turbo_array`) Buecher, setzt die Werte des Arrays wie Laenge, Groesse
der Elemente und den Pointer zu dem alloziierten Bereich. Nun ueberschreibt
man diese Arbeitsspeicherregion mit den Testwerten.

Bei einer Suche in einer Liste, die nicht den Wert 123456789 beinhaltet
benoetigt das Programm 17-18 Iterationen.
Wenn der Wert tatsaechlich vorliegt, benoetigt das Programm zwischen
15 und 19 Iterationen.

Der Iterationscounter wird mit jedem weiteren Aufruf der `do_sort_array`
Funktion inkrementiert.
