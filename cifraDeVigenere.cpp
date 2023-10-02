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
// Frequência de letras em português
    map<char, double> frequenciaIngles = {
        {'a', 8.167},
        {'b', 1.492},
        {'c', 2.782},
        {'d', 4.253},
        {'e', 12.702},
        {'f', 2.228},
        {'g', 2.015},
        {'h', 6.094},
        {'i', 6.966},
        {'j', 0.153},
        {'k', 0.772},
        {'l', 4.025},
        {'m', 2.406},
        {'n', 6.749},
        {'o', 7.507},
        {'p', 1.929},
        {'q', 0.095},
        {'r', 5.987},
        {'s', 6.327},
        {'t', 9.056},
        {'u', 2.758},
        {'v', 0.978},
        {'w', 0.360},
        {'x', 0.150},
        {'y', 1.974},
        {'z', 0.074}
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

    // string textoQuebrado = quebrarCifra(textoCifrado);
    // cout << "Texto Quebrado: " << endl << textoQuebrado << endl;

    string textoDecifrado = decifraVigenere(textoCifrado, chave);
    cout << "Texto decifrado: " << endl  << textoDecifrado << endl;

    return 0;
}

