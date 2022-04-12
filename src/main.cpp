
#include<Arduino.h>
//#include "WIFIConnector_MKR1000.h"
//#include "MQTTConnector.h"
#include <Wire.h>                       //Pour la communication I2C
#include <Keypad.h> //https://github.com/Chris--A/Keypad

//Constants
#define ROWS 4
#define COLS 4
const int DIG_A =   6;            
const int DIG_B =   7;           
const int DIG_C =   8;            
const int DIG_D =   9;            
const int DIG_E =   10;            //Broche relier au clavier matriciel
const int DIG_F =   11;            
const int DIG_G =   12;            
const int DIG_H =   13;            
const int ANALOG_PIN     = A1;    // Broche pour le potentionmetre

//Declaration des variables
int TentionBrocheAnalogique = 0;         // Pour contenir la tension sur la broche Analogique
int ValeurChoisie = 0;


//Creation d'un objet de 4 lignes et 4 colonnes = 16 touches
const char kp4x4Keys[ROWS][COLS]  = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};

byte rowKp4x4Pin [4] = {6, 7, 8, 9};       // Broches representants les 4 lignes de la matrices
byte colKp4x4Pin [4] = {10, 11, 12, 13};       // Broches representants les 4 colonnes de la matrices

//Initialisation d'une classe au format matrice 4x4
Keypad kp4x4  = Keypad(makeKeymap(kp4x4Keys), rowKp4x4Pin, colKp4x4Pin, ROWS, COLS);

void setup() {
//Serial.begin(9600);
//wifiConnect();                  //Branchement au réseau WIFI
//MQTTConnect();                  //Branchement au broker MQTT

  // Démarrer le bus I2C en tant que controleur
  Wire.begin();

  pinMode(ANALOG_PIN, INPUT);  //Broche analogue en mode lecture pour lire la tention au niveau du potentionmetre (0-1023)
  pinMode(DIG_A, OUTPUT);
  pinMode(DIG_B, OUTPUT);
  pinMode(DIG_C, OUTPUT);
  pinMode(DIG_D, OUTPUT);
  pinMode(DIG_E, OUTPUT);
  pinMode(DIG_F, OUTPUT);
  pinMode(DIG_G, OUTPUT);
  pinMode(DIG_H, OUTPUT);
  
}

// Boucle infinie qui permet au uC de faire une ou plusieurs taches sans arrêt
void loop()
 {
    char customKey = kp4x4.getKey();
    if (customKey)
    {
        switch (customKey)
        {
          case 'A':
              ValeurChoisie = 1;
            break;
          case 'B':
              ValeurChoisie = 2;
            break;
          case 'C':
              ValeurChoisie = 3;
            break;
          case 'D':
              ValeurChoisie = 4;
            break;
          default:
              Serial.println("Broche");
            break;
        }
    }

     Wire.beginTransmission(9); // transmettre à l'appareil #9
      Wire.write(ValeurChoisie); // envoie x
      Wire.endTransmission(); // arrête de transmettre

 }