# Overview
This project is an OpenGL-based particle system designed to simulate real-time particle effects like fire, smoke, water, or explosions. The particle effects can be customized in XML files to change properties such as color, blend mode, texture, duration, size, velocity, acceleration, lifetime, start position, spawn rate, pool size and scale. The particles are recycled from a fixed size pool that is handled with a linked list. This improves rendering efficiency by limiting the number of particle objects created. Each particle emitter renders all particles in one draw call in order to improve efficiency.

# Terminology
* **Effect:** A container to hold one or more emitters, encapsulating an entire particle effect such as fire, water, etc.
* **Emitter:** A container for a desired type of particle in an effect. For example a fire effect would be made of a fire and smoke emitter. Emitters manage the particles they contain and maintain a list of associated affectors.
* **Affector:** An element that modifies particles over their lifespan, influencing properties such as size, color, position, velocity, etc.

https://github.com/RyanCampbelljc/OpenGL-Particle-System/assets/97364160/f876dad6-c4be-4a49-a6ea-a4e579575f83

