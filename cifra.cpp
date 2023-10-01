#include <iostream>
#include <string>
#include <vector>
#include <cmath>  // Adicionado para usar a função abs()
#include <limits> // Adicionado para usar numeric_limits
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


int findKeySize(const string& text);

double calcularIndiceCoincidencia(const string& texto) {
    int tamanhoTexto = texto.length();

    vector<int> frequencia(26, 0); // Frequência de letras de A a Z

    for (char letra : texto) {
        if (isalpha(letra)) {
            frequencia[tolower(letra) - 'a']++; // Converter para minúscula e contar frequência
        }
    }

    double ic = 0.0;
    for (int i : frequencia) {
        ic += (double)i * (i - 1);
    }

    ic /= (double)(tamanhoTexto * (tamanhoTexto - 1));

    return ic;
}

int findKeySize(const string& text, double ic) {
    vector<double> icValues(20, 0.0); // Criar um vetor para armazenar os valores de IC
    vector<int> factors(20, 0);      // Criar um vetor para armazenar a contagem de fatores

    for (int blockSize = 2; blockSize <= 20; blockSize++) {
        double icSum = 0.0;

        for (int i = 0; i < blockSize; i++) {
            string seq;

            for (int j = i; j < text.length(); j += blockSize) {
                seq += text[j];
            }

            double blockIC = calcularIndiceCoincidencia(seq);
            icSum += blockIC;
        }

        double averageIC = icSum / blockSize;
        icValues[blockSize - 2] = averageIC;
    }

    // Imprimir os valores de IC para diferentes tamanhos de bloco
    cout << "Valores de IC para diferentes tamanhos de bloco:" << endl;
    for (int i = 0; i < icValues.size(); i++) {
        cout << "\t" << i + 2 << " : " << icValues[i] << endl;
    }

    // Encontrar o tamanho da chave com base no IC
    int selectedBlockSize = 0;
    double minICDifference = numeric_limits<double>::max();

    for (int i = 0; i < icValues.size(); i++) {
        double icDifference = abs(icValues[i] - ic); // 0.067 é o IC esperado para texto em português
        if (icDifference < minICDifference) {
            minICDifference = icDifference;
            selectedBlockSize = i + 2;
        }
    }

    cout << "Tamanho da chave selecionado com base no IC: " << selectedBlockSize << endl;

    return selectedBlockSize;
}




int main() {
    string mensagem_cifrada = "X pnf p kegag whsytel. Un avhe tng W xwg upvvvgd 30 mspia cod. Za jbfh ocu V etvi tenelb gjixekath jjea oxf hfv eibi gq bnr vcjjm qv Xlhtsqty sjteqai. Li vhrg wccz cf bd xug nbrscfi iaf vezr uf tzc izkxgbh xb gb tr Fddm! Pt tnkd you skvzlvpxrk: tux izwvyb, bwi uqtre, sjtiggjqck. Ye aag o cwigtn argkrgd. Kt zrombfiegd mhh bxxpg et kbv ztruwss. Vv lew yoaweutia.Q jis e tenelb htizvdtt argkrgd. An jbangmiaf ghon at whv is gjif rhozap rzxtrwvxe kevhojiiav. Mr vhr mlrrav bh dyv fiageu, wv tcdt qr a oeum qvihvquyp tiaz dbr ym cazih oe mo aogig jqb. V wnl usoacg ucgtvvueq. L gpzl pw. M nixx kwa, jhv X oagw B gwrc’v lerg tb mdffn pvo. Li yaf qxwht iaizn eaf ftd. Wi enu pajhn."; // Substitua pela sua mensagem cifrada

    int tamanhoChave;
    float IC;
    // texto em Português ou Inglês
    int EN = 1;
    int PT = 0;
    if (EN == 1) {
        IC = 0.0667;
    }
    else if (PT == 1) {
        IC = 0.0745;
    }
    tamanhoChave = findKeySize(mensagem_cifrada, IC);

    string mensagemDescriptografada;

    cout << "Mensagem descriptografada:" << endl;
    cout << mensagemDescriptografada << endl;

    return 0;
}


