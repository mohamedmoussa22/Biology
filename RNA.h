#ifndef RNA_H
#define RNA_H

enum RNA_Type { mRNA, pre_mRNA, mRNA_exon, mRNA_intron };
#include "Sequence.h"
#include "Protein.h"
#include "CodonsTable.h"
#include "DNA.h"
class DNA;
class Protein;
class RNA : public Sequence
{
private:
	RNA_Type type;
	int startIndex;
	int endIndex;
public:
	/// constructors and destructor
	RNA();
	RNA(char* seq, RNA_Type atype);
	RNA(const RNA& rhs);
	~RNA();
	/// function to be overridden to print all the RNA information
	void Print();
	/// function to convert the RNA sequence into protein sequence
	/// using the codonsTable object
	Protein ConvertToProtein( CodonsTable & table);
	/// function to convert the RNA sequence back to DNA
	DNA ConvertToDNA();
	friend istream& operator>> (istream& in, RNA& R);
    friend ostream& operator<< (ostream& out, RNA& R);
    bool operator== (RNA& R);
    bool operator!= (RNA& R);
    RNA operator+ (RNA& R);
    RNA operator= (RNA& R);
    ///function to set the value of the startIndex
	void set_startIndex();
	///function to set the value of endIndex
	void set_endIndex();
	///function to return the value of startndex
	int get_startIndex();
	///function to return the value of endIndex
	int get_endIndex();
    /// function to load sequence from file
    void Load_Sequence();
    /// function to save sequence from file
    void Save_Sequence();
};




#endif // RNA_H
