#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);

void setup(void) {
  Serial.begin(115200);
  Serial.println("Hello!");

  nfc.begin();

  // Obter a versão do firmware do PN532
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Não foi possível encontrar a placa PN53x");
    while (1); // Parar o programa
  }

  // Se a placa foi encontrada, imprime informações do firmware
  Serial.print("Chip PN5 encontrado: "); 
  Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); 
  Serial.print((versiondata >> 16) & 0xFF, DEC); 
  Serial.print('.'); 
  Serial.println((versiondata >> 8) & 0xFF, DEC);

  // Configura o número máximo de tentativas de leitura de um cartão
  nfc.setPassiveActivationRetries(0xFF);

  // Configura a placa para ler tags RFID
  nfc.SAMConfig();

  Serial.println("Aguardando um cartão ISO14443A");
}

void loop(void) {
  boolean success;
  uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0}; // Buffer para armazenar o UID retornado
  uint8_t uidLength; // Comprimento do UID (4 ou 7 bytes dependendo do tipo de cartão ISO14443A)

  // Espera por um cartão do tipo ISO14443A (Mifare, etc.).
  // Quando encontrado, 'uid' será preenchido com o UID e 'uidLength' indicará
  // se o UID possui 4 bytes (Mifare Classic) ou 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  if (success) {
    Serial.println("Cartão encontrado!");
    Serial.print("Comprimento do UID: ");
    Serial.print(uidLength, DEC);
    Serial.println(" bytes");
    Serial.print("Valor do UID: ");
    String hex_value = "";
    for (uint8_t i = 0; i < uidLength; i++) {
      Serial.print(" 0x");
      Serial.print(uid[i], HEX);
      hex_value += (String)uid[i];
    }

    Serial.println(", valor=" + hex_value);

    // Verifica se o UID corresponde a alguns valores específicos
    if (hex_value == "16517722582") {
      Serial.println("Este é um Key Tag.");
    } else if (hex_value == "230522426") {
      Serial.println("Este é um Card Tag.");
    } else if (hex_value == "63156295") {
      Serial.println("Este é um Phone Tag.");
    } else {
      Serial.println("Não sei.");
    }

    Serial.println("");
    delay(1000); // Aguarda 1 segundo antes de continuar
  } else {
    // O PN532 provavelmente atingiu o tempo limite aguardando por um cartão
    Serial.println("Aguardando por um cartão...");
  }
}