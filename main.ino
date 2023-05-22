#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <Password.h>
#include <Keypad.h>

const int pinRx = 50;
const int pinTx = 51;
const int led_verde = 10;
const int led_vermelho = 9;
const int rele = 11;
const int proximidade = 8;
const int led_amarelo = 12;
const int buzzer = A0;
const int ldr = A1;

const byte LINHAS = 4;
const byte COLUNAS = 4;
int sensorValue = 0;   
int setpoint = 200; 

Password senha = Password("061723");

const char TECLAS_MATRIZ[LINHAS][COLUNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

const byte PINOS_LINHAS[LINHAS] = {45, 43, 41, 39}; 
const byte PINOS_COLUNAS[COLUNAS] = {37, 35, 33, 31};

Keypad teclado_personalizado = Keypad(makeKeymap(TECLAS_MATRIZ), PINOS_LINHAS, PINOS_COLUNAS, LINHAS, COLUNAS);

extern void removerDigital();
extern void adicionarDigital();
extern void sem_correspodencia();
extern void nao_encontrou_digital();
extern void erro_comunicacao();
extern void imagem_confusa();
extern void erro_desconhecido();
extern void autorizado();
extern void mensagem();
extern void mensagem1();
extern void mensagem2();
extern void buzzer_pi();
extern void buzzer_pi3();
extern void buzzer_pi2();
extern void bem_vindo();

bool modo_cadastro = false;
bool modo_remover = false;
bool passapadento = false;
bool modo_livre = false;
bool grava = false;

LiquidCrystal_I2C lcd(0x3F,20,4);

SoftwareSerial mySerial(pinTx, pinRx);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;

void setup() {


  Serial.begin(115200);
  finger.begin(57600);
  delay(100);
  lcd.init();
  lcd.backlight(); 
  pinMode(led_verde, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_vermelho , OUTPUT);
  pinMode(rele, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(rele, HIGH);
  digitalWrite(buzzer, LOW);
  pinMode(ldr, INPUT);
  pinMode(proximidade, INPUT);
  //O rele utilizado é invertido, ele precisa inciar em HIGH, e caso queira aciona-lo, mande um pulso LOW
  if (finger.verifyPassword()) {
    lcd.clear();
    lcd.setCursor(1,1);
    lcd.print("Leitor biometrico");
    lcd.setCursor(2,2);
    lcd.print("esta funcionando");
    lcd.setCursor(4,3);
    lcd.print("corretamente");
    digitalWrite(led_verde, HIGH);
    buzzer_pi3();
    delay(1000);
    digitalWrite(led_verde, LOW);
    bem_vindo();
} else {
    digitalWrite(led_amarelo, HIGH);
  lcd.clear();
  lcd.setCursor(4,1);
  lcd.print("O sensor nao");
  lcd.setCursor(2,2);
  lcd.print(" foi encontrado.");
  lcd.setCursor(0,3);
  lcd.print("Verifique a ligacao!");
    while (1) { 
      delay(1);
    }
  }
  if (grava) {
    while (  getFingerprintEnroll(id) == -1 );
  }
}

String lastMsg = "";

void loop() {

  char leitura_teclas = teclado_personalizado.getKey();
  sensorValue = analogRead(ldr);
  Serial.println(sensorValue); 
//Quando a sala estiver escura, luz apagada a tranca é desbloqueada
   if(sensorValue < setpoint){
     digitalWrite(rele, 0);
  } else {
	 digitalWrite(rele, 1);
  }
//Sensor de presença  
  if (digitalRead(proximidade) == LOW){
    digitalWrite(rele, 0);
  }else{
    digitalWrite(rele, 1);
  }
  if (leitura_teclas) {
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    if (leitura_teclas == 'C') {
      modo_cadastro = true;
      senha.reset();
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("DIGITE A SENHA");
      lcd.setCursor(4,1);
      lcd.print("PARA ENTRAR");
      lcd.setCursor(1,2);
      lcd.print("NO MODO CADASTRO");
    } else if (leitura_teclas == 'D') {
      modo_remover = true;
      senha.reset();
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("DIGITE A SENHA");
      lcd.setCursor(4,1);
      lcd.print("PARA ENTRAR");
      lcd.setCursor(2,2);
      lcd.print("NO MODO REMOVER");
    } else if (leitura_teclas == 'A') {
      passapadento = true;
      senha.reset();
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("DIGITE A SENHA");
      lcd.setCursor(4,1);
      lcd.print("PARA ENTRAR");
      lcd.setCursor(2,2);
      lcd.print("DESTRANCAR A PORTA");
    } else if (leitura_teclas == 'B') {
      modo_livre = true;
      senha.reset();
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("DIGITE A SENHA");
      lcd.setCursor(4,1);
      lcd.print("PARA ENTRAR");
      lcd.setCursor(3,2);
      lcd.print("NO MODO LIVRE");
    } else if (modo_cadastro) {
      if (leitura_teclas == '#') {
        if (senha.evaluate()) {
          adicionarDigital();
        } else {
          lcd.clear();
          lcd.setCursor(3,1);
          lcd.print("SENHA INCORRETA");
          digitalWrite(led_vermelho, HIGH);
          buzzer_pi2();
          delay(700);
          digitalWrite(led_vermelho, LOW);
          bem_vindo();
        }
        modo_cadastro = false;
      } else if (leitura_teclas == '*') {
          modo_cadastro = false;
          lcd.clear();
          lcd.setCursor(1,1);
          lcd.print("OPERACAO CANCELADA");
          buzzer_pi2();
          delay(500);
          bem_vindo();
      } else {
          Serial.print(leitura_teclas);
          senha.append(leitura_teclas);
      }
    } else if (modo_remover) {
      if (leitura_teclas == '#') {
        if (senha.evaluate()) {
          senha.reset();
          Serial.println("Senha removida com sucesso!");
          removerDigital();
        } else {
          lcd.clear();
          lcd.setCursor(3,1);
          lcd.print("SENHA INCORRETA");
          digitalWrite(led_vermelho, HIGH);
          buzzer_pi2();
          delay(700);
          digitalWrite(led_vermelho, LOW);
          bem_vindo();
        }
        modo_remover = false;
      } else if (leitura_teclas == '*') {
        modo_remover = false;
        Serial.println("Operação cancelada");
        lcd.clear();
        lcd.setCursor(1,1);
        lcd.print("OPERACAO CANCELADA");
        buzzer_pi2();
        delay(500);
        bem_vindo();
      } else {
        Serial.print(leitura_teclas);
        senha.append(leitura_teclas);
      }
    } else if (passapadento) {
      if (leitura_teclas == '#') {
        if (senha.evaluate()) {
          senha.reset();
          autorizado();
        } else {
          lcd.clear();
          lcd.setCursor(3,1);
          lcd.print("SENHA INCORRETA");
          digitalWrite(led_vermelho, HIGH);
          buzzer_pi2();
          delay(700);
          digitalWrite(led_vermelho, LOW);
          bem_vindo();
        }
        passapadento = false;
      } else if (leitura_teclas == '*') {
        passapadento = false;
        lcd.clear();
        lcd.setCursor(1,1);
        lcd.print("OPERACAO CANCELADA");
        buzzer_pi2();
        delay(500);
        bem_vindo();
      } else {
        Serial.print(leitura_teclas);
        senha.append(leitura_teclas); 
      }
    } else if (modo_livre) { 
      if (leitura_teclas == '#') {
        if (senha.evaluate()) {
          senha.reset();
          buzzer_pi();
          lcd.clear();
          while (true) {
            leitura_teclas = teclado_personalizado.getKey(); 
            if (leitura_teclas == 'B') {
              modo_livre = false;
              buzzer_pi();
              digitalWrite(rele, 1);
              bem_vindo();
              break; 
            }
            senha.reset();
            lcd.setCursor(5, 1);
            lcd.print("MODO LIVRE");
            lcd.setCursor(2, 1);
            lcd.print(" ");
            delay(100);
            digitalWrite(rele, 0);
        }
        } else {
          lcd.clear();
          lcd.setCursor(3,1);
          lcd.print("SENHA INCORRETA");
          digitalWrite(led_vermelho, HIGH);
          buzzer_pi2();
          delay(700);
          digitalWrite(led_vermelho, LOW);
          bem_vindo();
        }
        modo_livre = false;
      } else if (leitura_teclas == '*') {
        modo_livre = false;
        lcd.clear();
        lcd.setCursor(1,1);
        lcd.print("OPERACAO CANCELADA");
        buzzer_pi2();
        delay(500);
        bem_vindo();
      } else {
        Serial.print(leitura_teclas);
        senha.append(leitura_teclas); 
      }
    }else {
      Serial.println(leitura_teclas);
    }
  }
  byte leitura = getFingerprintID();
}
uint8_t readnumberadd(void) {
  uint8_t num = 0;
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      break;
    case FINGERPRINT_NOFINGER:
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Erro na comunnicacao");
      erro_comunicacao();
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Erro na imagem");
      return p;
    default:
      Serial.println("Erro desconhecido");
      erro_desconhecido();
      return p;
  }

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagem Convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagem muito confusa");
      imagem_confusa();
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Erro na comunicacao");
      erro_comunicacao();
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Nao foi possive encontrar digital");
          nao_encontrou_digital();
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Nao foi possive encontrar digital");
          nao_encontrou_digital();
      return p;
    default:
      Serial.println("Erro desconhecido");
      erro_desconhecido();
      return p;
  }

  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Impressao compativel");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Erro de comunicacao");
    erro_comunicacao();
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Sem correspodencia");
    sem_correspodencia();
    return p;
  } else {
    Serial.println("Erro Desconhecido");
    erro_desconhecido();
    return p;
  }
  autorizado();
}