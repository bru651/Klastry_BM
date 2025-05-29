#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
//#include <cstdlib>
//#include <cmath>
#include <ctime>
#include <iostream>



bool checkNeigbours(std::vector<std::vector<int>> const &oilNew,int x, int y) {
    int size = oilNew.size();
    //std::vector<sf::Vector2i> neighs;
    std::vector<sf::Vector2i> borders{ sf::Vector2i (0, 1),sf::Vector2i(0, -1),sf::Vector2i(-1, 0),sf::Vector2i(1, 0) };
    int rnx, rny;
    for (int n = 0; n < 4; n++) {
        rnx = x + borders[n].x; rny = y + borders[n].y;
        if (rnx  < 0 || rny < 0 || rnx > size - 1 || rny > size - 1) continue;
        else {
            if (oilNew[rnx][rny]!=1)continue;
            else return 1;
        }
    }
    return 0;
}

void StainUpdate(std::vector<std::vector<int>>& oilNew) {
    int size = oilNew.size();   // Za³o¿enie ¿e tablica ma kszta³t kwadratu
    std::vector<sf::Vector2i> neighbours{ sf::Vector2i(0, 1),sf::Vector2i(0, -1),sf::Vector2i(-1, 0),sf::Vector2i(1, 0)};
    sf::Vector2i move;
    int rnx, rny;

    //std::cout << "CHECK 8" << std::endl;
    // Zamieñ 2(Nowe) na 1(Istniej¹ce)
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (oilNew[x][y] > 1)oilNew[x][y] = 1;
        }
    }
    //std::cout << "CHECK 9" << std::endl;
}


int main()
{
    std::srand(std::time({}));
    // Ustawienia
    int displaySize = 800;
    bool pause = true;
    int iterations = 100000;     // Iloœæ iteracji
    int curIteration = 1;     // Obecna iteracja
    //int probability = 500;  // Od 0 do 1000
    bool display = true; // Czy ma rysowaæ gry
    int size = 200;     // Wymiar tablicy
    int space = size * size;
    float blocksize = static_cast<float>(displaySize) / size;  // Graficzna wielkoœæ pola

    // Zbiorniki
    //std::vector<std::vector<bool>> oil(size, std::vector<bool>(size, false));
    std::vector<std::vector<int>> oilNew(size, std::vector<int>(size, 0));
    oilNew[size / 2][size / 2] = 1;

    // Grafika
    sf::RenderWindow window(sf::VideoMode(displaySize, displaySize), "KLastr DLA");
    //window.setFramerateLimit(30);
    sf::RectangleShape shape(sf::Vector2f(blocksize, blocksize));
    shape.setFillColor(sf::Color::Green);

    //density.push_back(generateRandom(oil, size, probability));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyReleased) {    // Keyboard input
                if (event.key.code == sf::Keyboard::Space) {    // Pause button (Space)
                    pause = !pause;
                }
                if (event.key.code == sf::Keyboard::Escape) {    // Close program
                    window.close();
                }
                if (event.key.code == sf::Keyboard::R) {    // Iloœæ iteracji
                    display = !display;
                }
                if (event.key.code == sf::Keyboard::I) {    // Iloœæ kroków
                    std::cout << "Kroki: "<< curIteration << " / " << iterations << std::endl;
                }
            }
        }
        if (!pause) {
            curIteration += 1;
            StainUpdate(oilNew);
            //pause = true;
        }
        if (iterations == curIteration) {
                pause = true;
                std::cout << "DONE" << std::endl;
                iterations = -1;
                //window.close();//*/
        }

        if (display) {
            window.clear();
            shape.setFillColor(sf::Color::Red);
            // Rysuje Klastr
            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {
                    if (oilNew[x][y] > 0) {
                        
                        //std::cout << "X: "<< x<<" Y: "<<y << std::endl;
                        shape.setPosition(sf::Vector2f(blocksize * x, blocksize * y));
                        window.draw(shape);
                        
                    }
                    //else std::cout << "Nay" << std::endl;
                }
            }

            window.display();
        }//*/
    }

    return 0;
}