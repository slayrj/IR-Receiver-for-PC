#include <Arduino.h>
#include <HID-Project.h>
#include <IRremote.h>

int IR_RECEIVE_PIN = 6;

IRrecv IrReceiver(IR_RECEIVE_PIN);

bool windowsMode = false;

#define relePin 4

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(relePin, OUTPUT);
    digitalWrite(relePin, LOW);

    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)
    delay(2000); // Para ativar a leitura de porta serial
#endif
    Serial.println(F("START " __FILE__ " from " __DATE__));
    IrReceiver.enableIRIn();  // Inicia o receiver
    IrReceiver.blink13(true); // Ativa o LED de feedback

    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN);

    // Inicia a conexão HID
    Consumer.begin(); // HID para Controle Remoto
    Keyboard.begin(); // HID para Teclado
}

void dump() {

    if (IrReceiver.results.value == 0x8011840E || IrReceiver.results.value == 0x8011040E) {
      Consumer.write(MEDIA_VOLUME_MUTE);
      delay(250);
    }

    if (IrReceiver.results.value == 0x80118410 || IrReceiver.results.value == 0x80110410) {
      Consumer.write(MEDIA_VOLUME_UP);
      delay(250);
    }

    if (IrReceiver.results.value == 0x80110411 || IrReceiver.results.value == 0x80118411) {
      Consumer.write(MEDIA_VOLUME_DOWN);
      delay(250);
    }

    if (IrReceiver.results.value == 0x80110416 || IrReceiver.results.value == 0x80118416) {
      Consumer.write(MEDIA_PLAY_PAUSE);
      delay(250);
    }

    if (IrReceiver.results.value == 0x80110419 || IrReceiver.results.value == 0x80118419) {
      Consumer.write(MEDIA_STOP);
      delay(250);
    }

    if (IrReceiver.results.value == 0x80118414 || IrReceiver.results.value == 0x80110414) {
      Consumer.write(MEDIA_FAST_FORWARD);
      delay(250);
    }

    if (IrReceiver.results.value == 0x80118415 || IrReceiver.results.value == 0x80110415) {
      Consumer.write(MEDIA_REWIND);
      delay(250);
    }

    if (IrReceiver.results.value == 0x8011841A || IrReceiver.results.value == 0x8011041A) {
      Consumer.write(MEDIA_NEXT);
      delay(250);
    }

    if (IrReceiver.results.value == 0x8011041B || IrReceiver.results.value == 0x8011841B) {
      Consumer.write(MEDIA_PREVIOUS);
      delay(250);
    }

    if (IrReceiver.results.value == 0x8011040C || IrReceiver.results.value == 0x8011840C) {
      Consumer.write(CONSUMER_POWER);
      delay(250);
    }

    if ((IrReceiver.results.value == 0x80118422 && windowsMode == false) || (IrReceiver.results.value == 0x80110422 && windowsMode == false)) {
      Consumer.write(HID_CONSUMER_MENU_PICK);
      delay(250);
    }

    if ((IrReceiver.results.value == 0x8011841E && windowsMode == false) || (IrReceiver.results.value == 0x8011041E && windowsMode == false)) {
      Consumer.write(HID_CONSUMER_MENU_UP);
      delay(250);
    }

    if ((IrReceiver.results.value == 0x8011041F && windowsMode == false) || (IrReceiver.results.value == 0x8011841F && windowsMode == false)) {
      Consumer.write(HID_CONSUMER_MENU_DOWN);
      delay(250);
    }

    if ((IrReceiver.results.value == 0x80118420 && windowsMode == false) || (IrReceiver.results.value == 0x80110420 && windowsMode == false)) {
      Consumer.write(HID_CONSUMER_MENU_LEFT);
      delay(250);
    }

    if ((IrReceiver.results.value == 0x80110421 && windowsMode == false) || (IrReceiver.results.value == 0x80118421 && windowsMode == false)) {
      Consumer.write(HID_CONSUMER_MENU_RIGHT);
      delay(250);
    }

    if (IrReceiver.results.value == 0x80118423 || IrReceiver.results.value == 0x80110423) {
      Consumer.write(HID_CONSUMER_MENU_ESCAPE);
      delay(250);
    }

    if (IrReceiver.results.value == 0x8011040D || IrReceiver.results.value == 0x8011840D) {
      // Keyboard.write(KeyboardKeycode(93));
      Keyboard.write(KEY_RIGHT_WINDOWS);
      delay(250);
    }

    if (IrReceiver.results.value == 0x80110412 || IrReceiver.results.value == 0x80118412) {
      Keyboard.write(KEY_PAGE_UP);
      delay(250);
    }

    if (IrReceiver.results.value == 0x80110413 || IrReceiver.results.value == 0x80118413) {
      Keyboard.write(KEY_PAGE_DOWN);
      delay(250);
    }
// Tecla com Tela
    if (IrReceiver.results.value == 0x8011044F || IrReceiver.results.value == 0x8011844F) {
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_RETURN);
      Keyboard.release(KEY_RETURN);
      Keyboard.release(KEY_LEFT_ALT);
      delay(250);
    }
// Tecla DVD
    if (IrReceiver.results.value == 0x80110424 || IrReceiver.results.value == 0x80118424) {
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F4);
      Keyboard.release(KEY_F4);
      Keyboard.release(KEY_LEFT_ALT);
      delay(250);
    }

    // Modo Windows ativado
    if ((IrReceiver.results.value == 0x80118422 && windowsMode == true) || (IrReceiver.results.value == 0x80110422 && windowsMode == true)) {
      Keyboard.write(KEY_ENTER);
      Serial.println("Enter Windows Key Pressed");
      delay(250);

    }
    if ((IrReceiver.results.value == 0x8011841E && windowsMode == true) || (IrReceiver.results.value == 0x8011041E && windowsMode == true)) {
      Keyboard.write(KEY_UP_ARROW);
      Serial.println("UP ARROW Windows Key Pressed");
      delay(250);

    }
    if ((IrReceiver.results.value == 0x8011041F && windowsMode == true) || (IrReceiver.results.value == 0x8011841F && windowsMode == true)) {
      Keyboard.write(KEY_DOWN_ARROW);
      Serial.println("DOWN ARROW Windows Key Pressed");
      delay(250);

    }
    if ((IrReceiver.results.value == 0x80118420 && windowsMode == true) || (IrReceiver.results.value == 0x80110420 && windowsMode == true)) {
      Keyboard.write(KEY_LEFT_ARROW);
      Serial.println("LEFT ARROW Windows Key Pressed");
      delay(250);

    }
    if ((IrReceiver.results.value == 0x80110421 && windowsMode == true) || (IrReceiver.results.value == 0x80118421 && windowsMode == true)) {
      Keyboard.write(KEY_RIGHT_ARROW);
      Serial.println("RIGHT ARROW Windows Key Pressed");
      delay(250);
    }

    if ((IrReceiver.results.value == 0x80118423 && windowsMode == true) || (IrReceiver.results.value == 0x80110423 && windowsMode == true)) {
      Keyboard.write(KEY_ESC);
      Serial.println("KEY_ESC Windows Key Pressed");
      delay(250);
    }

    if ((IrReceiver.results.value == 0x8011040F && windowsMode == true) || (IrReceiver.results.value == 0x8011840F && windowsMode == true)) {
      Keyboard.write(KEY_MENU);
      Serial.println("CONTEXT MENU Windows Key Pressed");
      delay(250);
    }

    if ((IrReceiver.results.value == 0x8011040C && windowsMode == true) || (IrReceiver.results.value == 0x8011840C && windowsMode == true)) {
      // Keyboard.write(KEY_POWER);
      digitalWrite(relePin, HIGH);
      delay(600);
      digitalWrite(relePin, LOW);
      Serial.println("RELE Acionado!");
      delay(250);
    }

    // Muda do modo HID Consumer para o modo Windows

    if (IrReceiver.results.value == 0x8011844A || IrReceiver.results.value == 0x8011044A) {
      windowsMode = !windowsMode;
      Serial.print("Windows Mode(1=ON - 2=OFF): ");
      Serial.println(windowsMode);
      delay(250);
    }

    Serial.println(IrReceiver.results.value, HEX);
}

void loop() {
    if (IrReceiver.decode()) {
        Serial.println();
        dump();
        IrReceiver.resume(); // Prepara para receber o proximo valor
    }
}