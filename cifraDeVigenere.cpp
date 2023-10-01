#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
// Tabela de frequência de letras em português
map<char, double> frequenciaPortugues = {
    {'a', 14.63},
    {'b', 1.04},
    {'c', 3.88},
    {'d', 4.99},
    {'e', 12.57},
    {'f', 1.02},
    {'g', 1.30},
    {'h', 1.28},
    {'i', 6.18},
    {'j', 0.40},
    {'k', 0.02},
    {'l', 2.78},
    {'m', 4.74},
    {'n', 5.05},
    {'o', 10.73},
    {'p', 2.52},
    {'q', 1.20},
    {'r', 6.53},
    {'s', 7.81},
    {'t', 4.34},
    {'u', 4.63},
    {'v', 1.67},
    {'w', 0.01},
    {'x', 0.21},
    {'y', 0.01},
    {'z', 0.47}
};

// Função para descriptografar um grupo de letras com base na tabela de frequência
string descriptografarGrupo(const string& grupo) {
    string resultado;
    map<char, int> frequenciaGrupo;

    // Contar a frequência das letras no grupo
    for (char letra : grupo) {
        frequenciaGrupo[letra]++;
    }

    // Encontrar a letra mais frequente no grupo
    char letraMaisFrequente = grupo[0];
    for (char letra : grupo) {
        if (frequenciaGrupo[letra] > frequenciaGrupo[letraMaisFrequente]) {
            letraMaisFrequente = letra;
        }
    }

    // Encontrar a letra correspondente na tabela de frequência
    char letraDescriptografada;
    for (const auto& pair : frequenciaPortugues) {
        if (pair.second == frequenciaPortugues[letraMaisFrequente]) {
            letraDescriptografada = pair.first;
            break;
        }
    }

    // Descriptografar o grupo
    for (char letra : grupo) {
        if (isalpha(letra)) {
            char letraOriginal = isupper(letra) ? toupper(letraDescriptografada) : letraDescriptografada;
            resultado += letraOriginal;
        } else {
            resultado += letra;
        }
    }

    return resultado;
}


string cifraVigenere(string texto, string chave) {
    string textoCifrado = "";
    int tamanhoChave = chave.length();

    for (int i = 0; i < texto.length(); i++) {
        char caractereOriginal = texto[i];
        char caractereChave = chave[i % tamanhoChave];

        // Verifique se o caractere original é uma letra do alfabeto
        if (isalpha(caractereOriginal)) {
            char base = islower(caractereOriginal) ? 'a' : 'A';

            // Converta o caractere original e chave para valores de 0 a 25
            int valorOriginal = caractereOriginal - base;

            int valorChave = tolower(caractereChave) - 'a';

            // Aplique a cifração de Vigenère
            int valorCifrado = (valorOriginal + valorChave) % 26;

            // Converta o valor cifrado de volta para um caractere no mesmo caso (minúscula ou maiúscula)
            char caractereCifrado = valorCifrado + base;

            // Adicione o caractere cifrado à string de texto cifrado
            textoCifrado += caractereCifrado;
        } else {
            // Mantenha caracteres não alfabéticos inalterados
            textoCifrado += caractereOriginal;
        }
    }
    return textoCifrado;
}

string decifraVigenere(string textoCifrado, string chave) {
    string textoDecifrado = "";
    int tamanhoChave = chave.length();

    for (int i = 0; i < textoCifrado.length(); i++) {
        char caractereCifrado = textoCifrado[i];
        char caractereChave = chave[i % tamanhoChave];

        // Verifique se o caractere cifrado é uma letra do alfabeto
        if (isalpha(caractereCifrado)) {
            char base = islower(caractereCifrado) ? 'a' : 'A';

            // Converta o caractere cifrado e chave para valores de 0 a 25
            int valorCifrado = caractereCifrado - base;

            int valorChave = tolower(caractereChave) - 'a';


            // Aplique a decifração de Vigenère
            int valorDecifrado = (valorCifrado - valorChave + 26) % 26;

            // Converta o valor decifrado de volta para um caractere no mesmo caso (minúscula ou maiúscula)
            char caractereDecifrado = valorDecifrado + base;

            // Adicione o caractere decifrado à string de texto decifrado
            textoDecifrado += caractereDecifrado;
        } else {
            // Mantenha caracteres não alfabéticos inalterados
            textoDecifrado += caractereCifrado;
        }
    }

    return textoDecifrado;
}

int main() {
    string textoOriginal = "I had a great weekend. My wife and I got married 30 years ago. My wife and I were really surprised when our son came to our house on Thursday evening. He then took us to the airport and gave us two tickets to go to Rome! He paid for everything: the flight, the hotel, everything. We had a lovely weekend. We remembered the night we got married. It was wonderful.I had a really terrible weekend. My boyfriend took me out to this really expensive restaurant. In the middle of our dinner, he gave me a very beautiful ring and he asked me to marry him. I was really surprised. I said no. I like him, but I knew I didn’t want to marry him. He was quite angry and sad. It was awful.";
    string chave = "principeencantadoo";



    cout << "Texto original: " << endl << textoOriginal << endl;
    string textoCifrado = cifraVigenere(textoOriginal, chave);
    cout << "Texto cifrado: " << endl << textoCifrado << endl;

    // string textoQuebrado = quebrarCifra(textoCifrado);
    // cout << "Texto Quebrado: " << endl << textoQuebrado << endl;

    string textoDecifrado = decifraVigenere(textoCifrado, chave);
    cout << "Texto decifrado: " << endl  << textoDecifrado << endl;

    return 0;
}

