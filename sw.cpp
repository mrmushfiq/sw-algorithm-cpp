//SW algorithm
//Md Mushfiqur Rahman
//Physics Department, FAU

#include <iostream>
#include <istream>
#include <ostream>
#include <cstdio>
#include <armadillo> // Using Armadillo library for linear algebra. Easy to install in linux
#include <new>
#include <fstream>
#include <cmath>
#include <complex>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

using namespace std;
using namespace arma;



int main()
{
  int Ham,ro,coll,k,v;

   string seq1 ="IISAIFLLKEEEGALI";
   string seq2 ="AISLIFSLEVEVGAL";

 char s1[200];
 char s2[200];
 strcpy(s1,seq1.c_str());
 strcpy(s2,seq2.c_str());
 ro = seq1.length() + 1;   // 1 row and column extra for 0s
 coll = seq2.length() + 1;
 mat H = zeros<mat>(ro,coll);  //Filling up the matrix with zeros

// leaving first row and column as zero and rest of them are 1 or 0

//cout<<ro<<"--"<<coll<<endl;

  for (k=1;k<=ro-1;k++){
    for (v=1;v<=coll-1;v++)
    {
        if(s1[k-1] == s2[v-1])
        H(k,v)= 1.0 ;
    }
  }

for(int i=1; i<=ro-1; i++)
   {
   for(int j=1; j<=coll-1; j++)
    {

        if (H(i-1,j-1) != 0)
        {
        if (H(i,j)==1)
        H(i,j) += H(i-1,j-1);
        else
        {
        H(i,j) += H(i-1,j-1)-0.33;
        if (H(i,j) < 0) H(i,j)=0.0;
        }

         }

    }
   }

int c =1;

for (int j=1; j<=coll-1; j++)
   {
   for (int i=1; i<=ro-1; i++ )
    {

       if (H(i-1,j) >= 0.3)
       {

         if (c==1)
          H(i,j) = H(i-1,j) - (1 + 0.3*c) > H(i,j) ? H(i-1,j) - (1 + 0.3*c) : H(i,j);
          else
          H(i,j) = H(i-1,j) - 0.33 > H(i,j) ? H(i-1,j) -  0.33 : H(i,j);

          c++;
          if(H(i,j) <= 0) { H(i,j) = 0; c=1;}

          }
          }
    }

for (int i=1; i<=ro-1; i++)
   {
   for (int j=1; j<=coll-1; j++ )
    {

       if (H(i,j-1) > 0.3)
       {

         if (c==1)
          H(i,j) = H(i,j-1) - (1 + 0.3*c) > H(i,j) ? H(i,j-1) - (1 + 0.3*c) : H(i,j);
          else
          H(i,j) = H(i,j-1) - 0.33 > H(i,j) ? H(i,j-1) -  0.33 : H(i,j);

          c++;
          if(H(i,j) < 0) { H(i,j) = 0.00; c=1;}

          }
          }
    }


ofstream out;
out.open("sw.txt");

 for(int j=0; j<=coll-2; j++)
  {
    if (j==0) {
            out<<"             "<<s2[j]<<"  |  ";
    }
    else if(j<coll-2)
     {
     out<<s2[j]<<"   |  ";
     }
  else{
        out<<s2[j]<<endl;
    out<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
     }
    }

for(int i=0; i<=ro-1; i++)
   { if(i < 1) {out<<"    ";}
    else
      out<<s1[i-1]<<" | ";

   for(int j=0; j<=coll-1; j++)
    {
      out<<fixed << showpoint <<setprecision(2)<<H(i,j)<<" | ";
    } out<<endl
    <<"-------------------------------------------------------------------------------------------------------------------"<<endl;
   }
out.close();
cout<<"Final matrix is printed in SW.txt"<<endl;
}
