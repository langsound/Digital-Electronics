void sendMIDI(int statusByte, int Data1, int Data2){
  Serial.write(statusByte);   //midi status byte
  Serial.write(Data1);        //cc number or note number
  Serial.write(Data2);        //cc data or note velocity
  delay(3);
}//end void sendMIDI
