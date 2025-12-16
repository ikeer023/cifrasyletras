#include <fstream>
#include <map>
#include <iostream>
#include "dictionary.h"
#include "letters_set.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 4) {
        cout << "Los parametros son: " << endl;
        cout << "1.- El fichero con el diccionario" << endl;
        cout << "2.- El fichero con las letras" << endl;
        cout << "3.- El fichero de salida" << endl;
        return 0;
    }

    // Abrimos el diccionario
    ifstream f_dic(argv[1]);
    if (!f_dic) {
        cout << "Error, no se pudo abrir el fichero del diccionario" << endl;
        return 0;
    }

    Dictionary dic;
    f_dic >> dic;
    f_dic.close();

    // Abrimos el fichero de letras
    ifstream f_let(argv[2]);
    if (!f_let) {
        cout << "Error, no se pudo abrir el fichero de letras" << endl;
        return 0;
    }

    LettersSet letras;
    f_let >> letras;
    f_let.close();

    // Calculamos las apariciones de cada letra en el diccionario
    map<char, int> apariciones;
    int total = 0;

    for (LettersSet::iterator it = letras.begin(); it != letras.end(); ++it) {
        char car = (*it).first; 
        int n = dic.getOccurrencias(car);

        apariciones[car] = n;
        total += n;
    }

    // Abrimos el fichero de salida
    ofstream f_out(argv[3]);
    if (!f_out) {
        cout << "Error, no se pudo abrir el fichero de salida" << endl;
        return 0;
    }

    // Calculamos la puntuación usando el porcentaje
    for (auto it = apariciones.begin(); it != apariciones.end(); ++it) {
        char car = it->first;
        int a = it->second;

        double porcentaje = (double) a / total;
        int puntuacion = 0;

        if (porcentaje > 0)
            puntuacion = (int)(10.0 / porcentaje);  // Inverso proporcional

        f_out << car << " " << a << " " << puntuacion << endl;
    }

    f_out.close();

    return 0;
}


