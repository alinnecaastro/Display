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

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C



//Função principal
int main() {
    stdio_init_all();
    npInit(MATRIX_LED_PIN);

    // Inicializa e Configura o LED Vermelho 
    gpio_init(GPIO_PIN_RED);
    gpio_set_dir(GPIO_PIN_RED, GPIO_OUT);
    gpio_init(GPIO_PIN_BLUE);
    gpio_set_dir(GPIO_PIN_BLUE, GPIO_OUT);
    gpio_init(GPIO_PIN_GREEN);
    gpio_set_dir(GPIO_PIN_GREEN, GPIO_OUT);
    gpio_init(BUTTON_PIN_A);
    gpio_set_dir(BUTTON_PIN_A, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_A);
    gpio_set_irq_enabled_with_callback(BUTTON_PIN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);//    // Configura as interrupções para ambos os botões, usando a mesma callback.
   
    // Inicializa e Configura o Botão B e PUll-Up
    gpio_init(BUTTON_PIN_B);
    gpio_set_dir(BUTTON_PIN_B, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_B);
    gpio_set_irq_enabled(BUTTON_PIN_B, GPIO_IRQ_EDGE_FALL, true); // Borda de descida apenas

    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_t ssd;
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);

    //Limpa o display
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
    bool cor = true;

    while(1){
 
    sleep_ms(1000);
    led_vermelho(); // Acende o LED vermelho

        // Processa botão A
        if (flag_button_a) {
            contador = (contador + 1) % 10;
            printf("Contador: %d\n", contador);
            mostrar_numero(contador);
            flag_button_a = false;
        }

        // Processa botão B
        if (flag_button_b) {
            contador = (contador == 0) ? 9 : contador - 1;
            printf("Contador: %d\n", contador);
            mostrar_numero(contador);
            flag_button_b = false;
        }
// Leitura de caracteres via UART
        int c = getchar_timeout_us(0); // Lê um caractere do Serial Monitor
        if (c != PICO_ERROR_TIMEOUT) {
            // Limpa o display antes de exibir o novo caractere
            ssd1306_fill(&ssd, false);

            // Exibe o caractere no display SSD1306
            ssd1306_draw_char(&ssd, c, 10, 10);
            ssd1306_send_data(&ssd);

            // Verifica se o caractere é um número (0-9)
            if (c >= '0' && c <= '9') {
                int number = c - '0'; // Converte o caractere para um número
                mostrar_numero(number); // Exibe o símbolo correspondente na matriz WS2812
            }
        }

        tight_loop_contents(); // Otimiza o loop principal
    }
}

 
    

