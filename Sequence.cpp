#include "Sequence.h"

Sequence::Sequence()
{
}

Sequence::Sequence(int length)
{
    seq = new char[length];

}

Sequence::~Sequence()
{
    delete seq;
}

Sequence::Sequence(const Sequence& rhs)
{
    seq = new char[sizeof(rhs.seq)];
    for (int i = 0; i <sizeof(rhs.seq); i++)
        seq[i] = rhs.seq[i];
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

int lcs(char *X, char *Y, int m, int n,int** t)
{
    int i, j;
    /* Following steps build L[m+1][n+1] in bottom up fashion. Note
    that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
    for (i=0; i<=m; i++)
    {
        for (j=0; j<=n; j++)
        {
            if (i == 0 || j == 0)
                t[i][j] = 0;
            else if (X[i-1] == Y[j-1])
                t[i][j] = t[i-1][j-1] + 1;
            else
                t[i][j] = max(t[i-1][j], t[i][j-1]);
        }
    }
    return t[m][n];
}


char* Align(Sequence * s1, Sequence * s2, int& l)
{

    string res = "";
    int** mat = new int* [strlen(s1->seq)+1];
    for (int i = 0; i < strlen(s1->seq)+1; i++)
    {
        mat[i] = new int[strlen(s2->seq)+1];
    }
    for (int i = 0; i < strlen(s1->seq); i++)
    {
        for (int j = 0; j < strlen(s2->seq); j++)
        {
            mat[i][j] = 0;
        }
    }

    int cn = lcs(s1->seq, s2->seq, strlen(s1->seq), strlen(s2->seq),mat);
    int LCS = cn;
    for (int i = strlen(s1->seq); i > 0; i--)
    {
        for (int j = strlen(s2->seq); j > 0; j--)
        {
            if (mat[i][j] == cn && s1->seq[i-1] == s2->seq[j-1])
            {
                cn--;
                res += s1->seq[i-1];
                break;
            }
        }
    }
    char* result = new char[LCS];
    for (int i = LCS; i > 0; i--)
    {
        result[LCS-i] = res[i-1];
    }
    l = LCS;
    return result;
}

