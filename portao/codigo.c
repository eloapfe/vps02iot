const int aberto = 4;
const int fechado = 2;
const int comando = 8;
const int ligado = 12;
const int direcao = 13;
int dir = 1;

const int ledPinVermelho = 10; // LED vermelho
const int ledPinVerde = 11; // LED verde
const int intervaloAberto = 1000; // Intervalo para aberto (1 segundo)
const int intervaloFechado = 500; // Intervalo para fechado (0.5 segundo)

void setup() {
  pinMode(aberto, INPUT);
  pinMode(fechado, INPUT);
  pinMode(comando, INPUT);
  pinMode(ligado, OUTPUT);
  pinMode(direcao, OUTPUT);
  pinMode(ledPinVermelho, OUTPUT);
  pinMode(ledPinVerde, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int inicioEstado = digitalRead(aberto);
  int fimEstado = digitalRead(fechado);
  int com = digitalRead(comando);
  delay(400);

  if (inicioEstado == HIGH) {
    Serial.println("Aberto");
    digitalWrite(ligado, LOW);
    dir = 1;
  } else if (fimEstado == HIGH) {
    Serial.println("Fechado");
    digitalWrite(ligado, LOW);
    dir = 0;
  } else {
    digitalWrite(direcao, dir);
    if (com == HIGH) {
      if (dir == 1) {
        dir = 0;
        Serial.println("Portão fechando");
      } else {
        dir = 1;
        Serial.println("Portão abrindo");
      }
      digitalWrite(ligado, HIGH);
    }
    
    if (dir == 1) { // Se estiver abrindo
      digitalWrite(ledPinVerde, HIGH); // Acende o LED verde
      piscarLed(ledPinVermelho, intervaloAberto); // Pisca o LED vermelho
    } else { // Se estiver fechando
      digitalWrite(ledPinVermelho, HIGH); // Acende o LED vermelho
      piscarLed(ledPinVerde, intervaloFechado); // Pisca o LED verde
    }
  }
}

// Função para piscar o LED
void piscarLed(int pin, int intervalo) {
  digitalWrite(pin, HIGH);
  delay(intervalo);
  digitalWrite(pin, LOW);
  delay(intervalo);
}
