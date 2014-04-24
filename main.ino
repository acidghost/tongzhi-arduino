/*
 * This is the Arduino side of tongzhi
 *
 * It will receive messages from the node.js notifier
 * and take some actions accordingly
*/

const int fbLikesLed = 13;

const String fbLikesMsg = "FB-likes ";

unsigned int fbLikes = 0;
unsigned int fbLikesCount = 0;

void setup() {
	Serial.begin(9600);

	pinMode(fbLikesLed, OUTPUT);
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
		Serial.println("Received: "+line);

		if(line.indexOf(fbLikesMsg) == 0) {
			fbLikes = line.substring(fbLikesMsg.length(), line.length()).toInt();
			fbLikesCount = fbLikes;
		}
	}

	if(fbLikes > 0 && fbLikesCount > 0) {
		digitalWrite(fbLikesLed, HIGH);
	}

	delay(500);

	if(fbLikes > 0 && fbLikesCount > 0) {
		digitalWrite(fbLikesLed, LOW);
		fbLikesCount--;
	}

	delay(250);
}
