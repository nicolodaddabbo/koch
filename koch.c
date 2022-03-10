/****************************************************************************
 *
 * koch.c -- Curva di Koch
 *
 * Copyright (C) 2021, 2022 Moreno Marzolla
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************************/

/***
% LabASD - Fiocco di neve di Koch
% Moreno Marzolla <moreno.marzolla@unibo.it>
% Ultimo aggiornamento: 2022-03-07

(Crediti: prof. [Violetta Lonati](http://lonati.di.unimi.it/), Università di Milano)

![Niels Fabian Helge von Koch By Olof Edlund, Public Domain, <https://commons.wikimedia.org/w/index.php?curid=10118465>](Helge_von_Koch.jpg)

## Libreria `libpsgraph.c`

Questo esercizio fa uso della libreria `libpsgraph` che consente di
produrre dei semplici grafici in
[PostScript](https://en.wikipedia.org/wiki/PostScript). Per usare
la libreria si può procedere come segue:

* creare una directory (si può usare la directory corrente);

* salvare in essa i file [libpsgraph.c](libpsgraph.c) e
  [libpsgraph.h](libpsgraph.h);

* scrivere la propria applicazione (che nel nostro caso è il file
  [koch.c](koch.c)), che include all'inizio la direttiva

        #include "libpsgraph.h"

* compilare il programma con il comando

        gcc -std=c90 -Wall -Wpedantic libpsgraph.c koch.c -lm -o koch
  (attenzione alla necessità di linkare la libreria matematica usando
  il flag `-lm`; su Code::Blocks non dovrebbe essere necessario fare
  nulla di particolare, dato che la libreria matematica dovrebbe essere
  linkata di default).

## Funzioni fornite dalla libreria

La libreria permette di disegnare usando le funzioni della ["turtle
graphics"](https://en.wikipedia.org/wiki/Turtle_graphics); il disegno
prodotto viene salvato in formato PostScript su un file, il cui nome
va specificato prima di iniziare a disegnare. Il file essere
visualizzato con un apposito programma; se non ne avete uno già
installato, si può caricare il file su [questa pagina
Web](https://ehubsoft.herokuapp.com/psviewer/).

La libreria va usata in questo modo:

* per prima cosa, si invoca la funzione `start(nomefile)` passando
  come parametro il nome del file in cui si vuole che il grafico venga
  salvato, ad esempio `start("prova.ps");`

* a questo punto è possibile disegnare usando le funzioni seguenti,
  che accettano un parametro di tipo `double`:

  * `draw(x)`: disegna un segmento lungo $x$ millimetri;

  * `move(x)`: si sposta (senza disegnare) di un segmento lungo $x$ millimetri;

  * `turn(x)`: ruota di $x$ gradi in senso orario;

* alla fine, occorre invocare la funzione `end()`.

All'inizio, la "tartaruga" è orientata verso destra in orizzontale;
quindi, se la prima istruzione è `draw(10)` ci si trova con un
segmento orizzontale di lunghezza 10 orientato da sinistra verso
destra.

Ad esempio, il programma seguente disegna un quadrato:

```C
#include "libpsgraph.h"

int main( void )
{
    start("square.ps");
    draw(100); turn(90);
    draw(100); turn(90);
    draw(100); turn(90);
    draw(100);
    end();
    return 0;
}

```

## Curva di Koch

Realizzare una funzione che, data una lunghezza in millimetri $x$ e un
intero $n \geq 0$ produce la _curva di Koch_ di ordine $n$ e di
"lunghezza" $x$; per "lunghezza" qui si intende la lunghezza della sola
base.

La curva di Koch prende il nome dal matematico svedese Niels Fabian
Helge von Koch, che l'ha studiata per primo, ed è definita come segue:

* se $n = 0$, la curva è un segmento di lunghezza $x$;

* se $n > 0$, la curva è ottenuta concatenando quattro curve di Koch
  di ordine $n-1$ e di lunghezza $x/3$, disposte come mostrato in
  Figura 1.

![Figura 1: Curve di Koch dall'ordine $n=0$ (in basso) fino a $n=4$ (in alto)](koch-curve.png)

Le curve in Figura 1 sono state ottenute con $x=50$.

## Fiocco di neve di Koch

Realizzare ora una funzione che, data una lunghezza in millimetri $x$
e un intero $n \geq 0$, produce il _fiocco di neve di Koch_ di ordine
$n$: esso si ottiene da un triangolo equilatero i cui lati siano
costituiti da curve di Koch di ordine $n$ e lunghezza $x$ (Figura 2).

![Figura 2: Fiocco di neve di Koch di ordine $n=4$](koch-snowflake.png)

Il fiocco di neve di Koch in Figura 2 è stato ottenuto da tre curve di
Koch di lunghezza $x=50$ e ordine $n=4$.

## Domande

- Sia $K(n)$ il numero complessivo di invocazioni della funzione
  `koch()` necessarie per disegnare la curva di Koch di ordine
  $n$. Quindi si ha $K(0)=1$, dato che la funzione viene invocata una
  sola volta quando $n=0$; $K(1)=5$ dato che la funzione viene
  invocata una volta con $n=1$ e quattro volte con $n=0$; e così
  via. Scrivere una espressione chiusa (cioè non ricorsiva) per $K(n)$
  (Suggerimento: si può partire da una espressione ricorsiva ed
  espandere i primi termini per individuare l'espressione chiusa).

- Dati $x$ e $n$, qual è la lunghezza complessiva della curva
  disegnata dalla chiamate `koch(x, k)`? Per "lunghezza complessiva"
  si intende la somma delle lunghezze di tutti i segmenti che la
  compongono.

## File

- [koch.c](koch.c)
- [libpsgraph.c](libpsgraph.c)
- [libpsgraph.h](libpsgraph.h)

***/
#include <stdio.h>
#include <stdlib.h>
#include "libpsgraph.h"

/* Disegna la curva di Koch di ordine n e lunghezza x */
void koch(double x, int n)
{
  if (n == 0) {
    draw(x);
  } else if (n > 0) {
    koch(x/3, n-1);
    turn(-60);
    koch(x/3, n-1);
    turn(120);
    koch(x/3, n-1);
    turn(-60);
    koch(x/3, n-1);
  }
}

void fiocco(double x, int n) {
  koch(x, n);
  turn(120);
  koch(x, n);
  turn(120);
  koch(x, n);
}


int main( void )
{
    /* L'esempio seguente disegna un quadrato, e serve per prendere
       familiarità con la libreria `libpsgraph`.  Modificare il codice
       per disegnare la curva di Koch, completando la funzione koch(x,
       n) definita sopra e invocandola opportunamente (si suggerisce
       di usare n=4). */
    /*
    start("square.ps");
    draw(100); turn(90);
    draw(100); turn(90);
    draw(100); turn(90);
    draw(100);
    end();
    */

    start("koch.ps");
    koch(50, 4);
    end();   
    start("fiocco.ps");
    fiocco(50, 4);
    end();   
    return EXIT_SUCCESS;
}
