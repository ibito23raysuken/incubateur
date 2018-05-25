
/*************************************************
 initialisation des pin arduino
 ******************************************************/
 /*variable de debut*/
 /*variable pur le bouton*/
byte etat_jour,direction_,etat_pompe;
int buttonState; 
unsigned long lastDebounceTime = 0 ;
unsigned long debounceDelay = 250; 
int lastButtonState = HIGH; 
int etat_buton_run,date_save,date_today,nbr_jour,consigne_temp,consigne_humidite;
const byte T0=0,T1=1,T2=2,T3=3,T4=4,T5=5,T6=6;
const byte S0=0,S1=1,S2=2,S3=3,S4=4,S5=5;
const byte P0=0,P1=1,P2=2;
 /*variable normal*/
String consigne="Cons: H:70% T:37C";
int tempancien=0;      
const long interval = 1000; 
const int button_run = 2,fin_de_course_haut = 18,fin_de_course_bas = 3,verin_haut = 22,verin_bas = 23,pinflotteur = 19;

byte Compteur = 0,etat_bascule;
float h,temp;
boolean etat_tache[4],findecourse_haut,findecourse_bas,etat_prg;
int deb_jour,fin_jour,count,count1,delais_temps,delais_temps1,flotteur;
int i = 0,j=0,k = 0,delayTime2 = 1000,ventilateur = 24,lamp = 25,resistance=26,motor_pompe=27,etat_fin_bas,etat_fin_haut,memoire_haut,memoire_bas,x=0;
//construction de caractere special:
//Time  t;
byte celcus[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
/*************************************************
 initialisation des tache
 ******************************************************/
 typedef void (*action_t)(void);
 const unsigned int _affichagelcd=0;
 const unsigned int _acquisition=0;
 void Tache_debutIncubation();
 void Tache_Principale();
 void Tache_acquisition();
 /*tableau de tache*/
 action_t Tache[]={
    Tache_Principale,
    Tache_acquisition,
    
 };
 /*************************************************
 initialisation des variable de regulation
 ******************************************************/
 const float TempMax=37;//definir sur 38
 const float TempMin=36;//definir sur 36
 const float HumMax=80;//definir sur 80
 const float HumMin=70;//definir sur 75
 /*************************************************
gestion du temp
 ******************************************************/
// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;
