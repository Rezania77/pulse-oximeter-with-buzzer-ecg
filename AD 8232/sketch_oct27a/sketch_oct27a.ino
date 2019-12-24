void setup() {
pinMode(10,INPUT);
pinMode(11,INPUT);

}

void loop() {
Serial.begin(9600);
if((digitalRead(10)==1)||(digitalRead(11)==1)){
Serial.println("NIL");
}
else{
Serial.println(analogRead(A0));
}
delay(100);
Serial.end();
delay(100);
}
