# sdl-othello
Projet scolaire de premier semestre de DUT

**Attention** : c'est moyennement bien codé et l'architecture du code est largement améliorable.

Cependant le jeu est très complet, 100 % fonctionnel et sans bug. Il comporte notamment :
 - une interface graphique rétro
 - un système de replay avec enregistrement dans le système de fichiers
 - une IA (très) basique
 - un mode 2 joueurs

## Pour jouer
Le projet ne peut se compiler pour l'instant que sous environnement Unix (Linux voir Mac, même si je n'ai pas testé ce dernier).

**Pré-requis** : paquets de développement SDL et SDL_ttf, commande make, gcc

Sous Debian 8 par exemple : `apt-get install libsdl1.2-dev libsdl-ttf2.0-dev make gcc`

Ensuite, une fois le dépôt cloné :
```
cd sdl-othello
make
./bin/Release/Othello
```
