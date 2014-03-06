#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdio>
#include "LinkedList.h"

using namespace std;

class atomic
{

private:

	static LinkedList<atomic>* get_match(LinkedList<atomic> a, LinkedList<atomic> b, int match_a, int match_b)
	{
		LinkedList<atomic>* lla = new LinkedList<atomic>();
		for(int i = 0; i < a.size; i++)
		{
			for(int j = 0; j < b.size; j++)
			{
				if (contains(*lla,a.get(i)) == false && i != match_a)
					lla->add(a.get(i));
				if (contains(*lla,b.get(j)) == false && j != match_b)
					lla->add(b.get(j));
			}
		}
		return lla;
	}

public:
	string atom;
	bool negate;

	static bool contains(LinkedList<atomic>a, atomic b)
	{
		for(int i = 0; i < a.size; i++)
		{
			if (a.get(i)->compare(b) == true)
				return true;
		}
		return false;
	}

	atomic(string atom, bool negate)
	{
		this->atom = atom;
		this->negate = negate;
	}

	atomic(atomic* atom)
	{
		this->atom = atom->atom;
		this->negate = atom->negate;
	}

	atomic()
	{
		this->atom = "";
		this->negate = false;
	}

	bool compare(atomic a)
	{
		return ((this->atom.compare(a.atom) == 0) && (this->negate == a.negate));
	}

	string toString()
	{
		string s = (negate==true? "~" : "") + this->atom;
		return s;
	}

	static LinkedList<atomic>* atomic_from_string(string formula_clausal)
	{
		LinkedList<atomic> * lla = new LinkedList<atomic>();
		string* s = new string("");
		for(int i = 1; i < formula_clausal.length()-1;i++)
		{
			if (formula_clausal.at(i) != ',')
			{
				s->append(formula_clausal.substr(i,1));
			}
			else
			{
				if (s->substr(0,1).at(0) == '~')
					lla->add(new atomic(s->substr(1),true));
				else
					lla->add(new atomic(*s,false));
				s = new string("");
			}
		}
		if (s->substr(0,1).at(0) == '~')
			lla->add(new atomic(s->substr(1),true));
		else
			lla->add(new atomic(*s,false));

		return lla;
		//parei aqui
	}

	static LinkedList< LinkedList<atomic> >* atomic_from_formula(string formula)
	{
		LinkedList< LinkedList<atomic> > * llf = new LinkedList< LinkedList<atomic> >();
		string* s = new string("");
		for(int i = 1; i < formula.size()-1; i++)
		{
			if (formula.at(i) != '}')
			{
				s->append(formula.substr(i,1));
			}
			else
			{
				if (formula.at(i) == '}')
				{
					s->append("}");
					i++;
				}
				llf->add(atomic::atomic_from_string(*s));
				s = new string("");
			}
		}
		//llf->add(atomic::atomic_from_string(*s));
		//s = new string("");
		return llf;
	}

	static bool tableaux_contains_formula(LinkedList< LinkedList<atomic> > tableaux, LinkedList<atomic> formula)
	{
	
		for(int i = 0; i < tableaux.size; i++)
		{
			bool containsb = true;
			int containscount = 0;
			LinkedList<atomic>* formula_tableaux = tableaux.get(i);
			for(int j = 0; j < formula.size; j++)
			{
				if(contains(*formula_tableaux,*formula.get(j)) == false)
				{
					containsb = false;
					break;
				}
				else
					containscount++;
			}
			if (containsb == true && containscount == formula_tableaux->size)
				return true;
			/*for(int j = 0; j < tableaux.get(i)->size; j++)
			{
				if (formula_tableaux->size != formula.size)
				{
					contains = false;
					break;
				}
				bool equals = formula_tableaux->get(j)->compare(formula.get(j));
				if (!equals)
					contains = false;
			}
			if (contains == true)
			{
				return true;
			}*/
		}
		return false;
	}
	

	static bool iteract_tableaux(LinkedList< LinkedList<atomic> >* tableaux)
	{
		int i = 0;
		bool alteration = false;
		while (i < tableaux->size)
		{
			int j = 0;
			while (j < tableaux->size)
			{
				LinkedList<atomic>* formula1 = tableaux->get(i);
				LinkedList<atomic>* formula2 = tableaux->get(j);
				LinkedList<LinkedList<atomic>>* new_formulas = atomic::resolve_two_atomic(*formula1,*formula2);

				if (formula1->size == 1 && formula2->size == 1)
				{
					if (tableaux->get(i)->get(0)->atom.compare(tableaux->get(j)->get(0)->atom) && tableaux->get(i)->get(0)->negate != tableaux->get(j)->get(0)->negate)
					{
						LinkedList<atomic>* at = new LinkedList<atomic>();
						at->add(new atomic(*new string(""), false));
						tableaux->add(at);
						return false;
					}
				}
				int z = 0;
				while (z < new_formulas->size)
				{
					if (tableaux_contains_formula(*tableaux, *new_formulas->get(z)) == false)
					{
						tableaux->add(new_formulas->get(z));
						alteration = true;
					}
					z++;
				}
				j++;
			}
			i++;
		}
		return alteration;
	}

	static LinkedList< LinkedList<atomic> >* resolve_two_atomic(LinkedList<atomic> a, LinkedList<atomic> b)
	{
		LinkedList< LinkedList<atomic> >* llf = new LinkedList< LinkedList<atomic> >();
		int i = 0;
		while (i < a.size)
		{
			int j = 0;
			while (j < b.size)
			{
				if (a.get(i)->atom.compare(b.get(j)->atom) == 0 && a.get(i)->negate != b.get(j)->negate)
				{
					LinkedList<atomic>* new_atomic = get_match(a,b,i,j);
					if (tableaux_contains_formula(*llf,*new_atomic) == false)
						llf->add(get_match(a,b,i,j));

				}
				j++;
			}
			i++;
		}
		return llf;
	}
};