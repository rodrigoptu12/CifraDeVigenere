# Trabalho de Cifra de Vigenère

Este é um trabalho que envolve a cifra de Vigenère e um ataque para quebrar a cifra. Aqui estão as instruções para executar os dois aspectos do trabalho: cifragem e ataque.

## Cifragem

Para cifrar um texto usando a cifra de Vigenère, siga os seguintes passos:

1. Abra o arquivo `cifraDeVigenere.cpp`.
2. Na variável `textoOriginal`, coloque a mensagem que você deseja cifrar.
3. Na variável `chave`, coloque a chave que você deseja usar para a cifra.
4. Execute o seguinte comando no terminal para compilar e executar o programa:

   ```
   g++ cifraDeVigenere.cpp ; ./a.out
   ```

5. A saída incluirá o texto original, o texto cifrado e o texto decifrado.

## Ataque

Para realizar um ataque à cifra de Vigenère e quebrá-la, siga os seguintes passos:

1. Abra o arquivo `Ataque.cpp`.
2. Na variável `mensagem_cifrada`, substitua o conteúdo pela mensagem que você deseja quebrar.
3. Escolha se o textoo sera em portugues ou ingles na variavel `usar_freq_portugues`
4. Execute o seguinte comando no terminal para compilar e executar o programa:

   ```
   g++ Ataque.cpp ; ./a.out
   ```

5. Você terá que escolher o tamanho da chave com base no tamanho das chaves e quantidades. Quanto maior o tamanho, melhor. Comece pelo maior tamanho de chave e, se não for satisfatório, execute novamente e escolha outro tamanho.

---

