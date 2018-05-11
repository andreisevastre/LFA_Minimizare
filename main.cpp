#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <set>

using namespace std;

map<char,int> *dfa,*dfamin,*dfa2;
map<char,int>::iterator it3;
set<int> stari_finale, *stari, stari_finale2;
set<int>::iterator it1,it2;
int ma[1000][1000];

typedef struct
{
    int x,y;
}coada;
coada D[1000];

int verificare(int a,int b,int ultim)
{
    for(int i=0;i<=ultim;i++)
    if(D[i].x==a && D[i].y==b || D[i].x==b && D[i].y==a)
    return 0;
    return 1;
}

int main(int argc, char **argv)
{
    int n,nf,s,st,ends,i,nr,j,k,prim,ultim;
    char c;
    freopen("fisier.in", "r", stdin);
                                              //CITIRE DATE INTRARE

    cin>>n>>nf>>s;


    for(i=0;i<nf;i++)
    {
        cin>>nr;
        stari_finale.insert(nr);
    }



    dfa=new map<char,int> [n];
    dfa2=new map<char,int> [n+1];

    while(!feof(stdin))  //st, c, end
         {
             cin>>st>>c>>ends;
             dfa[st].insert(pair<char,int>(c, ends));
             dfa2[st].insert(pair<char,int>(c, ends));
         }
        /*for(i=0;i<s;i++)
        {
            int simbol=97+i;   //codul ASCII
            for(j=0;j<n;j++)
            if(dfa[j].count(simbol) == 0)  //daca simbolul respectiv nu se gaseste in automat
                dfa2[j].insert(pair<char,int>(simbol, n));

        }*/
        /*for(i=0;i<s;i++)    //s = numarul de simboli
        {
            dfa2[n].insert(pair<char,int>(97+i, n));
        }*/

        n++;
        k=0;
    for(i=0;i<n;i++)
     for(j=i+1;j<n;j++)
      {
           it1 = stari_finale.find(i);
           it2= stari_finale.find(j);
           if((it1 != stari_finale.end() && it2==stari_finale.end()) || (it1 == stari_finale.end() && it2!=stari_finale.end()))
            {
                ma[i][j]=ma[j][i]=1;        //o casuta din matrice este 1 daca starile i si j pot fi distinse si 0 altfel
                D[k].x=i;                  // daca dint-o stare nefinala se poate ajunge intr o stare finala
                D[k++].y=j;
            }
      }



     prim=0;
     ultim=k-1;

     while(prim<=ultim)
     {
         for(int p=0;p<s;p++)
         {
             char simbol=97+p;
              for(i=0;i<n;i++)
              {
                  if (dfa2[i].count(simbol) != 0 && (dfa2[i].find(simbol)->second)==D[prim].x)
                   {
                       for(j=0;j<n;j++)
                       if (dfa2[j].count(simbol) != 0 && (dfa2[j].find(simbol)->second)==D[prim].y)
                        if(verificare(i,j,ultim))
                        {
                            D[++ultim].x=i;
                            D[ultim].y=j;
                            ma[i][j]=ma[j][i]=1;

                        }
                   }

              }
         }
         prim++;
     }



     /* for(i=0;i<n;i++)
      {
          for(j=0;j<n;j++)
          cout<<ma[i][j]<<" ";
          cout<<endl;
      }
      cout<<"\n\n";*/
n--;


  stari= new  set<int> [n];
  k=0;
  stari[k].insert(0);
     for(i=1;i<n;i++)
     {
          int gasit=0;
         for(j=0;j<i;j++)
            if(ma[i][j]==0)
            {

             for(int p=0;p<=k;p++)
             { it1 = stari[p].find(j);                 //crearea partitiilor
               if (it1 != stari[p].end())
               {
                   stari[p].insert(i);
                   gasit=1;
               }
            }
            }
         if(!gasit)
         {
             stari[++k].insert(i);
         }
     }
   /*cout<<"Partitiile sunt\n";

   for(i=0;i<=k;i++)
   {
       for (it1 = stari[i].begin(); it1 != stari[i].end(); it1++)
       cout<<*it1<<" ";
       cout<<endl;
   }*/

   k++;


   dfamin=new map<char,int> [k];                    // automatul minimizat

   k--;
   for(i=0;i<=k;i++)
   {
       for (it1 = stari[i].begin(); it1 != stari[i].end(); it1++)
       {
           it2 = stari_finale.find(*it1);
               if (it2 != stari_finale.end())
               stari_finale2.insert(i);

        for (it3 = dfa[*it1].begin(); it3 != dfa[*it1].end(); it3++)
        {
            nr=(*it3).second;
            for(j=0;j<=k;j++)
            {
               it2 = stari[j].find(nr);
               if (it2 != stari[j].end())
               break;
            }
             dfamin[i].insert(pair<char,int>( (*it3).first ,j));
        }
       }
   }
   //cout<<"\n\n";
   cout<<k+1<<" "<<stari_finale2.size()<<" "<<s<<endl;                              //afisarea finala
   for (it2 = stari_finale2.begin(); it2 != stari_finale2.end(); it2++)
            {
                cout << (*it2)<<" ";              //afiseaza starea finala
            }
   cout<<endl;
    for(i=0;i<=k;i++)
        {

            for (it3 = dfamin[i].begin(); it3 != dfamin[i].end(); it3++)
            {
                cout<<i<<" " << (*it3).first << " " << (*it3).second << endl;
            }

        }

        /* for(i=0;i<n;i++)
      {
          for(j=0;j<n;j++)
          cout<<ma[i][j]<<" ";
          cout<<endl;
      }
      cout<<"\n\n";*/

        return 0;
}


