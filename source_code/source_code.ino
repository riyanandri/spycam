//////////////////////////
//........SPYCAM........//
//////////////////////////

// Tower Pro MG996R
#include <Servo.h>
Servo camServo;
int currentPIRpos = 0;

// LED status
int pinLED[] = {9,10,11,12,13};
int currentLEDpin = 9;

// HC-SR501
int pinPIR[] = {2,3,4,5,6};
int currentPIRpin = 2;
int PIRcond[] = {1,1,1,1,1};
int PIRpos[] = {157,117.75,78.5,39.25,0};
boolean PIRstatus;

//////// SETUP //////////
void setup() {
    Serial.begin(9600);
    camServo.attach(7);

    for(int pir=0; pir<5; pir++) {
        pinMode(pinPIR[pir], INPUT);
    }

    for(int led=0; led<5; led++) {
        pinMode(pinLED[led], OUTPUT);
    }

    ////// KALIBRASI SENSOR /////////
    Serial.print("Tunggu sebantar slur, Sensor sedang dikalibrasi..");
    for(int calibrate=0; calibrate<15; calibrate++) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("Sensor sudah siap");

    camServo.write(78.5);
}

void loop() {
    for(int pir=0; pir<5; pir++) {
        currentPIRpin = pinPIR[pir];
        currentLEDpin = pinLED[pir];
        PIRstatus = digitalRead(currentPIRpin);

        if(PIRstatus == HIGH) {
            digitalWrite(currentLEDpin, HIGH);
            if(PIRcond[pir] == 0) {
                if(currentPIRpos != currentPIRpin && PIRcond[pir] == 0) {
                    camServo.write(PIRpos[pir]);
                    Serial.print("Posisi kamera : ");
                    Serial.println(PIRpos[pir]);
                    delay(50);
                    currentPIRpos = currentPIRpin;
                    PIRcond[pir] = 1;
                }
                PIRcond[pir] = 1;
            }
        }else {
            digitalWrite(currentLEDpin, LOW);
            PIRcond[pir] = 0;
        }
    }
}