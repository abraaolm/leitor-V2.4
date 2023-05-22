extern const int led_verde; // Defina o pino do LED verde
extern const int led_vermelho; // Defina o pino do LED vermelho
extern const int led_amarelo; // Defina o pino do LED amarelo

// Defina as funções buzzer_pi(), buzzer_pi2() e buzzer_pi3()

extern const byte LINHAS; // Defina o número de linhas do teclado
extern const byte COLUNAS; // Defina o número de colunas do teclado

extern char TECLAS[LINHAS][COLUNAS];

extern Keypad teclado_personalizado;

void removerDigital() {
lcd.clear();
    lcd.setCursor(4,1);
    lcd.print("MODO REMOVER");
    digitalWrite(led_amarelo, HIGH);
    buzzer_pi2();
    delay(1200);
    lcd.clear();
    lcd.setCursor(3,1);
    lcd.print("Insira o ID da");
    lcd.setCursor(5,2);
    lcd.print("digital que");
    lcd.setCursor(1,3);
    lcd.print(" deseja remover:");
    buzzer_pi();

    String id_str = "";
    while (id_str.length() < 8) { // aguarda entrada de 4 dígitos no teclado
        char key = teclado_personalizado.getKey();
        if (key >= '0' && key <= '9') {
            id_str += key;
            lcd.print(key);
            buzzer_pi();
        } else if (key == '#') { // se a tecla A for pressionada, prossegue com a remoção
            break;
        }
    }
    int id = id_str.toInt();
    int r = finger.deleteModel(id);
    if (r != FINGERPRINT_OK) {
        lcd.clear();
        lcd.setCursor(3,1);
        lcd.print("ERRO AO REMOVER");
        lcd.setCursor(6,2);
        lcd.print("A DIGITAL");
        digitalWrite(led_amarelo, LOW);
        falha();
        delay(1000);
        bem_vindo();
    } else {
        lcd.clear();
        lcd.setCursor(5,1);
        lcd.print("A DIGITAL ");
        lcd.print(id);
        lcd.setCursor(4,2);
        lcd.print("FOI REMOVIDA");
        lcd.setCursor(5,3);
        lcd.print("COM SUCESSO");
        digitalWrite(led_verde, HIGH);
        digitalWrite(led_amarelo, LOW);
        buzzer_pi3();
        delay(1000);
        digitalWrite(led_verde, LOW);
        bem_vindo();
    }
    //delay(1500);
    //bem_vindo();
}
