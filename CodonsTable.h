#ifndef CODONSTABLE_H
#define CODONSTABLE_H
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
/// need to create one object of that class to load the AminoAcids table
/// into memory
struct Codon
{
    char value[4];    	    /// 4th location for null character
    char AminoAcid;  	    /// corresponding AminoAcid according to Table
};

class CodonsTable
{
public:
    Codon codons[64];
public:
    /// constructors and destructor
    CodonsTable();
    ~CodonsTable();
    /// function to load all codons from the given text file
    void LoadCodonsFromFile(string codonsFileName);
    Codon getAminoAcid(char * value);
    void setCodon(char * value, char AminoAcid, int index);
};
#endif // CODONSTABLE_H
