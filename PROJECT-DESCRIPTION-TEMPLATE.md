# Night Camp

201/2023 - Ivana Erić

Night Camp je 3D scena noćnog kampa koja sadrži šator, logorsku vatru sa loncem i drveće.
Scena koristi više tipova osvetljenja: directional light, point light koji predstavlja svetlost
logorske vatre i spotlight vezan za kameru.

Jačina i boja svetlosti vatre mogu da se podešavaju preko ImGui interfejsa, a jačina vatre
može da se menja i preko tastature. Implementiran je i vremenski događaj kojim se svetlost
vatre nakon određenog vremena menja i zatim slabi.

Scena koristi blending za transparentne delove teksture lišća, face culling, cubemap/skybox
i framebuffer sa grayscale post-processing efektom.

## Controls

W -> Kretanje kamere napred  
S -> Kretanje kamere nazad  
A -> Kretanje kamere levo  
D -> Kretanje kamere desno

Mouse / touchpad -> Rotacija kamere  
Mouse scroll -> Zoom

UP -> Povećavanje intenziteta svetlosti vatre  
DOWN -> Smanjivanje intenziteta svetlosti vatre

T -> Pokretanje vremenskog događaja:
nakon 2 sekunde svetlost vatre postaje crvenija,
a nakon još 2 sekunde intenzitet svetlosti se smanjuje.

ImGui Fire intensity -> Podešavanje intenziteta point light-a vatre  
ImGui Fire color -> Podešavanje boje point light-a vatre  
ImGui Grayscale -> Podešavanje grayscale post-processing efekta

## Features

### Fundamental:

[x] Model with lighting

[x] Two types of lighting with customizable colors and movement through GUI or ACTIONS

[x] T --- AFTER 2 SECONDS ---Triggers---> Fire becomes redder
---> AFTER 2 SECONDS ---Triggers---> Fire light intensity decreases

### Group A:

[x] Frame-buffers with post-processing

[ ] Off-screen Anti-Aliasing

[ ] Parallax Mapping

[ ] Bloom with the use of HDR

### Group B:

[ ] Deferred Shading

[ ] Point Shadows

[ ] SSAO

### Engine improvement:

[ ] -

## Models:

- Campsite / campfire model - model from the MATF project resources
- Tree model - model from the MATF project resources

## Textures

- Textures supplied with the campsite model
- Textures supplied with the tree model

## Other resources

Night skybox:
Author: Emil Persson (Humus)
License: Creative Commons Attribution 3.0 Unported

The project also uses blending, face culling and cubemap/skybox rendering.