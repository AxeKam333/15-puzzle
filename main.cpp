#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

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

int ruch(int **T, int &a, int &b,int zamiana, int m, char czyt)
{
    if (czyt=='w')
    {
        if(a+1==m) return 2;
        else
        {
            up(T,a,b,zamiana);
            return 1;
        }
    }
    else if (czyt=='s')
    {
        if(a==0) return 2;
        else
        {
            down(T,a,b,zamiana);
            return 1;
        }
    }
    else if (czyt=='a')
    {
        if(b+1==m) return 2;

        else
        {
            left(T,a,b,zamiana);
            return 1;
        }
    }
    else if  (czyt=='d')
    {
        if(b==0) return 2;
        else
        {
            right(T,a,b,zamiana);
            return 1;
        }
    }
    else if (czyt=='x')
    {
        return 3;
    }
    else return 0;
}

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
                    color(14);
                    cout<<"0 ";
                    color(15);
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
                        color(14);
                        cout<<"00 ";
                        color(15);
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
    color(15);
    system("CLS");
    cout<<"Witaj w grze \"pietnastka\"! wybierz poziom trudnosci: ";
    int m;
    cin>>m;
    if (m<3)
    {
        cout<<"niestety to niemozliwe.";
        return 0;
    }
    else if (m>11)
    {
        cout<<"Zbyt epicki poziom trudnosci! ;)";
        return 0;
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
    //zrobic stringa ktory pozwoli na zapisywanie swojego wyniku i na cofanie ruchow.
    srand( time( NULL ) );
    for (int i=0;i<9000;i++)
    {
        ruch( T,a,b,T[a][b],m,int(rand()));
    }
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
