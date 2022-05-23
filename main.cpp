#include <LiquidCrystal.h> 

// Consideram pinul de trigger corespunzator senzorului ultrasonic de distanta ca 
// fiind corespunzator cu pinul 12 de pe placa Arduino, de asemenea pinul de echo
// avand corespunzator pinul 13. De asemenea, definim pinii corespunzatori
// pentru restul functionalitatilor
#define trigger 12
#define echo 13
#define rs 1
#define enable 2
#define D4 3
#define D5 4
#define D6 5
#define D7 6
// Definim un lcd si setam prinii corespunzatori pentru rs, enable, D4, D4, D6, D7.
LiquidCrystal lcd(rs, enable, D4, D5, D6, D7); 
// Avem nevoie de distanta curenta dar si de cea 
// anterioara pentru a elimina fluctuatia la nivelul 
// zecimalelor.
const int inf = 2e9;
double distance, duration, before_distance = inf;

/**
 * Initiem ecranul lcd ca avand dimensiunile clasice
 * si punem pinul de echo ca fiind cel 
 * de input iar trigger-ul ca fiind cel de output
 * */
void setup() {

	lcd.begin(16,2); 
	pinMode(trigger, OUTPUT);
	pinMode(echo, INPUT);
}

void loop() {

	// Pentru ca functia de pulse ce inregistreaza 
	// durata pulsului pe HIGH, trebuie sa trecem din 
	// Low in High si apoi iar in Low. Senzorul 
	// de distanta ultrasonic ne va transmite durata in 
	// timp pana la obiectul dorit.
	digitalWrite(trigger, LOW);
	digitalWrite(trigger, HIGH);
	digitalWrite(trigger, LOW);
	duration = pulseIn(echo, HIGH);
	// Astfel, odata ce avem durata, trebuie sa obtinem
	// distanta in cm. Pentru aceasta am ales sa impart la 
	// valoarea corespunzatoare pentru ca afisarea de pe LCD sa
	// fie cat mai apropiata de distanta returnata de senzor.
	distance= duration / 58.08;
	// Pentru a afisa valori fixe cu o eroare mica de aproximare, 
	// am folosit idea de verificare daca fluctuatia distantei este 
	// mai mica de 3/10. Daca da, se considera aceasi distanta, daca nu,
	// se face update distantei.
	if (fabs(distance - before_distance) < 3e-1) {
		distance = before_distance;
	}
	else {
		before_distance = distance;
	}
	// Pentru afisare trebuie sa setam cursorul pe prima linie
	// la primul caracter, afisam mesajul de distance apoi trecem
	// pe randul urmator si afisam distanta in cm.
	lcd.setCursor(0,0);
	lcd.print("Distance is: ");
	lcd.setCursor(0, 1); 
	lcd.print(distance); 
	lcd.print(" cm");
}
