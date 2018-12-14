#include "Protein.h"


Protein::Protein()
{
}


Protein::~Protein()
{
    delete seq;
}
Protein:: Protein(char * p)
{
    seq = new char [strlen(p)];
    for(int i=0 ; i<strlen(p) ; i++)
    {
        seq[i] = p[i];
    }
}

void Protein::Print()
{
    for(int i=0 ; i<strlen(seq) ; i++)
    {
        cout<<seq[i];
    }
}


/*DNA* Protein :: GetDNAStrandsEncodingMe(DNA bigDNA,int & DNACount)
{
    string temp = ""; // string to carry all characters converted from DNA
    DNA * allStrands = new DNA[strlen(bigDNA.seq)];
    int strandCounter = 0; // count of found DNA strands identical to Protein
    RNA bigRNA = bigDNA.ConvertToRNA();
    CodonsTable cdns;
    int counter = 0;
    // Loop on every 3 characters to check the amino acid character.
    for (int i = 0; i < strlen(bigDNA.seq) - 2; i+=3)
    {
        for (int j = 0; j < 64; j++)
        {
            if (bigRNA.getCharFromSeq(i) == cdns.codons[j].value[0] && bigRNA.getCharFromSeq(i + 1) == cdns.codons[j].value[1] && bigRNA.getCharFromSeq(i + 2) == cdns.codons[j].value[2])
            {
                temp += cdns.codons[j].AminoAcid;
                counter++;

                // if the string length is same of protein length, start checking if it is Identical the protein object
                if (counter == length)
                {
                    //dnaStrandsToProtein.push_back(temp);
                    //dnaStrandsIndex.push_back(i - len*3);

                    bool isEqual = true;
                    for (int m = 0; m < length; m++)
                    {
                        if (temp[m] != seq[m])
                        {
                            isEqual = false;
                            break;
                        }
                    }
                    if (isEqual)
                    {
                        char * sequence = new char[length*3];
                        int seqCount = 0;
                        i -= (length-1)*3;
                        for (int j = i; j < (i + (length * 3)); j += 3)
                        {
                            sequence[seqCount++] = bigDNA.getCharFromSeq(bigDNA.getLength() - j - 1);
                            sequence[seqCount++] = bigDNA.getCharFromSeq(bigDNA.getLength() - (j + 1) - 1);
                            sequence[seqCount++] = bigDNA.getCharFromSeq(bigDNA.getLength() - (j + 2) - 1);
                        }


                        DNA onePossibility(0,length*3,sequence,promoter,length);
                        allStrands[strandCounter++] = onePossibility;
                        i += ((length-1) * 3); // if it is identical, loop starting from the next character.
                        //k += (len * 3 - 1);
                    }
                    else
                    {
                        i -= (length - 1)*3 + 2; // if not found start checking again from the index right after the first character taken in the temp string.
                    }

                    temp = "";
                    counter = 0;
                    break;
                }
                break;
            }
        }
    }
    DNACount = strandCounter;
    return allStrands;
}
*/
istream& operator>> (istream& in, Protein& P)
{
    int length ;
    string s="Invalid Sequence of Protein.";
    cout<<"Please, Enter the length of Protein : ";
    cin>>length;
    P.seq =  new char [length];
    cout<<"Please, Enter The Protein Sequence : ";
    for(int i=0 ; i<length ; i++)
    {

        in>>P.seq[i];
        int counter=0;
        char arr[]= {'K','N','T','R','S','I','M','Q','H','P','L','E','D','A','G','V','Y','C','W','F'};
        for(int i=0 ; i<length ; i++)
        {
            for(int j=0 ; j<20 ; j++)
            {
                if(P.seq[i]!=arr[j])
                {
                    counter++;
                    break;
                }
            }
            if(counter>0)
            {
                throw s;
                break;
            }
        }
    }
}


ostream& operator<< (ostream& out, Protein& P)
{
    cout<<"The Protein Sequence : ";
    for(int i=0 ; i<strlen(P.seq) ; i++)
    {
        out<<P.seq[i];
    }
}

bool Protein :: operator== (Protein& P)
{
    if(strlen(P.seq)==strlen(seq))
    {
        int counter=0;
        for(int i=0 ; i<strlen(seq) ; i++)
        {
            if(seq[i]==P.seq[i])
            {
                counter++;
            }
            else
                break;
        }
        if(counter==strlen(seq))
            return true;
        else
            return false;
    }
    else
        return false;
}
bool Protein :: operator!= (Protein& P)
{
    if(strlen(P.seq)==strlen(seq))
    {
        int counter=0;
        for(int i=0 ; i<strlen(seq) ; i++)
        {
            if(seq[i]!=P.seq[i])
            {
                return true;
                break;
            }
            else
                counter++;
        }
        if(counter !=0)
            return false;
        else
            return true;
    }
    else
        return true;
}

Protein Protein :: operator+ (Protein& P)
{
    Protein P2;
    P2.seq=new char [strlen(seq)+strlen(P.seq)+1];
    P.seq[strlen(seq)+strlen(P.seq)]='\0';
    int x=0;
    for(int i=0 ; i<strlen(seq); i++)
    {
        P2.seq[i]=seq[i];
    }
    for(int i=strlen(seq) ; i<strlen(seq)+strlen(P.seq) ; i++)
    {
        P2.seq[i]=P.seq[x];
        x++;
    }
    return P2;
}


Protein Protein :: operator= (Protein& P)
{
    seq = new char [strlen(P.seq)];
    for(int i=0 ; i<strlen(P.seq) ; i++)
    {
        seq[i] = P.seq[i];
    }
    return *this;
}

void Protein::Load_Sequence()
{
    string s;
    fstream datafile;
    char filename[80];
    cout<<"Please, Enter file name : ";
    cin.getline(filename,80);
    datafile.open(filename);
    while(!datafile.eof() && !datafile.fail())
    {
        datafile >> s;
    }
    seq = new char [s.size()];
    for(int i=0 ; i<s.size() ; i++)
    {
        seq[i]=s[i];
    }
    datafile.close();
}

void Protein::Save_Sequence()
{
    fstream datafile;
    char filename[80];
    cout<<"Please, Enter file name : ";
    cin.ignore();
    cin.getline(filename,80);
    datafile.open(filename,ios::app);
    for(int i=0 ; i<strlen(seq) ; i++)
    {
        datafile << seq[i];
    }
    datafile.close();
}

