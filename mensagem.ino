#include <LiquidCrystal_I2C.h>

extern String lastMsg;

void mensagem(String msg) {
  lcd.clear();
  lcd.setCursor(0, 0);
  int len = msg.length();
  if (len <= 20) {
    lcd.print(msg);
  } else {
    for (int i = 0; i <= len - 20; i++) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(msg.substring(i, i + 20));
      delay(300);
      lcd.scrollDisplayLeft();
      lcd.setCursor(0, 1);
    }
  }
  lastMsg = "";
}


void mensagem1(String msg) {
  lcd.clear();
  lcd.setCursor(0, 0);
  int len = msg.length();
  if (len <= 20) {
    lcd.print(msg);
  } else {
    for (int i = 0; i <= len - 20; i++) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(msg.substring(i, i + 20));
      delay(300);
      lcd.scrollDisplayLeft();
      lcd.setCursor(0, 1);
    }
  }
  delay(1000);
  lastMsg = "";
}

void mensagem2(String msg) {
  lcd.clear();
  lcd.setCursor(0, 0);
  int len = msg.length();
  if (len <= 20) {
    lcd.print(msg);
  } else {
    for (int i = 0; i <= len - 20; i++) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(msg.substring(i, i + 20));
      delay(300);
      lcd.scrollDisplayLeft();
      lcd.setCursor(0, 1);
    }
  }
  delay(2000);
  lastMsg = "";
}


void sucesso(){
  digitalWrite(led_verde, HIGH);
  buzzer_pi();
  delay(400);
  digitalWrite(led_verde, LOW);
}
void falha(){
  digitalWrite(led_vermelho, HIGH);
  buzzer_pi2();
  digitalWrite(led_vermelho, LOW);
}

void bem_vindo(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Bem Vido ao LIMS");
  lcd.setCursor(1,2);
  lcd.print("INSIRA SUA DIGITAL");
}
