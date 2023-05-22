extern const int led_verde;
extern const int led_vermelho;
extern const int led_amarelo;

extern void buzzer_pi3();
extern void buzzer_pi();
extern void buzzer_pi2();
extern void erro_comunicacao();
extern void erro_desconhecido();
extern void imagem_confusa();
extern void sucesso();
extern void falha();
extern void erro_na_comunicacao_1();
extern void erro_na_imagem_1();
extern void erro_desconhecido_1();
extern void imagem_baguncada();
extern void erro_na_comunicacao_2();
extern void nao_encontrou_digital_2();
extern void erro_desconhecido_2();

void adicionarDigital() {

  lcd.clear();
  lcd.setCursor(4,1);
  lcd.print("MODO CADASTRO");
  digitalWrite(led_amarelo, HIGH);
  buzzer_pi3();
  //Serial.println("\nCadastro de digital");
  //Serial.println("Digite o ID # (entre 1 e 127) da digital que vai gravar...");
  delay(1000);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Digite o ID #");
  lcd.setCursor(3,1);
  lcd.print("(entre 1 e 127)");
  lcd.setCursor(4,2);
  lcd.print("da digital que");
  lcd.setCursor(5,3);
  lcd.print("registrada:");
  buzzer_pi();
  
  String id_str = "";
  bool id_done = false;

  while (!id_done) {
      char key = teclado_personalizado.getKey();
      if (key >= '0' && key <= '9') {
          id_str += key;
          lcd.print(key);
          buzzer_pi();
      } else if (key == '#' && id_str.length() > 0) {
          id_done = true;
      }
  }

  int id = id_str.toInt();
  Serial.print("Cadastrando ID #");
  Serial.println(id);
  delay(500);
  
  while (!getFingerprintEnroll(id));
}

uint8_t getFingerprintEnroll(int id) {

  int p = -1;
      lcd.clear();
      lcd.setCursor(2,1);
      lcd.print("INSIRA A DIGITAL");
      lcd.setCursor(3,2);
      lcd.print("PARA CADASTRO");
      sucesso();
      delay(500);

  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        erro_na_comunicacao_1();
        break;
      case FINGERPRINT_IMAGEFAIL:
        erro_na_imagem_1();
        break;
      default:
        erro_desconhecido_1();
        break;
    }
  }

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      break;
    case FINGERPRINT_IMAGEMESS:
      imagem_baguncada();
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      erro_na_comunicacao_2();
      return p;
    case FINGERPRINT_FEATUREFAIL:
      nao_encontrou_digital_2();
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      nao_encontrou_digital_2();
      return p;
    default:
      erro_desconhecido_2();
      return p;
  }
      lcd.clear();
      lcd.setCursor(4,1);
      lcd.print("RETIRE O DEDO");
      sucesso();

  delay(1000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;

      lcd.clear();
      lcd.setCursor(3,1);
      lcd.print("INSIRA O MESMO");
      lcd.setCursor(3,2);
      lcd.print("DEDO NOVAMENTE");
      sucesso();
      delay(500);

  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        erro_na_comunicacao_1();
        break;
      case FINGERPRINT_IMAGEFAIL:
        erro_na_imagem_1();
        break;
      default:
        erro_desconhecido_1();
        break;
    }
  }

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      break;
    case FINGERPRINT_IMAGEMESS:
      imagem_baguncada();
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      erro_na_comunicacao_2();
      return p;
    case FINGERPRINT_FEATUREFAIL:
      nao_encontrou_recurso();
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      nao_encontrou_recurso();
      return p;
    default:
      erro_desconhecido_2();
      return p;
  }

  //Serial.print("Criando modelo para ID #");  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    //Serial.println("Digitais conferem!");

  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    erro_na_comunicacao_2();
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
      lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("DIGITAIS NAO BATEM");
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
    return p;
  } else {
    erro_desconhecido_2();
    return p;
  }

  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
      lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("CADASTRO REALIZADO");
      lcd.setCursor(4,2);
      lcd.print("COM SUCESSO");
      digitalWrite(led_verde, HIGH);
      digitalWrite(led_amarelo, LOW);
      buzzer_pi3();
      delay(1000);
      digitalWrite(led_verde, LOW);
      bem_vindo();  

  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
      erro_na_comunicacao_2();
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
      lcd.clear();
      lcd.setCursor(3,1);
      lcd.print("NAO E POSSIVEL");
      lcd.setCursor(1,2);
      lcd.print("GRAVAR NESTE LOCAL");
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
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
      lcd.clear();
      lcd.setCursor(3,1);
      lcd.print("ERRO AO GRAVAR");
      lcd.setCursor(6,2);
      lcd.print("NO FLASH");
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
    return p;
  } else {
      erro_desconhecido_2();
    return p;
  }

  return true;
}
uint8_t readnumber(void) {
  uint8_t num = 0;

  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}