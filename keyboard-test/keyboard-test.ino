#include <Bounce.h>

Bounce button0 = Bounce(0, 10);
Bounce button1 = Bounce(1, 10);  // 10 ms debounce time is appropriate
Bounce button2 = Bounce(2, 10);  // for most mechanical pushbuttons
Bounce button3 = Bounce(3, 10);
Bounce button4 = Bounce(4, 10);  // if a button is too "sensitive"

const byte numChars = 64;
char receivedChars[numChars];

boolean newData = false;

byte ledPin = 13;   // the onboard LE

String data_string = "";

void setup() {
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
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

void volumeChange(int vol) {
  if (vol > 50) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
}

void loop() {

  recvWithStartEndMarkers();

  if (newData == true) {
    String input_string(receivedChars);
    data_string = input_string;
    data_string.remove(0,1);
    Serial.println(input_string);
    if(input_string.startsWith("V")){
      int volume = data_string.toInt();
      if (volume > 30) {
        digitalWrite(ledPin, HIGH);
      }
      else {
        digitalWrite(ledPin, LOW);
      }
    }

    newData = false;
  }

  // Update all the buttons.
  button0.update();
  button1.update();
  button2.update();
  button3.update();
  button4.update();

  // Check each button for "falling" edge.
  // falling = high (not pressed - voltage from pullup resistor)
  //           to low (pressed - button connects pin to ground)
  if (button0.fallingEdge()) {
    Serial.println("button0");
    Keyboard.press(KEY_MEDIA_PREV_TRACK);
    Keyboard.release(KEY_MEDIA_PREV_TRACK);
  }
  if (button1.fallingEdge()) {
    Serial.println("button1");
    Keyboard.press(KEY_MEDIA_PLAY_PAUSE);
    Keyboard.release(KEY_MEDIA_PLAY_PAUSE);
  }
  if (button2.fallingEdge()) {
    Serial.println("button2");
    Keyboard.press(KEY_MEDIA_NEXT_TRACK);
    Keyboard.release(KEY_MEDIA_NEXT_TRACK);
  }
  if (button3.fallingEdge()) {
    Serial.println("button3");
    Keyboard.press(KEY_MEDIA_VOLUME_DEC);
    Keyboard.release(KEY_MEDIA_VOLUME_DEC);
  }
  if (button4.fallingEdge()) {
    Serial.println("button4");
    Keyboard.press(KEY_MEDIA_VOLUME_INC);
    Keyboard.release(KEY_MEDIA_VOLUME_INC);
  }
}

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
