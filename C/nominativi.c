/********************************************************************************************************************************************************
Traccia - Nominativi

Si vuole sviluppare un algoritmo per la generazione a caso di nominativi di persone. Una function a ogni chiamata visualizza un nominativo del tipo:

ROSSI ALDO nato a NAPOLI il 20 GENNAIO 1983. Si osservi che un nominativo è costituito da un campo Cognome, un campo nome, un campo Luogo di nascita un
campo Giorno di nascita, un campo Mese di nascita e un campo Anno di nascita. In particolare, un cognome deve essere scelto (a caso)
in un insieme (da prefissare, di 30 cognomi); un nome deve essere scelto (a caso) in un insieme (da prefissare, di 40 nomi);
un Luogo di nascita deve essere scelto (a caso) in un insieme (da prefissare, di 15 luoghi di nascita);
e così via fino all’anno che deve essere un intero da scegliere (sempre a caso) nell’insieme che va da 1930 a 2004.
Chiamare la function 50 volte e visualizzare i 50 nominativi casuali. Successivamente permettere all’utente di scegliere tra le seguenti opzioni:

    Ordinare in ordine alfabetico i nominativi
    Visualizzare tutti i nominativi nati nello stesso giorno fornito dall’utente

*********************************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>


#define NUM_COGNOMI 30
#define NUM_NOMI 40
#define NUM_LUOGHI 15
char *nominativi[50];

char *cognomi[NUM_COGNOMI] = {"ROSSI", "BIANCHI", "VERDI", "NORI", "FERRARI", "RUSSO", "ESPOSITO", "ROMANO", "GALLI", "MARCHETTI",
                              "MARIANI", "VILLA", "CONTI", "DELUCA", "BRUNO", "FONTANA", "MONTI", "BARBIERI", "MARTINI", "CARUSO",
                              "GRECO", "SANTORO", "LOMBARDI", "MORETTI", "COLLI", "MARINO", "GRECHI", "CAPUTO", "LOMBARDINI", "PARISI"};

char *nomi[NUM_NOMI] = {"ALDO", "GIUSEPPE", "MARIA", "ANNA", "LUCA", "GIULIA", "GIOVANNI", "MARIO", "FRANCESCA", "CARLO",
                        "ANDREA", "ROBERTO", "SIMONE", "FEDERICO", "MATTEO", "CHIARA", "SERENA", "RICCARDO", "ALESSANDRO", "GIORGIO",
                        "LAURA", "ELENA", "LUCIA", "PAOLA", "LUDOVICA", "STEFANO", "SARA", "EMANUELE", "ENRICO", "FABIO",
                        "MICHELE", "ALESSIO", "VINCENZO", "DANIELE", "FABRIZIO", "CLAUDIO", "DAVIDE", "ELISA", "SILVIA", "ROSSELLA"};

char *luoghi_nascita[NUM_LUOGHI] = {"NAPOLI", "MILANO", "ROMA", "TORINO", "PALERMO", "GENOVA", "BOLOGNA", "FIRENZE", "BARI", "CATANIA", "VENEZIA", "VERONA", "TARANTO", "BRESCIA", "CAGLIARI"};
//array di puntarori che contengono nomi cognomi e luoghi predefiniti, per generare nomi cognomi e luoghi casuali
void genera_nominativo(char *nominativo[]) {//funzione per generare i nominativi ha come input l'array di nominativi
    char cognome[20], nome[20], luogo[20];
    int giorno, mese, anno;

    strcpy(cognome, cognomi[rand() % NUM_COGNOMI]);//crea il cognome randomicamente, copiandolo nell'array in cognome
    strcpy(nome, nomi[rand() % NUM_NOMI]);//crea il nome randomicamente, copiandolo nell'array in nome
    strcpy(luogo, luoghi_nascita[rand() % NUM_LUOGHI]);//crea il luogo di nascità randomicamente, copiandolo nell'array luogo
    giorno = rand() % 31 + 1;//crea il giorno di nascità randomicamente
    mese = rand() % 12 + 1;//crea il mese di nascità randomicamente
    anno = rand() % (2004 - 1930 + 1) + 1930;//crea l'anno di nascità (genera un numero casuale nell'intervallo tra 1930 e 2004 inclusi).

    sprintf(nominativo, "%s %s nato a %s il %d %s %d.", cognome, nome, luogo, giorno,
        mese == 1 ? "GENNAIO" : mese == 2 ? "FEBBRAIO" : mese == 3 ? "MARZO" : mese == 4 ? "APRILE" :
        mese == 5 ? "MAGGIO" : mese == 6 ? "GIUGNO" : mese == 7 ? "LUGLIO" : mese == 8 ? "AGOSTO" :
        mese == 9 ? "SETTEMBRE" : mese == 10 ? "OTTOBRE" : mese == 11 ? "NOVEMBRE" : "DICEMBRE", anno);/* questa istruzione formatta una stringa contenente informazioni su una persona
        (nome, cognome, luogo e data di nascita) e la memorizza nella variabile */

}
void stampa_nominativi(char *nominativi[], int num_nominativi){/*questa funzione serve per stampare i nominativi ha come input l'array di nominativi e il numero totale dei nominativi
    ha come output la stampa di tutti i nominativi*/
    int i;
    for (i = 0; i < num_nominativi; i++) {//for per stampare tutti i nominativi
        nominativi[i] = malloc(100 * sizeof(char));/*questa istruzione alloca dinamicamente memoria per una stringa di caratteri di dimensione 100
        e assegna il puntatore risultante all'elemento i dell'array nominativi*/
        genera_nominativo(nominativi[i]);//richiamo la funzione per generare i nominativi
         printf("persona n:%i DATI DELLA PERSONA:%s\n",i, nominativi[i]);//stampo i nominativi
    }

}

void ordina_nominativi(char *nominativi[], int num_nominativi) {/*questa funzione serve per stampare i nominativi ordinati ha come input l'array di nominativi e il numero totale dei nominativi
    ha come output la stampa ordinata di tutti i nominativi*/
    int i, j, min_idx;
    char *temp;

    // algoritmo di ordinamento per ordinare i nominativi in ordine alfabetico
    for (i = 0; i < num_nominativi - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < num_nominativi; j++) {
            if (strcmp(nominativi[j], nominativi[min_idx]) < 0) {// Confronta l'elemento corrente con il minimo attuale
                min_idx = j;
            }
        }
        // scambio l'elemento minimo con l'elemento corrente
        temp = nominativi[min_idx];
        nominativi[min_idx] = nominativi[i];
        nominativi[i] = temp;
    }

    // Stampare i nominativi ordinati
    printf("\nNominativi ordinati per minimo:\n");
    for (i = 0; i < num_nominativi; i++) {
        printf("%s\n", nominativi[i]);
    }
}

void nominativi_stesso_giorno(char *nominativi[], int num_nominativi) {/*questa funzione serve per visualizzare tutti i nominativi nati nello stesso giorno fornito dall’utente
    ha come input l'array di nominativi e il numero totale di nominativi ha come output la stampa delle persone nate lo stesso giorno*/
    printf("Inserisci il giorno di nascita: ");
            int giorno;
            scanf("%d", &giorno);
            //inserisce e salva il giorno da ricercare
    int i;
    for (i = 0; i < num_nominativi; i++) {
        char nome[20], cognome[20], luogo[20];
        int giorno_nascita;
        sscanf(nominativi[i], "%s %s nato a %s il %d", cognome, nome, luogo, &giorno_nascita);// estrae i dati dal nominativo corrente
        if (giorno_nascita == giorno) {// controlla se il giorno di nascita del nominativo corrente corrisponde al giorno inserito dall'utente
            printf("%s\n", nominativi[i]);// Stampa il nominativo corrente se il giorno di nascita corrisponde
        }
    }
}
void gestione_opzioni(char *nominativi[], int num_nominativi) {/*questa funzione serve per le 2 opzioni di scelta dell'utente ha come input l'array di nominativi e il numero totale di nominativi*/
    int scelta;
    printf("\nScegli un'opzione:\n");
    printf("1. Ordina in ordine alfabetico i nominativi\n");
    printf("2. Visualizza tutti i nominativi nati nello stesso giorno fornito dall'utente\n");
    scanf("%d", &scelta);
    //salva la scleta dell'utente

    switch (scelta) {//switch per la scelta dell'utente
        case 1:
            ordina_nominativi(nominativi, num_nominativi);//richiamo funzione
            break;
        case 2: {
            nominativi_stesso_giorno(nominativi, num_nominativi);//richiamo funzione
            break;
        }
        default:
            printf("Opzione non valida.\n");
            break;
    }
}
void elimina(char *nominativi[]){/*questa funzione serve per deallocare memoria ha come input l'array di nominativi*/
    for (int i = 0; i < 50; i++) {
        free(nominativi[i]);
    }
}


int main() {
    srand(time(NULL));
    stampa_nominativi(nominativi,50);
    gestione_opzioni(nominativi, 50);
    elimina(nominativi);
    return 0;
}

