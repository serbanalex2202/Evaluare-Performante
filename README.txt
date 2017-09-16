Tema Ep Serban Alexandru 341 C5

ex1.
a) Crearea Fisierului cu numere 
Am iterat de la 0 pana la N si pentru fiecare i am generat un umar folosind functia de hash, la fiecare itaratie scriu in fisier.
Functia de Hash am implmentat-o recursiv.

b) Calcului Medianei
Am deschis fisierul cu numere am citit toate numerele intr-o lista.
Am folosit un algoritm de selectie pentru a calcula mediana in O(n).
Algoritmul l-am gasit aici https://discuss.codechef.com/questions/1489/find-median-in-an-unsorted-array-without-sorting-it

c) Abaterea de la Standard
Am citit din fisier toate valorile intr-o lista.
Am calculat media acestora.
Am calculat abaterea fiecarui punct.
Le-am adunat si am impartit la cate sunt afland astfel dispersia.
iar Abaterea de la standard reprezinta sqrt(dispersie).
Pentru calcului abaterii de la standard am urmarit algoritmul descris aici : 
https://en.wikipedia.org/wiki/Standard_deviation

ex2. Crearea scriptului
Am sters datele generate de la rulari precedente
Am iterat cu i prin cele 4 limitari de memorie 1024 512 256 128
Am iterat descrescator deoarece am intampinat o problema : 
nu aveam dreptul sa maresc limita de memorie, nu aveam drepturi
Am pornit utilitarele vmstat iostat si mpstat in threaduri separate apoi am pornit prgroamul principal
Am asteptat cu “wait” terminarea threadurilor create
Am modificat fiserele cu date pastrand doar ce am nevoie pentru grafice


ex3. Crearea Graficelor
Am modificat fisierele cu date pentru a avea doar informatiiloe necesare graficelor
Am selectat coloanele de interes din fiserele cu date
Am atribuit ca nume indicii de interes
In urma generarii graficelor am salvat pe rand fiecare grafic ca imagine si le-am introdus in PDF

Analiza rezultatelor : am intampinat niste rezultate contradictorii pe care le-am explicat cat de bine am putut si am scris la sfarsitul raportului modul in care programul ar fi trebuit sa se comporte