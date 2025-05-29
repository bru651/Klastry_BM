#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
//#include <cstdlib>
//#include <cmath>
#include <ctime>
#include <iostream>



bool checkNeigbours(std::vector<std::vector<int>> const &oilNew,int x, int y, int threshold) {
    int size = oilNew.size();
    int neighs = 0;
    bool even = 0;
    if (y % 2 == 0)even = 1;
    std::vector<sf::Vector2i> borders;
    if (even)borders = { sf::Vector2i(0, 1), sf::Vector2i(0, -1), sf::Vector2i(-1, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(1, -1) };
    else borders = { sf::Vector2i(0, 1), sf::Vector2i(0, -1), sf::Vector2i(-1, 0), sf::Vector2i(1, 0), sf::Vector2i(-1, 1), sf::Vector2i(-1, -1) };
    int rnx, rny;
    for (int n = 0; n < 6; n++) {
        rnx = x + borders[n].x; rny = y + borders[n].y;
        if (rnx  < 0 || rny < 0 || rnx > size - 1 || rny > size - 1) continue;
        else {
            if (oilNew[rnx][rny] != 1)continue;
            else neighs += 1;
        }
    }
    if (neighs == threshold)return 1;
    else return 0;
}

void StainUpdate(std::vector<std::vector<int>>& oilNew, int threshold) {
    int size = oilNew.size();   // Za³o¿enie ¿e tablica ma kszta³t kwadratu
    if (threshold == 0)threshold = 1 + rand() % 3;
    std::vector<sf::Vector2i> neighbours{ sf::Vector2i(0, 1),sf::Vector2i(0, -1),sf::Vector2i(-1, 0),sf::Vector2i(1, 0)};
    // Zamieñ 2(Nowe) na 1(Istniej¹ce)
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (oilNew[x][y] > 1)oilNew[x][y] = 1;
        }
    }
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (oilNew[x][y] != 1) {
                if (checkNeigbours(oilNew, x, y, threshold)) oilNew[x][y] = 2;
            }
        }
    }
    //std::cout << "CHECK 8" << std::endl;

    //std::cout << "CHECK 9" << std::endl;
}


int main()
{
    std::srand(std::time({}));
    // Ustawienia
    int displaySize = 800;
    bool pause = true;
    int iterations = 90;     // Iloœæ iteracji
    int curIteration = 1;     // Obecna iteracja
    //int probability = 500;  // Od 0 do 1000
    bool display = true; // Czy ma rysowaæ gry
    int size = 200;     // Wymiar tablicy
    int space = size * size;
    float blocksize = static_cast<float>(displaySize) / size;  // Graficzna wielkoœæ pola
    float shift = blocksize * 0.25f;    // Przesuniêcie bloków dla hexagonalnoœci
    bool even = true;  // Pilnuje hexagonalnoœæ rusowania tablicy
    bool slowmode = false;   // Czy spacja to pauza czy jeden krok
    int threshold = 0; // Ilu musi byæ s¹siadów do rozrostu p³atka

    // Zbiorniki
    //std::vector<std::vector<bool>> oil(size, std::vector<bool>(size, false));
    std::vector<std::vector<int>> oilNew(size, std::vector<int>(size, 0));
    sf::Vector2i center = sf::Vector2i(size / 2, size / 2);
    //oilNew[center.x ][center.y] = 1;
    oilNew[center.x+1][center.y] = 1;
    oilNew[center.x][center.y+1] = 1;
    oilNew[center.x+1][center.y+1] = 1;
    oilNew[center.x-1][center.y] = 1;
    oilNew[center.x][center.y-1] = 1;
    oilNew[center.x+1][center.y-1] = 1;

    oilNew[center.x+2][center.y] = 1;
    oilNew[center.x-2][center.y] = 1;
    oilNew[center.x][center.y+2] = 1;
    oilNew[center.x][center.y-2] = 1;

    // Grafika
    sf::RenderWindow window(sf::VideoMode(displaySize, displaySize), "Snowflake");
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
                if (event.key.code == sf::Keyboard::T) {    // Czy spacja to pauza czy jeden krok
                    slowmode = !slowmode;
                }
                if (event.key.code == sf::Keyboard::I) {    // Iloœæ kroków
                    std::cout << "Kroki: "<< curIteration << " / " << iterations << std::endl;
                }
            }
        }
        if (!pause) {
            curIteration += 1;
            StainUpdate(oilNew, threshold);
            if(slowmode)pause = true;
        }
        if (iterations == curIteration) {
                pause = true;
                std::cout << "DONE" << std::endl;
                iterations = -1;
                //window.close();//*/
        }

        if (display) {
            window.clear();
            shape.setFillColor(sf::Color::White);
            // Rysuje Klastr
            for (int y = 0; y < size; y++) {
                even = !even;
                if (y == 0)even = true;
                for (int x = 0; x < size; x++) {
                    if (oilNew[x][y] > 0) {
                        if (oilNew[x][y] > 1) shape.setFillColor(sf::Color::Blue);
                        else shape.setFillColor(sf::Color::White);
                        //std::cout << "X: "<< x<<" Y: "<<y << std::endl;
                        if(even) shape.setPosition(sf::Vector2f(blocksize * x + shift, blocksize * y));
                        else shape.setPosition(sf::Vector2f(blocksize * x - shift, blocksize * y));
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