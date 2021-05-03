#include <iostream>
#include <windows.h>
#include <conio.h>

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
        return 4;
    }
    else return 0;
}

///zero - niepoprawna wartosc
///jeden - nastapila zamiana
///dwa - wartosc poprawna, nie nastapila zamiana
///trzy - nastapila zmiana, nastapila wygrana
///cztery - zamknij program

void wyswietl(int **T,int m)
{
    system("CLS");
    cout<<"Pietnastka, poziom "<<m;
    cout<<"\nPrzesuwaj klocki na planszy za pomoca klawiszy w s a d.\n\'x\' oznacza wyjscie z gry.";
    cout<<"\n------------------------\n";
    if (m<4)
    {
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
    }
    else if (m<11)
    {
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
}

int main()
{
    color(15);
    cout<<"Witaj w grze \"pietnastka\"! wybierz poziom trudnosci: ";
    int m;
    cin>>m;
    if (m<2)
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

    int a=m-1,b=m-1;
    int ruchy;
    char czyt;
    //zrobic stringa ktory pozwoli na zapisywanie swojego wyniku i na cofanie ruchow.
    wyswietl(T,m);
    for (;;)
    {
///zero - niepoprawna wartosc
///jeden - nastapila zamiana
///dwa - wartosc poprawna, nie nastapila zamiana
///trzy - nastapila zmiana, nastapila wygrana
///cztery - zamknij program
        czyt=getch();
        ruchy=ruch(T,a,b,T[a][b],m,czyt);
        if (ruchy==4)
        {
            for (int i=0; i<m; i++)
                delete [] T[i];
            delete [] T;
            return 0;
        }
        else if (ruchy==0)
        {
            wyswietl(T,m);
            cout<<"NIEPOPRAWNA WARTOSC";
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
