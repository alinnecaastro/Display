# Interrupções com Matriz

## Estrutura do Projeto  
- **build/** → Diretório de compilação gerado pelo CMake. 
- **codigo_txt** → Codigos de atividade anteriores que foram usadas para ajudar nessa.  
- **debounce.c** → Arquivo que importa a interrupção e o debounce do codigo 
- **definicoes.h** → Arquivo que importa as variaveis dos botoes, matriz,delay,led... 
- **numeros.c** → Arquivos que importa as funções do numeros e a função que mostra os leds na matriz. 
- **diagram.json** → Simulação do Wokwi 
- **CMakeLists.txt** → Configuração do CMake para compilação.  
- **Display.c** → Código principal do projeto.  
- **font.h** → Biblioteca da criação das letras minuscula
- **pio_config.h** → Configuração do PIO para LEDs NeoPixel.  
- **pico_sdk_import.cmake** → Importação do SDK do Raspberry Pi Pico.  
- **README.md** → Documentação do projeto.  
- **ssd1306.c / ssd1306.h** → Bibliotecas para controle do Display ssd1306
- **wokwi.toml** → Arquivos de configuração para simulação no Wokwi.  
- **ws2812.pio / ws2812.pio.h** → Código PIO para controle dos LEDs WS2812.  


## Descrição Geral

Este projeto, desenvolve um sistema que envolve a comunicação seria via UART, controle de LEDs, interação com botões e exibição de informações em um display OLED (ssd1306).
 

## Video do funcionamento do projeto
https://drive.google.com/file/d/1hbgJRcGhmBk6lB4Os9uZbv4Ke20ou6hC/view?usp=drive_link

## Video do funcionamento no simulador dentro do vscode 
https://drive.google.com/file/d/1byZJLNJpwZhFGIgqjEsBnnD_frL0D2gR/view?usp=drive_link

## Funcionalidades do Projeto
° O objetivo é implementar um sistema que utiliza diferentes componentes de hardawre conectados a uma placa de desenvolvimento BitDogLab com o microcontrolador RP2040.
- 1 → Modificação da biblioteca font.h;
- 2 → Entrada de caracteres via PC(Serial Monitor);
- 3 → Interações com os botões A e B;
- 4 → Controle da Matriz ws2812
- 5 → Controle do Display ssd1306

## Requisitos do Projeto
° Uso de interrupções: Todas as funcionalidades relacionadas aos botões devem ser implementadas
utilizando rotinas de interrupção (IRQ);
° Debouncing: É obrigatório implementar o tratamento do bouncing dos botões via software;
° Controle de LEDs: O projeto deve incluir o uso de LEDs comuns e LEDs WS2812, demonstrando o
domínio de diferentes tipos de controle;
° Uso do Display ssd1306;
° Comunicação via UART

## Conclusão
Este projeto proporciona uma excelente oportunidade para consolidar os conceitos de comunicação serial, controle de hardware (LEDs comuns, ws2812 e display ssd1306) e interrupções em sistemas embarcados. Ao implementar as funcionalidades propostas, terão a chance de demonstrar seu entendimento.
