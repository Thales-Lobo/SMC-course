const int BAUD_RATE = 9600;

// Define Arduino pin for LED
const int LED_PIN = 13;

// Constants for delay times
const int VOWEL_DELAY = 3000;  // 3 seconds delay time
const int CONSONANT_DELAY = 0; // Null time delay for consonants

// Structure that define the vowels
struct Vowels {
  char vowels[5] = {
    'a',
    'e',
    'i',
    'o',
    'u'
  };
};

// Function prototypes
void setupSerial();
void checkVowelAndControlLED();

// Global variables
Vowels vowelsList;

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(BAUD_RATE);

  // Initialize LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // Setup serial communication
  setupSerial();
}

void loop() {
  // Check for received character and control LED accordingly
  checkVowelAndControlLED();
}

// Setup serial communication
void setupSerial() {
  Serial.println("Arduino is ready for serial communication!");
}

// Check received character and control LED
void checkVowelAndControlLED() {
  // Check if data is available to read
  if (Serial.available() > 0) {
    // Read the incoming byte
    char receivedChar = Serial.read();
    Serial.println(receivedChar);

    // Check if the received character is a vowel
    bool isVowel = false;
    for (int vowelIndex = 0; vowelIndex < sizeof(vowelsList.vowels); vowelIndex++) {
      if (receivedChar == vowelsList.vowels[vowelIndex] || receivedChar == toupper(vowelsList.vowels[vowelIndex])) {
        isVowel = true;
        break;
      }
    }

    // Control LED based on the received character
    if (isVowel) {
      digitalWrite(LED_PIN, HIGH);
      delay(VOWEL_DELAY);
    } else {
      digitalWrite(LED_PIN, LOW);
      delay(CONSONANT_DELAY);
    }
    
    digitalWrite(LED_PIN, LOW);
  }
}
