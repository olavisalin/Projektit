// 284132 Olavi Salin olavi.salin@tuni.fi
/* Documentataatio: Tämä ohjelma on toteutus hanoin torni -pelistä käyttöliittymällä.
 * Käynnistäessä ohjelman, aukeaa ikkuna, jossa on pelialue, jossa kolme eriväristä
 * paalua, close-nappula, start-nappula, palikoiden määrän asetus spinboxi ja
 * tekstikenttä, joka kertoo mitä pitää tehdä. Peli alkaa kiekkojen määrän valitsemi-
 * sella spinboxista, jossa oletuksena on arvo 6. Pienin arvo kiekkojen määrälle on 1
 * ja suurin 20. Maksimiraja on asetettu sen takia, että kiekkojen lisääminene
 * pysyy yksinkertaisena. (jos kiekon korkeus kertaa kiekkojen määrä > tapin pituus,
 * pitäisi kiekkojen korkeutta pienentää niin, että kaikki kiekot mahtuvat tappiin.
 * Sama myös kiekkojen leveyden suhteen. Tätä ei sinänsä olisi ollut vaikea toteuttaa
 * mutta peliä ei todellisuudessa ole järkevää pelata edes tuolla maksimimäärä 20
 * kiekolla, koska siirtoja vaaditaan niin paljon. Siksi asetin kiekkojen määrälle
 * jonkin maksimin.) Kun kiekkojen määrä on valittu tai tyydytty oletusarvoon
 * painetaan nappia 'start'. Nyt kiekot ilmestyvät pelialueelle, ja osa alareunassa
 * olevista liikuttelunapeista aktivoituu. Myös ajastin alkaa laskemaan sekunteja.
 * Painamalla jotakin liikuttelunappia(jos mahdollista) napin yläpuolella olevasta
 * paalusta siirretään ylin kiekko napin osoittamaan toiseen torniin. (Oletetaan,
 * että pelaaja ymmärtää mihin torneihin 1, 2 ja 3 viittaavat). Pelin voi aloittaa
 * alusta uudella/samalla kiekko määrällä milloin tahansa painamalla start-nappia.
 * Vastaavasti pelin voi sulkea milloin tahansa painamalla close-nappia. Kun pelaaja
 * voittaa, eli saa kaikki kiekot laillisesti joko vihreään tai siniseen tappiin,
 * ajastin pysähtyy ja liikuttelunapit epäaktivoituvat":D". Pelaajalle kerrotaan
 * voitosta ja myöskulunut aika minuutteina ja sekunteina. Voiton jälkeen taas voidaan
 * aloittaa uudestaan painamalla starttia tai lopettaa leikki close-napilla.
 */

#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
