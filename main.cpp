#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


using namespace std;

const int NUM_BLOCKS = 3;
const int block = 100;
const int margin = 15;
const int width = (block * 3) + (4 * margin);
const int heigh = (block * 3) + (4 * margin);

char mas[3][3] = { 0 };

int query = 0;
bool game_over = false;
int color;
int num;
string cross_or_toe_or_draw;


sf::RectangleShape rectangle(sf::Vector2f(100, 100));
sf::RectangleShape rectangle1(sf::Vector2f(100, 100));

bool win_game(char mas[3][3], char sign, string &cross_or_toe_or_draw) {
    int zeroes = 0;
    int signs_in_row;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (mas[row][col] == 0) {
                zeroes++;
            }
        }
    }
    for (int row = 0; row < 3; row++) {
        if ((mas[row][0] == sign) && (mas[row][1] == sign) && (mas[row][2] == sign)) {
            cross_or_toe_or_draw = sign;
            return true;
        }
    }
    for (int col = 0; col < 3; col++) {
        if ((mas[0][col] == sign) && (mas[1][col] == sign) && (mas[2][col] == sign)) {
            cross_or_toe_or_draw = sign;
            return true;
        }
    }
    for (int col = 0; col < 3; col++) {
        if ((mas[0][0] == sign) && (mas[1][1] == sign) && (mas[2][2] == sign)) {
            cross_or_toe_or_draw = sign;
            return true;
        }
    }
    for (int col = 0; col < 3; col++) {
        if ((mas[2][0] == sign) && (mas[1][1] == sign) && (mas[0][2] == sign)) {
            cross_or_toe_or_draw = sign;
            return true;
        }
    }
    if (zeroes == 0) {
        cross_or_toe_or_draw = "draw";
        return true;
    }

    cout << "nothing success";
    return false;
}



int main()
{
    int query = 0;
    sf::RenderWindow window(sf::VideoMode(width, heigh), "tic tac toe");

    while (window.isOpen())
    {
        sf::Mouse mouse;
        sf::Event event;
        sf::Font font;
        sf::Text text;
        sf::Texture krestik;
        sf::Texture nolik;
        sf::Texture nothing;

        krestik.loadFromFile("images/krestik_board.png");
        nolik.loadFromFile("images/nolik_baord.png");
        nothing.loadFromFile("images/White_board.png");

        font.loadFromFile("fonts/Minecraft_Rus_NEW.otf");

        text.setFont(font);
        text.setPosition(100, 150);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && not game_over) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//забираем коорд курсора
                sf::Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
                int col = pos.x / (block + margin);
                int row = pos.y / (block + margin);
                if (mas[row][col] == 0) {
                    if (query % 2 == 0) {
                        mas[row][col] = 'x';
                    }
                    else {
                        mas[row][col] = 'o';
                    }
                    query++;
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                game_over = false;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++) {
                        mas[i][j] = 0;
                    }
                }
                query = 0;
                
            }
            
        }

        if (not game_over) {
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    if (mas[row][col] == 'x') {
                        color = 1;
                    }
                    else if (mas[row][col] == 'o') {
                        color = 2;
                    }
                    else {
                        color = 0;
                    }
                    int x = col * block + (col + 1) * margin;
                    int y = row * block + (row + 1) * margin;
                    switch (color)
                    {
                    case(1):
                        rectangle.setTexture(&krestik);
                        break;
                    case(2):
                        rectangle.setTexture(&nolik);
                        break;
                    case(0):
                        rectangle.setTexture(&nothing);
                        break;
                    default:
                        break;
                    }
                    rectangle.setPosition(x, y);
                    window.draw(rectangle);
                }
            }
        }
        
        if ((query - 1) % 2 == 0) {
            game_over = win_game(mas, 'x', cross_or_toe_or_draw);
        }
        else {
            game_over = win_game(mas, 'o', cross_or_toe_or_draw);
        }
        if (game_over) {
            if (cross_or_toe_or_draw == "x") {
                text.setString("X are win");
            }
            else if (cross_or_toe_or_draw == "o") {
                text.setString("O are win");
            }
            else {
                text.setString("DRAW");
            }
            window.clear();
            
        }
        window.draw(text);
        window.display();
        
        
    }

    return 0;
}


