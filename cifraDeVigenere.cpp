#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

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
std::string retiraEspacosPontuacao(const std::string &texto)
{
    std::string textoSemEspacosPontuacao;
    for (char letra : texto)
    {
        if (std::isalpha(letra))
        {
            textoSemEspacosPontuacao += letra;
        }
    }

    return textoSemEspacosPontuacao;
}
int main() {
    string textoOriginal = "Quem se interessa por aprender a falar Português já pode contar com um ensino eficiente. Com os nossos métodos conseguimos ensinar, sobretudo alunos iniciantes, por meio de textos práticos, que favorecem a boa leitura e consequente compreensão do que é ensinado.Todo o aprendizado foi concebido com o objetivo de proporcionar uma forma inovadora e agradável de ensino, algo que foi estabelecido ao se empregar artigos de interesse geral que são voltados à construção de vocabulário e compreensão dos elementos gramaticais.";
    string chave = "principeencantadoo";

    string textoOriginalSemEspacosPontuacao = retiraEspacosPontuacao(textoOriginal);
    // to lower
    for (char &c : textoOriginalSemEspacosPontuacao) {
        c = tolower(c);
    }



    cout << "Texto original: " << endl << textoOriginal << endl;
    string textoCifrado = cifraVigenere(textoOriginalSemEspacosPontuacao, chave);
    cout << "Texto cifrado: " << endl << textoCifrado << endl;


    string textoDecifrado = decifraVigenere(textoCifrado, chave);
    cout << "Texto decifrado: " << endl  << textoDecifrado << endl;

    return 0;
}

