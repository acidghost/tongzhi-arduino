/*
 * This is the Arduino side of tongzhi
 *
 * It will receive messages from the node.js notifier
 * and take some actions accordingly
*/

const int fbLikesLed = 13;
const int fbMsgsLed = 12;

const String fbLikesMsg = "FB-likes ";
const String fbMsgsMsg = "FB-msg ";

unsigned int fbLikes = 0;
unsigned int fbLikesCount = 0;
unsigned int fbMsgs = 0;
unsigned int fbMsgsCount = 0;

void setup() {
	Serial.begin(9600);

	pinMode(fbLikesLed, OUTPUT);
	pinMode(fbMsgsLed, OUTPUT);
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
		} else if(line.indexOf(fbMsgsMsg) == 0) {
			fbMsgs = line.substring(fbMsgsMsg.length(), line.length()).toInt();
			fbMsgsCount = fbMsgs;
		}
	}

	// Turn on FB likes LED notification
	if(fbLikes > 0 && fbLikesCount > 0) {
		digitalWrite(fbLikesLed, HIGH);
	}
	// Turn on FB unread messages LED notification
	if(fbMsgs > 0 && fbMsgsCount > 0) {
		digitalWrite(fbMsgsLed, HIGH);
	}

	delay(500);

	// Turn off FB likes LED notification
	if(fbLikes > 0 && fbLikesCount > 0) {
		digitalWrite(fbLikesLed, LOW);
		fbLikesCount--;
	}
	// Turn off FB unread messages LED notification
	if(fbMsgs > 0 && fbMsgsCount > 0) {
		digitalWrite(fbMsgsLed, LOW);
		fbMsgsCount--;
	}

	if(fbLikes>0 || fbMsgs>0) {
		if(fbLikesCount==0 && fbMsgsCount==0) {
			delay(5750);
			fbLikesCount = fbLikes;
			fbMsgsCount = fbMsgs;
		}
	}

	delay(250);
}
