/*************************************************
les divers initalisation materiel
 ******************************************************/
 void Initialisation_verin(){
  pinMode(fin_de_course_haut, INPUT_PULLUP);
  pinMode(fin_de_course_bas, INPUT_PULLUP);
  pinMode(verin_haut, OUTPUT);
  pinMode(verin_bas, OUTPUT);
  etat_fin_bas = HIGH;
  etat_fin_haut = HIGH;
  memoire_haut=1;
  memoire_bas=1;
}
void Initialisation_RTC(){
 // données pour mettre à l'heure l'horloge
    clock.begin();   
  // Set sketch compiling time
 // clock.setDateTime(__DATE__, __TIME__);
 /*
  DS3231_init(DS3231_INTCN);
  t.hour=12; //definir heure
  t.min=43; //definir min
  t.sec=40; //definir seconde
  t.mday=6; //definr jour
  t.mon=4;//definir mois
  t.year=2018;//definir annee
  DS3231_set(t); //entree les configuration
  */
//  rtc.begin();
}
void Initialisation_lcd(){
  lcd.begin(20,4);
  lcd.createChar(0, celcus);

}
void Initialisation_inter(){
  TCCR2A=0;
  TCCR2B = 0b00000111;      // Clock / 1024 soit 16 micro-s et WGM22 = 0
  TIMSK2 = 0b00000001; // TOIE2
  TCNT2 = 256 - 250;        // Chargement du timer à 6
  sei();               // autorise les interruptions
}
void Initilisation_materiel(){
  pinMode(ventilateur, OUTPUT);
  pinMode(resistance, OUTPUT);
  pinMode(motor_pompe, OUTPUT);
  pinMode(lamp, OUTPUT);
  digitalWrite(ventilateur, HIGH) ;
  digitalWrite(resistance, HIGH) ;
  digitalWrite(motor_pompe, HIGH) ;
  digitalWrite(lamp, HIGH) ;
  pinMode(fin_de_course_haut, INPUT_PULLUP);
  pinMode(fin_de_course_bas, INPUT_PULLUP);
  pinMode(verin_haut, OUTPUT);
  pinMode(verin_bas, OUTPUT);
  digitalWrite(verin_bas,HIGH);
  digitalWrite(verin_haut,HIGH);
  etat_fin_bas = HIGH;
  etat_fin_haut = HIGH;
  memoire_haut=1;
  memoire_bas=1;
/*initialisation de jour de l'incubation*/
  pinMode(button_run,INPUT_PULLUP);
   etat_jour=T0;
   etat_pompe=P0;
   date_save=1;
   date_today=1;
   etat_prg=true;
}
