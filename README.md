# Racket-Sensor
Projet ingénieur essai- Capteur pour raquette de squash et analyse des données. Améliorez votre jeu avec la data. 🎾📊

Ce repository contient un projet passionnant visant à développer un capteur fixé sur une raquette de squash. L'objectif principal est de monter en compétence dans les essais de produits sportifs en acquérant des connaissances pratiques en capteurs, électronique, microcontrôleurs et traitement de données.

<img src="https://centralclub.fr/wp-content/uploads/2022/09/image10.jpg" height="200px"></a>
<img src="https://github.com/agounand/Racket-Sensor/assets/125287388/dcc4cb73-f92a-4768-bf52-f9cb160e7de3" height="200px"></a>


## Idée et début : Capteur de Raquette de Squash et Compétences en Essais Sportifs
Ce projet vise à concevoir un capteur intégré à ma raquette de squash pour améliorer mes compétences en essais de produits sportifs. J'acquerrai ainsi des connaissances en capteurs, électronique, microcontrôleurs et traitement des données pour exploiter efficacement les informations recueillies.

- Collecter des données telles que la vitesse, l'angle d'impact et la force de frappe.
- Traiter et analyser les données pour améliorer les compétences en jeu de squash.
- Acquérir des connaissances pratiques en électronique et microcontrôleurs ainsi que d'analyse de données provenant de capteurs.
- Monter en compétence sur la qualitée des données obtenue et précision des dispositifs 

## Contenu du Repository
**/capteur** : Documentation technique sur le capteur, son schéma de montage et son fonctionnement / code.

**/analyse_donnees** : Scripts d'analyse des données.

**/ressources** : Fichiers et ressources utiles pour le projet.

**/images** : images du projet

**/impression_3d** : fichiers 3d, fichier stl pour l'impression 3d ...

## Phase 01 : [Developpement du capteur](capteur/Developpment_capteur.md)
<img src="images/schema_v4.jpg" height="200px"></a>
<img src="images/montage_1.JPEG" height="200px"></a>

<img src="images/ass_2.JPEG" height="200px"></a>
<img src="images/cablev1.JPEG" height="200px"></a>
<img src="images/sensorv1.JPEG" height="200px"></a>


## Phase 02 : [Conception de pièces 3d](impression_3d/notes.md)
<img src="images/explosion_3d_boitier_v1.png" height="200px"></a>
<img src="images/explosion_3d_sensor_v1.png" height="200px"></a>

<img src="images/explosion_3d_boitier_v1.gif" height="200px"></a>

## Phase 03 : [Premiers traitements des données](analyse_donnees/analyse_traitement_data.md)

- premiers fichier enregistrés

```
time [ms], AccX [g], AccY [g], AccZ [g], GyroX [deg/s], GyroY [deg/s], GyroZ [deg/s]
118838,1.06,-0.02,-0.05,0.12,-0.18,0.03
118841,1.22,-0.02,-0.08,-35.33,33.98,-101.46
118844,1.23,-0.02,-0.08,-36.66,43.53,-110.74
118847,1.23,-0.01,-0.09,-36.05,51.31,-119.38
118850,1.24,-0.00,-0.08,-34.96,58.30,-127.82
118854,1.24,-0.01,-0.07,-33.12,64.99,-138.83
118857,1.23,0.00,-0.04,-30.73,69.04,-151.81
118860,1.25,0.01,-0.06,-28.89,72.75,-161.91
118863,1.24,0.02,-0.08,-28.11,78.59,-171.36
118866,1.24,0.04,-0.08,-27.71,84.85,-176.62
118870,1.24,0.07,-0.05,-28.80,91.13,-178.57
```

## Phase d'essais 01 : en cours ...

## Phase 01.1

Autres inspirations : 

https://github.com/hongyang-zhao/TennisEye/tree/master

https://github.com/alvarowolfx/tinyml-smart-tennis-sensor


IDEES :
- passer par le bluetooth pour save les data
- mignaturisation du controleur :
  - arduino nana esp32
  - seeed studio 
- mignaturisation de la batterie
- conception et commande d'une PCB
- integrer le tout au niveau de la mesure

- ajouter la mesure du magnetometre pour affiner et augmenter la précision du capteur -> MPU9250
- avec ces 9 composantes il est possible de remonter a la position relative en intégrant 2x
  