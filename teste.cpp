#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
using namespace std;

// 1) Procure por grupos de letras repetidas na mensagem cifrada que possuam alta frequência
// 2) Conte a distancia entre esses grupos
// 3) Calcule o MDC mais comum entre essas distâncias
// 4) Utilize o valor do passo 3 como tamanho da chave
// 5) Divida a mensagem cifrada em n sequencias de letras cuja distancia entre elas seja igual ao tamanho da chave
// 6) Aplique analise de frequencia em cada umas das n sequencias de caracteres individualmente e, ao final, reorganize as letras de acordo com a frequencia de letras do alfabeto portugues
// 7) caso o resultado não seja satisfatório, repita o processo com o segundo valor mais comum de MDC(passo 3)
// 8) FIM


int findKeySize(const string& text) {
    vector<int> factors(19, 0); // Criar um vetor de 19 elementos inicializados com 0

    for (int i = 0; i < text.length() - 2; i++) {
        string seq = text.substr(i, 3);

        for (int j = i + 3; j < text.length() - 2; j++) {
            if (seq == text.substr(j, 3)) {
                int dist = j - i;
                cout << seq << " " << dist << endl;
                for (int k = 2; k <= 20; k++) {
                    if (dist % k == 0) {
                        factors[k - 2]++;
                    }
                }
                break;
            }
        }
    }

    cout << "Tamanhos de chaves e suas quantidades encontradas:" << endl;

    for (int i = 0; i < factors.size(); i++) {
        cout << "\t" << i + 2 << " : " << factors[i] << endl;
    }

    int selected;
    cout << "Selecione o tamanho da chave: ";
    cin >> selected;

    return selected;
}
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




int main() {
    string mensagem_cifrada = "Glfxu dzcnu wnrxm gbb vwom, vntbzzhxbim kwqvbririd xtwo. Gcrezs zrwlucy, gqye broxs czobsvqkl auoowvqsn, gqye trni nthmsmbmy drro, oqhvo ntzkhirzp xtwo oeqz uocvb xtwo. Ewxxl rkpif rjvyk ybs jhbh, qjxcxkzxsaa xrbxwnmsgo xkoc. Bntzvw xcollum, bbaz fsmik trcmfqbmg evmzovhkb, bbaz xslt nkzadzwxa zvsm, ohzjz iebfdmsxa xkoc bzbb qsdtm xkoc. Zhzsh siaaf jxglf awo kfmz, ixipsvbsoeb ijboobxfbz sgsd. Tnkrjh snqghyn, tbrr qfhtm pvdkqibdy pihkqqdoc, tbrr ifge igdbbkoxr ngfh, jddkx aesxrxfsl sgsd mrbs edqox sgsd. Rhqkv fdlca nyewx roc xaxb, mygakvskcpo tlwkscvqtz kudq. Vigvkf knhyvja, vwnv oqztd dgqfbkwzc ntzkhirzp, vwnv gqye auoowvqsn oeqz, broxs czobsvqkl kudq xtwo fbbgx kudq. Tcmow qvlts ylzhz nsd isxs, xlblmqoodnz tcoydpqbvu ovbb. Maugxa midcwhl, mobg jbboz eebxbbonn iebfdmsxa, mobg bbaz evmzovhkb bzbb, fsmik trcmfqbmg ovbb xkoc swmis ovbb. Kuazj bxgpw wwrhq bdq tuso, vwtldiczqik oyszbaibmm ziwm. Ieveis darnjcw, isce bbsgn rzmzwxsol aesxrxfsl, isce tbrr pihkqqdoc mrbs, qfhtm pvdkqibdy ziwm sgsd domzk ziwm"; // Substitua pela sua mensagem cifrada
    int tamanhoChave;
    tamanhoChave = findKeySize(mensagem_cifrada);

    cout << "O tamanho da chave é: " << tamanhoChave << endl;

    double ic = calcularIndiceCoincidencia(mensagem_cifrada);

    cout << "Índice de Coincidência: " << ic << endl;
    return 0;
}