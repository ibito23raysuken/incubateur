void _regulation(){
  /***gestion des temperature***/
  if(temp<TempMin){
  //  _ArretVentille();
    _MarcheLampe();
  }
  else if(temp>TempMax){
   // _MarcheResistance();
  // Serial.println("resistance");
     _ArretLampe();
  }
  else{
    _ArretVentille();
  }
  /***gestion des humiditer***/
  if(h>HumMax){
   // _ArretResistance();
      _ArretVentille();
  }
  else if(h<HumMin){
   // _MarcheResistance();
  // Serial.println("resistance");
      _MarcheVentille();
  }
  else{
   //_ArretResistance();
  _ArretVentille();
  }
}
