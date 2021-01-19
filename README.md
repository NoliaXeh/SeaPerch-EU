# SeaPerch-EU

## AFMotor_ConstantSpeed.ino

La bilbiothèque pour contrôler les moteurs se trouvent dans `AFMotor.h`.

### Init

On initialise un moteurs par:
```
AF_DCMotor motor1(1, MOTOR12_64KHZ);
```

Le premier paramètre est le numéro du moteur de 1 à 4. Le second est la fréquence du moteur, ça  marche bien avec 64Hz. Pour les moteurs 1 et 2 on utilise la macro `MOTOR12_64HZ` tandis que pour les moteurs 3 et 4 c'est la macro `MOTOR34_64HZ`.

### Setup

Je set la vitesse du moteur avec `motor1.setSpeed(speed);`, `speed` en ms.

### Loop

Je lance le moteur avec `Motor.run(FORWARD);`, il y a 3 commandes :
- `FORWARD` : avancer
- `BACKWARD` : reculer
- `RELEASE` : arret (equivalent à `setSpeed(0)`

### Fonctionnement asynchrone

J'ai ajouté la biblio `Scheduler.h` faite par Arduino pour gérer les moteurs en parallèle, dans `setup()` on lance avec la fonction de setup, la fonction de loop et le nombre d'iterations.

Le code actuel n'est pas testé.
