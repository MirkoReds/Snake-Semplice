//Snake semplice  - Rossi Mirko (4E)
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
// Termina il gioco
bool gameOver;
// Dimensioni mappa
const int width = 38;
const int height = 20;
// Posizione giocatore
int x, y;
// Posizione frutto
int fruitX, fruitY;
// Punteggio
int score;
// Posizione coda - Lunghezza
int tailX[100], tailY[100];
int nTail;
// Possibili direzioni che può assumere il serpente
enum eDirection {STOP = 0, LEFT,RIGHT, UP, DOWN};
// Controllo direzione
eDirection dir;
void MainMenu ()
{
    int exit=0,menu=0;
    while (exit==0)
    {
        cout<<"Snake by Rossi Mirko 4E - Informatica GALILEO GALILEI"<<endl<<endl;
        cout<<"1) Gioca a Snake "<<endl;
        cout<<"2) Esci dal programma"<<endl<<endl;
        cout<<"Scelta: ";
        cin>>menu;
        cout<<endl;
        switch (menu)
        {
        case 1:
            gameOver = false;
            menu=1;
            exit=1;
            break;
        case 2:
            cout<<"Grazie per aver utilizzato il programma!"<<endl<<endl;
            gameOver = true;
            menu=1;
            exit=1;
            break;
        default:
            cout<<"Hai inserito un opzione non valida!"<<endl<<endl;
            menu=0;
        }
    }
}
void Setup ()
{
    dir = STOP;                // ferma il serpente
    x = width / 2;             // centro mappa wid
    y = height / 2;            // centro mappa hei
    fruitX = rand()%width;     // pos. frutto cord. X
    fruitY = rand()%height;    // pos. frutto cord. Y
    score = 0;                 // pone a zero il risultato
}
void Draw () //Disegna la mappa di gioco e tiene conto del risultato
{
    system ("cls"); // system("clear"); LINUX pulisce lo schermo
    for (int i=0; i < width+2; i++)
            cout<<"#";
    cout<<endl;
    for (int i=0; i< height; i++)
    {
        for (int j=0; j<width; j++)
        {
            if (j==0)
                cout<<"#";
            if (i== y && j == x)
                cout<<"O";
            else if (i== fruitY && j == fruitX)
                cout<<"F";
            else
            {
                bool print = false; // variabile booleana che gestisce la stampa della coda
                for (int k=0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout<<"o";
                        print = true;
                    }
                }
                if (!print)
                    cout<<" ";
            }
            if (j == width -1)
                cout<<"#";
        }
        cout<<endl;
    }
    for (int i=0; i<width+2; i++)
        cout<<"#";
    cout<<endl;
    cout<<setw (24)<<"Punteggio: "<<score <<endl; // Stampa il risultato aggiornato
}
void Input ()
{
    if (_kbhit())         // ritorna 1 se premi un tasto
    {
        switch (_getch()) // prende in input un carattere per cambiare la direzione
        {
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'x':
            gameOver = true; //premendo X si può concludere il gioco !
            break;
        default:
            break;
        }
    }
}
void Logic ()
{
    // Coda del serpente
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;                // permette alla coda di seguire il resto del corpo in cordinata X
    tailY[0] = y;                // permette alla coda di seguire il resto del corpo in cordinata Y
    for (int i=1; i< nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) // muove la testa del verme a seconda dell'input
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x > width || x < 0 || y > height || y < 0) // uscita dal recinto
        gameOver = true;                           // termine del gioco
    for (int i =0; i< nTail; i++)
    {
        if (tailX[i]==x && tailY[i]==y)
                gameOver = true;   // suicidio del serpente in caso di contatto tra testa e coda
    }
    if (x == fruitX && y== fruitY) // frutto preso
    {
        nTail++;                   // aumenta la coda di un unità
        score += 10;               // aumenta di 10 il punteggio
        fruitX = rand()%width;     // spawna un frutto in cord X casuale
        fruitY = rand()%height;    // spawna un frutto in cord Y casuale
    }
}
string getFileContents (ifstream& File)
{
    string Lines = "";             //Tutte le linee
    if (File)                      //Controlla se è tutto apposto
    {
        while (File.good ())
        {
            string TempLine;                        //Linea temporanea
            getline (File , TempLine);              //Prende la linea temporeanea e la mette in File
            TempLine += "\n";                       //Va a capo dalla linea temporanea
            Lines += TempLine;                      //Crea un altra linea
        }
        return Lines;
    }
    else                                             //Return errore
    {
        return "ERRORE Il file non esiste !";
    }
}
void printFileContents ()
{
    system ("cls");
    if (nTail < 100)
    {
        ifstream Loser ("File1.txt");                //Apre file con arte ASCII "GAME OVER"
        string Art = getFileContents (Loser);        //Assume i valori ASCII
        cout << Art << endl;                         //Stampa la scritta
        Loser.close ();                              //Chiude il file di testo
    }
    if (nTail >= 100)
    {
        ifstream Winner ("File2.txt");               //Apre file con arte ASCII "WINNER" in caso che qualcuno finisca il gioco (coda a 100)
        string ArtW = getFileContents (Winner);      //Assume i valori ASCII
        cout << ArtW << endl;                        //Stampa la scritta
        Winner.close ();                             //Chiude il file di testo
    }
    cout<< "Punteggio Finale: "<<score <<endl<<endl<<endl; //Stampa il risultato finale
}
int main()
{
    MainMenu ();
    Setup ();
    while (gameOver==false)
    {
        Draw();
        Input();
        if (dir == LEFT || dir == RIGHT)
        {
            Sleep(5);
        }
        Sleep(100);
        if (dir == UP || dir == DOWN)
        {
            Sleep(60);
        }
        Logic();
    }
    printFileContents ();
    return 0;
}
