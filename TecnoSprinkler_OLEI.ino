
const int sensor = A0;          //Pin en el que está conectado el sensor
const int Rc = 330;            //Resistencia de calibración
const int relay = 4;            //Pin en en que está conectado el Relay            
int V;
int contador = 0;
long Rsensor;
long Resk;
unsigned long tr = 1;            //Tiempo de regado  en minutos                                  
unsigned long tespera = 10;      //Tiempo espera en minutos                                      
const int rr = 13;/////               //Resistencia (en kohmios) a partir de la cual empieza a regar   
const int pinecho = 5;
const int pintrigger = 6;

unsigned int tiempo, distancia;

void setup() {
  Serial.begin(9600);             //inicia comunicación serial
  pinMode (relay,OUTPUT);         //Configurar relay como salida
  pinMode(pinecho, INPUT);        //Pin ECHO ultrasonico
  pinMode(pintrigger, OUTPUT);    //Pin TIGGER ultrasonico
}

void loop() {
  V =  analogRead(sensor);        //leer sensor
  Rsensor = 1024L * Rc / V - Rc;  //calcular resistencia del sensor
  Resk = Rsensor /1000;           //pasar a kiloohmios

  Serial.print(contador); Serial.println("  riegos.");  //contador para ver en serial cuantas veces se ha regado
Serial.print("Valor resistencia: "); Serial.print(Resk); Serial.println(" mil ohmios ");   //escribir en serial el valor de la resistencia
  delay(1000);

 if (Resk>rr){
  digitalWrite(relay,HIGH);       //activar relay
  delay(tr*60*1000);              // Espera Tiempo de regado con relay activado
  digitalWrite(relay,LOW);        //desactivar relay
  delay(tespera*60*330);         // Espera Tiempo de espera entre regados con relay desactivado para que el agua se filtre a la tierra y llegue al sensor
  contador = contador + 1 ;   
  }
  
  
  digitalWrite(pintrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pintrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pintrigger, LOW);
 
  // MEDIR EL TIEMPO EN ESTADO ALTO DEL PIN "ECHO" EL PULSO ES PROPORCIONAL A LA DISTANCIA MEDIDA
  tiempo = pulseIn(pinecho, HIGH);
 
  // LA VELOCIDAD DEL SONIDO ES DE 340 M/S O 29 MICROSEGUNDOS POR CENTIMETRO
  // DIVIDIMOS EL TIEMPO DEL PULSO ENTRE 58, TIEMPO QUE TARDA RECORRER IDA Y VUELTA UN CENTIMETRO LA ONDA SONORA
  distancia = tiempo / 58;
 
  // ENVIAR EL RESULTADO AL MONITOR SERIAL
  Serial.print(distancia);
  Serial.println(" cm");
  delay(200);
 
  // ENCENDER EL LED CUANDO SE CUMPLA CON CIERTA DISTANCIA
  if (distancia <= 20) {
    digitalWrite(2, HIGH);
    delay(500);
  } else {
    digitalWrite(2, LOW);
  }

 }


