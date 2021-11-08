#include <iostream>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <typeinfo>
#include <set>
#include <vector>
#include <list>
#include <map>

using namespace std;
ifstream fin("mag.in");
ofstream fout("mag.out");

class Client;
class Comanda; /// has-a Produs
class Produs;
class Livrare;
class AfisareStatut; ///interfata
class PaletaMachiaj;///is-a
class Buze; ///is-a
class Taxe; ///clasa abstracta

class Livrare
{private:
    string nume_firma;
    string nume_curier;
    string nr_telefon;
    int nr_livrari;
    float *distanta_livrare;
    const int idCurier;
public:
    static int contorIdCurier ;
     Livrare();
     ~Livrare();
     Livrare(const Livrare& l);
     Livrare(string nr_telefon);
     Livrare(string nume_firma,string nume_curier,string nr_telefon,int nr_livrari,float *distanta_livrare);
     friend istream& operator>> (istream& in, Livrare & l);
     friend ifstream& operator>> (ifstream& in, Livrare & l);
     friend ostream& operator<<(ostream& out,const  Livrare& l);
     const Livrare& operator++();
     const Livrare operator++(int);
     bool operator==(Livrare l);
     bool operator<(Livrare l);
     Livrare operator+(Livrare l);
     Livrare operator-(Livrare l);
     Livrare operator=(Livrare);
     float &operator[](int);
     explicit operator float(){return (float)this->distanta_livrare[0];}
     void bonus();
     string get_nr_telefon(){return this->nr_telefon;}
     int get_id_curier(){return this->idCurier;}

};
int Livrare::contorIdCurier=1000;
Livrare::Livrare():idCurier(contorIdCurier++)
{
    this->nume_firma="Firma";
    this->nume_curier="Curier";
    this->nr_telefon="?";
    this->nr_livrari=0;
    this->distanta_livrare=new float[1];
    this->distanta_livrare[0]=0;
}
Livrare::~Livrare()
{
     if(this->distanta_livrare!=NULL)
         delete[] this->distanta_livrare;
}
Livrare:: Livrare(const Livrare &l):idCurier(contorIdCurier++)
 {  this->nume_firma=l.nume_firma;
    this->nume_curier=l.nume_curier;
    this->nr_telefon=l.nr_telefon;
    this->nr_livrari=l.nr_livrari;
    this->distanta_livrare=new float[1];
    this->distanta_livrare[0]=l.distanta_livrare[0];
}
Livrare::Livrare(string nume_firma,string nume_curier,string nr_telefon,int nr_livrari,float *distanta_livrare):idCurier(contorIdCurier++)
{
    this->nume_firma=nume_firma;
    this->nume_curier=nume_curier;
    this->nr_telefon=nr_telefon;
    this->nr_livrari=nr_livrari;
    this->distanta_livrare=new float[1];
    this->distanta_livrare[0]=distanta_livrare[0];
}
Livrare::Livrare(string nr_telefon):idCurier(contorIdCurier++)
{
    this->nume_firma="Firma";
    this->nume_curier="Curier";
    this->nr_telefon=nr_telefon;
    this->nr_livrari=0;
    this->distanta_livrare=new float[1];
    this->distanta_livrare[0]=0;
}
const Livrare Livrare::operator++(int)
{
    Livrare  aux(*this);
    this->nr_livrari++;
    return aux;
}
const Livrare& Livrare::operator++()
{
    this->nr_livrari++;
    return *this;

}
Livrare Livrare:: operator=(Livrare l)
{ if(this!=&l)
    {if(this->distanta_livrare!=NULL)
                delete[] this->distanta_livrare;
    this->nume_firma=l.nume_firma;
    this->nume_curier=l.nume_curier;
    this->nr_telefon=l.nr_telefon;
    this->nr_livrari=l.nr_livrari;
    this->distanta_livrare=new float[1];
    this->distanta_livrare[0]=l.distanta_livrare[0];
    }
return *this;

}
 bool Livrare:: operator==(Livrare l)
{
        if((nr_telefon==l.nr_telefon)&&(nume_curier==l.nume_curier)&&(nume_firma==l.nume_firma)&&(nr_livrari==l.nr_livrari)&&(distanta_livrare[0]==l.distanta_livrare[0]))
            return true;

    return false;
}
 bool Livrare:: operator<(Livrare l)
{
        if(nume_curier<l.nume_curier)
            return true;

        return false;
}
Livrare Livrare::operator+(Livrare l)
{   Livrare aux(*this);
    aux.nr_livrari=l.nr_livrari+aux.nr_livrari;
    return aux;
}
Livrare Livrare::operator-(Livrare l)
{
   Livrare aux(*this);
   aux.nr_livrari=aux.nr_livrari-l.nr_livrari;
   return aux;

}
float & Livrare::operator[](int i)
{
    if(i==0)
        return distanta_livrare[i];
    else
        exit(0);

}
void Livrare:: bonus()
{
    if(this->nr_livrari%100==0 and this->nr_livrari>0)
        cout<<"Curierul nr."<<this->idCurier<<" va primi bonus de 300 de lei";

}

istream& operator>> (istream& in, Livrare & l)
 {   cout<<"Numele firmei: ";
    in>>l.nume_firma;
    cout<<"Nume curier: ";
    in>>l.nume_curier;
    cout<<"Numar telefon curier: ";
    in>>l.nr_telefon;
    cout<<"Numar livrari efectuate: ";
    in>>l.nr_livrari;
    cout<<"Distanta comanda: ";
    in>>l.distanta_livrare[0];
    return in;
}
ifstream& operator>> (ifstream& in, Livrare & l)
 {
    getline(in,l.nume_firma);
    getline(in,l.nume_curier);
    in>>l.nr_telefon;
    in>>l.nr_livrari;
    in>>l.distanta_livrare[0];
    return in;
}
ostream& operator<<(ostream& out, const Livrare& l)
 {
    out<<"\nNumele curierului: "<<l.nume_curier;
    out<<"\nNumar telefon curier: "<<l.nr_telefon;

    return out;

}
class Taxe
{protected:
    float procentTVA;
public:
     Taxe();
     ~Taxe();
     Taxe(const Taxe& tx);
     Taxe(float procentTVA);
     Taxe&operator=(const Taxe &tx);
     friend istream& operator>> (istream& in, Taxe & tx);
     friend ostream& operator<<(ostream& out,const  Taxe& tx);
     virtual ostream& AfisareVirtuala(ostream& out)const;
     virtual istream& CitireVirtuala (istream& in);
     friend ifstream& operator>> (ifstream& in, Taxe & tx);
     virtual ifstream& CitireVirtuala (ifstream& in);
     float set_TVA(float x){this->procentTVA=x; return this->procentTVA;}
     virtual float pretFaraTVA()=0;
};
Taxe::Taxe()
{
   this->procentTVA=0.19;
}
Taxe::~Taxe(){}

Taxe:: Taxe(const Taxe &tx)
{
    this->procentTVA=tx.procentTVA;
}

Taxe::Taxe(float procentTVA)
{
    this->procentTVA=procentTVA;

}
Taxe&Taxe:: operator =(const Taxe& tx)
{
    if(this!=&tx)
    {
        this->procentTVA=tx.procentTVA;

    }
    return *this;
}
istream& Taxe::CitireVirtuala(istream& in){

    cout<<"Procentul de TVA este: ";
    in>>this->procentTVA;

    return in;

}

ostream& Taxe::AfisareVirtuala (ostream& out) const{

    out<<"\nProcentul de TVA este: "<<procentTVA;

    return out;


}

istream& operator>>(istream & in,Taxe& tx)
{
    return tx.CitireVirtuala(in);
}
 ostream& operator<<(ostream & out,const Taxe& tx)
{
    return tx.AfisareVirtuala(out);
}
ifstream& operator>>(ifstream & in,Taxe& tx)
{
    return tx.CitireVirtuala(in);
}

ifstream& Taxe::CitireVirtuala(ifstream& in){

    in>>this->procentTVA;
    in.ignore();
    return in;

}

class Produs:public Taxe
{private:
    string marca;
    string nume_produs;
    int nr_ingrediente;
    string *ingrediente;
    double greutate;
    int valabilitate;
    int in_stoc;
    float pret;
    const int idProdus;
public:
     static int contorIdProdus;
     Produs();
     Produs(string marca,string nume_produs,int nr_ingrediente,string *ingrediente,
            double greutate,int valabilitate,int in_stoc,float pret,float procentTVA);
     Produs(const Produs&);
     ~Produs();
     Produs(string marca,string nume_produs,float procentTVA);
     const Produs& operator--();
     const Produs operator--(int);
     Produs operator=(Produs);
     Produs operator+(Produs p);
     Produs operator-(Produs p);
     bool operator==(Produs p);
     bool operator<(const Produs p)const;
     const Produs& operator+=(float);
     string&operator[](int);
     explicit operator int(){return (int)this->pret;}
     void set_marca(string marca) { this->marca=marca;}
     string get_marca(){return marca;}
     void set_nume_produs(string nume_produs) { this->nume_produs=nume_produs;}
     string get_nume_produs(){return nume_produs;}
     void set_greutate(double greutate) { this->greutate=greutate;}
     double get_greutate(){return greutate;}
     void set_pret(double pret) { this->pret=pret;}
     double get_pret(){return pret;}
     void set_valabilitate(int valabilitate) { this->valabilitate=valabilitate;}
     int get_valabilitate(){return valabilitate;}
     void set_in_stoc(int in_stoc) { this->in_stoc=in_stoc;}
     int get_in_stoc(){return in_stoc;}
     void set_nr_ingrediente(int nr_ingrediente) { this->nr_ingrediente=nr_ingrediente;}
     int get_nr_ingrediente(){return nr_ingrediente;}
     void set_ingrediente(string *ingrediente,int nr_ingrediente)
     { this->nr_ingrediente=nr_ingrediente;
        if(this->ingrediente!=NULL)
            delete[] this->ingrediente;
        this->ingrediente=new string[nr_ingrediente];
        for(int i=0; i<nr_ingrediente; i++)
            this-> ingrediente[i]= ingrediente[i];}
     string* get_ingrediente(){return ingrediente;}
     bool contine_ingredientul(string cuvant);
     bool contine_cuvantul(string cuvant);
     virtual ostream& AfisareVirtuala(ostream& out)const;
     virtual istream& CitireVirtuala (istream& in);
     virtual ifstream& CitireVirtuala (ifstream& in);
     virtual float pretFaraTVA(){
          return this->pret-this->pret*procentTVA;}

};
int Produs::contorIdProdus=10000;

Produs::Produs():Taxe(),idProdus(contorIdProdus++)
{
    this->marca="?";
    this->nume_produs="?";
    this->nr_ingrediente=0;
    this->ingrediente=NULL;
    this->greutate=0;
    this->valabilitate=0;
    this->in_stoc=0;
    this->pret=0;
}

Produs::Produs(const Produs &p):Taxe(p),idProdus(p.idProdus)
{
    this->nr_ingrediente=p.nr_ingrediente;
    this->ingrediente=new string[nr_ingrediente];
    for(int i=0;i<nr_ingrediente;i++)
            this->ingrediente[i]=p.ingrediente[i];
    this->marca=p.marca;
    this->nume_produs=p.nume_produs;
    this->greutate=p.greutate;
    this->valabilitate=p.valabilitate;
    this->in_stoc=p.in_stoc;
    this->pret=p.pret;
}
Produs::~Produs()
 {   if(this->ingrediente!=NULL)
            delete[] this->ingrediente;

}
Produs::Produs(string marca,string nume_produs,int nr_ingrediente,string *ingrediente,
               double greutate,int valabilitate,int in_stoc,float pret,float procentTVA):Taxe(procentTVA),idProdus(contorIdProdus ++)
{
    this->nr_ingrediente=nr_ingrediente;
    this->ingrediente=new string[nr_ingrediente];
    for(int i=0;i<nr_ingrediente;i++)
            this->ingrediente[i]=ingrediente[i];
    this->marca=marca;
    this->nume_produs=nume_produs;
    this->greutate=greutate;
    this->valabilitate=valabilitate;
    this->in_stoc=in_stoc;
    this->pret=pret;
}
Produs::Produs(string marca,string nume_produs,float procentTVA):Taxe( procentTVA),idProdus(contorIdProdus ++)
{
    this->marca=marca;
    this->nume_produs=nume_produs;
    this->nr_ingrediente=0;
    this->ingrediente=NULL;
    this->greutate=0;
    this->valabilitate=0;
    this->in_stoc=0;
    this->pret=0;
}
bool Produs::contine_ingredientul(string cuvant)
 {
     for(int i=0;i<this->nr_ingrediente;i++)
         if (this->ingrediente[i]==cuvant)
            return 1;

   return 0;

}
bool Produs::contine_cuvantul(string cuvant)
 {   string word="";

for(auto x:this->nume_produs)
    if(x==' ')
        {if(word==cuvant)
            return 1;

        word="";}
    else
        {word=word+x;
     }
    if(word==cuvant)
        return 1;
    else
    {word="";
       for(auto x:this->marca)
        {if(x==' ')
            {if(word==cuvant)
                return 1;

                word="";}
          else
            word=word+x;}

if(word==cuvant)
    return 1;}

   return 0;

}

const Produs Produs ::operator--(int){
    Produs  aux(*this);
    this->in_stoc--;
    return aux;
}
const Produs& Produs::operator--()
{
    this->in_stoc--;
    return *this;

}

 bool Produs:: operator==(Produs p)
 {
    if((marca==p.marca)&&(nume_produs==p.nume_produs)&&(nr_ingrediente==p.nr_ingrediente)&&(greutate==p.greutate)&&(valabilitate==p.valabilitate)&&(in_stoc==p.in_stoc)&&(pret==p.pret))
        {for(int i=0;i<nr_ingrediente;i++)
            if(ingrediente[i]!=p.ingrediente[i])
                     return false;
        return true;}

   return false;
}
bool Produs:: operator<(const Produs p)const
{
    if(in_stoc<p.in_stoc)
          return true;

    return false;
}
const Produs& Produs::operator+=(float x){

    this->greutate+=x;
    return *this;

}


Produs Produs::operator+(Produs p)
{   Produs aux(*this);
    aux.in_stoc=p.in_stoc+aux.in_stoc;
    return aux;

}
Produs Produs::operator-(Produs p)
{
    Produs aux(*this);
    aux.in_stoc=aux.in_stoc-p.in_stoc;
    return aux;

}
Produs Produs ::operator=(Produs p)
{
    if (this != &p)
        { Taxe::operator=(p);
            if(this->ingrediente!=NULL)
                delete[] this->ingrediente;
        this->nr_ingrediente=p.nr_ingrediente;
        this->ingrediente=new string[nr_ingrediente];
        for(int i=0;i<nr_ingrediente;i++)
                this->ingrediente[i]=p.ingrediente[i];
        this->marca=p.marca;
        this->nume_produs=p.nume_produs;
        this->greutate=p.greutate;
        this->valabilitate=p.valabilitate;
        this->in_stoc=p.in_stoc;
        this->pret=p.pret;}

    return *this;
}
string& Produs::operator[](int i)
{  if(0<=i&&i<this->nr_ingrediente)
        return ingrediente[i];
    else
      exit(0);
}
istream& Produs::CitireVirtuala(istream& in){
int i;
in.ignore();
    cout<<"Marca: ";
    getline(in,marca);
    cout<<"Nume produs:  ";
    getline(in,nume_produs);
    cout<<"Pret:  ";
    in>>pret;
    Taxe::CitireVirtuala(in);
    cout<<"Numar ingrediente:  ";
    in >> nr_ingrediente;
    cout<<"Ingrediente:  ";
    if(ingrediente!=NULL)
        delete[] ingrediente;
    ingrediente=new string[nr_ingrediente];
    in.ignore();
     for(i=0;i<nr_ingrediente;i++)
        getline(in,ingrediente[i]);
    cout<<"Greutate:  ";
    in>>greutate;
    cout<<"Valabilitate:  ";
    in>>valabilitate;
    cout<<"Produse in stoc:  ";
    in>>in_stoc;


    return in;


}
ifstream& Produs::CitireVirtuala(ifstream& in){
int i;


    getline(in,marca);
    getline(in,nume_produs);
    in>>pret;
    Taxe::CitireVirtuala(in);
    in >> nr_ingrediente;
    in.ignore();
    if(ingrediente!=NULL)
        delete[] ingrediente;
    ingrediente=new string[nr_ingrediente];
     for(i=0;i<nr_ingrediente;i++)
        getline(in,ingrediente[i]);
    in>>greutate;
    in>>valabilitate;
    in>>in_stoc;


    return in;


}
ostream& Produs::AfisareVirtuala(ostream& out) const{


    out<<"\nIDProdus: "<<idProdus;
    out<<"\nNume produs: "<<nume_produs;
    out<<"\nMarca: "<<marca;
    out<<"\nPret: "<<pret<<" lei";
    Taxe::AfisareVirtuala(out);
    out<<"\nProdusul contine  "<<nr_ingrediente<<" ingrediente: ";
    for(int i=0; i<nr_ingrediente;i++)
        if(i!=nr_ingrediente-1)
           out<<ingrediente[i]<<", ";
        else
            out<<ingrediente[i];
    out<<"\nGreutate produs: "<<greutate<<" grame";
    out<<"\nValabilitate: "<<valabilitate<<" luni";
    out<<"\nProduse in stoc: "<<in_stoc;
    cout<<endl;

    return out;

}

class PaletaMachiaj:public Produs{
private:
    int nr_culori;
    string *culori_paleta;
public:
    PaletaMachiaj();
    PaletaMachiaj(string marca,string nume_produs,int nr_ingrediente,string *ingrediente,double greutate,int valabilitate,int in_stoc,float pret,int nr_culori, string* culori_paleta,float procentTVA);
    PaletaMachiaj(const PaletaMachiaj &pm);
    ~PaletaMachiaj();
    PaletaMachiaj & operator=(const PaletaMachiaj &pm);
    virtual ostream& AfisareVirtuala(ostream& out)const;
    virtual istream& CitireVirtuala (istream& in);
    virtual ifstream& CitireVirtuala (ifstream& in);
    void marime()
    {
        if(nr_culori>8)
            cout<<"Paleta este de dimensiune mare";
        else
            cout<<"Paleta este de dimensiune mica";
    }


};
PaletaMachiaj::PaletaMachiaj():Produs()
    {

        this->nr_culori=0;
        this->culori_paleta=NULL;

    }
PaletaMachiaj::PaletaMachiaj(string marca,string nume_produs,int nr_ingrediente,string *ingrediente,double greutate,int valabilitate,int in_stoc,float pret,int nr_culori, string* culori_paleta,float procentTVA):
     Produs( marca,nume_produs,nr_ingrediente,ingrediente, greutate, valabilitate, in_stoc, pret,procentTVA)
{
    this->nr_culori=nr_culori;
   this->culori_paleta=new string[nr_culori];
        for(int i=0; i<nr_culori; i++)
            this->culori_paleta[i]=culori_paleta[i];

}
PaletaMachiaj::~PaletaMachiaj()
{
    if(this->culori_paleta!=NULL)
            delete[] this->culori_paleta;
}
PaletaMachiaj::PaletaMachiaj(const PaletaMachiaj &pm):Produs(pm)
{
    this->nr_culori=pm.nr_culori;
    this->culori_paleta=new string[pm.nr_culori];
    for(int i=0; i<pm.nr_culori; i++)
            this->culori_paleta[i]=pm.culori_paleta[i];
}
PaletaMachiaj&PaletaMachiaj:: operator =(const PaletaMachiaj& pm)
{
    if(this!=&pm)
    {   if(this->culori_paleta!=NULL)
            delete[] this->culori_paleta;

        Produs::operator=(pm);
        this->nr_culori=pm.nr_culori;
        this->culori_paleta=new string[pm.nr_culori];
        for(int i=0; i<pm.nr_culori; i++)
            this->culori_paleta[i]=pm.culori_paleta[i];

    }
    return *this;
}

istream&  PaletaMachiaj::CitireVirtuala(istream& in){
int i;
   Produs::CitireVirtuala(in);
    cout<<"Numar culori: ";
    in>>nr_culori;
    cout<<"Paleta contine culorile:  ";
    if(culori_paleta!=NULL)
        delete[] culori_paleta;
        culori_paleta=new string[nr_culori];
        in.ignore();
    for(i=0;i<nr_culori;i++)
        getline(in,culori_paleta[i]);
        return in;



}
ifstream&  PaletaMachiaj::CitireVirtuala(ifstream& in){
int i;
   Produs::CitireVirtuala(in);
    in>>nr_culori;
    in.ignore();
    if(culori_paleta!=NULL)
        delete[] culori_paleta;
        culori_paleta=new string[nr_culori];
    for(i=0;i<nr_culori;i++)
        getline(in,culori_paleta[i]);


   return in;



}
ostream& PaletaMachiaj::AfisareVirtuala(ostream& out) const{
int i;
    Produs::AfisareVirtuala(out);
    out<<"Numar culori: "<<nr_culori<<"\nPaleta contine culorile: ";
    for( i=0; i<nr_culori;i++)
            if(i!=nr_culori-1)
               out<<culori_paleta[i]<<", ";
            else
                out<<culori_paleta[i];

    return out;


}
class Buze:public Produs{
private:
    string nuanta_ruj;
    string tip_ruj;
public:
    Buze();
    Buze(string marca,string nume_produs,int nr_ingrediente,string *ingrediente,double greutate,int valabilitate,int in_stoc,float pret,string nuanta_ruj, string tip_ruj,float procentTVA);
    Buze(const Buze &ruj);
    ~Buze();
    Buze&operator=(const Buze &ruj);
    virtual ostream& AfisareVirtuala(ostream& out)const;
    virtual istream& CitireVirtuala (istream& in);
    virtual ifstream& CitireVirtuala (ifstream& in);

};
Buze::Buze():Produs()
    {

        this->nuanta_ruj="?";
        this->tip_ruj="?";

    }
Buze::Buze(string marca,string nume_produs,int nr_ingrediente,string *ingrediente,double greutate,int valabilitate,int in_stoc,float pret,string nuanta_ruj, string tip_ruj,float procentTVA):Produs( marca,nume_produs,nr_ingrediente,ingrediente, greutate, valabilitate, in_stoc, pret,procentTVA)
{
    this->nuanta_ruj=nuanta_ruj;
    this->tip_ruj=tip_ruj;

}
Buze::~Buze(){}

Buze::Buze(const Buze &ruj):Produs(ruj)
{
    this->nuanta_ruj=ruj.nuanta_ruj;
    this->tip_ruj=ruj.tip_ruj;
}
Buze&Buze:: operator =(const Buze& ruj)
{
    if(this!=&ruj)
    {
        Produs::operator=(ruj);
        this->nuanta_ruj=ruj.nuanta_ruj;
        this->tip_ruj=ruj.tip_ruj;

    }
    return *this;
}


istream& Buze::CitireVirtuala(istream& in){

   Produs::CitireVirtuala(in);
   in.ignore();
    cout<<"Nuanta : ";
    getline(in,nuanta_ruj);
    cout<<"Tip ruj:  ";
    getline(in,tip_ruj);

        return in;



}
ifstream& Buze::CitireVirtuala(ifstream& in){

        Produs::CitireVirtuala(in);
        in.ignore();
        getline(in,nuanta_ruj);
        getline(in,tip_ruj);

        return in;



}
ostream& Buze::AfisareVirtuala(ostream& out) const{

        Produs::AfisareVirtuala(out);
        out<<"\nNuanta : "<<nuanta_ruj;
        out<<"\nTip ruj: ";
        out<<tip_ruj;
        return out;


}


class Comanda
{private:

    int nr_produse;
    string *produse_comanda;
    string adresa;
    string *detalii_card;
    float suma_produse;
    float suma_transport;
    const int idComanda;
    string data_comanda;
    string cod_postal;
    int zile_estimate_livrare;
    PaletaMachiaj *prod;
    int nr_prod;
    Buze *prodbuze;
    int nr_prodbuze;
public:
    static int contorIdComanda;
    Comanda();
    Comanda(int nr_produse,string*produse_comanda,string adresa,string*detalii_card,float suma_produse,float suma_transport,
            string data_comanda,string cod_postal,int zile_estimate_livrare,int nr_prod,PaletaMachiaj *prod,int nr_prodbuze,Buze *prodbuze);
     Comanda(const Comanda&);
     ~Comanda();
     Comanda(string *produse_comanda,int nr_produse);
     const Comanda& operator++();
     const Comanda operator++(int);
     const Comanda& operator+=(int);
     Comanda operator=(Comanda);
     Comanda operator+(Comanda);
     Comanda operator-(Comanda);
     bool operator==(Comanda c);
     bool operator<(Comanda c);
     string& operator[](int);
     friend istream& operator>> (istream& in, Comanda& c);
     friend ostream& operator<<(ostream& out, const Comanda& c);
      friend ifstream& operator>> (ifstream& in, Comanda& c);

     friend Comanda operator+(Comanda c,  PaletaMachiaj& p);
     friend Comanda operator+(Comanda c,Buze& bz);
     explicit operator int(){return (int)this->suma_produse;}
     void reducere();
     void reducere_angajat();
     void sterge_paleta(PaletaMachiaj p);
     void sterge_buze(Buze bz);
     int get_id_comanda(){return idComanda;}
     int get_nr_produse(){return nr_produse;}
     int get_zile_livrare(){return zile_estimate_livrare;}
     float calculeazaSumaComanda();


};


int Comanda::contorIdComanda=1000;

void Comanda::reducere()
{float x=calculeazaSumaComanda();
    if (idComanda%1000==0)
        fout<<"\nSuma totala: "<<(x+this->suma_transport)-(x+this->suma_transport)*20/100<<"lei, cu reducere de 20% din pretul final";
   else if(x>=300)
           cout<<"Suma totala: "<<x<<"lei,cu transport gratuit";
   else
    fout<<"\nSuma totala: "<<(x+this->suma_transport)<<"lei";



}
void Comanda::reducere_angajat()
{
    float x=calculeazaSumaComanda();
cout<<"Suma totala: "<<(x)-(x)*25/100<<"lei, cu reducere de angajat";




}
float Comanda::calculeazaSumaComanda()
{float suma_totala=0;
double x=0;

    for(int i=0; i<nr_prod;i++)
        {x=prod[i].get_pret();
        suma_totala+=x;}

    for(int i=0; i<nr_prodbuze;i++)
         {x=prodbuze[i].get_pret();
        suma_totala+=x;}
 return suma_totala;


}
Comanda::Comanda():idComanda(contorIdComanda++)
{       string detalii[]={"?","?","?","?"};
        this->nr_produse=0;
        this->produse_comanda=NULL;
        this->adresa="?";
        this->detalii_card=new string[4];
        for(int i=0;i<4;i++)
        this->detalii_card[i]=detalii[i];
        this->suma_produse=0;
        this->suma_transport=15;
        this->cod_postal="?";
        this->data_comanda="?";
        this->zile_estimate_livrare=5;
        this->nr_prod=0;
        this->prod=NULL;
         this->nr_prodbuze=0;
        this->prodbuze=NULL;


    }

Comanda::Comanda(const Comanda &c):idComanda(c.idComanda)
    {
        this->nr_produse=c.nr_produse;
        this->produse_comanda=new string[nr_produse];
        for(int i=0;i<nr_produse;i++)
            this->produse_comanda[i]=c.produse_comanda[i];
        this->adresa=c.adresa;
        this->detalii_card=new string[4];
        for(int i=0;i<4;i++)
            this->detalii_card[i]=c.detalii_card[i];
        this->suma_produse=c.suma_produse;
        this->suma_transport=c.suma_transport;
        this->cod_postal=c.cod_postal;
        this->data_comanda=c.data_comanda;
        this->zile_estimate_livrare=c.zile_estimate_livrare;
        this->nr_prod=c.nr_prod;
        this->prod=new PaletaMachiaj[c.nr_prod];
        for(int i=0;i<c.nr_prod;i++)
            this->prod[i]=c.prod[i];
        this->nr_prodbuze=c.nr_prodbuze;
        this->prodbuze=new Buze[c.nr_prodbuze];
        for(int i=0;i<c.nr_prodbuze;i++)
            this->prodbuze[i]=c.prodbuze[i];

    }
Comanda::~Comanda()
    {

        if(this->produse_comanda!=NULL)
            delete[] this->produse_comanda;


        if(this->detalii_card!=NULL)
            delete[] this->detalii_card;

         if(this->prod!=NULL)
            delete[] this->prod;
        if(this->prodbuze!=NULL)
            delete[] this->prodbuze;

    }

Comanda::Comanda(int nr_produse,string*produse_comanda,string adresa,string*detalii_card,float suma_produse,float suma_transport,string data_comanda,
                 string cod_postal,int zile_estimate_livrare,int nr_prod,PaletaMachiaj *prod,int nr_prodbuze, Buze *prodbuze ):idComanda(contorIdComanda++)
    {
        this->nr_produse=nr_produse;
        this->produse_comanda=new string[nr_produse];
        for(int i=0;i<nr_produse;i++)
            this->produse_comanda[i]=produse_comanda[i];
        this->adresa=adresa;
        this->detalii_card=new string[4];
        for(int i=0;i<4;i++)
            this->detalii_card[i]=detalii_card[i];
        this->suma_produse=suma_produse;
        if (this->suma_produse<150)
           this->suma_transport=suma_transport;
        else
          this->suma_transport=0;
        this->cod_postal=cod_postal;
        this->data_comanda=data_comanda;
        this->zile_estimate_livrare=zile_estimate_livrare;
        this->nr_prod=nr_prod;
        this->prod=new PaletaMachiaj[nr_prod];
        for(int i=0;i<nr_prod;i++)
            this->prod[i]=prod[i];
        this->nr_prodbuze=nr_prodbuze;
        this->prodbuze=new Buze[nr_prodbuze];
        for(int i=0;i<nr_prodbuze;i++)
            this->prodbuze[i]=prodbuze[i];

    }

Comanda::Comanda(string* produse_comanda,int nr_produse):idComanda(contorIdComanda++)
    {     string detalii[]={"?","?","?","?"};
          this->nr_produse=nr_produse;
          this->produse_comanda=new string[nr_produse];
          for(int i=0;i<nr_produse;i++)
                this->produse_comanda[i]=produse_comanda[i];
            this->adresa="?";
        this->detalii_card=new string[4];
        for(int i=0;i<4;i++)
        this->detalii_card[i]=detalii[i];
        this->suma_produse=0;
        this->suma_transport=20;
        this->cod_postal="?";
        this->data_comanda="?";
        this->zile_estimate_livrare=0;
        this->nr_prod=0;
        this->prod=NULL;
        this->nr_prodbuze=0;
        this->prodbuze=NULL;
}
const Comanda Comanda::operator++(int)
{
        Comanda aux(*this);
        this->zile_estimate_livrare++;
        return aux;
}
string& Comanda::operator[](int i)
{
        if(0<=i &&i<nr_produse)
            return produse_comanda[i];
        else
            exit(0);
}
const Comanda& Comanda::operator++()
{
        this->zile_estimate_livrare++;
        return *this;

}
const Comanda& Comanda::operator+=(int x)
{
        this->zile_estimate_livrare+=x;
        return *this;

}
Comanda Comanda ::operator+(Comanda c)
{
     Comanda aux(*this);
    aux.zile_estimate_livrare=c.zile_estimate_livrare+aux.zile_estimate_livrare;
    return aux;

}
Comanda Comanda ::operator-(Comanda c)
{
      Comanda aux(*this);
    aux.zile_estimate_livrare=aux.zile_estimate_livrare-c.zile_estimate_livrare;
    return aux;

}


Comanda Comanda ::operator=(Comanda c)
{
    if (this != &c)
       {if(this->produse_comanda!=NULL)
            delete[] this->produse_comanda;
        if(this->detalii_card!=NULL)
            delete[] this->detalii_card;
        this->nr_produse=c.nr_produse;
        this->produse_comanda=new string[nr_produse];
        for(int i=0;i<nr_produse;i++)
            this->produse_comanda[i]=c.produse_comanda[i];
        this->adresa=c.adresa;
        this->detalii_card=new string[4];
        for(int i=0;i<4;i++)
            this->detalii_card[i]=c.detalii_card[i];
        this->suma_produse=c.suma_produse;
        this->suma_transport=c.suma_transport;
        this->cod_postal=c.cod_postal;
        this->data_comanda=c.data_comanda;
         this->zile_estimate_livrare=c.zile_estimate_livrare;
                  this->nr_prod=c.nr_prod;
         this->prod=new PaletaMachiaj[c.nr_prod];
         for(int i=0;i<c.nr_prod;i++)
            this->prod[i]=c.prod[i];}
            this->nr_prodbuze=c.nr_prodbuze;
        this->prodbuze=new Buze[c.nr_prodbuze];
        for(int i=0;i<c.nr_prodbuze;i++)
            this->prodbuze[i]=c.prodbuze[i];

    return *this;
}
 bool Comanda:: operator==(Comanda c)
{
        if((nr_produse==c.nr_produse)&&(suma_produse==c.suma_produse)&&(suma_transport==c.suma_transport))
            {for(int i=0;i<nr_produse;i++)
                if(produse_comanda[i]!=c.produse_comanda[i])
                     return false;
            return true;}

        return false;
}
bool Comanda:: operator<(Comanda c)
{
    if(nr_produse<c.nr_produse)
            return true;

    return false;
}
Comanda operator+(Comanda c,  PaletaMachiaj& p)
{

        PaletaMachiaj* lista;
        lista=new PaletaMachiaj[c.nr_prod];
        for(int i=0; i<c.nr_prod;i++)
            lista[i]=c.prod[i];

        if(c.prod!=NULL)
            delete[] c.prod;

        c.nr_prod++;
        c.prod=new PaletaMachiaj[c.nr_prod];
        for(int i=0; i<c.nr_prod-1 ;i++)
            c.prod[i]=lista[i];
       c.prod[c.nr_prod-1]=p;

       p--;

        return c;

}
Comanda operator+(Comanda c,  Buze& bz)
{



        Buze* listabuze;
        listabuze=new Buze[c.nr_prodbuze];
        for(int i=0; i<c.nr_prodbuze;i++)
            listabuze[i]=c.prodbuze[i];

        if(c.prodbuze!=NULL)
            delete[] c.prodbuze;

        c.nr_prodbuze++;
        c.prodbuze=new Buze[c.nr_prodbuze];
        for(int i=0; i<c.nr_prodbuze-1 ;i++)
            c.prodbuze[i]=listabuze[i];
       c.prodbuze[c.nr_prodbuze-1]=bz;
       bz--;
        return c;

}
void Comanda::sterge_paleta(PaletaMachiaj p)
{
        int k=0,ok=0,i=0;
        int stoc=p.get_in_stoc();
        stoc++;
        PaletaMachiaj* lista;
        lista=new PaletaMachiaj[this->nr_prod];
        for(int i=0; i<this->nr_prod; i++)
           {lista[i]=this->prod[i];
            if(this->prod[i]==p)
                k++;}

            if(this->prod!=NULL)
                delete[] this->prod;


            this->prod=new PaletaMachiaj[this->nr_prod-k];

            while(i<this->nr_prod)
            {
                if(lista[i]==p)
                    i++;
                else
                {
                    this->prod[ok]=lista[i];
                    ok++;
                    i++;

                }

            }

            this->nr_prod=this->nr_prod-k;


}

void Comanda::sterge_buze(Buze bz)
{
        int k=0,ok=0,i=0;
        Buze* lista;
        lista=new Buze[this->nr_prodbuze];
        for(int i=0; i<this->nr_prodbuze; i++)
           {lista[i]=this->prodbuze[i];
            if(this->prodbuze[i]==bz)
                k++;}

        if(this->prodbuze!=NULL)
                delete[] this->prodbuze;


        this->prodbuze=new Buze[this->nr_prodbuze-k];

        while(i<this->nr_prodbuze)
            {
                if(lista[i]==bz)
                    i++;
                else
                {
                    this->prodbuze[ok]=lista[i];
                    ok++;
                    i++;

                }

            }
            this->nr_prodbuze=this->nr_prodbuze-k;


}


istream& operator>> (istream& in, Comanda& c)
{   int i;

    cout<<"Adresa: ";
    in>>c.adresa;
    cout<<"Detalii card:  \n";
     if(c.detalii_card!=NULL)
        delete[] c.detalii_card;
        c.detalii_card=new string[4];
    for(i=0;i<4;i++)
        {if(i==0)
        cout<<"Nr card: ";
        if(i==1)
        cout<<"Data expirarii: ";
         if(i==2)
        cout<<"Cod securitate: ";
         if(i==3)
        cout<<"Titular card: ";
       in>>c.detalii_card[i];}
    cout<<"Data comenzii:  ";
    in>>c.data_comanda;
    cout<<"cod postal:  ";
    in>>c.cod_postal;

    return in;
}

ifstream& operator>> (ifstream& in, Comanda& c)
{   int i;
    in >> c.nr_produse;
    in.ignore();
    if(c.produse_comanda!=NULL)
        delete[] c.produse_comanda;
        c.produse_comanda=new string[c.nr_produse];
        for(i=0;i<c.nr_produse;i++)
     getline(in,c.produse_comanda[i]);

    in>>c.adresa;
     if(c.detalii_card!=NULL)
        delete[] c.detalii_card;
        c.detalii_card=new string[4];
    for(i=0;i<4;i++)
       in>>c.detalii_card[i];
    in>>c.suma_transport;
    in>>c.data_comanda;
    in>>c.cod_postal;
    in>> c.zile_estimate_livrare;
    in>>c.nr_prod;
    if(c.prod!=NULL)
        delete[] c.prod;
    c.prod=new PaletaMachiaj[c.nr_prod];
    for(int i=0; i<c.nr_prod;i++)
        in>>c.prod[i];
    in>>c.nr_prodbuze;
    if(c.prodbuze!=NULL)
        delete[] c.prodbuze;
    c.prodbuze=new Buze[c.nr_prodbuze];
    for(int i=0; i<c.nr_prodbuze;i++)
        in>>c.prodbuze[i];
    return in;
}
 ostream& operator<<(ostream& out, const Comanda& c){

    out<<"\nAdresa: "<<c.adresa;
    out<<"\nData comenzii "<<c.data_comanda;
    out<<"\nCod postal:"<<c.cod_postal;
    out<<"\nZile estimate pana la livrare: "<<c.zile_estimate_livrare;
      out<<"\nDetalii card: ";
       for(int i=0; i<4;i++)
         if(i!=3)
            out<<c.detalii_card[i]<<", ";
        else
            out<<c.detalii_card[i];
        out<<"\n\nRezumatul cumparaturilor tale\n";
     if(c.nr_prod!=0)
     {
    for(int i=0; i<c.nr_prod;i++)
            {out<<c.prod[i];
            out<<endl;}}
    if(c.nr_prodbuze!=0)
    {
    for(int i=0; i<c.nr_prodbuze;i++)
            {out<<c.prodbuze[i];
            out<<endl;}}
    return out;

}

class AfisareStatut{
public:
    virtual void afis()=0;
};

class Client:public AfisareStatut
{protected:
    //double e la clasa Produs
    char *nume;
    char gen;
    string prenume;
    string *produse_in_cos;
    string email;
    string telefon;
    const int idClient;
    bool major;
    int cate_in_cos;
    int nr_comenzi;
    float *plata_comenzi;
    float rank_client;
    int *varsta;
    int ani_vechime;
    Comanda *com;




public:
     static int contorId;
     Client();
     Client(const Client&);
     Client(char* nume,string prenume,string email,string telefon,char gen,float rank_client,
            bool major,int cate_in_cos, string *produse_in_cos,int nr_comenzi,float*plata_comenzi,int*varsta,int ani_vechime,Comanda *com);
     Client(char* nume,string prenume,string email);
     ~Client();
     Client operator=(Client);
     Client operator+(Client om);
     Client operator-(Client om);
    const Client& operator++();
    const Client operator++(int);
    const Client&  operator+=(int);
    bool operator==(Client om);
     bool operator<(Client om);
     string& operator[](int i);
     virtual ostream& AfisareVirt(ostream& out)const;
     virtual istream& CitireVirt (istream& in);
     friend istream& operator>> (istream& in, Client& om);
     friend ostream& operator<<(ostream& out, const Client& om);
          virtual ifstream& CitireVirt (ifstream& in);
     friend ifstream& operator>> (ifstream& in, Client& om);
     explicit operator int(){return (int)this->rank_client;}

     friend Client operator+(Client om, const Comanda& com);
     virtual void sterg_comanda(Comanda cm);

     void fidelitate();
     void set_nume(char* nume)
     {if(this->nume!=NULL)
            delete[] this->nume;
     this->nume=new char[strlen(nume)+1];
     strcpy(this->nume,nume);}
     char* get_nume(){return nume;}
     void set_prenume(string prenume) {this->prenume=prenume;}
     string get_prenume(){return prenume;}
     void set_email(string email) { this->email=email;}
     string get_email(){return email;}
      void set_telefon(string telefon) { this->telefon=telefon;}
     string get_telefon(){return this->telefon;}
     void set_major(bool major) { this->major=major;}
     bool get_major(){return major;}
     void set_gen(char gen) { this->gen=gen;}
     char get_gen(){return gen;}
     const int get_id(){return idClient;}
     void set_rank(float rank_client) { this->rank_client=rank_client;}
     float get_rank_client(){return rank_client;}
     void set_cate_in_cos(int cate_in_cos) { this->cate_in_cos=cate_in_cos;}
     int get_cate_in_cos(){return cate_in_cos;}
     void set_produse_in_cos(string * produse_in_cos,int cate_in_cos)
     { this->cate_in_cos=cate_in_cos;
        if(this->produse_in_cos!=NULL)
            delete[] this->produse_in_cos;
        this->produse_in_cos=new string[cate_in_cos];
        for(int i=0; i<cate_in_cos; i++)
            this-> produse_in_cos[i]= produse_in_cos[i];}
     string* get_produse_in_cos(){return produse_in_cos;}
     void set_nr_comenzi(int nr_comenzi) { this->nr_comenzi=nr_comenzi;}
     int get_nr_comenzi(){return nr_comenzi;}
     void set_plata_comenzi(float * plata_comenzi,int nr_comenzi)
         {this->nr_comenzi=nr_comenzi;
         if(this-> plata_comenzi!=NULL)
            delete[]  this->plata_comenzi;
         this-> plata_comenzi=new float[nr_comenzi];
         for(int i=0; i<nr_comenzi; i++)
            this->  plata_comenzi[i]=  plata_comenzi[i];}
     float *get_plata_comenzi(){return plata_comenzi;}
     void set_varsta(int *varsta){
        this->varsta[0]=varsta[0];}
     int *get_varsta(){return this->varsta;}
     void set_ani_vechime(int ani_vechime) { this->ani_vechime=ani_vechime;}
     int get_ani_vechime(){return this->ani_vechime;}
     virtual void afis(){cout<<"CLIENT";}

};
int Client::contorId=1;

Client::Client():idClient(contorId++)
    {

        this->nume=new char[strlen("Client")+1];
        strcpy(this->nume,"Client");
        this->prenume="Anonim";
        this->varsta=new int[1];
        this->varsta[0]=18;
        this->major=true;
        this->nr_comenzi=0;
        this->plata_comenzi=0;
        this->rank_client=5;
        this->produse_in_cos=NULL;
        this->cate_in_cos=0;
        this->email="?";
        this->telefon="?";
        this->gen='?';
        this->ani_vechime=0;
        this->com=NULL;



    }
Client::Client(const Client& om):idClient(om.idClient)
    {

        this->nume=new char[strlen("Client")+1];
        strcpy(this->nume,om.nume);
        this->prenume=om.prenume;
        this->major=om.major;
        this->varsta=new int[1];
        this->varsta[0]=om.varsta[0];
        this->nr_comenzi=om.nr_comenzi;

        this->plata_comenzi=new float[om.nr_comenzi];
        for(int i=0; i<om.nr_comenzi; i++)
            this->plata_comenzi[i]=om.plata_comenzi[i];

        this->rank_client=om.rank_client;
        this->cate_in_cos=om.cate_in_cos;
        this->produse_in_cos=new string[om.cate_in_cos];
        for(int i=0; i<om.cate_in_cos; i++)
            this->produse_in_cos[i]=om.produse_in_cos[i];

        this->email=om.email;
        this->telefon=om.telefon;
        this->gen=om.gen;
        this->ani_vechime=om.ani_vechime;

            this->nr_comenzi=om.nr_comenzi;
        this->com=new Comanda[om.nr_comenzi];
        for(int i=0;i<om.nr_comenzi;i++)
            this->com[i]=om.com[i];

}
Client::~Client()
    {

        if(this->nume!=NULL)
            delete[] this->nume;


        if(this->produse_in_cos!=NULL)
            delete[] this->produse_in_cos;

        if(this->plata_comenzi!=NULL)
            delete[] this->plata_comenzi;

        if(this->varsta!=NULL)
            delete[] this->varsta;

         if(this->com!=NULL)
            delete[] this->com;


    }
Client::Client(char *nume,string prenume,string email,string telefon,char gen,float rank_client,
               bool major,int cate_in_cos,string *produse_in_cos,int nr_comenzi,float* plata_comenzi,int *varsta,int ani_vechime,Comanda *com):idClient(contorId++)
    {

        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
        this->prenume=prenume;
        this->major=major;
        this->nr_comenzi=nr_comenzi;

        this->plata_comenzi=new float[nr_comenzi];
        for(int i=0; i<nr_comenzi; i++)
            this->plata_comenzi[i]=plata_comenzi[i];
        this->varsta=new int[1];
         this->varsta[0]=varsta[0];

        this->rank_client=rank_client;

        this->cate_in_cos=cate_in_cos;
        this->produse_in_cos=new string[cate_in_cos];
        for(int i=0; i<cate_in_cos; i++)
            this->produse_in_cos[i]=produse_in_cos[i];

        this->email=email;
        this->telefon=telefon;
        this->gen=gen;
        this->ani_vechime=ani_vechime;

               this->nr_comenzi=nr_comenzi;
        this->com=new Comanda [nr_comenzi];
        for(int i=0;i<nr_comenzi;i++)
            this->com[i]=com[i];


}
Client::Client(char *nume,string prenume,string email):idClient(contorId++)
{
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
        this->prenume=prenume;
         this->email=email;
        this->major=true;
        this->nr_comenzi=0;
        this->plata_comenzi=0;
        this->rank_client=0;
        this->produse_in_cos=NULL;
        this->cate_in_cos=0;
        this->varsta[0]=18;
        this->telefon="?";
        this->gen='?';
        this->ani_vechime=0;

         this->com=NULL;
}

void Client::fidelitate()
{   float suma=0;
    for(int i=0;i<this->nr_comenzi;i++)
        suma+=this->plata_comenzi[i];
    if(this->nr_comenzi>=5 && suma>500)
        cout<<"Clientul nr."<<this->idClient<<" este fidel";
    else
            cout<<"Client obisnuit ";

}

Client Client::operator=(Client om)
{
    if (this != &om)
    {   if(this->nume!=NULL)
            delete[] this->nume;
        this->nume=new char[strlen(om.nume)+1];
        strcpy(this->nume,om.nume);
        this->prenume=om.prenume;
        this->major=om.major;
       this->nr_comenzi=om.nr_comenzi;
         if(this->varsta!=NULL)
            delete[] this->varsta;
        this->varsta=new int[1];
        this->varsta[0]=om.varsta[0];
       if(this->plata_comenzi!=NULL)
            delete[] this->plata_comenzi;
        this->plata_comenzi=new float[om.nr_comenzi];
        for(int i=0; i<om.nr_comenzi; i++)
            this->plata_comenzi[i]=om.plata_comenzi[i];

        this->rank_client=om.rank_client;
         this->cate_in_cos=om.cate_in_cos;
         if(this->produse_in_cos!=NULL)
            delete[] this->produse_in_cos;
        this->produse_in_cos=new string[om.cate_in_cos];
        for(int i=0; i<om.cate_in_cos; i++)
            this->produse_in_cos[i]=om.produse_in_cos[i];

        this->email=om.email;
        this->telefon=om.telefon;
        this->gen=om.gen;
        this->ani_vechime=om.ani_vechime;

             this->nr_comenzi=om.nr_comenzi;
        this->com=new Comanda[om.nr_comenzi];
        for(int i=0;i<om.nr_comenzi;i++)
            this->com[i]=om.com[i];

    }
    return *this;
}
const Client& Client::operator+=(int x){

        this->ani_vechime+=x;
        return *this;

}
const Client Client::operator++(int){
       Client aux(*this);
        this->ani_vechime++;
        return aux;
}
const Client& Client::operator++(){

        this->ani_vechime++;
        return *this;

}
Client Client::operator+(Client  om)
{
Client aux(*this);
   aux.ani_vechime=om.ani_vechime+ aux.ani_vechime;
    return aux;
}
Client Client::operator-(Client  om)
{  Client aux(*this);
   aux.ani_vechime=aux.ani_vechime-om.ani_vechime;
    return aux;
}
 bool Client:: operator==(Client om)
{
        if((nume[0]==om.nume[0])&&(gen==om.gen)&&(prenume==om.prenume)&&(email==om.email)&&(telefon==om.telefon)&&(major==om.major)&&(cate_in_cos==om.cate_in_cos)&&(nr_comenzi==om.nr_comenzi)&&(rank_client==om.rank_client)&&(ani_vechime==om.ani_vechime)&&(varsta[0]==om.varsta[0]))
            {for(int i=0;i<cate_in_cos;i++)
                if(produse_in_cos[i]!=om.produse_in_cos[i])
                     return false;
             for(int i=0;i<nr_comenzi;i++)
                if(plata_comenzi[i]!=om.plata_comenzi[i])
                     return false;

            return true;}

        return false;
}
bool Client::operator<(Client om)
{
    if(ani_vechime<om.ani_vechime)
        return true;

    return false;
}
string& Client::operator[](int i)
{
          if(i<=0&&i<this->cate_in_cos)
            return produse_in_cos[i];
          else
            exit(0);

}
Client operator+(Client om, const Comanda& cm)
{

        Comanda* lista;
        lista=new Comanda[om.nr_comenzi];
        for(int i=0; i<om.nr_comenzi;i++)
            lista[i]=om.com[i];

        if(om.com!=NULL)
            delete[] om.com;

        om.nr_comenzi++;
        om.com=new Comanda[om.nr_comenzi];
        for(int i=0; i<om.nr_comenzi-1 ;i++)
            om.com[i]=lista[i];
        om.com[om.nr_comenzi-1]=cm;



        return om;

}
void Client::sterg_comanda(Comanda cm)
{
        int k=0,ok=0,i=0;
        Comanda* lista;
        lista=new Comanda[this->nr_comenzi];
        for(int i=0; i<this->nr_comenzi; i++)
           {lista[i]=this->com[i];
            if(this->com[i]==cm)
                k++;}

            if(this->com!=NULL)
                delete[] this->com;


            this->com=new Comanda[this->nr_comenzi-k];

            while(i<this->nr_comenzi)
            {
                if(lista[i]==cm)
                    i++;
                else
                {
                    this->com[ok]=lista[i];
                    ok++;
                    i++;

                }

            }
            this->nr_comenzi=this->nr_comenzi-k;

}

ostream& Client::AfisareVirt (ostream& out) const{
   out<<"\nID: "<<idClient;
    out<<"\nNume: "<<nume;
    out<<"\nPrenume: "<<prenume;
    out<<"\nEmail: "<<email;
    out<<"\nTelefon "<<telefon;
    out<<"\nVarsta: "<<varsta[0];
    out<<"\nGen: "<<gen;
    out<<"\nRank: "<<rank_client;
    out<<"\nEste client de "<<ani_vechime<<" ani";
    out<<"\nMajor: ";
    if(major) out<<"da";
    else out<<"nu";

     out<<"\nAre in cos "<<cate_in_cos<<" produse: ";
     for(int i=0; i<cate_in_cos;i++)
        if(i!=cate_in_cos-1)
        out<<produse_in_cos[i]<<", ";
     else
            out<<produse_in_cos[i];
    if(nr_comenzi==0)
         out<<"\nA comandat pana acum "<<nr_comenzi<<" produse";
    else
    out<<"\nA comandat pana acum "<<nr_comenzi;
    if(nr_comenzi!=0)
    {out<<"\nProdusele  comandate: ";
    for(int i=0; i<nr_comenzi;i++)
            {out<<com[i];
            cout<<endl;}
    }



    return out;


}

istream& Client::CitireVirt(istream& in){

        int i;
    cout<<"Nume:  ";
    in >> nume;
    cout<<"Prenume:  ";
    in.ignore();
    getline(in,prenume);
    cout<<"Gen: ";
    in>>gen;
    cout<<"major[1 da /0 nu]:  ";
    in>>major;
    cout<<"email:  ";
    in>>email;
    cout<<"telefon:  ";
    in>>telefon;
    cout<<"De cand este client: ";
    in>>ani_vechime;
    cout<<"varsta:  ";
    if(varsta!=NULL)
        delete[] varsta;
        varsta=new int[1];
        in>>varsta[0];
    cout<<"Cate produse are in cos:  ";
    in>>cate_in_cos;
    if(cate_in_cos!=0)
    {cout<<"Ce produse are in cos:  ";
    if(produse_in_cos!=NULL)
        delete[] produse_in_cos;
        produse_in_cos=new string[cate_in_cos];
        in.ignore();
        for(i=0;i<cate_in_cos;i++)
        getline(in,produse_in_cos[i]);}



return in;
}

istream& operator>>(istream & in,Client& om)
{
    return om.CitireVirt(in);
}
 ostream& operator<<(ostream & out,const Client& om)
{
    return om.AfisareVirt(out);
}


ifstream& Client::CitireVirt(ifstream& in){



        int i;

    in >> nume;
    in.ignore();
    getline(in,prenume);
    in>>gen;
    in>>major;
    in>>email;
    in>>telefon;
    in>>ani_vechime;
    if(varsta!=NULL)
        delete[] varsta;
        varsta=new int[1];
        in>>varsta[0];
    in>>cate_in_cos;
    in.ignore();
    if(produse_in_cos!=NULL)
        delete[] produse_in_cos;
        produse_in_cos=new string[cate_in_cos];
        for(i=0;i<cate_in_cos;i++)
        getline(in,produse_in_cos[i]);
    in>>nr_comenzi;
    if(plata_comenzi!=NULL)
        delete[] plata_comenzi;
        plata_comenzi=new float [nr_comenzi];
        for(i=0;i<nr_comenzi;i++)
    in>>plata_comenzi[i];



    if(com!=NULL)
        delete[] com;
   com=new Comanda[nr_comenzi];

    for(int i=0; i<nr_comenzi;i++)
        in>>com[i];

return in;
}

ifstream& operator>>(ifstream & in,Client& om)
{
    return om.CitireVirt(in);
}

class Angajat:public Client{
private:
    string functie_in_firma;

public:
    Angajat();
    Angajat(char *nume,string prenume,string email,string telefon,char gen,float rank_client,
               bool major,int cate_in_cos,string *produse_in_cos,int nr_comenzi,float* plata_comenzi,int *varsta,int ani_vechime,Comanda *com,string functie_in_firma);
    Angajat(const Angajat &ang);
    ~Angajat();
    Angajat&operator=(const Angajat &ang);
    virtual ostream& AfisareVirt(ostream& out)const;
    virtual istream& CitireVirt (istream& in);
    virtual ifstream& CitireVirt (ifstream& in);
    virtual void afis(){cout<<"ANGAJAT";}
    friend Angajat operator+(Angajat om, const Comanda& com);


};
Angajat::Angajat():Client()
    {

        this->functie_in_firma="?";

    }
Angajat::Angajat(char *nume,string prenume,string email,string telefon,char gen,float rank_client,bool major,int cate_in_cos,string *produse_in_cos,int nr_comenzi,float* plata_comenzi,int *varsta,int ani_vechime,Comanda *com,string functie_in_firma):Client(nume,prenume,email,telefon, gen, rank_client,major,cate_in_cos,produse_in_cos,nr_comenzi,plata_comenzi,varsta,ani_vechime,com)
{
    this->functie_in_firma=functie_in_firma;
}
Angajat::~Angajat(){}

Angajat::Angajat(const Angajat &ang):Client(ang)
{
    this->functie_in_firma=ang.functie_in_firma;

}
Angajat &Angajat:: operator =(const Angajat& ang)
{
    if(this!=&ang)
    {
        Client::operator=(ang);
        this->functie_in_firma=ang.functie_in_firma;

    }
    return *this;
}
Angajat operator+(Angajat om, const Comanda& cm)
{

        Comanda* lista;
        lista=new Comanda[om.nr_comenzi];
        for(int i=0; i<om.nr_comenzi;i++)
            lista[i]=om.com[i];

        if(om.com!=NULL)
            delete[] om.com;

        om.nr_comenzi++;
        om.com=new Comanda[om.nr_comenzi];
        for(int i=0; i<om.nr_comenzi-1 ;i++)
            om.com[i]=lista[i];
        om.com[om.nr_comenzi-1]=cm;



        return om;

}


istream& Angajat::CitireVirt(istream &in)
    {
       Client::CitireVirt(in);
       cout<<"Functie in firma : ";
        in.ignore();
        getline(in,functie_in_firma);
        return in;
    }
ifstream& Angajat::CitireVirt(ifstream &in)
    {
       Client::CitireVirt(in);
        in.ignore();
        getline(in,functie_in_firma);
        return in;
    }
ostream& Angajat::AfisareVirt(ostream &out)const
{
        Client::AfisareVirt(out);
        out<<"\nFunctie in firma: ";
      out<<functie_in_firma;

        return out;

}



int main()
{
set<Produs*> ListaProduse;
vector<Client*>ListaClienti;
vector<Livrare*>ListaCurieri;
list<Comanda *>ListaComanda;
map<Comanda*,Livrare*> sarcini_Livratori;

for(int i=0;i<3;i++)
    {PaletaMachiaj *paleta=new PaletaMachiaj;
    fin>>*paleta;
    ListaProduse.insert(&(*paleta));
    }

for(int i=0;i<3;i++)
   {Buze *ruj=new Buze;
    fin>>*ruj;
    ListaProduse.insert(&(*ruj));}

for(int i=0;i<3;i++)
   {Client *om=new Client;
    fin>>*om;
    ListaClienti.push_back(&(*om));}

for(int i=0;i<3;i++)
   {Client *ang=new Angajat;
    fin>>*ang;
    ListaClienti.push_back(&(*ang));}

for(int i=0;i<2;i++)
   {Livrare *ang=new Livrare;
    fin>>*ang;
    ListaCurieri.push_back(&(*ang));
    fin.ignore();}


int c1=0;
while(c1==0)
{
cout<<"[ruleaza 1/ oprire 0]\n";
int c2;cin>>c2;
if(c2==1)
{char l;
cout<<"Pentru ADMINISTRATOR apasati tasta 'A'\n";
cout<<"Pentru CLIENT apasati tasta 'C'\n";
cin>>l;
if(l=='A')
{cout<<"Introuceti parola: ";
string parola;
cin>>parola;
if(parola=="123")

    {system("cls");
    int k=1;
    int i=0,l=0;
    while(k==1){

        cout<<"\n1 Adaugati paleta de machiaj ";
        cout<<"\n2 Adaugati ruj ";
        cout<<"\n3 Afisare produse ";
        cout<<"\n4 Sterge produs ";
        cout<<"\n5 Adaugati client/angajat ";
        cout<<"\n6 Sterge client ";
        cout<<"\n7 Afisare clienti ";
        cout<<"\n8 Cautati un produs ";
        cout<<"\n9 Afisare produse BIO ";
        cout<<"\n10 Stop ";
        cout<<"\n11 Afisare comenzi \n";


        int comanda;
        cin>> comanda;


        switch(comanda){

            case 1:{
                 system("cls");
                PaletaMachiaj *paleta=new PaletaMachiaj;
                cin>>*paleta;
                ListaProduse.insert(&(*paleta));
                break;


            }
            case 2:{
                system("cls");
                Buze *ruj=new Buze;
                cin>>*ruj;
                ListaProduse.insert(&(*ruj));
                break;


            }
             case 3:{system("cls");
                set<Produs*>::iterator itr;
                cout<<"Produsele in stoc: "<<endl;

                for (itr = ListaProduse.begin(); itr != ListaProduse.end(); itr++)
                 {cout << (*itr)->get_nume_produs()<<", "<<(*itr)->get_pret()<<" lei"<<", "<<(*itr)->get_in_stoc()<<" ramase in stoc";
                 cout<<"\n------------------------------\n";}

                break;
            }

           case 4:{system("cls");
                string nume_produs;
                set<Produs*>::iterator itr;
                cout<<"Stergeti produsul cu numele: "<<endl;
                cin>>nume_produs;
                for (itr = ListaProduse.begin(); itr != ListaProduse.end(); itr++)
                    if(nume_produs==((*itr)->get_nume_produs()))
                       {
                           ListaProduse.erase(*itr);
                           break;

                        }
                break;


            }

            case 5:{system("cls");
                 int statut;
                 cout<<"Apasati tasta corespunzatoare client[1]/angajat[0]:\n";
                 cin>>statut;
                 if(statut==1)
                   {
                        Client *om=new Client;
                        cin>>*om;
                        ListaClienti.push_back(&(*om));

                    }
                else
                    {
                        Angajat *om=new Angajat;
                        cin>>*om;
                        ListaClienti.push_back(&(*om));
                    }
                break;


            }
            case 6:{system("cls");
                int id;
                vector<Client*>::iterator itr;
                cout<<"Stergeti clientul cu ID-ul: "<<endl;
                cin>>id;
                for (itr = ListaClienti.begin(); itr != ListaClienti.end(); itr++)
                     if(id==((*itr)->get_id()))
                       {
                           ListaClienti.erase(itr);
                           break;

                        }
                break;

            }
             case 7:{system("cls");
                cout<<"Clientii magazinului: ";
                vector<Client*>::iterator itr;
                for (itr = ListaClienti.begin(); itr != ListaClienti.end(); itr++)
                     {
                         cout << (*(*(itr)));
                         cout<<"\n------------------------------\n";
                     }
                break;
            }

           case 8:{system("cls");
                string nume_produs;
                set<Produs*>::iterator itr;
                cout<<"Ce produs cautati?: "<<endl;
                cin>>nume_produs;
                for (itr = ListaProduse.begin(); itr != ListaProduse.end(); itr++)
                     if(((*itr)->contine_cuvantul(nume_produs))==1)
                        {
                            cout << (*itr)->get_nume_produs()<<", "<<(*itr)->get_pret()<<" lei";
                            cout<<"\n------------------------------\n";
                          }

                   cout<<"Apasati tasta 1 petru DETALII PRODUSE sau 0 in caz contrar";
                    int x;
                    cin>>x;
                    if(x==1)
                        for (itr = ListaProduse.begin(); itr != ListaProduse.end(); itr++)
                         if(((*itr)->contine_cuvantul(nume_produs))==1)
                            {cout << *(*itr);
                              cout<<"\n------------------------------\n";}

                break;


            }

             case 10:{system("cls");


                k=0;
                break;


            }

           case 9:{system("cls");

                 set<Produs*>::iterator itr;


                for (itr = ListaProduse.begin(); itr != ListaProduse.end(); itr++)
                     if(((*itr)->contine_ingredientul("bio"))==1)
                        {
                          cout << (*itr)->get_nume_produs()<<", "<<(*itr)->get_pret()<<" lei";
                          cout<<"\n------------------------------\n";
                          }


                break;

            }


               case 11:{system("cls");
                cout<<"Comenzile : ";
                list<Comanda*>::iterator itr;
                for (itr = ListaComanda.begin(); itr != ListaComanda.end(); itr++)
                 {cout << (*(*(itr)))<<"\nLivrare efectuata de: ";
                 cout<<*(sarcini_Livratori[(*itr)]);
                 cout<<"\n------------------------------\n";}
                break;
            }




        }


    }

    }
    else {
    system("cls");
    cout<<"Parola GRESITA. Incercati iar\n";

    }


}
else
      {system("cls");
    int k=1;
    int i=0,l=0;
    int id,id_ok=1;  cout<<"Id client: ";  cin>>id;
    Client *om=new Client;
    vector<Client*>::iterator itr;
        for (itr = ListaClienti.begin(); itr != ListaClienti.end() && id_ok==1; itr++)
            if(id==((*itr)->get_id()))
                    {id_ok=0;
                    *om=*(*itr);}

        if(id_ok==1)
        {

                cin>>*om;
                ListaClienti.push_back(&(*om));
        }


    while(k==1){
        cout<<"\n1 Plasati o comanda ";
        cout<<"\n2 Afisati toate comenzile ";
        cout<<"\n3 Afisare produse ";
        cout<<"\n4 Anulati o comanda ";
        cout<<"\n5 Cautati un produs ";
        cout<<"\n6 Afisare produse BIO ";
        cout<<"\n7 Stop \n";

        int comanda;
        cin>> comanda;


        switch(comanda){

                 case 1:{
                system("cls");
                int ok=0;
                Comanda *com=new Comanda;
                while(ok==0)
                {int x;cout<<"\n[1 adauga produs/0 finalizeaza comanda]\n";cin>>x;
                if (x==0)
                    { ok=1;
                    cin>>*com;
                    ListaComanda.push_front(&(*com));
                    *om=*om+((*com));

                    fout<<"COMANDA TA  NR. "<<com->get_id_comanda()<<" A FOST PREDATA! \n\n ";
                    fout<<*com<<endl;
                    (com)->reducere();
                     if(com->get_zile_livrare()!=0)
                           fout<<endl<<"\nStatus comanda : in curs de livrare";
                        else
                           fout<<endl<<"\nStatus comanda : livrata";

                  fout<<"\n\nTe putem ajuta cu ceva? Suna la 0723150906 sau scrie-ne la adraBeauty@gmail.com";
                  fout<<endl<<"\nReturnare gratuita in maxim 30 de zile"<<endl<<"\nDetalii livrare:\n";


                    if(com->get_nr_produse()<=7)
                        sarcini_Livratori.insert(pair<Comanda*,Livrare*>(&(*com),&(*ListaCurieri[0])));
                    else
                       sarcini_Livratori.insert(pair<Comanda*,Livrare*>(&(*com),&(*ListaCurieri[1])));

                   fout<<*(sarcini_Livratori[(com)]);
                   fout<<"\n\n\n";
                   fout<<"\n------------------------------\n";

                    }
                else if(x==1)
                {  string cuvant;
                    cout<<"Introdu numele produsului: ";
                    cin.ignore();
                    getline(cin,cuvant);
                    set<Produs*>::iterator itr;
                for (itr = ListaProduse.begin(); itr != ListaProduse.end(); itr++)
                     if((*itr)->get_nume_produs()==cuvant)
                       {

                      if(typeid(*(*itr))==typeid(PaletaMachiaj))
                        {
                           PaletaMachiaj *paleta= (PaletaMachiaj*)&(*(*itr));
                           *com=*com+(*paleta);
                           *paleta--;
                          }
                     else
                        {
                        Buze *paleta= (Buze*)&(*(*itr));
                           *com=*com+(*paleta);
                           *paleta--;
                     }
                     }

                }
                else {string cuvant;
                    cout<<"Introdu numele produsului care trebuie sters: ";
                    cin.ignore();
                    getline(cin,cuvant);
                    set<Produs*>::iterator itr;
                for (itr = ListaProduse.begin(); itr != ListaProduse.end(); itr++)
                     if((*itr)->get_nume_produs()==cuvant)
                        {if(typeid(*(*itr))==typeid(PaletaMachiaj))
                        {
                            PaletaMachiaj *paleta= (PaletaMachiaj*)&(*(*itr));
                               com->sterge_paleta(*paleta);

                          }
                     else
                        {
                           Buze *paleta= (Buze*)&(*(*itr));
                           com->sterge_buze(*paleta);


                     }
                     }
                }




                }

                break;


            }
                case 2:{system("cls");
                cout<<"Comenzile : ";
                list<Comanda*>::iterator itr;
                for (itr = ListaComanda.begin(); itr != ListaComanda.end(); itr++)
                 {cout << (*(*(itr)));
                 cout<<"\n------------------------------\n";}
                break;
            }

             case 3:{system("cls");
                set<Produs*>::iterator itr;
                cout<<"Produsele in stoc: "<<endl;
                for (itr = ListaProduse.begin(); itr != ListaProduse.end(); itr++)
                     {cout << (*itr)->get_nume_produs()<<", "<<(*itr)->get_pret()<<" lei"<<", "<<(*itr)->get_in_stoc()<<" ramase in stoc";
                     cout<<"\n------------------------------\n";}

                break;
            }

              case 4:{system("cls");

                   int cuvant;
                    cout<<"introdu id comanda: ";
                    cin>>cuvant;
                   list<Comanda*>::iterator itr;
                   for (itr = ListaComanda.begin(); itr != ListaComanda.end(); itr++)
                     if((*itr)->get_id_comanda()==cuvant)
                        {ListaComanda.erase(*&itr);
                        om->sterg_comanda(*(*itr));}






                        break;
                    }


           case 5:{system("cls");
                string nume_produs;
                 set<Produs*>::iterator itr;
                cout<<"Ce produs cautati?: "<<endl;
                cin>>nume_produs;
                for (itr = ListaProduse.begin(); itr != ListaProduse.end(); itr++)
                     if(((*itr)->contine_cuvantul(nume_produs))==1)

                        {cout << (*itr)->get_nume_produs()<<", "<<(*itr)->get_pret()<<" lei";
                          cout<<"\n------------------------------\n";}
                   cout<<"Apasati tasta 1 petru DETALII PRODUSE sau 0 in caz contrar\n";

                    int x;cin>>x;
                    if(x==1)
                        for (itr = ListaProduse.begin(); itr != ListaProduse.end(); itr++)
                     if(((*itr)->contine_cuvantul(nume_produs))==1)
                        {cout << *(*itr);
                          cout<<"\n------------------------------\n";}

                break;


            }

             case 7:{system("cls");


                k=0;
                break;


            }

           case 6:{system("cls");

                 set<Produs*>::iterator itr;


                for (itr = ListaProduse.begin(); itr != ListaProduse.end(); itr++)
                     if(((*itr)->contine_ingredientul("bio"))==1)
                        {cout << (*itr)->get_nume_produs()<<", "<<(*itr)->get_pret()<<" lei";
                          cout<<"\n------------------------------\n";}


                break;

            }



        }


       }


      }


    }
    else c1=1;
}
    return 0;
}
