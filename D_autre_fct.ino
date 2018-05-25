void _pompe_a_eau(){
  flotteur = digitalRead(pinflotteur);
  /*
  if(flotteur==LOW)
      _ArretPompe();
  else
      _MarchePompe();*/
   
  switch(etat_pompe){
    case P0:
    //Serial.println("P0");
      _MarchePompe();
      if(flotteur==LOW)
        etat_pompe=P1;
    break;
    case P1:
     //Serial.println("P1");
       _ArretPompe();
     if(flotteur==HIGH)
        etat_pompe=P0;
    break;
    default:
           //default
    break;
  }
}
void _MarcheVentille(){
 // Serial.println("refroidire");
 digitalWrite(ventilateur, LOW) ;
 digitalWrite(resistance, LOW) ;
}
void _ArretVentille(){
  //Serial.println("arret ventille");
  digitalWrite(ventilateur, HIGH) ;
  digitalWrite(resistance, HIGH) ;
}
void _MarcheLampe(){
 //Serial.println("chauffer");
 digitalWrite(lamp, LOW) ;
}
void _ArretLampe(){
 //Serial.println("arret lampe");
 digitalWrite(lamp, HIGH) ;
}

void _ArretGeneral(){
  digitalWrite(verin_haut,HIGH);
  digitalWrite(verin_bas,HIGH);
  digitalWrite(lamp, HIGH) ;
  _ArretVentille();
}
void _MarchePompe(){
  //Serial.println("marche pompe");
  digitalWrite(motor_pompe, LOW) ;
}
void _ArretPompe(){
  //Serial.println("arret pompe");
  digitalWrite(motor_pompe, HIGH) ;
}
void scrollInFromRight (String str) {
    lcd.setCursor(0,0);
    lcd.print(str);
}
void fonction_bouton(){
         if ( etat_buton_run != lastButtonState ) {
          lastDebounceTime = millis ( ) ;
        }
        etat_buton_run= digitalRead(button_run);
        //Serial.println(millis ( ) - lastDebounceTime );
        //Serial.println(buttonState );
        if ( ( millis ( ) - lastDebounceTime ) > debounceDelay ) {     
          if(etat_buton_run == LOW){
              etat_jour=direction_;         
          }
        }
       lastDebounceTime=0;
}
void loading(){
     unsigned long tempcourant = millis();
     if ((unsigned long)(tempcourant - tempancien) >= interval){
      lcd.setCursor(0,4);
      lcd.print("loading.    ");
    }
     else if ((unsigned long)(tempcourant - tempancien) >= interval*2){
      lcd.setCursor(0,4);
      lcd.print("loading...");
     tempancien= tempcourant;
    }

}
void calcul_nbrjr(){
       if(date_today-value<0){
        value = EEPROM.read(1);
        if(value==4 || value==6|| value==9|| value==11 ){
          value = EEPROM.read(0);
          nbr_jour=30-value+date_today;
        }
        else if (value==2){
          value = EEPROM.read(0);
          nbr_jour=28-value+date_today;     
        }
        else{
          value = EEPROM.read(0);
          nbr_jour=31-value+date_today;
        }
       }
       else{     
        nbr_jour=date_today-value+1;
       }
}
void fonction_reglage_incubation(){
        if(nbr_jour<19){
          //40 % humiditer
        }
        else{
           //40 % humiditer
        }
        
}
