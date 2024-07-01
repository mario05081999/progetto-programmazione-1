/******************************************************************************************************************************
Traccia - Distributore carburante

Si vuole simulare la gestione di un distributore automatico di carburante. Si suppone di avere 3 tipi di carburante
identificati da un nome, da un codice identificativo, dal numero di litri presenti nella scorta e da un prezzo per litro.

Permettere all’utente di:

    Inserire dei soldi (5,10, 20, 50 euro)
    Scegliere il tipo carburante
        Controllare se è possibile soddisfare la richiesta
        Nel caso è possibile soddisfare la richiesta rifornire di carburante (aggiornando la scorta)
    Periodicamente controllare i prodotti sotto scorta (minore di 10 litri)
    Dato un tipo di carburante visualizzare il giorno in cui si è avuto la massima vendita.

*******************************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Definizione della struttura del carburante
typedef struct {
    char nome[20];
    int codice;
    int litri;
    float prezzo;
    int max_vendita_giorno[7];
} Carburante;

// funzioni per aggiornare la scorta del carburante hanno come input la struttura e i litri aggiunti o erogati dal distributore
void rifornisci_carburante(Carburante *carburante, int litri_levati) {
    carburante->litri -= litri_levati;
}
void rifornisci_carburante1(Carburante *carburante, int litri_aggiunti) {
    carburante->litri += litri_aggiunti;
}
// funzione per registrare una transazione e aggiornare la massima vendita giornaliera ha come input la struttura i litri erogati e il giorno
void registra_transazione(Carburante *carburante, int litri, int giorno) {
    if (litri > carburante->max_vendita_giorno[giorno - 1]) {
        carburante->max_vendita_giorno[giorno - 1] = litri;// nota: Si sottrae 1 da 'giorno' perché gli indici dell'array partono da 0
    }
}

// funzione per ottenere la massima vendita di un carburante in un giorno specifico ha come input la struttura e il giorno ha come output il massimo numero di litri venduti nel giorno specificato
int massima_vendita_giorno(Carburante *carburante, int giorno) {
    return carburante->max_vendita_giorno[giorno - 1];// nota: Si sottrae 1 da 'giorno' perché gli indici dell'array partono da 0
}

/* funzione per controllare se è possibile soddisfare la richiesta ha come input la struttura e i litri richiesti
ha come output true se la quantità di carburante disponibile è sufficiente per soddisfare la richiesta,false altrimenti*/
bool controlla_disponibilita(Carburante *carburante, int litri_richiesti) {
    return carburante->litri >= litri_richiesti;
}

// funzione per controllare i prodotti sotto scorta ha come input la struttura e come input il nome del carburante sotto scorta
void controlla_scorta(Carburante *carburante) {
    if (carburante->litri < 10) {
        printf("Il carburante %s e' sotto scorta!\n", carburante->nome);
    }else{
         printf("Il carburante %s non e' sotto scorta!\n", carburante->nome);
    }
}

int main() {
    // inizializzazione dei carburanti
    Carburante benzina = {"Benzina", 1, 50, 1.5, 0};
    Carburante diesel = {"Diesel", 2, 40, 1.3, 0};
    Carburante gasolio = {"Gasolio", 3, 60, 1.2, 0};

    // variabile per tenere traccia del giorno corrente
    int giorno_corrente = 1;
    float soldi=0;
    // loop principale
    while (true) {
        int scelta;
        //scelta delle opzioni
        printf("\n1. Inserire soldi (5, 10, 20, 50 euro)\n");
        printf("2. Scegliere tipo carburante\n");
        printf("3. Controllare prodotti sotto scorta\n");
        printf("4. Rifornire il distributore\n");
        printf("5. Massimo giorno\n");
        printf("6. Servizio finito\n");
        printf("7. Uscita\n");
        printf("Scegli un'opzione: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1: {
                // implementazione inserimento soldi
                printf("Inserisci soldi (5, 10, 20, 50 euro): ");
                scanf("%f", &soldi);
                printf("soldi inseriti\n");
                break;
            }
            case 2: {
                //controlo per vedere se sono stati caricati dei soldi
                if (soldi !=5 && soldi !=10 && soldi!=20 && soldi!=50) {
        printf("Devi inserire soldi prima di poter fare il rifornimento.\n");
        break;
                }
                // implementazione scelta tipo carburante
                int tipo_carburante;
                printf("\nScegli il tipo di carburante:\n");
                printf("1. Benzina\n");
                printf("2. Diesel\n");
                printf("3. Gasolio\n");
                printf("Scelta: ");
                scanf("%d", &tipo_carburante);

                Carburante *carburante_scelto;

                // assegnamento del carburante scelto
                switch (tipo_carburante) {
                    case 1:
                        carburante_scelto = &benzina;
                        break;
                    case 2:
                        carburante_scelto = &diesel;
                        break;
                    case 3:
                        carburante_scelto = &gasolio;
                        break;
                    default:
                        printf("Scelta non valida.\n");
                        continue;
                }

                // implementazione rifornimento carburante
                int litri_richiesti;
                printf("Inserisci i litri richiesti: ");
                scanf("%d", &litri_richiesti);
                // Calcolo del costo totale del carburante richiesto
                float costo_totale = litri_richiesti * carburante_scelto->prezzo;

                if (controlla_disponibilita(carburante_scelto, litri_richiesti)&& soldi >= costo_totale ) {//richiamo della funzione
                        soldi -= costo_totale;
                    rifornisci_carburante(carburante_scelto, litri_richiesti);//richiamo della funzione
                    registra_transazione(carburante_scelto, litri_richiesti, giorno_corrente);//richiamo della funzione
                    printf("l'auto e' stata riempita con %i litri di %s\n",litri_richiesti,carburante_scelto->nome);
                // Calcolo e stampa del resto
                if (soldi > 0) {
                printf("Resto: %.2f euro\n", soldi);
                soldi = 0; // Azzeramento dei soldi dopo aver stampato il resto
        }
                } else {
                    printf("Carburante non disponibile o soldi insufficienti.\n");
                    soldi=0;
                }

                break;
            }
            case 3: {
                // implementazione controllo prodotti sotto scorta
                //richiami delle funzioni
                controlla_scorta(&benzina);
                controlla_scorta(&diesel);
                controlla_scorta(&gasolio);
                break;
            }
            case 4: {
                 // implementazione scelta tipo carburante
                int tipo_carburante1;
                printf("\nScegli il tipo di carburante:\n");
                printf("1. Benzina\n");
                printf("2. Diesel\n");
                printf("3. Gasolio\n");
                printf("Scelta: ");
                scanf("%d", &tipo_carburante1);

                Carburante *carburante_scelto;

                // assegnamento del carburante scelto
                switch (tipo_carburante1) {
                    case 1:
                        carburante_scelto = &benzina;
                        break;
                    case 2:
                        carburante_scelto = &diesel;
                        break;
                    case 3:
                        carburante_scelto = &gasolio;
                        break;
                    default:
                        printf("Scelta non valida.\n");
                        continue;
                }
                //implementazione del rifornimento del distributore
                 int litri_richiesti1;
                printf("Inserisci i litri che vuoi aggiungere: ");
                scanf("%d", &litri_richiesti1);
               rifornisci_carburante1(carburante_scelto, litri_richiesti1);//richiamo della funzione
               printf("il distributore e' stato riempito con %i litri di %s\n",litri_richiesti1,carburante_scelto->nome);;
               break;
            }
            case 5: {
                 // implementazione scelta tipo carburante
                int tipo_carburante2;
                 printf("\nScegli il tipo di carburante:\n");
                printf("1. Benzina\n");
                printf("2. Diesel\n");
                printf("3. Gasolio\n");
                printf("Scelta: ");
                scanf("%d", &tipo_carburante2);

                Carburante *carburante_scelto;

                // assegnamento del carburante scelto
                switch (tipo_carburante2) {
                    case 1:
                        carburante_scelto = &benzina;
                        break;
                    case 2:
                        carburante_scelto = &diesel;
                        break;
                    case 3:
                        carburante_scelto = &gasolio;
                        break;
                    default:
                        printf("Scelta non valida.\n");
                        continue;
                }
                //implementazione della massima vendita chiedendo in input il nome del carburante e il giorno
                int giorno_ricerca;
    printf("Inserisci il giorno per cui desideri visualizzare la massima vendita (1-7): ");
    scanf("%d", &giorno_ricerca);
    if (giorno_ricerca >= 1 && giorno_ricerca <= 7) {
                int max_vendita = massima_vendita_giorno(carburante_scelto, giorno_ricerca);//richiamo della funzione
                float costo_totale_vendita = max_vendita * carburante_scelto->prezzo;
    printf("Massima vendita di %s nel giorno %d: %d litri\n", carburante_scelto->nome, giorno_ricerca, max_vendita);
    printf("guadagno massimo ottenuto nel giorno %d: %.2f euro\n", giorno_ricerca, costo_totale_vendita);
    }else{
        printf("Errore: Il giorno inserito non e' valido. Inserisci un giorno compreso tra 1 e 7.\n");
    }
                break;
            }
            case 6: {
                //implementazione del giorno seguente
                giorno_corrente = (giorno_corrente % 7) + 1;
                printf("\n e' il giorno:%i",giorno_corrente);
                break;
            }
            case 7: {
                // uscita dal programma
                printf("Uscita dal programma.\n");
                return 0;
            }
            default:
                printf("Scelta non valida.\n");
                break;
        }
    }
}


