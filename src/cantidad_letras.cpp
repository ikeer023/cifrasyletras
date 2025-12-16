#include <fstream>
#include <iostream>
#include <map>
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

    // Abrir el fichero del diccionario
    ifstream dic_fich(argv[1]);
    Dictionary dic;
    dic_fich >> dic;
    dic_fich.close();

    // Abrir el fichero con las letras
    ifstream letras_fich(argv[2]);
    LettersSet conjunto_de_letras;
    letras_fich >> conjunto_de_letras;
    letras_fich.close();

    // Mapa que guarda la cantidad de apariciones de cada letra
    map<char, int> cant_apariciones;
    int apariciones_minimas = -1;
    int apariciones_maximas = 0;

    // Contar las apariciones de cada letra en el diccionario
    for (LettersSet::iterator iterador = conjunto_de_letras.begin(); iterador != conjunto_de_letras.end(); ++iterador) {
        char letra = (*iterador).first;
        int cantidad = dic.getOccurrences(letra);

        cant_apariciones[letra] = cantidad;

        // Encontrar la letra con el mínimo y máximo de apariciones
        if (cantidad > 0 && (apariciones_minimas == -1 || cantidad < apariciones_minimas))
            apariciones_minimas = cantidad;

        if (cantidad > apariciones_maximas)
            apariciones_maximas = cantidad;
    }

    // Abrir el fichero de salida donde se guardarán los resultados
    ofstream fich_out(argv[3]);
    fich_out << "Letra Cantidad Puntos" << endl;

    // Calcular la puntuación de cada letra
    for (auto it = cant_apariciones.begin(); it != cant_apariciones.end(); ++it) {
        char letra = it->first;
        int apariciones = it->second;
        int puntuacion = 1;

        // Solo calculamos puntuación si la letra tiene apariciones
        if (apariciones > 0 && apariciones_maximas != apariciones_minimas)
            puntuacion = 1 + 9 * (apariciones_maximas - apariciones) / (apariciones_maximas - apariciones_minimas);

        fich_out << letra << "      " << apariciones << "      " << puntuacion << endl;
    }

    fich_out.close();
    return 0;
}


