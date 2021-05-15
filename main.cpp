#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

void color(int x)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
    return;
}

void up(int **T, int &a,int b,int x)
{
    T[a][b]=T[a+1][b];
    T[a+1][b]=x;
    a++;
    return;
}

void down(int **T, int &a,int b,int x)
{
    T[a][b]=T[a-1][b];
    T[a-1][b]=x;
    a--;
    return;
}

void left(int **T, int a,int &b,int x)
{
    T[a][b]=T[a][b+1];
    T[a][b+1]=x;
    b++;
    return;
}

void right(int **T, int a,int &b,int x)
{
    T[a][b]=T[a][b-1];
    T[a][b-1]=x;
    b--;
    return;
}

int ruch(int **T, int &a, int &b,int zamiana, int m, char czyt)///poprosi jeszcze o stringa z zapisem i tam bedzie dokonywac zmian
{
    if (czyt=='w'||czyt=='W')
    {
        if(a+1==m) return 2;
        else
        {
            up(T,a,b,zamiana);
            return 1;
        }
    }
    else if (czyt=='s'||czyt=='S')
    {
        if(a==0) return 2;
        else
        {
            down(T,a,b,zamiana);
            return 1;
        }
    }
    else if (czyt=='a'||czyt=='A')
    {
        if(b+1==m) return 2;

        else
        {
            left(T,a,b,zamiana);
            return 1;
        }
    }
    else if  (czyt=='d'||czyt=='D')
    {
        if(b==0) return 2;
        else
        {
            right(T,a,b,zamiana);
            return 1;
        }
    }
    ///nalezy dodac jeszcze literke r ktora cofa ruch. bedzie wywolywala funkcje dla poprzedniej
    ///zapisanej w stringu literki po czym bedzie ja usuwala.
    else if (czyt=='x'||czyt=='X')
    {
        return 3;
    }
    else return 0;
}

///moze byc uzywana do uzywania nasionka

void ruch(int **T, int &a, int &b,int zamiana, int m, int los)
{
    char czyt;
    if (los%4==1) czyt='w';
    else if (los%4==2) czyt='s';
    else if (los%4==3) czyt='a';
    else czyt='d';
    ruch(T,a,b,T[a][b],m,czyt);
}

///zero - niepoprawna wartosc
///jeden - nastapila zamiana
///dwa - wartosc poprawna, nie nastapila zamiana
///trzy - zamknij program

void wyswietl(int **T,int m)
{
    system("CLS");
    cout<<"Pietnastka, poziom "<<m;
    cout<<"\nPrzesuwaj klocki na planszy za pomoca klawiszy w s a d.\n\'x\' oznacza wyjscie z gry.";
    cout<<"\n------------------------\n";
    if (m<4)
        for (int i=0; i<m; i++)
        {
            for (int j=0; j<m; j++)
            {
                if (T[i][j]==0)
                {
                    color(0);
                    cout<<"0 ";
                    color(7);
                }
                else
                    cout<<T[i][j]<<" ";
            }
            cout<<endl;
        }
    else if (m<11)
        for (int i=0; i<m; i++)
        {
            for (int j=0; j<m; j++)
                if (T[i][j]<10)
                    if (T[i][j]==0)
                    {
                        color(0);
                        cout<<"00 ";
                        color(7);
                    }
                    else cout<<"0"<<T[i][j]<<" ";
                else cout<<T[i][j]<<" ";
            cout<<endl;
        }
}

bool identyczne (int **T, int **F, int m)
{
    for (int i=0; i<m; i++)
        for (int j=0; j<m; j++)
        {
            if (T[i][j]!=F[i][j]) return false;
        }
    return true;
}

int main()
{
    color(9);
    system("CLS");
    cout<<"   _________                         __   \n";
    cout<<"  <  / ____/  ____  __  __________  / /__ \n";
    cout<<"  / /___ \\   / __ \\/ / / /_  /_  / / / _ \\\n";
    cout<<" / /___/ /  / /_/ / /_/ / / /_/ /_/ /  __/\n";
    cout<<"/_/_____/  / .___/\\__,_/ /___/___/_/\\___/ \n";
    cout<<"          /_/                             \n\n";
    color(7);
    cout<<"Witaj w grze \"Pietnastka\"!\nWybierz tryb gry:\n1 - spokojna gra";
    cout<<"\n2 - gra na czas\n3 - wczytaj plansze\n";
    int tryb;
    cin>>tryb;
    if (tryb<1||tryb>3)
    {
        cout<<"niestety to niemozliwe.";
        getch();
        main();
        return 0;
    }
    cout<<"Wybierz poziom trudnosci: ";
    int m;
    cin>>m;
    if (m<3||m>10)
    {
        cout<<"niestety to niemozliwe.";
        getch();
        main();
        return 0;
    }
    if (tryb==3)
    {
        cout<<"Wpisz nasiono gry: ";
        string wczyt;
        cin>>wczyt;
    }
    int ** T = new int * [m];
    for (int i=0; i<m; i++)
        T[i] = new int [m];
    int licz=1;
    for (int i=0; i<m; i++)
        for (int j=0; j<m; j++)
        {
            T[i][j]=licz;
            licz++;
        }
    T[m-1][m-1]=0;

    int ** F = new int * [m];
    for (int i=0; i<m; i++)
        F[i] = new int [m];
    licz=1;
    for (int i=0; i<m; i++)
        for (int j=0; j<m; j++)
        {
            F[i][j]=licz;
            licz++;
        }
    F[m-1][m-1]=0;

    int a=m-1,b=m-1;
    int ruchy;
    ///zrobic stringa ktory pozwoli na zapisywanie swojego wyniku i na cofanie ruchow.
    ///ustawienia, ktore na poczatku pozwalaja na zmiane kolorkow
    srand( time( NULL ) );
    if (tryb!=3)
    for (int i=0; i<1000; i++)
        ruch( T,a,b,T[a][b],m,int(rand()));
    else
        for (int i=0; i<wczyt.size();i++)
            ruch( T,a,b,T[a][b],m,wczyt[i]);

    wyswietl(T,m);
    for (;;)
    {
        ruchy=ruch( T,a,b,T[a][b],m,char( getch() ) );
        if (ruchy==3)
        {
            for (int i=0; i<m; i++)
                delete [] T[i];
            delete [] T;
            for (int i=0; i<m; i++)
                delete [] F[i];
            delete [] F;
            return 0;
        }
        else if (ruchy==0)
        {
            wyswietl(T,m);
            cout<<"NIEPOPRAWNA WARTOSC";
        }
        else if (ruchy==1 && a==m-1 && b==m-1 && identyczne(T,F,m))
        {

            wyswietl(T,m);
            cout<<"\nBrawo! Wygrales!!!\nCzy chcesz kontynuowac rozgrywke?";
            cout<<"\nWpisz \"tak\" lub program sie zakonczy.\n";
            string raz;
            cin>>raz;
            if (raz=="tak")
                main();
            for (int i=0; i<m; i++)
                delete [] T[i];
            delete [] T;
            for (int i=0; i<m; i++)
                delete [] F[i];
            delete [] F;
            return 0;
        }
        else if (ruchy==1)
        {
            wyswietl(T,m);
        }
        else if (ruchy==2)
        {
            wyswietl(T,m);
            cout<<"NIE MOZNA WYKONAC TEGO RUCHU";
        }


    }
}
