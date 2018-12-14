#ifndef DNA_H
#define DNA_H

enum DNA_Type{ promoter, motif, tail, noncoding };
#include "Sequence.h"
#include "RNA.h"
#include <cstring>
class RNA;
class DNA : public Sequence
{
private:
	DNA_Type type;
	DNA * complementary_strand;
	int startIndex;
	int endIndex;
public:
	// constructors and destructor
	DNA();
	DNA(char * seq, DNA_Type atype);
	DNA(const DNA& rhs);
	~DNA();
	// function printing DNA sequence information to user
	void Print();
	/* function to convert the DNA sequence to RNA sequence
	 It starts by building the complementary_strand of the current
	 DNA sequence (starting from the startIndex to the endIndex), then,
	 it builds the RNA corresponding to that complementary_strand.*/
	RNA ConvertToRNA();
	/* function to build the second strand/pair of DNA sequence
	 To build a complementary_strand (starting from the startIndex to
	 the endIndex), convert each A to T, each T to A, each C to G, and
	 each G to C. Then reverse the resulting sequence.*/
	void BuildComplementaryStrand();
	///function to set the value of the startIndex
	void set_startIndex();
	///function to set the value of endIndex
	void set_endIndex();
	///function to return the value of startIndex
	int get_startIndex();
	///function to return the value of endIndex
	int get_endIndex();
	///function to load Sequence from file
	void Load_Sequence();
	///function to save Sequence to file
	void Save_Sequence();
	friend istream& operator>> (istream& in , DNA& d) ;
    friend ostream& operator<< (ostream& out , DNA& d) ;
    bool operator== (DNA& d);
    bool operator!= (DNA& d);
    DNA operator+ (DNA& d);
    DNA operator= (DNA& D);
};


#endif // DNA_H
