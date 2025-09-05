# Pit Viper Remastered

## Description
**Pit Viper Remastered** is a 2D top-down space shooter built with the Viper engine. Players control a spaceship, navigate through enemies, collect power-ups, and progress through increasingly difficult levels.

---

## Core Features

- **Player Health System**: Player has HP and lives. Taking damage reduces HP; losing all HP reduces lives.
- **Enemy Scaling**: Enemies gain more HP and shoot faster with each level.
- **Levels**: 5 levels; advance by destroying 15 enemies per level.
- **Power-Ups**:
  - Life
  - Energy
  - Speed Boost
  - Double Shoot
  - Explosion (destroys nearby enemies)
- **Player Abilities**:
  - Temporary double shooting
  - Speed boosts
  - Area explosion
- **Enemy AI**:
  - Rotate towards the player
  - Shoot when the player is within sight
- **User Interface**:
  - Displays score, lives, HP, energy, and current level

---

## Extra Features

- Particle-based explosion effects for enemies
- Dynamic difficulty scaling
- Simple HUD with level and power-up indicators

---

## Building and Running

### Requirements
- C++17 compatible compiler
- SDL2
- Viper Engine dependencies (Renderer, Audio, Input, etc.)

### Steps
1. Clone the repository:
   ```bash
   git clone 
