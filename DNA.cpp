#include "DNA.h"
#include <iostream>
using namespace std;

DNA::DNA()
{
    seq = new char [0];
    type = promoter;
}

DNA::DNA(char *seq, DNA_Type atype)
{
    type = atype;
    this->seq = new char[strlen(seq)];
    for (int i = 0; i < strlen(seq); i++)
    {
        this->seq[i] = seq[i];
    }
}

DNA::DNA(const DNA& rhs)
{
    seq = new char[strlen(rhs.seq)];
    type = rhs.type;
    startIndex = rhs.startIndex;
    endIndex = rhs.endIndex;
    for (int i = 0; i <strlen(rhs.seq); i++)
        seq[i] = rhs.seq[i];
}

DNA::~DNA()
{
    delete seq;
}

void DNA::Print()
{
    for (int i = 0; i < strlen(seq) ; i++)
    {
        cout << seq[i];
    }
}

void DNA::set_startIndex()
{
    int num;
    cout << "Please, enter start index : ";
    cin >> num;
    startIndex = num;
}

void DNA::set_endIndex()
{
    int num;
    cout << "Please, enter end index : ";
    cin >> num;
    endIndex = num;
}

int DNA::get_startIndex()
{
    return startIndex;
}

int DNA::get_endIndex()
{
    return endIndex;
}

void DNA::BuildComplementaryStrand()
{
    complementary_strand = new DNA;
    for (int i = 0 ; i < strlen(seq) ; i++)
    {
        if (seq[i] == 'A')
            complementary_strand->seq[i] = 'T';
        else if (seq[i] == 'T')
            complementary_strand->seq[i] = 'A';
        else if (seq[i] == 'G')
            complementary_strand->seq[i] = 'C';
        else
            complementary_strand->seq[i] = 'G';
    }
    for (int i = 0; i < strlen(seq)/2; i++)
    {
        char temp = complementary_strand->seq[i];
        complementary_strand->seq[i] = complementary_strand->seq[strlen(seq) - i-1];
        complementary_strand->seq[strlen(seq) - i-1] = temp;
    }
}

RNA DNA::ConvertToRNA()
{
    set_startIndex();
    set_endIndex();
    int x, j;
    if (startIndex == -1 && endIndex == -1)
    {
        x = 0;
        j = strlen(complementary_strand->seq)-1;
    }
    else
    {
        x = startIndex-1;
        j = endIndex-1;
    }
    int y=0;
    char *temp = new char[strlen(complementary_strand->seq)+1];
    temp[strlen(complementary_strand->seq)]='\0';
    for (int k=x; k <= j; k++)
    {
        if (complementary_strand->seq[k] == 'T')
            temp[y] = 'U';
        else
            temp[y] = complementary_strand->seq[k];
        y++;
    }
    RNA r(temp, mRNA);
    return r;
}

istream& operator>> (istream& in, DNA& d)
{
    int length ;
    string s="Invalid Sequence of DNA.";
    cout<<"Please, Enter the length of DNA : ";
    cin>>length;
    cout<<"Please, Enter the DNA Sequence : ";
    d.seq =  new char [length];
    for(int i=0 ; i<length ; i++)
    {
        in>>d.seq[i];
        if(d.seq[i]!='A'&&d.seq[i]!='T'&&d.seq[i]!='C'&&d.seq[i]!='G')
            throw s;
    }
    return in;
}

ostream& operator<< (ostream& out, DNA& d)
{
    cout<<"The DNA Sequence : ";
    for(int i=0 ; i<strlen(d.seq) ; i++)
    {
        out<<d.seq[i];
    }
    return out;
}

bool DNA :: operator== (DNA& d)
{
    if(strlen(seq)==strlen(d.seq))
    {
        int counter=0;
        for(int i=0 ; i<strlen(seq) ; i++)
        {
            if(seq[i]==d.seq[i])
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
bool DNA :: operator!= (DNA& d)
{
    if(strlen(seq)==strlen(d.seq))
    {
        int counter=0;
        for(int i=0 ; i<strlen(seq) ; i++)
        {
            if(seq[i]!=d.seq[i])
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

DNA DNA :: operator+ (DNA& d)
{
    DNA d2;
    d2.seq=new char [strlen(seq)+strlen(d.seq)+1];
    d2.seq[strlen(seq)+strlen(d.seq)]='\0';
    int x=0;
    for(int i=0 ; i<strlen(seq); i++)
    {
        d2.seq[i]=seq[i];
    }
    for(int i=strlen(seq) ; i<(strlen(seq)+strlen(d.seq)) ; i++)
    {
        d2.seq[i]=d.seq[x];
        x++;
    }
    return d2;
}

DNA DNA :: operator= (DNA& D)
{
    seq = new char [strlen(D.seq)];
    for(int i=0 ; i<strlen(D.seq) ; i++)
    {
        seq[i] = D.seq[i];
    }
    return *this;
}


void DNA::Load_Sequence()
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

void DNA::Save_Sequence()
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

