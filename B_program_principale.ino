
/*************************************************
 programme principale
 ******************************************************/
void setup()
{
  Serial.begin(9600);
  Initialisation_lcd();
  Initialisation_RTC();
  Initialisation_inter();
  Initilisation_materiel();
  pinMode(button_run,INPUT_PULLUP);
  pinMode(pinflotteur,INPUT_PULLUP);
  flotteur=HIGH;
  /*initialisation des etat de tache*/
  etat_tache[0]=true;
  etat_tache[1]=false;
  delais_temps1=100;
  delais_temps=1000;
  count=delais_temps;
  count1=delais_temps1;
  etat_prg=false;
}
void loop(){
  if(etat_tache[0]==true) Tache[0]();
  if(etat_tache[1]==true) Tache[1]();
  delay(5);
}
/*************************************************
gestion des intrruption
 ******************************************************/
ISR (TIMER2_OVF_vect) {
  TCNT2 = 6;
  if (Compteur++ == 5) {
    Compteur=0;
    etat_tache[0]=false;
    etat_tache[1]=true;
  }
}

/*************************************************
gestion des taches
 ******************************************************/
void Tache_Principale(){
    scrollInFromRight(consigne);
    _Affichagelcd();
    Tache_debutIncubation();
    _pompe_a_eau();
    _bascule();
    _regulation();
    if(etat_prg==true){
            
    }
}
void Tache_debutIncubation(){
switch(etat_jour){
    case T0:
      date_today=dt.day;
      value = EEPROM.read(0);
      calcul_nbrjr();
      Serial.print(nbr_jour);
      lcd.setCursor(0,3);
      lcd.print("     push button     ");
      direction_=T1;
      fonction_bouton();
      //calcule de jour d'incubation
       if(nbr_jour!=0){
        etat_jour=T1;
       }
    break;
    case T1:
       if(value==0){
        Serial.println(nbr_jour);
        etat_jour=T5;
       }
       else{
        //recuperer date dans epromm
        //recuper date aujourdhui
        //afficher dateeprom-dateaujourdhui +1
        //etat_prg=true;
        if(nbr_jour>21){
          etat_jour=T2;
        }
        else{
         direction_=T3;
        fonction_bouton();
        lcd.setCursor(0,3);
        lcd.print("Jour Incubation:  ");
         lcd.print(nbr_jour);
        delay(50);    
        }
       }

       //date_today++;
    break;
    case T2:
      lcd.setCursor(0,3);
      lcd.print("fin de l'incubation ");
      date_today=0;
      direction_=T0;
      nbr_jour=0;
      fonction_bouton();     
    break;
    case T3:
      lcd.setCursor(0,3);
      lcd.print("  ---   reset  --- ");
      etat_prg=false;
     //_ArretGeneral();
     /* direction_=T1;
      fonction_bouton();*/
      date_today=0;
      direction_=T0;
      nbr_jour=0;
      fonction_bouton(); 
    break;
    case T4:
      loading();
      _MarcheLampe();
        if(temp>TempMin){
          etat_jour=T0;
        }
    break;
    case T5:
      Serial.println("ici");
      EEPROM.put(0, dt.day);
      EEPROM.put(1,dt.month);
      etat_jour=T1;
    break;
    default:
           //default
    break;
  }
}

void Tache_acquisition(){
 h = dht.readHumidity();
 temp = dht.readTemperature();
 //serial envoie de donner humiditer et temperature
/*
 Serial.print("temperature:");
 Serial.print((int)temp);
 Serial.println("°C");
 Serial.print("humidite:");
 Serial.print((int)h);
 Serial.println("%");
 */
//affichage lcd
  lcd.setCursor(0,2);
  lcd.print("H: ");
  lcd.print((int)h);
  lcd.print(" %");
  lcd.print("T:");
  lcd.print((int)temp);
  lcd.write(byte(0));
  lcd.print("C");
  etat_tache[0]=true;
  etat_tache[1]=false;

}

void _Affichagelcd(){
//  t = rtc.getTime();
  dt = clock.getDateTime();
  lcd.setCursor(0,1);
  /**affichage de date**/
  lcd.print(dt.day, DEC);
  lcd.print("/");
  lcd.print(dt.month, DEC);
  lcd.print("/");
  lcd.print(dt.year, DEC);
  lcd.print("-");
  /**affichage de heure**/
  lcd.print(dt.hour, DEC);
  lcd.print(":");
  lcd.print(dt.minute, DEC);
  lcd.print(":");
  lcd.print(dt.second, DEC);
  lcd.print("   ");
}
void _bascule(){
  switch(etat_bascule){
    case S0:
       //Serial.println("S0");
       etat_fin_bas = digitalRead(fin_de_course_bas);
       etat_fin_haut = digitalRead(fin_de_course_haut);
       if(etat_fin_bas == LOW){
           etat_bascule=S3;
       }
       else if(etat_fin_haut == LOW ){
          etat_bascule=S4;
        }
        else{
           digitalWrite(verin_bas,HIGH);
           digitalWrite(verin_haut,HIGH);
        }
    break;
    case S1:
           //Serial.println("S1");
           etat_fin_haut = digitalRead(fin_de_course_haut);
          if(etat_fin_haut == LOW) {
            etat_bascule=S4;
           }
           else{
            digitalWrite(verin_haut,HIGH);
            digitalWrite(verin_bas,LOW);
            etat_bascule=S1;
          }
    break;
    case S2:
    //Serial.println("S2");
          memoire_haut=1;
          memoire_bas=0;
          etat_fin_bas = digitalRead(fin_de_course_bas);
          if(etat_fin_bas == LOW)   {
              etat_bascule=S3;
           }
           else{
          digitalWrite(verin_haut,LOW);
          digitalWrite(verin_bas,HIGH);
           etat_bascule=S2;
           }
    break;
    case S3:
    Serial.println("S3");
         digitalWrite(verin_bas,HIGH);
         digitalWrite(verin_haut,HIGH);
         if(dt.hour==16){
            count=delais_temps;
            etat_bascule=S1;
          }
        else {
            count--;
        }
    break;
    case S4:
    Serial.println("S4");
      digitalWrite(verin_bas,HIGH);
      digitalWrite(verin_haut,HIGH);
      if(dt.hour==10){
         count=delais_temps;
         etat_bascule=S2;
      }
      else {
            count--;
        }
    break;
    default:
           //default
    break;
  }
}



