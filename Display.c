#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "pio_config.h"
#include "hardware/pwm.h"
#include "pico/bootrom.h"
#include "ws2812.pio.h"
#include "libs/numeros.c"//arquivos para implementação dos numeros
#include "libs/definicoes.h"//arquivos para variaveis globais
#include "libs/debounce.c"//arquivos para debounce
#include <stdlib.h>
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "font.h"
#include "pico/bootrom.h"

#define I2C_PORT i2c1 // Especifica qual porta I2C está sendo usada, no caso o i2c
#define I2C_SDA 14 // Especifica I2C Data e conecta a GPIO 14
#define I2C_SCL 15 // Especifica I2C Clock e conecta a GPIO 15
#define endereco 0x3C // Define o endereço I2C do dispositivo com o qual
                      //  voce esta se comunicando, sendo esse o displays OLEDm como o ssd1306
//Declara variavel booleanas das leds
bool led_verde = false; 
bool led_azul = false;

//Função principal
int main() {
    stdio_init_all();
    npInit(MATRIX_LED_PIN);

    // Inicializa e Configura o LED Vermelho 
    gpio_init(GPIO_PIN_RED);
    gpio_set_dir(GPIO_PIN_RED, GPIO_OUT);
    // Inicializa e Configura o LED Azul
    gpio_init(GPIO_PIN_BLUE);
    gpio_set_dir(GPIO_PIN_BLUE, GPIO_OUT);
    // Inicializa e Configura o LED Verde
    gpio_init(GPIO_PIN_GREEN);
    gpio_set_dir(GPIO_PIN_GREEN, GPIO_OUT);
    // Inicializa e Configura o Botão A e Pull-Up
    gpio_init(BUTTON_PIN_A);
    gpio_set_dir(BUTTON_PIN_A, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_A);
    //// Configura as interrupções para ambos os botões, usando a mesma callback.
    gpio_set_irq_enabled_with_callback(BUTTON_PIN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);   
    // Inicializa e Configura o Botão B e PUll-Up
    gpio_init(BUTTON_PIN_B);
    gpio_set_dir(BUTTON_PIN_B, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_B);
    gpio_set_irq_enabled(BUTTON_PIN_B, GPIO_IRQ_EDGE_FALL, true); // Borda de descida apenas

    // Inicaliza a comunicação I2C em um microcontrolador em 400kHz
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);//Configura o pino para funcionar como um pino I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);// Configura o pino para funcionar como o pino de relogio I2C, sincronizar a comunicação entre os dispositivos.
    // Garanti que as linhas de comunicação I2C sejam mantidas em um nivel logico alto
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_t ssd;//Declara uma variavel do tipo ssd1306_t, representa o display.
   // Inicializa o display, dimensões do display,parametro que especifica esta invertido ou nao, enderço I2C, a porta que esta sendo usada
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    // Aplica configurações adicionais ao display
    ssd1306_config(&ssd);
    // Envia os dados configurados para o display
    ssd1306_send_data(&ssd);

    //Limpa o display
    ssd1306_fill(&ssd, false);
    // Envia os dados configurados para o display
    ssd1306_send_data(&ssd);
    printf("OFF");

    while(1){

    sleep_ms(1000);

        // Processa botão A
        if (flag_button_a) {
            led_verde =!led_verde;
            flag_button_a = false;
        }
        // Processa botão B
        if (flag_button_b) {
            led_azul = !led_azul;
            flag_button_b = false;
        }
           

            if(led_verde && led_azul){
                gpio_put(GPIO_PIN_GREEN,1);
                gpio_put(GPIO_PIN_BLUE, 1);
                gpio_put(GPIO_PIN_RED, 0);
            }
            else if(led_verde){
            gpio_put(GPIO_PIN_GREEN,1);
            gpio_put(GPIO_PIN_BLUE, 0);
            gpio_put(GPIO_PIN_RED, 0);
            }
            else if(led_azul){
            gpio_put(GPIO_PIN_GREEN,0);
            gpio_put(GPIO_PIN_BLUE, 1);
            gpio_put(GPIO_PIN_RED, 0);
            }
            else{
            gpio_put(GPIO_PIN_GREEN,0);
            gpio_put(GPIO_PIN_BLUE, 0);
            gpio_put(GPIO_PIN_RED, 0);
            }
            
        ssd1306_fill(&ssd, false);//Limpa o display
        ssd1306_send_data(&ssd);
        // Exibe os status de ambos os LEDs no display
        ssd1306_fill(&ssd,false); //Limpa o display
        ssd1306_draw_string(&ssd,"LEDS ",20,15);//Desenha uma string no display
        
        ssd1306_draw_string(&ssd, "LED verde: ", 20, 30);
        if (led_verde) {
           
            ssd1306_draw_string(&ssd, "ON", 100, 30); // LED verde está ligado
        } else {
           
            ssd1306_draw_string(&ssd, "OFF", 100, 30); // LED verde está desligado
        }
        ssd1306_draw_string(&ssd, "LED azul: ", 20, 50);
        if (led_azul) {
            
            ssd1306_draw_string(&ssd, "ON", 100, 50); // LED azul está ligado
        } else {
            
            ssd1306_draw_string(&ssd, "OFF", 100, 50); // LED azul está desligado
        }
        ssd1306_send_data(&ssd); // Atualiza o display
        ssd1306_fill(&ssd,false);

        // Leitura de caracteres via UART
        //Parametro (0) significa que nao ha tempo limite
        int c = getchar_timeout_us(0); // Lê um caractere do Serial Monitor
        if (c != PICO_ERROR_TIMEOUT) { //Verifica se a leitura nao ocorreu erro.
            // Limpa o display antes de exibir o novo caractere
            ssd1306_fill(&ssd, false);
            

            // Exibe o caractere no display SSD1306
            ssd1306_draw_char(&ssd, c, 20, 30);
            ssd1306_send_data(&ssd);

            // Verifica se o caractere é um número (0-9)
            if (c >= '0' && c <= '9') {
                int number = c - '0'; // Converte o caractere para um número
                mostrar_numero(number); // Exibe o símbolo correspondente na matriz WS2812
            }else
            if(c == '#'){
                npClear();
                npWrite(NULL,0);
            }
        }

        tight_loop_contents(); // Otimiza o loop principal
    }
}


 
    

