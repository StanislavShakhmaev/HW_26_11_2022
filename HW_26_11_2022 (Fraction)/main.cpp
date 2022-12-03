#include <iostream>
using namespace std;

#define WIDTH 32

class Fraction;
Fraction operator+(Fraction left, Fraction right);
Fraction operator*(Fraction left, Fraction right);
Fraction operator-(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);

class Fraction
{
	int integer;
	int numerator;
	int denominator;
public:
	int get_integer() const
	{
		return integer;
	}
	int get_numerator() const
	{
		return numerator;
	}
	int get_denominator() const
	{
		return denominator;
	}
	void set_integer (int integer)
	{
		this->integer = integer;
	}
	void set_numerator (int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator (int denominator)
	{
		if (denominator == 0) denominator = 1;
		this->denominator = denominator;
	}
	
	// Constructor:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout.width(WIDTH);
		cout << left << "DeafaultConstructor:\t" << this << endl;
	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout.width(WIDTH);
		cout << left << "SingleArgumentConstructor:\t" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout.width(WIDTH);
		cout << left << "Constructor:\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator (denominator);
		cout.width(WIDTH);
		cout << left << "Constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout.width(WIDTH);
		cout << left << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}
	//Operators:

	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout.width(WIDTH);
		cout << left << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	Fraction& operator+=(const Fraction& other)
	{
		return *this = *this+other;
	}
	Fraction& operator-=(const Fraction& other)
	{
		return *this = *this - other;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this*other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this/other;
	}
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction& operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}
	Fraction& operator--()
	{
		integer--;
		return *this;
	}
	Fraction& operator--(int)
	{
		Fraction old = *this;
		integer--;
		return old;
	}

	// Methods:
	void to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
	}
	void to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
	}
	Fraction inverted() const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		int buffer = inverted.numerator;
		inverted.numerator = inverted.denominator;
		inverted.denominator = buffer;
		return inverted;
	}
	Fraction reduce()
	{
		int more, less, rest;
		if (numerator > denominator)
		{
			more = numerator;
			less = denominator;
		}
		else
		{
			more = denominator;
			less = numerator;
		}
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more;
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}
	Fraction Check()
	{
		if (denominator < 0)
		{
			if (integer) denominator = denominator * (-1);
			else
			{
				numerator = numerator * (-1);
				denominator = denominator * (-1);
			}
		}
		return *this;
	}
	void print() const
	{
		if (integer) cout << integer;
		if (numerator)
		{
			if (integer) cout << "(";
			cout << numerator << "/" << denominator;
			if (integer) cout << ")";
		}
		else if (integer == 0) cout << 0;
		cout << endl;
	}
};

Fraction operator+(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	Fraction res;
	res.set_numerator(left.get_numerator()*right.get_denominator() + right.get_numerator()*left.get_denominator());
	res.set_denominator(left.get_denominator()*right.get_denominator());
	res.to_proper();
	res.reduce();
	return res;
}

Fraction operator-(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	Fraction res;
	res.set_numerator(left.get_numerator()*right.get_denominator() - right.get_numerator()*left.get_denominator());
	res.set_denominator(left.get_denominator()*right.get_denominator());
	
	res.to_proper();
	res.reduce();
	res.Check();
	return res;
}

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	Fraction res;
	res.set_numerator(left.get_numerator()*right.get_numerator());
	res.set_denominator(left.get_denominator()*right.get_denominator());
	res.to_proper();
	res.reduce();
	return res;
}

Fraction operator/(const Fraction& left,const Fraction& right)
{
	/*left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator()*right.get_denominator(),
		left.get_denominator()*right.get_numerator()
	);*/
	return left * right.inverted();
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_numerator()*right.get_denominator() > right.get_numerator()*left.get_denominator()) return true;
	else return false;
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_numerator()*right.get_denominator() < right.get_numerator()*left.get_denominator()) return true;
	else return false;
}
bool operator<=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_numerator()*right.get_denominator() <= right.get_numerator()*left.get_denominator()) return true;
	else return false;
}
bool operator>=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_numerator()*right.get_denominator() >= right.get_numerator()*left.get_denominator()) return true;
	else return false;
}
bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	if (left.get_numerator()*right.get_denominator() == right.get_numerator()*left.get_denominator()) return true;
	else return false;
}
bool operator!=(Fraction left, Fraction right)
{
	return !(left == right);
}
//#define CONSTRUCTORS_CHECK
#define ARITHMETICAL_OPERATORS_CHECK
//#define INCREMENT_CHECK

void main()
{
	setlocale(LC_ALL, " ");
	
#ifdef CONSTRUCTORS_CHECK
	Fraction A;
	A.print();

	Fraction B = 5;
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();

	Fraction E = D;
	E.print();

	Fraction F;
	F = E;
	F.print();
#endif
#ifdef ARITHMETICAL_OPERATORS_CHECK
	Fraction A(2, 3, 4);
	A.print();
	/*A.to_improper();
	A.print();
	A.to_proper();
	A.print();*/

	Fraction B(3, 4, 5);
	B.print();
	/*B.to_improper();
	B.print();
	B.to_proper();
	B.print();*/

	Fraction C = A * B;
	C.print();
	C = A / B;
	C.print();

	A *= B;
	A.print();

	A /= B;
	A.print();
	
	Fraction F;
	F = A + B;
	F.print();

	Fraction G;
	G = A - B;
	G.print();

	A += B;
	A.print();

	A -= B;
	A.print();

#endif
#ifdef INCREMENT_CHECK
	for (double i = 0.50738; i < 10; i++)
	{
		cout << i << "\t";
	}
	cout << endl;

	for (Fraction i(1, 2); i.get_integer() < 10; i++)
	{
		i.print();
	}
	for (Fraction i(10,1, 2); i.get_integer() > 0; i--)
	{
		i.print();
	}
#endif
	cout << (Fraction(1, 2) == Fraction(5, 10)) << endl;
	cout << (Fraction(1, 2) != Fraction(5, 10)) << endl;
	cout << (Fraction(1, 2) > Fraction(6, 10)) << endl;
	cout << (Fraction(1, 2) < Fraction(6, 10)) << endl;
	cout << (Fraction(1, 2) >= Fraction(5, 10)) << endl;
	cout << (Fraction(1, 2) <= Fraction(5, 10)) << endl;
}