# Snake Game

Welcome to the Snake Game repository! This is a classic Snake game implemented in C++. The game is designed to be simple and fun, with a text-based interface.

## Table of Contents
- [Features](#features)
- [How to Play](#how-to-play)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features
- **Text-based Interface**: The game uses a simple text-based interface to display the game board.
- **Random Apple Placement**: The apple (food) is placed randomly on the board each time it is eaten.
- **Snake Growth**: The snake grows in length each time it eats an apple.
- **Game Over Conditions**: The game ends if the snake collides with the walls or itself.

## How to Play
- Use the **W/A/S/D** keys or the **Arrow keys** to control the direction of the snake.
- The goal is to eat the apples (`&`) that appear on the board.
- Each apple eaten increases the length of the snake.
- Avoid colliding with the walls (`-` and `|`) or the snake's own body (`@`).
- Press **X** or **ESC** to quit the game at any time.

## Installation
To run the Snake Game, you need to have a C++ compiler installed on your system.

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/snake-game.git
   cd snake-game
   ```

2. **Compile the code**:
   - On **Windows**:
     ```bash
     g++ -o snake_game main.cpp
     ```

3. **Run the game**:
   - On **Windows**:
     ```bash
     .\snake_game
     ```

## Usage
After starting the game, you will be presented with a menu:
1. **Start Game**: Begins a new game of Snake.
2. **Instructions**: Displays the game instructions.
3. **Exit**: Exits the game.

## Contributing
Contributions are welcome! If you have any suggestions, bug reports, or feature requests, please open an issue or submit a pull request.

1. **Fork the repository**.
2. **Create a new branch** for your feature or bug fix.
3. **Commit your changes**.
4. **Push your branch** to your fork.
5. **Submit a pull request**.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Enjoy the game and happy coding! 🎮🐍