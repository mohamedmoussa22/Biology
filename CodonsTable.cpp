#include "CodonsTable.h"



CodonsTable::CodonsTable()
{
}

CodonsTable::~CodonsTable()
{
}

void CodonsTable:: LoadCodonsFromFile(string codonsFileName)
{
    fstream datafile;
    datafile.open(codonsFileName.c_str());
    int i = 0;
    while (!datafile.eof() && !datafile.fail())
    {
        datafile >> codons[i].value;
        codons[i].AminoAcid = codons[i].value[3];
        codons[i].value[3] = '\0';
        i++;
    }
}

Codon CodonsTable::getAminoAcid(char* value)
{
    for (int i = 0; i < 64; i++)
    {
        if (codons[i].value == value)
            return codons[i];
    }
}

void CodonsTable :: setCodon(char * value, char AminoAcid, int index)
{
    Codon temp;
    for (int i = 0; i < 4; i++)
    {
        temp.value[i] = value[i];
    }
    temp.AminoAcid = AminoAcid;
    codons[index] = temp;
}
