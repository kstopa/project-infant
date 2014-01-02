#ifndef WORD_H
#define WORD_H

#include <vector>
#include <string>

#include "Tag.hpp"
#include "Something.hpp"


class Word {
    public:
        // Tag that define the category/word.
        Tag tag;
        // Constructor
        Word();
        // Constructor
        Word(Tag T);
        // Establece la categoria superiror y devuelve el elemento que anteriormente la ocupada.
        Word* SetUpper(Word* wu);
        // Obtiene la categoria superior.
        Word* GetUpper();
        // Establece la categoria inferior.
        Word* SetLower(Word * wl);
        // Obtiene la categoria inferior.
        Word* GetLower();
        // Finds for a word that its deffined by tag t in this and lower categorized words.
        Word* FindWord(Tag T);
        // Subtituye una palabra en las lowerWords por una nueva.
        int ReplaceLowerWord(Word* org, Word* rep);
        // Elimina el enlace a del dentro de las lower de la palabra.
        int RemoveLowerWord(Word* del);
        // Anade un nuevo objeto asociado al tag.
        void AddThing(Something* s);
        // Obtiene el numero de objetos guardados en la categoria.
        int CountThings();
        /**
         * Reorganiza las palabras y jerarquias inferiores de la palabra.
         */
        void Resort();
        /**
         * Adds new word for lower words in the hierarchy of this word.
         */
        void AddLowerWord(Word* w);
        /**
         * \fn Generate a lua script for known objects represented by this word.
         * \return Negative value if there are any problem for generate the script.
         */
        int GetLuaScript(string script_path);
        /**
         * Execute generated lua script and compare something it in.
         * \param S Something pointer that will be compared.
         * \return percent value that indicates the similarity whit objects known by this word.
         */
        int Compare(string script_path, Something* s, Word& w);
        /**
         * Return full tag name of this word, it means this word tag and all except main tag that
         * identifies objects described by this word.
         * \return String with tag concatenated data.
         */
        string ToString();

        /**
         * Class default destructor.
         */
        virtual ~Word();

        /// Todo.... estudiar formas de obtener caracteristicas que identifiquen los objetos del grupo (vectores, reglas, etc).
    protected:
    private:
        // Punteros a los objetos que se definen con el tag.
        vector<Something*> things;
        // Puntero a la palabra anterior de la jerarquia.
        Word* upperWord;
        // Punteros a las siguiente palabras en la jerarquia.
        vector<Word*> lowerWords;
};

#endif // WORD_H
