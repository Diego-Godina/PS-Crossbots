
# Documentação — PRG003.c (Jogo da Velha)

## Sumário
1. Visão geral
2. Estrutura geral do código
3. Explicação detalhada de cada função

---

## 1. Visão geral
Este programa implementa o clássico **Jogo da Velha (Tic-Tac-Toe)** em C, onde o **Jogador 1** é um humano (símbolo `'X'`) e o **Jogador 2** é um bot (símbolo `'O'`) que utiliza o algoritmo **Minimax** para jogar de forma ótima. O tabuleiro é uma matriz 3×3 de caracteres.

---

## 2. Estrutura geral do código

Eu escolhi executar a solução deste problema em C, pois é a linguagem que tenho mais familiaridade dentre as opções forneciados devido a utilização do C em maratonas de programação que participei. Dito isso, o código está dividido em funções que seguem o padrão "Verbo" + "Substantivo" e todas as variáveis e nomes de função estão definidas utilizando camelCase, o que torna o código mais claro. 

Além disso, em cada função desenvolvido há um comentário breve sobre a execução de cada bloco de código e todos os métodos, nomes de variáveis e comentários estão em inglês, porém as saídas para o usuário e esta documentação desenvolvi em português, com isso estou seguindo o padrão que estou mais familiarizado, visto que não foi estipulado o padrão que deveriamos seguir.

Principais funções:
- `initBoard()` — Inicializa o tabuleiro.
- `printBoard()` — Imprime o tabuleiro no console.
- `checkWinner()` — Verifica se há vencedor.
- `isMovesLeft()` — Verifica se ainda há movimentos possíveis.
- `evaluateMove()` — Avalia o tabuleiro (usado pelo minimax).
- `execMinimax(int depth, int isMax)` — Algoritmo minimax recursivo.
- `moveBot()` — Calcula e faz a melhor jogada para o bot.
- `movePlayer()` — Lê e aplica a jogada do jogador.
- `main()` — Loop principal do jogo.

---

## 3. Explicação detalhada de cada função

> **Observação:** abaixo cada função é descrita com: *assinatura*, *propósito*, *parâmetros*, *valor de retorno*, *efeitos colaterais* e *Detalhes do funcionamento*.

### `void initBoard()`
**Propósito:** Inicializa todas as posições do tabuleiro com o valor `EMPTY` (espaço `' '`), preparando o tabuleiro para uma nova partida.  
**Parâmetros:** Nenhum.  
**Retorno:** `void`.  
**Efeito colateral:** Modifica a matriz global `board[3][3]`.  

**Detalhes do funcionamento:** Apenas percorre i = 0..2 e j = 0..2 e atribui vazio (`board[i][j] = EMPTY`).

---

### `void printBoard()`
**Propósito:** Exibe o estado atual do tabuleiro no console com formatação legível (linhas e separadores).  
**Parâmetros:** Nenhum.  
**Retorno:** `void`.  
**Efeito colateral:** Imprime no `stdout` a renderização do tabuleiro.  

**Detalhes do funcionamento:** Inicia quebrando linha, após isso, itera linhas i = 0..2 e para cada linha imprime na tela os valores separados por |, além disso para cada linha imprime o separador de linhas (---+---+---), exceto para a última linha (`if (i < 2)`).

---

### `char checkWinner()`
**Propósito:** Checar se algum jogador venceu: retorna `'X'` ou `'O'` conforme vencedor, ou `EMPTY` se não houver vencedor ainda.
**Parâmetros:** Nenhum.
**Retorno:** `char` — `'X'` (`PLAYER`), `'O'` (`BOT`) ou `EMPTY` (sem vencedor).
**Efeito colateral:** Nenhum.

**Detalhes do funcionamento:** Este método faz 4 verificações no tabuleiro para ver se há algum vencedor e retorna o item da primeira posição verificada, essas verificações são feitas todas da mesma forma, dito isso para haver um vencedor 3 critérios são verificados na estrutura condicional dessa função:

1. O primeiro item não pode ser vazio;
2. O item da posição 0 deve ser igual ao da posição 1;
3. O item da posição 1 deve ser igual ao da posição 2.

As duas primeiras verificações são feitas dentro do for inicial fazendo a iteração i = 0..2, com esse for podemos verificar tanto as linhas quanto as colunas. As linhas são verificadas no primeiro if e as colunas são verificadas no segundo if, seguindo os 3 critérios mencionados acima.

As duas últimas verificações são feitas fora da estrutura for, por meio de duas estruturas condicionais. O primeiro If verifica a diagonal principal (00, 11, 22) e o segundo If verifica a diagonal secundária (02, 11, 20)

---

### `int isMovesLeft()`
**Propósito:** Verificar se ainda existem posições vazias no tabuleiro.
**Parâmetros:** Nenhum.  
**Retorno:** `1` (verdadeiro) se existe ao menos uma posição vazia; `0` caso contrário.  
**Efeito colateral:** Nenhum.

**Detalhes do funcionamento:** Este método apenas realiza dois for para iterar por todo o tabuleiro e para cada posição verifica se a posição atual é igual a vazia ou não, se for vazia, ou seja, se entrar no if, é retornado o valor 1, caso contrário os dois for são finalizados e o valor retornado é 0. 

---

### `int evaluateMove()`
**Propósito:** Fornecer uma avaliação estática do tabuleiro para o minimax.
**Parâmetros:** Nenhum.  
**Retorno:** `int` (10, -10 ou 0).
- Retorna `+10` se o bot (`'O'`) venceu.
- Retorna `-10` se o jogador (`'X'`) venceu.
- Retorna `0` caso contrário (sem vencedor ainda).  

**Efeito colateral:** Nenhum.
**Detalhes do funcionamento:** Esta função apenas encapsula a heurística usada pelo minimax que diz que o bot deve maximizar as jogadas e o jogador minizar. Ou seja, a lógica dessa função é basicamente uma estrutura condicional checando se o bot ou o jogador 1 venceu e retornando os valores mencionados acima e em casa de nenhum vencedor ou empate retornar 0

---

### `int minimax(int depth, int isMax)`
**Propósito:** Implementar o algoritmo minimax recursivo para escolher a jogada ótima.  
**Parâmetros:**
- `depth` — Profundidade atual da recursão (usada para desempate de caminhos mais curtos).
- `isMax` — `1` Se é a vez do jogador "maximizador" (bot), `0` se é o minimizador (jogador 1).

**Retorno:** `int` — Valor da melhor jogada a partir do estado atual com a lógica minimax (valores próximos a +10/-10, ajustados pela profundidade).
**Efeito colateral:** Modifica temporariamente `board` durante a exploração (coloca e remove `BOT` ou `PLAYER`).  

**Comportamento detalhado:** Esta função é o coração deste código, por se tratar de fato da implementação do algoritmo minimax, devido a isso, vou enumerar as etapas que o código percorre, lembrando que é um método recursivo então ele é executa várias vezes para cada jogada. As etapas são as seguintes:

1. Chama `evaluateMove()` para verificar se há vencedor:
   - Se `score == 10` retorna `score - depth` (pois o bot prefere vitórias mais rápidas).
   - Se `score == -10` retorna `score + depth` (pois o  bot prefere atrasar a derrota).

2. Se não há jogadas restantes (`!isMovesLeft()`), retorna `0` (empate).

3. Se `isMax` é verdadeiro (vez do bot):
   - Inicializa `best = -1000`.
   - Para cada célula vazia, tenta `board[i][j] = BOT`, chama `minimax(depth+1, 0)` e reverte a jogada.
   - Mantém o maior valor (`best`) por meio de `if (val > best)` e retorna ao final.

4. Caso contrário (vez do jogador):
   - Inicializa `best = 1000`.
   - Para cada célula vazia, tenta `board[i][j] = PLAYER`, chama `minimax(depth+1, 1)` e reverte.
   - Mantém o menor valor (`best`) por meio de `if (val < best)` e retorna.

As etapas 3 e 4 são bem similares, pois ambas se tratam de dois for iterando por casa posição do tabuleiro, e executando a lógica apenas para as posições vazias (`if (board[i][j] == EMPTY)`), essa lógica, como resumida acima, se trata apenas de para cada posição vazia atribuir o valor do bot ou do jogador 1, verificar o valor retornado (recursividade) e dependendo se é maximizador ou minimizador manter o maior valor ou o menor valor, logo após isso, voltar o valor do tabuleiro para vazio.

---

### `void botMove()`
**Propósito:** Determinar a melhor jogada para o bot usando `minimax` e aplicar a jogada no tabuleiro.  
**Parâmetros:** Nenhum.  
**Retorno:** `void`.  
**Efeito colateral:** Modifica `board` definindo `BOT` em `bestRow,bestCol` e imprime a jogada do bot.  

**Detalhes do funcionamento:** Essa função também percorre todo o tabuleiro utilizando duas estruturas de repetição aninhadas, dentro delas, a lógica só sera executada para as posições que estão vazias (`if (board[i][j] == EMPTY)`). Essa lógica para determinar a melhor jogada para o bot é simplesmente atribuir a posição atual para o bot, iniciar a recursividade do minimax com profundidade 0 (`minimax(0, 0)`), retornar o valor para vazio e se a jogada é melhor que a jogada anterior salvar os dados dela nas variáveis bestRow, bestCol e bestVal. Com isso, ao final das iterações executar o melhor movimento (`board[bestRow][bestCol] = BOT;`) e printar na tela para o usuário.

---

### `void playerMove()`
**Propósito:** Ler do `stdin` a jogada do jogador (linha e coluna), validar e aplicar no tabuleiro.  
**Parâmetros:** Nenhum.
**Retorno:** `void`.  
**Efeito colateral:** Modifica `board` definindo `PLAYER` na posição escolhida; imprime confirmação da jogada.  

**Detalhes do funcionamento:** Esta função é feita pensando num tratamento de erros básico, ou seja, apenas sairá do while caso ocorra todas as seguintes opções em conjunto:

1. Valor da linha for maior ou igual do que 0
2. Valor da linha for menor do que 3
3. Valor da coluna for maior ou igual do que 0
4. Valor da coluna for menor do que 3
5. Posição no tabuleiro deve ser vazia

Caso uma dessas condições acima não seja atendida uma mensagem será exibida na tela (`printf("Posição inválida, tente novamente.\n");`). Outro ponto importante para se atentar é o fato que de o usuário entrada com as posições com valores entre 1 e 3, porém internamente eu trato como valores de 0 a 2, para facilitar a utilziação com as matrizes.

---

### `int main()`
**Propósito:** Loop principal do jogo que controla a sequência de jogadas até vitória ou empate.  
**Parâmetros:** Nenhum.
**Retorno:** `int`.
**Detalhes do funcionamento:** Após iniciar o tabuleiro, é realizado um loop que só será quebrado caso alguem vença ou dê empate. Dentro desse loop, as seguintes etapas ocorrem:

1. Jogador 1 realiza um movimento
2. O novo tabuleiro é renderizado
3. Caso o jogador tenha vencido o loop se encerra
4. Se não houver mais movimentos restantes o jogo é encerrado com um empate
5. O bot realiza um movimento
6. O novo tabuleiro é renderizado
7. Caso o bot tenha vencido o loop se encerra
8. Se não houver mais movimentos restantes o jogo é encerrado como um empate

Algo importante de notar aqui é que após cada movimento uma verificação de empate ou não é realizada, eu adicionei desta forma pois se fosse executado apenas uma vez dentro desse loop ocorreria que apenas no final do loop seria declarado um empate, ou seja, ou o bot ou o jogador 1 teriam uma jogada a mais inválida e impossível de ser realizada, gerando um erro onde o programa ficaria travado (Ocorreu nos meus testes...)
