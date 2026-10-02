# Night Camp

201/2023 - Ivana Erić

Night Camp je 3D scena noćnog kampa koja sadrži šator, logorsku vatru sa loncem i drveće.

Scena koristi Blinn-Phong model osvetljenja i tri tipa svetlosti:
directional light, point light koji predstavlja svetlost logorske vatre
i spotlight vezan za kameru.

Jačina i boja svetlosti vatre mogu da se podešavaju preko ImGui interfejsa,
a intenzitet svetlosti vatre može da se menja i preko tastature.

Implementiran je i vremenski događaj pokrenut pritiskom na taster T:
nakon 2 sekunde svetlost vatre postaje crvenija, a nakon još 2 sekunde
intenzitet svetlosti vatre se smanjuje.

Scena koristi blending za transparentne delove teksture lišća,
face culling, cubemap/skybox i framebuffer sa grayscale
post-processing efektom.

## Controls

W -> Kretanje kamere napred  
S -> Kretanje kamere nazad  
A -> Kretanje kamere levo  
D -> Kretanje kamere desno  
Mouse / touchpad -> Rotacija kamere  
Mouse scroll -> Zoom  
UP -> Povećavanje intenziteta svetlosti vatre  
DOWN -> Smanjivanje intenziteta svetlosti vatre  
T -> Pokretanje vremenskog događaja  
ImGui Fire intensity -> Podešavanje intenziteta svetlosti vatre  
ImGui Fire color -> Podešavanje boje svetlosti vatre  
ImGui Grayscale -> Podešavanje grayscale post-processing efekta

## Features

### Fundamental:

[x] Model with lighting  
[x] Two types of lighting with customizable colors and movement through GUI or ACTIONS  
[x] T --- AFTER 2 SECONDS ---Triggers---> Fire becomes redder ---> AFTER 2 SECONDS ---Triggers---> Fire light intensity decreases

### Group A:

[x] Frame-buffers with post-processing   
[ ] Instancing  
[ ] Off-screen Anti-Aliasing  
[ ] Parallax Mapping

### Group B:

[ ] Bloom with the use of HDR  
[ ] Deferred Shading  
[ ] Point Shadows  
[ ] SSAO

### Engine improvement:

[ ] ...

## Models:

- Campsite / campfire model - MATF project resources:  
  https://drive.google.com/drive/folders/1d29msL2hnkOwxCYKeXlxrn6QBOEw40vz

- Hand painted Tree model - MATF project resources:  
  https://drive.google.com/drive/folders/1d29msL2hnkOwxCYKeXlxrn6QBOEw40vz

## Textures

- Campsite / campfire textures - included with the campsite model
- Hand painted Tree textures - included with the tree model

## Other resources

Night skybox:  
https://opengameart.org/content/night-skyboxes

Author: Emil Persson (Humus)  
License: Creative Commons Attribution 3.0 Unported

Additional implemented techniques:
- Blending
- Face culling
- Cubemap / skybox rendering
- Blinn-Phong lighting
- Directional light
- Point light
- Spotlight
- ImGui lighting controls