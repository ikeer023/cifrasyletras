#include "letters_bag.h"
#include <cstdlib> // Necesario para utilizar rand.

// Constructor vacío
LettersBag::LettersBag() {}

// Constructor con LettersSet
LettersBag::LettersBag(const LettersSet &letterSet) {
    for (auto it = letterSet.begin(); it != letterSet.end(); ++it){
        char letter = it->first;  // Letra
        int cantidad = it->second.cantidad;  // Cantidad de veces que aparece dicha letra

        // Añadimos la letra a la bolsa tantas veces como indica la cantidad
        for (int i = 0; i < cantidad; i++) {
            letters.push_back(letter);
        }
    }
}

// Extrae una letra de la bolsa de letras
char LettersBag::extractLetter() {
    if (letters.empty()) {
        return '\0';  // Si la bolsa está vacía, devolvemos un valor nulo
    }

    int pos = rand() % letters.size();  // Calculamos una posición aleatoria, para extraer una letra
    char letter = letters[pos];

    letters.erase(letters.begin() + pos);  // Borramos la letra extraída
    return letter;
}

// Extrae varias letras de la bolsa en cada iteración
vector<char> LettersBag::extractLetter(int num) {
    vector<char> resultado;

    for (int i = 0; i < num && !letters.empty(); i++) {
        resultado.push_back(extractLetter());  // Extraemos una letra por iteración
    }

    return resultado;
}

// Devuelve el tamaño actual de la bolsa de letras
int LettersBag::size() const {
    return letters.size();
}

// Comprueba si la bolsa de letras está vacía
bool LettersBag::empty() const {
    return letters.empty();
}

// Limpia la bolsa de letras
void LettersBag::clear() {
    letters.clear();
}


