# Project-01 Competiton

Uma das possíveis abordagens para solução do problema da concorrência é a utilização de semáforos.
Na solução teórica para o problema da exclusão mútua utilizando semáforos, ou seja, um processo precisa avisar o outro que a 
operação de up ou down foi realizada e qual o valor do semáforo no momento. 
A “troca” de informações é realizada através da comunicação inter processos (IPC). 
Para introduzir o conceito analisamos um dos problemas mais famosos na área de Sistemas Operacionais: o jantar dos filósofos.

Cada filósofo possui um prato cheio de spaghetti à sua frente. 
Além disso, um garfo é posicionado entre cada par adjacente de filósofos 
(portanto, cada filósofo tem exatamente um garfo à sua esquerda e exatamente um garfo à sua direita).

![image](https://github.com/jenifer-mathias/sistemas-operacionais/blob/main/assets/philosophers-dinner.png)

Cada filósofo pode estar pensando ou comendo. Para comer são necessários dois garfos: direito e esquerdo. 
Se ele pega um dos garfos e o outro não está disponível, devolve-o à mesa e continua pensando 
até que consiga pegar os dois garfos de uma só vez. Quando conseguir pegar os dois garfos o filósofo come
e logo depois devolve ambos os garfos à mesa.

Levando em consideração o problema computacional proposto, responda a seguinte questão:

a) Implemente uma possível solução para o problema do jantar dos filósofos;

b) Explique, em cada trecho do seu programa, como é resolvido o problema da comunicação inter processos (IPC).


Para resolver o problema do jantar dos filósofos, criamos uma thread e um semáforo para cada filósofo e um vetor para armazenar o estado de cada filosofo (pensando, com fome ou comendo). Cada filósofo pensa, tenta pegar os garfos, come quando conseguir pegar e solta os garfos depois de comer.  Utilizamos o estado dos filósofos e os semáforos para verificar se o filósofo está comendo, ver quando os garfos então disponíveis (quando os filósofos à esquerda e à direita soltarem os garfos após comer).

![image](https://github.com/jenifer-mathias/sistemas-operacionais/blob/feat/projeto-01/assets/projeto.png)

![image](https://github.com/jenifer-mathias/sistemas-operacionais/blob/feat/projeto-01/assets/projeto1.png)
