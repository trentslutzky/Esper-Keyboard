

// This is very similar to Example 3 - Receive with start- and end-markers
//    in Serial Input Basics   http://forum.arduino.cc/index.php?topic=396450.0

const byte numChars = 64;
char receivedChars[numChars];

boolean newData = false;

byte ledPin = 13;   // the onboard LE

//===============

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);

    digitalWrite(ledPin, HIGH);

    delay(5000);

    digitalWrite(ledPin, LOW);
    delay(200);
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);

    Serial.println("<Arduino is ready>");
}

//===============

void loop() {
    recvWithStartEndMarkers();
    replyToPython();
}

//===============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//===============

void replyToPython() {
    if (newData == true) {
        Serial.print("<");
        //Serial.print(receivedChars);
        String test_string(receivedChars);
        Serial.print(test_string);
        //Serial.print("   ");
        //Serial.print(millis());
        Serial.println('>');

        if(test_string == "Volume:60"){
          digitalWrite(ledPin, HIGH);
        }
        else{
          digitalWrite(ledPin, LOW);
        }
        
        //    // change the state of the LED everytime a reply is sent
        //digitalWrite(ledPin, ! digitalRead(ledPin));
        newData = false;
    }
}

//===============
