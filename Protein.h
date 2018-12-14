#ifndef PROTEIN_H
#define PROTEIN_H


enum Protein_Type { Hormon, Enzyme, TF, Cellular_Function };
#include"Sequence.h"
#include "DNA.h"
class DNA;
class Sequence;
class Protein : public Sequence
{
private:
	Protein_Type type;
public:
	/// constructors and destructor
	Protein();
	Protein(char * p);
	~Protein();
    void Print();
    /// return an array of DNA sequences that can possibly
    /// generate that protein sequence
    DNA* GetDNAStrandsEncodingMe(const DNA & bigDNA);
    ///function to load Sequence from file
    void Load_Sequence();
    ///function to  save Sequence to file
    void Save_Sequence();
    /// operators >> , << , == , != , + , =
    friend istream& operator>> (istream& in, Protein& P);
    friend ostream& operator<< (ostream& out, Protein& P);
    bool operator== (Protein& P);
    bool operator!= (Protein& P);
    Protein operator+ (Protein& P);
    Protein operator= (Protein& P);
};



#endif // PROTEIN_H
