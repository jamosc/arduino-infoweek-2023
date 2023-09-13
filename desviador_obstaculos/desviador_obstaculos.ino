// Sensor ultrassonico
#define PIN_TRIG 2
#define PIN_ECHO 3
// Motor A
#define CH_A1 4
#define CH_A2 5
// Motor B
#define CH_B1 6
#define CH_B2 7
// Variaveis
float distancia = 0;

void setup()
{
  // Setup sensor ultrassonico
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);
  // Setup motores
  pinMode(CH_A1, OUTPUT);
  pinMode(CH_A2, OUTPUT);
  pinMode(CH_B1, OUTPUT);
  pinMode(CH_B2, OUTPUT);
}

void loop()
{
  // O robo começa se deslocando para frente
  paraFrente();
  // Mede a distancia ate a proxima parede
  distancia = medeDistancia();

  // Caso a distancia seja menor que 15 cm, faz uma curva
  if (distancia < 15)
  {
    curva();
  }
  // Caso contrário, continua seguindo em frente
  else
  {
    paraFrente();
  }
  // A cada 0,1 segundo o robo repete essa serie de comandos
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

void curva()
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

float medeDistancia()
{
  // Para fazer o sensor enviar um pulso ultrassonico, nos temos
  // que enviar para o pino de trigger um sinal de nivel alto
  // com pelo menos 10 microssegundos de duracao
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // Mede o tempo de duracao do sinal no pino de leitura em microssegundos
  float tempo_echo = pulseIn(PIN_ECHO, HIGH);
  // Velocidade do som em metros por microssegundos
  float velocidade_som = 0.00034029;

  // Multiplicamos o tempo que o som demora para ir de um pino a outro
  //(trigger ao echo) pela velocidade do som em microssegundos e então
  // dividimos por 2 (ida e volta)  e multiplicamos por 100 para
  // encontrarmos a distancia lida em centimetros
  return (100 * (tempo_echo * velocidade_som) / 2);
}