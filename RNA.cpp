#include "RNA.h"


RNA::RNA()
{
}

RNA::RNA(char * seq, RNA_Type atype)
{
    type = atype;
    this->seq = new char[strlen(seq)];
    for (int i = 0; i < strlen(seq); i++)
    {
        this->seq[i] = seq[i];
    }
}

RNA::RNA(const RNA& rhs)
{
    seq = new char[strlen(rhs.seq)];
    type = rhs.type;
    for (int i = 0; i <strlen(rhs.seq); i++)
        seq[i] = rhs.seq[i];
}

RNA::~RNA()
{
    delete seq;
}

void RNA::Print()
{
    for (int i = 0; i < strlen(seq); i++)
    {
        cout << seq[i];
    }
}

void RNA::set_startIndex()
{
    int num;
    cout << "Please, enter start index : ";
    cin >> num;
    startIndex = num;
}

void RNA::set_endIndex()
{
    int num;
    cout << "Please, enter end index : ";
    cin >> num;
    endIndex = num;
}

int RNA::get_startIndex()
{
    return startIndex;
}

int RNA::get_endIndex()
{
    return endIndex;
}


//DNA RNA::ConvertToDNA()
//{
//    int i, j;
//    set_startIndex();
//    set_endIndex();
//    if (startIndex == -1 && endIndex == -1)
//    {
//        i = 0;
//        j = strlen(seq)-1;
//    }
//    else
//    {
//        i = startIndex-1;
//        j = endIndex-1;
//    }
//    char* temp = new char[strlen(seq)+1];
//    temp[strlen(seq)] = '\0';
//    for (int x = i; x <= j; x++)
//    {
//        if (seq[i] == 'U')
//            temp[i] = 'T';
//        else
//            temp[i] = seq[i];
//    }
//    for (int k = 0; k < strlen(temp); k++)
//    {
//        char temp1 = temp[i];
//        temp[i] = temp[strlen(seq) - i - 1];
//        temp[strlen(seq) - i - 1] = temp1;
//    }
//    for (int y = 0; y < strlen(temp); y++)
//    {
//        if (temp[i] == 'A')
//            temp[i] = 'T';
//        else if (temp[i] == 'T')
//            temp[i] = 'A';
//        else if (temp[i] == 'G')
//            temp[i] = 'C';
//        else
//            temp[i] = 'G';
//    }
//    DNA d(temp, promoter);
//    d.Print();
//    return d;
//}


DNA RNA::ConvertToDNA()
{
    int i, j;
    int z=0;
    set_startIndex();
    set_endIndex();
    DNA d;
    if (startIndex == -1 && endIndex == -1)
    {
        i = 0;
        j = strlen(seq)-1;
        d.seq = new char [strlen(seq)];
    }
    else
    {
        i = startIndex-1;
        j = endIndex-1;
        d.seq = new char [j-i+1];
    }
    for (int x = i; x <= j; x++)
    {
        if (seq[x] == 'U')
            d.seq[x] = 'T';
        else
            d.seq[x] = seq[x];
    }
    for (int y = i; y <= j; y++)
    {
        if (d.seq[y] == 'A')
            d.seq[y] = 'T';
        else if (d.seq[y] == 'T')
            d.seq[y] = 'A';
        else if (d.seq[y] == 'G')
            d.seq[y] = 'C';
        else
            d.seq[y] = 'G';
    }
      for (int i = 0; i < strlen(d.seq)/2; i++)
    {
        char temp = d.seq[i];
        d.seq[i] = d.seq[strlen(seq) - i-1];
        d.seq[strlen(seq) - i-1] = temp;
    }
    return d;
}



Protein RNA::ConvertToProtein(CodonsTable& table)
{
    int counter=0, b=0, m=0, y=0;
    char* temp = new char [strlen(seq)/3+1];
    table.LoadCodonsFromFile("RNA_codon_table.txt");
    char x[3];
    int z = strlen(seq);
loop:
    for(int j=b*3 ; j<b*3+3 ; j++)
    {
        x[y]=seq[j];
        y++;
    }
    for(int i=0 ; i<64 ; i++)
    {
        for(int k=0 ; k<3 ; k++)
        {
            if(x[k]==table.codons[i].value[k])
                counter++;
            else
                break;
        }
        if(counter==3)
        {
            temp[m]=table.codons[i].AminoAcid;
            m++;
            break;
        }
        counter=0;
    }
    counter=0;
    b++;
    y=0;
    z-=3;
    if(z==0)
    {
        temp[strlen(seq)/3]='\0';
        Protein p(temp);
        return p;
    }
    else
        goto loop;
}


istream& operator>> (istream& in, RNA& R)
{
    int length ;
    string s="Invalid Sequence of DNA.";
    cout<<"Please, Enter the length of RNA : ";
    cin>>length;
    R.seq =  new char [length];
    cout<<"Please, Enter The RNA Sequence : ";
    for(int i=0 ; i<length ; i++)
    {
        in>>R.seq[i];
        if(R.seq[i]!='A'&&R.seq[i]!='U'&&R.seq[i]!='C'&&R.seq[i]!='G')
            throw s;
    }
}


ostream& operator<< (ostream& out, RNA& R)
{
    cout<<"The RNA Sequence : ";
    for(int i=0 ; i<strlen(R.seq) ; i++)
    {
        out<<R.seq[i];
    }
}

bool RNA :: operator== (RNA& R)
{
    if(strlen(seq)==strlen(R.seq))
    {
        int counter=0;
        for(int i=0 ; i<strlen(R.seq) ; i++)
        {
            if(seq[i]==R.seq[i])
            {
                counter++;
            }
            else
                break;
        }
        if(counter==strlen(R.seq))
            return true;
        else
            return false;
    }
    else
        return false;
}
bool RNA:: operator!= (RNA& R)
{
    if(strlen(seq)==strlen(R.seq))
    {
        int counter=0;
        for(int i=0 ; i<strlen(seq) ; i++)
        {
            if(R.seq[i]!=seq[i])
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

RNA RNA ::operator+ (RNA& R)
{
    RNA R2;
    R2.seq = new char [strlen(R.seq)+strlen(seq)+1];
    int x=0;
    R2.seq[strlen(R.seq)+strlen(seq)] = '\0';
    for(int i=0 ; i<strlen(seq); i++)
    {
        R2.seq[i]=seq[i];
    }
    for(int i=strlen(seq) ; i<strlen(R.seq)+strlen(seq) ; i++)
    {
        R2.seq[i]=R.seq[x];
        x++;
    }
    return R2;
}

RNA RNA :: operator= (RNA& R)
{
    seq = new char [strlen(R.seq)];
    for(int i=0 ; i<strlen(R.seq) ; i++)
    {
        seq[i] = R.seq[i];
    }
    return *this;
}


void RNA::Load_Sequence()
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

void RNA::Save_Sequence()
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
