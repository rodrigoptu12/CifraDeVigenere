#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;
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
    {'w', 2.360},
    {'x', 0.150},
    {'y', 1.974},
    {'z', 0.074}};
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
    {'z', 0.47}};

int findKeySize(const string &text)
{
    vector<int> factors(19, 0); // Criar um vetor de 19 elementos inicializados com 0

    for (int i = 0; i < text.length() - 2; i++)
    {
        string seq = text.substr(i, 3);

        for (int j = i + 3; j < text.length() - 2; j++)
        {
            if (seq == text.substr(j, 3))
            {
                int dist = j - i;
                // cout << seq << " " << dist << endl;
                for (int k = 2; k <= 20; k++)
                {
                    if (dist % k == 0)
                    {
                        factors[k - 2]++;
                    }
                }
                break;
            }
        }
    }

    cout << "Tamanhos de chaves e suas quantidades encontradas:" << endl;

    for (int i = 0; i < factors.size(); i++)
    {
        cout << "\t" << i + 2 << " : " << factors[i] << endl;
    }

    int selected;
    cout << "Selecione o tamanho da chave: ";
    cin >> selected;

    return selected;
}
void shiftMap(map<char, double> &myMap, int shift)
{
    // Cria um novo map para armazenar o resultado do shift
    map<char, double> shiftedMap;

    // Itera sobre o map original
    for (auto pair : myMap)
    {
        // Calcula o novo indice da letra
        int newIndex = (pair.first - 'a' + shift) % 26;

        // Adiciona a letra no novo map
        shiftedMap['a' + newIndex] = pair.second;
    }

    // Copia o novo map para o map original
    myMap = shiftedMap;
}
vector<string> divideEmBlocos(const string &texto, int tamanhoBloco)
{
    vector<string> blocos(tamanhoBloco);

    for (int i = 0; i < texto.length(); i++)
    {
        blocos[i % tamanhoBloco] += texto[i];
    }

    return blocos;
}
string aplicaAnaliseDeFrequencia(const vector<string> &sequencias, map<char, double> frequenciaLingua)
{
    string chave = "";
    for (const string &sequencia : sequencias)
    {
        map<char, int> frequenciaLetras;
        for (char letra : sequencia)
        {
            // lower case
            letra = tolower(letra);
            frequenciaLetras[letra]++;
        }
        // letras que não aparecem na sequencia tem frequencia 0
        for (char letra = 'a'; letra <= 'z'; letra++)
        {
            if (frequenciaLetras.find(letra) == frequenciaLetras.end())
            {
                frequenciaLetras[letra] = 0;
            }
        }
        // deixar em %
        map<char, double> frequenciaLetrasPercentual;

        for (auto par : frequenciaLetras)
        {
            frequenciaLetrasPercentual[par.first] = (double)par.second / (double)sequencia.length();
        }

        vector<double> dif;
        for (int i = 0; i < 26; i++)
        {
            double soma = 0.0;

            for (auto par : frequenciaLetrasPercentual)
            {
                map<char, double> freqLetrasAux = frequenciaLingua;
                shiftMap(freqLetrasAux, i);
                soma += abs(freqLetrasAux[par.first] / 100 - par.second);
            }
            dif.push_back(soma);
        }

        int shift = min_element(dif.begin(), dif.end()) - dif.begin();
        chave += 'a' + shift;
    }
    return chave;
}
std::string decifraVigenere(const std::string &textoCifrado, const std::string &chave)
{
    std::string textoDescriptografado;
    int tamanhoChave = chave.length();
    int indiceChave = 0;

    for (char letraCifrada : textoCifrado)
    {
        if (std::isalpha(letraCifrada))
        {
            char letraChave = chave[indiceChave];
            char letraDescriptografada;

            if (isupper(letraCifrada))
            {
                letraDescriptografada = 'A' + ((letraCifrada - letraChave + 26) % 26);
            }
            else
            {
                letraDescriptografada = 'a' + ((letraCifrada - letraChave + 26) % 26);
            }

            textoDescriptografado += letraDescriptografada;
            indiceChave = (indiceChave + 1) % tamanhoChave;
        }
        else
        {
            textoDescriptografado += letraCifrada;
        }
    }

    return textoDescriptografado;
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
int main()
{
    string mensagem_cifrada = "flmzumxrxrteflascfpgzrpltvesclnkprfhjxcflxdhipqngtrfcajdmauqcsiskcvxnwsqddwfpwhwsfotbwovqccjmtwqbswrpsvgaugcqimgwldephpofbnlqwpebruxdvqrkoqxthlhdjxevqrswdwestvrfsrvundwppivvuetefcbhvyhgviigbopexeqgcsfyhgmcwmacdbmogccpgzrplxdeqqfbbcrbqtsqqqkdqsbdjrmiycrtgzbrwggmbpaenmdtcgdivpwkehbtartguorkvtqgmcwmaqayzotisufqrubpfiygcvwodcgtvuctmvevnttvzovrsxebrtmhwitgrneqxsgdmwyvisswpqnfmrxcrtmwpcjjpvvqephmsfsteabfwhiproeamovufpdigkkpmw"; // Substitua pela sua mensagem cifrada
    int tamanhoChave;
    string textoOriginalSemEspacosPontuacao = retiraEspacosPontuacao(mensagem_cifrada);
    // to lower
    for (char &c : textoOriginalSemEspacosPontuacao)
    {
        c = tolower(c);
    }

    map<char, char> mapeamentoLetras;
    tamanhoChave = findKeySize(textoOriginalSemEspacosPontuacao);

    vector<string> blocos = divideEmBlocos(textoOriginalSemEspacosPontuacao, tamanhoChave);
    string chaveEncontrada;
    int usar_freq_portugues = 1;
    if (usar_freq_portugues)
    {
        chaveEncontrada = aplicaAnaliseDeFrequencia(blocos, frequenciaPortugues);
    }
    else
    {
        chaveEncontrada = aplicaAnaliseDeFrequencia(blocos, frequenciaIngles);
    }

    cout << "Chave encontrada: " << chaveEncontrada << endl;

    string mensagem_decifrada = decifraVigenere(textoOriginalSemEspacosPontuacao, chaveEncontrada);

    cout << "Mensagem decifrada: " << mensagem_decifrada << endl;

    return 0;
}