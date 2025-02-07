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

//Função principal
int main() {
    stdio_init_all();
    npInit(MATRIX_LED_PIN);

    // Inicializa e Configura o LED Vermelho 
    gpio_init(GPIO_PIN_RED);
    gpio_set_dir(GPIO_PIN_RED, GPIO_OUT);

    // Inicializa e Configura o Botão A e PUll-Up
    gpio_init(BUTTON_PIN_A);
    gpio_set_dir(BUTTON_PIN_A, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_A);
    gpio_set_irq_enabled_with_callback(BUTTON_PIN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);//    // Configura as interrupções para ambos os botões, usando a mesma callback.
    // Inicializa e Configura o Botão B e PUll-Up
    gpio_init(BUTTON_PIN_B);
    gpio_set_dir(BUTTON_PIN_B, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_B);
    gpio_set_irq_enabled(BUTTON_PIN_B, GPIO_IRQ_EDGE_FALL, true); // Borda de descida apenas

    printf("Sistema iniciado...\n");
    npClear();

    while (true) {
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

        tight_loop_contents();//Otimiza o loop principal
    }
}