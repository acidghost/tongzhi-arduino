/*
 * 
*/

void setup() {
	Serial.begin(9600);
}

void loop() {
	String line = "";
	while(Serial.available()) {
		delay(3);
		char c = Serial.read();
		if(c == '\n') {
			break;
		}
		line += c;
	}

	if(line != "") {
		Serial.println("Back: "+line);
	}
	delay(500);
}
