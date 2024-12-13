## Prova M4 - Gabriel Nascimento T12
 O esp32 reconhoce dois estados por meio da leitura com o sensor de luz LDR, escuro e claro, com valor estabelecido no inicio do código.
 No inicio, tudo fica apagado, e após 3 segundos, o esp32 começa a fazer leituras com o sensor LDR.

 Ao declarar que está escuro, ele ativa a função "escuro" e faz com que o led amarelo fique piscando num intevalo de 1 segundo.



 Ao declarar que está claro, a função "claro" é ativida, fazendo com que os leds fiquem alternando entre verde (3 segundos), amarelo (2 segundos) e vermelho (5 segundos).
