# CP5-EDGE

MEMBROS: Gabriel C. S. da Silva RM: 563169 João Gabriel C. M. Santos RM: 563953 Leonardo V. de Souza RM: 562299 Miguel dos Santos de Andrade RM: 563516 Pedro H. da Silva RM: 566235

## Objetivo do Projeto
Validar a arquitetura IoT e realizar uma prova de conceito funcional, demonstrando a comunicação entre dispositivos ESP32 e a plataforma FIWARE, enviando dados de temperatura, umidade, luminosidade e distância (ultrassom).

Criamos uma VM Ubuntu utilizando a AWS com IP público, configuramos o security group para permitir acesso as portas necessárias (1883 para MQTT, 4041 para IoT Agent, 1026 para Orion Context Broker, 27017 para MongoDB),
Instalamos o Docker e Docker Compose, clonamos o repositório git do FIWARE, acessamos e criamos os containers e o device que seria utilizado, mas o projeto apresentou problemas nessa etapa, o esp32 não conseguia enviar as informações para o
Orion, verificamos e o IoT agent apresentou erros ao tentar conectar ao MongoDB que tinha o papel de manter o registro de dispositivos e sua configuração, sem ele o IoT Agent não conseguia mapear as mensagens que chagavam, assim não conseguindo pubilcar os dados
no Context Broker Orion.
