#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
//#include <cstdlib>
//#include <cmath>
#include <ctime>
#include <iostream>
std::vector<sf::Vector2i> checkNeigbours(std::vector<std::vector<int>> const &oilNew,int x, int y) {
    int size = oilNew.size();
    std::vector<sf::Vector2i> neighs;
    std::vector<sf::Vector2i> borders{ sf::Vector2i (0, 1),sf::Vector2i(0, -1),sf::Vector2i(-1, 0),sf::Vector2i(1, 0) };
    int rnx, rny;
    for (int n = 0; n < 4; n++) {
        rnx = x + borders[n].x; rny = y + borders[n].y;
        if (rnx  < 0 || rny < 0 || rnx > size - 1 || rny > size - 1) continue;
        else {
            if (oilNew[rnx][rny]!=0)continue;
            else neighs.push_back(borders[n]);
        }
    }
    return neighs;
}

void StainUpdate(std::vector<std::vector<int>>& oilNew, int surf) {
    int size = oilNew.size();   // Za³o¿enie ¿e tablica ma kszta³t kwadratu
    std::vector<sf::Vector2i> neighbours;
    sf::Vector2i growth;
    int rnx, rny, pass;
    int growing = rand() % surf;    //Która komórka roœnie
    pass = 0; // Pominiête powiechrznie
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (oilNew[x][y] == 1) {
                if (!(pass<growing)) {
                    //std::cout << "CHECK" << std::endl;
                    neighbours = checkNeigbours(oilNew, x, y);
                    //std::cout << "UP1" << std::endl;
                    growth = neighbours[rand()%neighbours.size()];
                    rnx = x + growth.x; rny = y + growth.y;
                    //std::cout << "UP2" << std::endl;
                    oilNew[rnx][rny] = 1;
                    std::vector<sf::Vector2i> borders{ sf::Vector2i(rnx, rny), sf::Vector2i(rnx, rny+1),sf::Vector2i(rnx, rny -1),sf::Vector2i(rnx -1, rny),sf::Vector2i(rnx + 1, rny) };
                    //std::cout << "UP3" << std::endl;
                    for (int n = 0; n < 5; n++) {
                        
                        if (borders[n].x  < 0 || borders[n].y < 0 || borders[n].x > size - 1 || borders[n].y > size - 1 || oilNew[borders[n].x][borders[n].y]<1) continue;
                        neighbours = checkNeigbours(oilNew, borders[n].x, borders[n].y);
                        if (neighbours.size() < 1)oilNew[borders[n].x][borders[n].y] = 2;
                    }
                    return;
                }
                pass += 1;
            }
        }
    }

}

int SurfaceCount(std::vector<std::vector<int>> const& oilNew) {
    int size = oilNew.size();   // Za³o¿enie ¿e tablica ma kszta³t kwadratu
    int pass;
    pass = 0; // Pominiête powiechrznie
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (oilNew[x][y] == 1) {
                
                pass += 1;
            }
        }
    }
    return pass;
}


int main()
{
    std::srand(std::time({}));
    // Ustawienia
    int displaySize = 800;
    bool pause = true;
    int iterations = 5000;     // Iloœæ iteracji
    int curIteration = 1;     // Obecna iteracja
    //int probability = 500;  // Od 0 do 1000
    bool display = true; // Czy ma rysowaæ gry
    int size = 200;     // Wymiar tablicy
    int space = size * size;
    float blocksize = static_cast<float>(displaySize) / size;  // Graficzna wielkoœæ pola

    // Zbiorniki
    int surface = 1;
    //std::vector<std::vector<bool>> oil(size, std::vector<bool>(size, false));
    std::vector<std::vector<int>> oilNew(size, std::vector<int>(size, 0));
    oilNew[size / 2][size / 2] = 1;

    // Grafika
    sf::RenderWindow window(sf::VideoMode(displaySize, displaySize), "KLastr Edena");
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
            }
        }
        if (!pause&&surface!=0) {
            curIteration += 1;
            StainUpdate(oilNew, surface);
            surface = SurfaceCount(oilNew);
        }
        if (iterations == curIteration) {
                pause = true;
                std::cout << "DONE" << std::endl;
                iterations = -1;
                //window.close();//*/
        }

        if (display) {
            window.clear();
            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {
                    if (oilNew[x][y]!=0) {
                        shape.setFillColor(sf::Color::Green);
                        if (oilNew[x][y] < 2)shape.setFillColor(sf::Color::Red);
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