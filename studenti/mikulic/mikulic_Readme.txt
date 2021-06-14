##Opis programa:

![Screenshot molekule](https://ibb.co/gwT6sZ4)

Program prikazuje molekulu DNA čiji materijal simulira sjajnu plastiku, a napravljena je pomoću cjevčica.

* Na pritisak tipke R - počinje rotacija oko molekule i približavanje molekuli ako se prethodno ne isključi auto zoom
* Na pritisak tipke A - isključuje/uključuje se autozoom kod rotacije
* Na pritisak tipke W - približava se molekuli za vrijednost 0.05
* Na pritisak tipke S - udaljava se od molekule za vrijednost 0.05

##Opis izrade:

Vrijednosti prema kojima sam napravio zavojnicu(generate_helix) odabrao sam pomoću grafičkog kalkulatora - http://www.math3d.org/.
Vrijednosti sam dobio kao parametarsku krivulju.

Za modeliranje sam koristio cjevčice koje smo dobili u primjerima(sa songho.ca). Kao putanje(path) za cjevčice
interpolirao sam dobivene parametarske krivulje sa interpolacijskim funkcijama danim u primjerima. Vrijednosti za širinu
cjevčica su dobivene metodom pokušaj-promašaj.

Vektori za svjetlo i materijal su kombinacija vježbi, predavanja, lekcije(https://learnopengl.com/Lighting/Materials)
i mojeg ukusa kako bi to izgledalo što bliže zadanom materijalu(nadam se da sam pogodio).
Shadere sam preuzeo iz vježbi i malčice ih modificirao kako bih kasnije mogao dodati željenu boju.
Poziciju svjetla sam odabrao proizvoljno.

Kako bih omogućio kretanje oko DNA molekule napravio sam klasu Animation koja sadrži enable(pokrenuto ili ne),
time(vrijeme, pošto se rotacija događa uz pomoć vremena), radius(daljina iz koje se gleda - potrebno za zoom),
autoZoom(kada se pokrene rotacija samostalno će se zumirati ili neće) i naravno metode koje se koriste/kontroliraju te
varijable.

Za renderiranje komplementarnih parova modeliranih kao cjevčice sam napravio metodu(draw_nucleotides) u kojoj se crtaju
dvije poprečne cjevčice od jedne zavojnice do sredine i od sredine do druge zavojnice za svaku drugu točku zavojnice.
Svakoj od cjevčica se pridodjeljuje boja zavisno od rednoga broja točke(najjednostavnija implementacija).

GLFWova key_callback implementacija funkcije(https://www.glfw.org/docs/3.3/input_guide.html#input_key) mi je poslužila
za procesuiranje pritisnutih tipki.

Izrađeno u CLionu 2021.1.2 sa akademskom licencom na Ubuntu 20.04.2 LTS.
Github repo: https://github.com/mikulicmateo/DNAMolecule-OpenGL