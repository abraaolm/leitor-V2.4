#include <Arduino.h>

extern void buzzer_pi3();
extern void buzzer_pi2();
extern void buzzer_pi();
extern const int buzzer;
extern const int led_verde;
extern const int led_vermelho;
extern const int rele;
extern const int led_amarelo;
extern void falha();


void autorizado(){        
  digitalWrite(led_verde, HIGH);
  digitalWrite(rele, LOW);
  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("ACESSO PERMITIDO");
    Serial.println(id);
  buzzer_pi();
  delay(700);
  digitalWrite(rele, HIGH);
  delay(700);
  digitalWrite(led_verde, LOW);
  
  bem_vindo();
  delay(200);
  return finger.fingerID;
}

void sem_correspodencia(){
  digitalWrite(led_vermelho, HIGH);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("SEM CORRESPONDENCIA");
  buzzer_pi();
  delay(300);
  digitalWrite(led_vermelho, LOW);
  delay(100);
  bem_vindo();
}

void nao_encontrou_digital(){
  digitalWrite(led_amarelo, HIGH);
  lcd.clear();
  lcd.setCursor(4,1);
  lcd.print("DIGITAL  NAO");
  lcd.setCursor(5,2);
  lcd.print("ENCONTRADA");
  buzzer_pi2();
  delay(500);
  digitalWrite(led_amarelo, LOW);
  delay(100);
  bem_vindo();
  return finger.fingerID;
}

void erro_comunicacao(){
  digitalWrite(led_amarelo, HIGH);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("ERRO DE COMUNICACAO");
  buzzer_pi2();
  delay(1000);
  digitalWrite(led_amarelo, LOW);
  delay(200);
  bem_vindo();
  return finger.fingerID;
}

void imagem_confusa(){
  digitalWrite(led_amarelo, HIGH);
  lcd.clear();
  lcd.setCursor(5,1);
  lcd.print("IMAGEM ESTA");
  lcd.setCursor(4,2);
  lcd.print("MUITO CONFUSA");
  buzzer_pi2();
  delay(1000);
  digitalWrite(led_amarelo, LOW);
  delay(200);
  bem_vindo();
  return finger.fingerID;
}

void erro_desconhecido(){
  digitalWrite(led_amarelo, HIGH);
  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("ERRO DESCONHECIDO");
  buzzer_pi2();
  delay(1000);
  digitalWrite(led_amarelo, LOW);
  delay(200);
  bem_vindo();
  return finger.fingerID;
}

void erro_na_comunicacao_1(){
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("ERRO DE COMUNICACAO");
  falha();
  delay(1500);
  lcd.clear();
  lcd.setCursor(1,1);
  lcd.print("Aguardando digital");
  lcd.setCursor(2,2);
  lcd.print("para cadastro #");

}

void erro_na_imagem_1(){
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("ERRO NA IMAGEM");
  falha();
  delay(1500);
  lcd.clear();
  lcd.setCursor(1,1);
  lcd.print("Aguardando digital");
  lcd.setCursor(2,2);
  lcd.print("para cadastro #");
}

void erro_desconhecido_1(){
  lcd.setCursor(2,1);
  lcd.print("ERRO DESCONHECIDO");
  falha();
  delay(1500);
  lcd.clear();
  lcd.setCursor(1,1);
  lcd.print("Aguardando digital");
  lcd.setCursor(2,2);
  lcd.print("para cadastro #");
}

void imagem_baguncada(){
  lcd.clear();
  lcd.setCursor(5,1);
  lcd.print("IMAGEM ESTA");
  lcd.setCursor(3,2);
  lcd.print("MUITO BAGUNCADA");
  falha();
  delay(1000);
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("CADASTRO FALHOU");
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_amarelo, LOW);
  buzzer_pi3();
  delay(1000);
  digitalWrite(led_vermelho, LOW);
  bem_vindo();
}

void erro_na_comunicacao_2(){
  lcd.setCursor(0,1);
  lcd.print("ERRO DE COMUNICACAO");
  falha();
  delay(1000);
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("CADASTRO FALHOU");
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_amarelo, LOW);
  buzzer_pi3();
  delay(1000);
  digitalWrite(led_vermelho, LOW);
  bem_vindo();
}

void nao_encontrou_digital_2(){
  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("NAO FOI POSSIVEL");
  lcd.setCursor(1,2);
  lcd.print("ENCONTRAR RECURSOS");
  lcd.setCursor(4,3);
  lcd.print("DE IMPRESSAO");  
  falha();
  delay(1000);
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("CADASTRO FALHOU");
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_amarelo, LOW);
  buzzer_pi3();
  delay(1000);
  digitalWrite(led_vermelho, LOW);
  bem_vindo();
}

void erro_desconhecido_2(){
  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("ERRO DESCONHECIDO");
  falha();
  delay(1000);
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("CADASTRO FALHOU");
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_amarelo, LOW);
  buzzer_pi3();
  delay(1000);
  digitalWrite(led_vermelho, LOW);
  bem_vindo();
}

void nao_encontrou_recurso(){
  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("NAO FOI POSSIVEL");
  lcd.setCursor(1,2);
  lcd.print("ENCONTRAR RECURSOS");
  lcd.setCursor(4,3);
  lcd.print("DE IMPRESSAO");  
  falha();
  delay(1000);
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("CADASTRO FALHOU");
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_amarelo, LOW);
  buzzer_pi3();
  delay(1000);
  digitalWrite(led_vermelho, LOW);
  bem_vindo();
}