// Sensor ultrassonico frontal
#define PIN_TRIG_F 2
#define PIN_ECHO_F 3
// Sensor ultrassonico lateral
#define PIN_TRIG_L 8
#define PIN_ECHO_L 9
// Motor A
#define CH_A1 4
#define CH_A2 5
// Motor B
#define CH_B1 6
#define CH_B2 7
// Variaveis
float dist_frontal = 0;
float dist_lateral = 0;

void setup()
{
  // Setup sensores ultrassonicos
  pinMode(PIN_TRIG_F, OUTPUT);
  pinMode(PIN_ECHO_F, INPUT);
  digitalWrite(PIN_TRIG_F, LOW);
  pinMode(PIN_TRIG_L, OUTPUT);
  pinMode(PIN_ECHO_L, INPUT);
  digitalWrite(PIN_TRIG_L, LOW);
  // Setup motores
  pinMode(CH_A1, OUTPUT);
  pinMode(CH_A2, OUTPUT);
  pinMode(CH_B1, OUTPUT);
  pinMode(CH_B2, OUTPUT);
}

void loop()
{
  paraFrente();
  dist_frontal = medeDistancia(PIN_TRIG_F, PIN_ECHO_F);
  dist_lateral = medeDistancia(PIN_TRIG_L, PIN_ECHO_L);
  if (dist_frontal < 10 && dist_lateral < 10)
  {
    curvaEsquerda();
  }
  else if (dist_frontal < 10 && dist_lateral > 10)
  {
    curvaDireita();
  }
  else
  {
    paraFrente();
  }
  delay(100);
}

void paraFrente()
{
  // Gira o motor A para frente
  digitalWrite(CH_A1, HIGH);
  digitalWrite(CH_A2, LOW);
  // Gira o motor B para frente
  digitalWrite(CH_B1, HIGH);
  digitalWrite(CH_B2, LOW);
}

void curvaEsquerda()
{
  // Gira o motor A para trás
  digitalWrite(CH_A1, LOW);
  digitalWrite(CH_A2, HIGH);
  // Gira o motor B para frente
  digitalWrite(CH_B1, HIGH);
  digitalWrite(CH_B2, LOW);
  // Espera 1 segundo
  delay(1000);

  // Freia ambos os motores por 0,2 segundos
  digitalWrite(CH_A1, HIGH);
  digitalWrite(CH_A2, HIGH);
  digitalWrite(CH_B1, HIGH);
  digitalWrite(CH_B2, HIGH);
  delay(200);
}

void curvaDireita()
{
  // Gira o motor A para frente
  digitalWrite(CH_A1, HIGH);
  digitalWrite(CH_A2, LOW);
  // Gira o motor B para trás
  digitalWrite(CH_B1, LOW);
  digitalWrite(CH_B2, HIGH);
  // Espera 1 segundo
  delay(1000);

  // Freia ambos os motores por 0,2 segundos
  digitalWrite(CH_A1, HIGH);
  digitalWrite(CH_A2, HIGH);
  digitalWrite(CH_B1, HIGH);
  digitalWrite(CH_B2, HIGH);
  delay(200);
}

float medeDistancia(int pinTrig, int pinEcho)
{
  // Para fazer o sensor enviar um pulso ultrassonico, nos temos
  // que enviar para o pino de trigger um sinal de nivel alto
  // com pelo menos 10 microssegundos de duracao
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);

  // Mede o tempo de duracao do sinal no pino de leitura em microssegundos
  float tempo_echo = pulseIn(pinEcho, HIGH);
  // Velocidade do som em metros por microssegundos
  float velocidade_som = 0.00034029;

  // Multiplicamos o tempo que o som demora para ir de um pino a outro
  //(trigger ao echo) pela velocidade do som em microssegundos e então
  // dividimos por 2 (ida e volta)  e multiplicamos por 100 para
  // encontrarmos a distancia lida em centimetros
  return (100 * (tempo_echo * velocidade_som) / 2);
}