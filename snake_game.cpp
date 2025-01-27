#include <iostream>
#include <deque>
#include <windows.h>
#include <random>

using namespace std;

void checkDeviceType();
void displayLogo();
void displayMenu();
void startGame();
void initSnake();
void setNewApple();
void clearConsole();
void clearBoard();
void updateSnakeDirection();
void moveSnake();
void renderBoard();
void showInstructions();

enum deviceType
{
  WINDOWS,
  UNIX
};
enum directions
{
  LEFT,
  RIGHT,
  UP,
  DOWN,
};
int const HEIGHT = 20;
int const WIDTH = 30;
char board[HEIGHT][WIDTH];
deque<pair<int, int>> snake;
directions snake_dir = LEFT;
pair<int, int> apple;
deviceType device;
bool gameover = false;

random_device rd;  // Seed with a non-deterministic random number
mt19937 gen(rd()); // Mersenne Twister generator
uniform_int_distribution<> distH(1, HEIGHT - 1);
uniform_int_distribution<> distW(1, WIDTH - 1);

int main()
{
  int choice;
  bool exitGame = false;

  checkDeviceType();
  displayLogo();

  while (!exitGame)
  {
    displayMenu();
    cin >> choice;

    switch (choice)
    {
    case 1:
      startGame();
      break;
    case 2:
      showInstructions();
      break;
    case 3:
      cout << "Exiting the game. Goodbye!\n";
      exitGame = true;
      break;
    default:
      cout << "Invalid choice. Please try again.\n";
    }

    cout << endl;
  }

  return 0;
}

void checkDeviceType()
{
#ifdef _WIN32
  device = WINDOWS;
#elif __unix__ || __unix || (__APPLE__ && __MACH__)
  device = UNIX;
#endif
}

void displayLogo()
{
  clearConsole();
  cout << "  /$$$$$$                      /$$                        /$$$$$$                                   \n";
  cout << " /$$__  $$                    | $$                       /$$__  $$                                  \n";
  cout << "| $$  \\__/ /$$$$$$$   /$$$$$$ | $$   /$$  /$$$$$$       | $$  \\__/  /$$$$$$  /$$$$$$/$$$$   /$$$$$$ \n";
  cout << "|  $$$$$$ | $$__  $$ |____  $$| $$  /$$/ /$$__  $$      | $$ /$$$$ |____  $$| $$_  $$_  $$ /$$__  $$\n";
  cout << " \\____  $$| $$  \\ $$  /$$$$$$$| $$$$$$/ | $$$$$$$$      | $$|_  $$  /$$$$$$$| $$ \\ $$ \\ $$| $$$$$$$$\n";
  cout << " /$$  \\ $$| $$  | $$ /$$__  $$| $$_  $$ | $$_____/      | $$  \\ $$ /$$__  $$| $$ | $$ | $$| $$_____/\n";
  cout << "|  $$$$$$/| $$  | $$|  $$$$$$$| $$ \\  $$|  $$$$$$$      |  $$$$$$/|  $$$$$$$| $$ | $$ | $$|  $$$$$$$\n";
  cout << " \\______/ |__/  |__/ \\_______/|__/  \\__/ \\_______/       \\______/  \\_______/|__/ |__/ |__/ \\_______/\n";
}

void displayMenu()
{
  cout << "\n1. Start Game\n";
  cout << "2. Instructions\n";
  cout << "3. Exit\n";
  cout << "=================================\n";
  cout << "Enter your choice: ";
}

void showInstructions()
{
  cout << "\n=========== Instructions ==========\n";
  cout << "1. Use W/A/S/D or Arrow keys to move the snake.\n";
  cout << "2. Avoid hitting the walls or yourself.\n";
  cout << "3. Collect food to grow the snake.\n";
  cout << "4. Press X or ESC to quit during the game.\n";
  cout << "====================================\n";
  cout << "Press Enter to return to the menu...\n";
  cin.ignore(); // Wait for user to press Enter
  cin.get();
}

void startGame()
{
  gameover = false;
  initSnake();
  setNewApple();

  cout << "\nStarting the game...\n";
  Sleep(1000); // Simulate loading
  clearConsole();
  clearBoard();
  while (!gameover)
  {
    updateSnakeDirection();
    moveSnake();
    clearConsole();
    renderBoard();
    Sleep(200);
  }
}

void initSnake()
{
  snake.clear();
  snake.push_front({10, 20});
}

void setNewApple()
{
  int random_x = distH(gen);
  int random_y = distW(gen);
  while (board[random_x][random_y] == '@' ||
         board[random_x][random_y] == '|' ||
         board[random_x][random_y] == '-')
  {
    random_x = distH(gen);
    random_y = distW(gen);
  }
  apple = {random_x, random_y};
}

void clearConsole()
{
  if (device == WINDOWS)
  {
    system("cls");
  }
  else
  {
    system("clear");
  }
}

void clearBoard()
{
  for (size_t i = 0; i < HEIGHT; i++)
  {
    for (size_t j = 0; j < WIDTH; j++)
    {
      board[i][j] = ' ';
    }
  }
}

void updateSnakeDirection()
{
  if ((GetAsyncKeyState(VK_LEFT) & 0x01 ||
       GetAsyncKeyState(0x41) & 0x01) &&
      snake_dir != RIGHT)
  {
    snake_dir = LEFT;
  }
  else if ((GetAsyncKeyState(VK_RIGHT) & 0x01 ||
            GetAsyncKeyState(0x44) & 0x01) &&
           snake_dir != LEFT)
  {
    snake_dir = RIGHT;
  }
  else if ((GetAsyncKeyState(VK_UP) & 0x01 ||
            GetAsyncKeyState(0x57) & 0x01) &&
           snake_dir != DOWN)
  {
    snake_dir = UP;
  }
  else if ((GetAsyncKeyState(VK_DOWN) & 0x01 ||
            GetAsyncKeyState(0x53) & 0x01) &&
           snake_dir != UP)
  {
    snake_dir = DOWN;
  }
  else if (GetAsyncKeyState(0x58) & 0x01 ||
           GetAsyncKeyState(VK_ESCAPE) & 0x01)
  {
    gameover = true;
  }
}

void moveSnake()
{
  pair<int, int> s_head = snake.front();
  bool eat = false;

  switch (snake_dir)
  {
  case LEFT:
    if (board[s_head.first][s_head.second - 1] == '&')
      eat = true;
    else if (board[s_head.first][s_head.second - 1] == '|' ||
             board[s_head.first][s_head.second - 1] == '@')
      gameover = true;
    snake.push_front({s_head.first, s_head.second - 1});
    break;
  case RIGHT:
    if (board[s_head.first][s_head.second + 1] == '&')
      eat = true;
    else if (board[s_head.first][s_head.second + 1] == '|' ||
             board[s_head.first][s_head.second + 1] == '@')
      gameover = true;
    snake.push_front({s_head.first, s_head.second + 1});
    break;
  case UP:
    if (board[s_head.first - 1][s_head.second] == '&')
      eat = true;
    else if (board[s_head.first - 1][s_head.second] == '-' ||
             board[s_head.first - 1][s_head.second] == '@')
      gameover = true;
    snake.push_front({s_head.first - 1, s_head.second});
    break;
  case DOWN:
    if (board[s_head.first + 1][s_head.second] == '&')
      eat = true;
    else if (board[s_head.first + 1][s_head.second] == '-' ||
             board[s_head.first + 1][s_head.second] == '@')
      gameover = true;
    snake.push_front({s_head.first + 1, s_head.second});
    break;
  }

  if (!eat)
    snake.pop_back();
  else
    setNewApple();
}

void renderBoard()
{
  clearBoard();
  for (auto &&i : snake)
  {
    board[i.first][i.second] = '@';
  }

  board[apple.first][apple.second] = '&';

  for (size_t i = 0; i < WIDTH; i++)
  {
    board[0][i] = '-';
    board[HEIGHT - 1][i] = '-';
  }
  for (size_t i = 0; i < HEIGHT; i++)
  {
    board[i][0] = '|';
    board[i][WIDTH - 1] = '|';
  }

  for (size_t i = 0; i < HEIGHT; i++)
  {
    for (size_t j = 0; j < WIDTH; j++)
    {
      cout << board[i][j];
    }
    cout << '\n';
  }
}
