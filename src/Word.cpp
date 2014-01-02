#include "Word.hpp"
#include <string>
#include <sstream> //??

#include "LuaScriptGenerator.hpp"
#include "LuaScriptExecuter.hpp"

Word::Word()
{
    this->tag = Tag();
    this->upperWord = NULL;
    this->lowerWords = vector<Word*>();
    this->things = vector<Something*>();
}


Word::Word(Tag T)
{
    this->tag = T;
    this->upperWord = NULL;
    this->lowerWords = vector<Word*>();
    this->things = vector<Something*>();
}

//
Word* Word::FindWord(Tag t)
{
    if (this->tag == t) {
        return this;
    } else {
        for (int nS = 0; nS < lowerWords.size(); nS++)
        {
            Word* w = lowerWords[nS]->FindWord(t);
            if (w != NULL)
                return w;
        }
    }
    return NULL;
}



void Word::AddThing(Something* s)
{
     this->things.resize(this->things.size() + 1, s);

}

int Word::CountThings()
{
    return this->things.size();
}

void Word::Resort()
{
	// Se reordenan los niveles inferiores.
	for (int nW = 0; nW < this->lowerWords.size(); nW++)
		lowerWords[nW]->Resort();
    // Si el el numero de elementos en el nivel superior es menor que el numero del actual se
    if (upperWord != NULL)
    {
    	// En principio se definen los niveles:
    	//	- n0 que viene a ser el superior a la palabra superir this.
    	//	- n1 superior a this.
    	//  - n2 actual (this).
    	// -  n3 palabras de nivel inferir a this (loweWords de this).
        if (upperWord->CountThings() < this->CountThings())
        {
            ///ToDo : Preparar el algoritmo.
        	// En las referencias de n0 (nivel por enciama de upperWord) se busca la referencia a upper y se substituye por this.
        	upperWord->ReplaceLowerWord(upperWord, this);
        	// Se guarda la referencia a palabra de n0.
        	Word* w_n0 = upperWord->GetUpper();
        	// en la palabra de n1 se remplaza upperWord por la palabra de n2 (this)
        	upperWord->SetUpper(this);
        	// en las lower de la palabara de nivel 1 se elimina la referencia al nivel 2.
        	upperWord->RemoveLowerWord(this);
        	// en this se anade el nivel n1 los niveles de n3.
        	lowerWords.resize(lowerWords.size() + 1, upperWord);
        	// se establece en la actual la nueva upper que sera el nivel n0.
        	upperWord = w_n0;
        }
    }

}


int Word::ReplaceLowerWord(Word* org, Word* rep)
{
	for (int nW = 0; nW < lowerWords.size(); nW++)
	{
		if (lowerWords[nW] == org)
		{
			lowerWords[nW] = rep;
			return 0;
		}
	}
	return -1;
}


int Word::RemoveLowerWord(Word* del)
{
	vector<Word*> lower_tmp = vector<Word*>();
	for (int nW = 0; nW < lowerWords.size(); nW++)
	{
		if (lowerWords[nW] != del)
			lower_tmp.resize(lower_tmp.size() + 1, lowerWords[nW]);
	}
	// Check if any word was deleted, if not returns -1
	if (lower_tmp.size() == lowerWords.size())
	{
		return -1;
	} else {
		lowerWords = lower_tmp;
		return 0;
	}
}

Word* Word::GetUpper()
{
	return this->upperWord;
}

Word* Word::SetUpper(Word* wu)
{
	Word* temp_w = this->upperWord;
	this->upperWord = wu;
	return temp_w;
}


void Word::AddLowerWord(Word* w)
{
	this->lowerWords.resize(this->lowerWords.size() + 1, w);
}

/*string Word::ToString()
{
	string txt = "";
	ostringstream id_string; id_string << this->CountThings();
	for (int nW = 0; nW < this->lowerWords.size(); nW++)
		txt += this->lowerWords[nW]->ToString() + "\n";
	return txt += this->tag.GetTag() + " " + id_string.str();
}*/

int Word::GetLuaScript(string script_path) {
	string slua_file = script_path + this->tag.GetTag() + ".lua";
	LuaScriptGenerator* slua_gen = new LuaScriptGenerator();
	if (slua_gen->Open(slua_file) < 0) {
		return -1;
	} else {
		/**
		 * Converts something pointer array to something collection.
		 * \todo do without conversion.
		 */
		SomethingCollection* sc = new SomethingCollection();
		for (int nS = 0; nS < this->things.size(); nS++) {
			sc->Add(*this->things[nS]);
		}
		if (slua_gen->GenerateScript(sc)) {
			slua_gen->Close();
			return true;
		} else {
			slua_gen->Close();
			return false;
		}
	}
}

int Word::Compare(string script_path, Something* s, Word& w) {
	string slua_file = script_path + this->tag.GetTag() + ".lua";
	LuaScriptExecuter* luae = new LuaScriptExecuter(slua_file);
	luae->SetParameters(s);
	int pini = luae->Execute();
	for (unsigned int nS = 0; nS < lowerWords.size(); nS++)
	{
		int pb = lowerWords[nS]->Compare(script_path, s, w);
		if (pini < pb)
		{
			pini = pb;
			w = *lowerWords.at(nS);
		}
	}
	return pini;
}

string Word::ToString()
{
	Word* aux = this;
	string tags = "";
	while (aux != NULL) {
		tags = aux->tag.GetTag() + " " + tags;
		aux = aux->upperWord;
	}
	return tags;


}

Word::~Word()
{
    //dtor
}
