#include <Wire.h>
#include <MPU6050_tockn.h>
#include <SD.h>
#include <SPI.h>

MPU6050 mpu6050(Wire);
const int buttonPin = D0;  // Numéro de la broche du bouton poussoir
const int ledPin = LED_BUILTIN; // Numéro de la broche de la LED intégrée
const int chipSelect = D8; // Broche de sélection du module microSD

int buttonState = 0;  // Variable pour lire l'état du bouton
bool measurementsActive = false; // Variable pour indiquer si les mesures sont actives

int n = 0; // Variable pour itérer sur le nom du fichier enregistré
File dataFile; // Fichier de données

unsigned long initialTime; // Temps initial pour la première valeur

void setup() {
  Serial.begin(115200);
  Wire.begin(D4, D3); // Utilisation des broches D4 (GPIO2) pour SDA et D3 (GPIO0) pour SCL
  pinMode(ledPin, OUTPUT); // Initialise la broche de la LED comme une sortie
  pinMode(buttonPin, INPUT_PULLUP); // Initialise la broche du bouton avec une résistance de tirage vers le haut
  pinMode(chipSelect, OUTPUT); // Initialise la broche de sélection du module microSD

  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  Serial.println("MPU6050 Initialisé !");
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Erreur lors de l'initialisation de la carte SD !");
    while (1);
  }

  // Recherche du fichier avec la valeur la plus élevée de n
  n = findMaxN();
  Serial.println("Valeur actuelle de n : " + String(n));
}

void loop() {
  // Lecture de l'état du bouton
  buttonState = digitalRead(buttonPin);

  // Si le bouton est appuyé et les mesures ne sont pas actives, démarrer les mesures
  if (buttonState == HIGH && !measurementsActive) {
    measurementsActive = true;
    digitalWrite(ledPin, LOW); // Allume la LED
    delay(200); // Petite pause pour éviter les rebonds du bouton

    // Génère un nom de fichier unique
    String fileName = "data_" + String(n) + ".txt";
    
    // Ouvre le fichier en mode écriture
    dataFile = SD.open(fileName, FILE_WRITE);
    
    if (!dataFile) {
      Serial.println("Erreur lors de l'ouverture du fichier !");
      Serial.println("Fichier numéro " + String(n));
    } else {
      // Écrit l'en-tête dans le fichier
      dataFile.println("time [ms], AccX [g], AccY [g], AccZ [g], GyroX [deg/s], GyroY [deg/s], GyroZ [deg/s]");
      // Obtient le temps initial pour la première valeur
      unsigned long initialTime = millis();
      // Calcule et écrit la première valeur correspondant au temps
      dataFile.print(initialTime); // La première valeur est toujours 0 (correspondant au temps initial)
      dataFile.print(",");
      dataFile.print(mpu6050.getAccX());
      dataFile.print(",");
      dataFile.print(mpu6050.getAccY());
      dataFile.print(",");
      dataFile.print(mpu6050.getAccZ());
      dataFile.print(",");
      dataFile.print(mpu6050.getGyroX());
      dataFile.print(",");
      dataFile.print(mpu6050.getGyroY());
      dataFile.print(",");
      dataFile.println(mpu6050.getGyroZ());
      //delay(10);
    }
  }
  // Si le bouton est appuyé et les mesures sont actives, arrêter les mesures
  else if (buttonState == HIGH && measurementsActive) {
    measurementsActive = false;
    digitalWrite(ledPin, HIGH); // Éteint la LED
    delay(200); // Petite pause pour éviter les rebonds du bouton
    
    if (dataFile) {
      dataFile.close(); // Ferme le fichier
      n = n + 1;
    }
  }

  // Si les mesures sont actives, lire et afficher les données du capteur
  if (measurementsActive) {
    mpu6050.update();
    // Affichage des valeurs dans le moniteur série
    Serial.print(mpu6050.getAccX());
    Serial.print(",");
    Serial.print(mpu6050.getAccY());
    Serial.print(",");
    Serial.print(mpu6050.getAccZ());
    Serial.print(",");
    Serial.print(mpu6050.getGyroX());
    Serial.print(",");
    Serial.print(mpu6050.getGyroY());
    Serial.print(",");
    Serial.println(mpu6050.getGyroZ());

    if (dataFile) {
      // Calcule le temps écoulé depuis le début de l'enregistrement
      unsigned long currentTime = millis();
      unsigned long elapsedTime = currentTime - initialTime;
      
      // Écrit les valeurs dans le fichier texte
      dataFile.print(elapsedTime);
      dataFile.print(",");
      dataFile.print(mpu6050.getAccX());
      dataFile.print(",");
      dataFile.print(mpu6050.getAccY());
      dataFile.print(",");
      dataFile.print(mpu6050.getAccZ());
      dataFile.print(",");
      dataFile.print(mpu6050.getGyroX());
      dataFile.print(",");
      dataFile.print(mpu6050.getGyroY());
      dataFile.print(",");
      dataFile.println(mpu6050.getGyroZ());
      //delay(10);
    }
  }
}

// Fonction pour rechercher la valeur maximale de n parmi les fichiers existants
int findMaxN() {
  int maxN = 0;
  File root = SD.open("/");
  if (!root) {
    return maxN;
  }
  
  while (true) {
    File entry = root.openNextFile();
    if (!entry) {
      break;
    }
    
    if (!entry.isDirectory()) {
      String fileName = entry.name();
      if (fileName.startsWith("data_") && fileName.endsWith(".txt")) {
        int numStart = fileName.indexOf('_') + 1;
        int numEnd = fileName.indexOf('.');
        if (numStart > 0 && numEnd > numStart) {
          String numStr = fileName.substring(numStart, numEnd);
          int num = numStr.toInt();
          if (num > maxN) {
            maxN = num;
          }
        }
      }
    }
    
    entry.close();
  }
  
  root.close();
  return maxN + 1;
}
