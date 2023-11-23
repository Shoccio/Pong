#include "GameObjects.h"

bool KeyPressed(sf::Keyboard::Key);
void CheckForCollision(sf::RectangleShape&, std::string, GameObjects, float&, float&, sf::Sound&);
void DoesCollide(sf::RectangleShape&, std::string, sf::RectangleShape, float&, float&, sf::Sound&);
void CheckForCollision(sf::RectangleShape&, std::string, GameObjects);
void DoesCollide(sf::RectangleShape&, std::string, sf::RectangleShape);
bool CollideX(float, float, float, float);
bool CollideY(float, float, float, float);
bool CollisionX1(float, float, float, float);
bool CollisionX2(float, float, float, float);
bool CollisionY1(float, float, float, float);
bool CollisionY2(float, float, float, float);


int main()
{
    GameObjects listOfObjects;
    sf::SoundBuffer buffer;
    float speedX = 5.f, speedY = 5.f, speedXBall = 5.f, speedYBall = 5.f;
    std::string player = "player", playerTwo = "playertwo", top = "top", bottom = "bottom", ball = "ball", right = "right";
    int width = 500, height = 500;
    float playerWidth = 20.f, playerHeight = 50.f;
    bool flag = false;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::CircleShape ballCircle(5.f);

    buffer.loadFromFile("C:\\Users\\mynam\\projects\\hellowrld\\C++\\FirstSFML\\Audio\\8-Bit_Hit_Sound_Effect.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);
     

    listOfObjects.Insert(sf::RectangleShape(sf::Vector2f(playerWidth, playerHeight)), player, true);
    listOfObjects.Insert(sf::RectangleShape(sf::Vector2f(playerWidth, playerHeight)), playerTwo, true);
    listOfObjects.Insert(sf::RectangleShape(sf::Vector2f(width, 100)), top, false);
    listOfObjects.Insert(sf::RectangleShape(sf::Vector2f(width, 100)), bottom, false);
    //listOfObjects.Insert(sf::RectangleShape(sf::Vector2f(10, height)), right, false);
    listOfObjects.Insert(sf::RectangleShape(sf::Vector2f(ballCircle.getRadius() * 2, ballCircle.getRadius() * 2)), ball, true);

    listOfObjects[player].setOrigin(sf::Vector2f(playerWidth / 2, playerHeight / 2));
    listOfObjects[playerTwo].setOrigin(sf::Vector2f(playerWidth / 2, playerHeight / 2));
    listOfObjects[ball].setOrigin(sf::Vector2f(listOfObjects[ball].getSize().x / 2, listOfObjects[ball].getSize().y / 2));
    listOfObjects[top].setOrigin(listOfObjects[top].getSize().x / 2, listOfObjects[top].getSize().y / 2);
    listOfObjects[bottom].setOrigin(listOfObjects[bottom].getSize().x / 2, listOfObjects[bottom].getSize().y / 2);
    //listOfObjects[right].setOrigin(listOfObjects[right].getSize().x / 2, listOfObjects[right].getSize().y / 2);
    ballCircle.setOrigin(sf::Vector2f(ballCircle.getRadius(), ballCircle.getRadius()));

    listOfObjects[top].setPosition(sf::Vector2f((width / 2), (height / 10)));
    listOfObjects[bottom].setPosition(sf::Vector2f(width / 2, (height - height / 10)));
    listOfObjects[player].setPosition(sf::Vector2f(width / 5, height / 2));
    listOfObjects[playerTwo].setPosition(sf::Vector2f(4 * width / 5, height / 2));
    ballCircle.setPosition(sf::Vector2f((width / 5) + 20.f, height / 2));
    //listOfObjects[right].setPosition(sf::Vector2f(width, height / 2));
    listOfObjects[ball].setPosition(ballCircle.getPosition());

    listOfObjects[top].setFillColor(sf::Color::Black);
    listOfObjects[bottom].setFillColor(sf::Color::Black);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (KeyPressed(sf::Keyboard::W))
        {
            listOfObjects[player].move(sf::Vector2f(0.f, -speedY));
        }
        else if (KeyPressed(sf::Keyboard::S))
        {
            listOfObjects[player].move(sf::Vector2f(0.f, speedY));
        }
        else if (KeyPressed(sf::Keyboard::Space))
        {
            int a = 0;
        }

        if (KeyPressed(sf::Keyboard::O))
        {
            listOfObjects[playerTwo].move(sf::Vector2f(0.f, -speedY));
        }
        else if (KeyPressed(sf::Keyboard::L))
        {
            listOfObjects[playerTwo].move(sf::Vector2f(0.f, speedY));
        }

        listOfObjects[ball].move(sf::Vector2f(speedXBall, speedYBall));
        ballCircle.setPosition(listOfObjects[ball].getPosition());
        
        CheckForCollision(listOfObjects[ball], ball, listOfObjects, speedXBall, speedYBall, sound);
        CheckForCollision(listOfObjects[player], player, listOfObjects);
        CheckForCollision(listOfObjects[playerTwo], player, listOfObjects);


        window.clear(sf::Color::Blue);

        window.draw(ballCircle);
        window.draw(listOfObjects[player]);
        window.draw(listOfObjects[top]);
        window.draw(listOfObjects[bottom]);
        //window.draw(listOfObjects[right]);
        window.draw(listOfObjects[playerTwo]);

        window.display();

    }

    return 0;
}

bool KeyPressed(sf::Keyboard::Key keyPressed)
{
    return sf::Keyboard::isKeyPressed(keyPressed);
}

void CheckForCollision(sf::RectangleShape& original, std::string nameOriginal, GameObjects listOfGameObjects)
{
    for (int i = 0; i < listOfGameObjects.Size(); i++)
    {
        if (listOfGameObjects.GetName(i) != nameOriginal)
        {
            DoesCollide(original, nameOriginal, listOfGameObjects[i]);
        }
    }

}

void DoesCollide(sf::RectangleShape& original, std::string name, sf::RectangleShape collider)
{
    sf::Vector2f posOriginal = original.getPosition();
    sf::Vector2f posCollider = collider.getPosition();
    sf::Vector2f sizeOriginal = original.getSize();
    sf::Vector2f sizeCollider = collider.getSize();
    bool flagX = CollideX(posOriginal.x, sizeOriginal.x, posCollider.x, sizeCollider.x);
    bool flagY = CollideY(posOriginal.y, sizeOriginal.y, posCollider.y, sizeCollider.y);

    if (flagX && flagY)
    {
        if (flagX)
        {

            float distance = 0.f;

            if (posOriginal.x > posCollider.x)
                distance = (posOriginal.x - (sizeOriginal.x / 2)) - (posCollider.x + (sizeCollider.x / 2));
            else if (posOriginal.x < posCollider.x)
                distance = (posOriginal.x + (sizeOriginal.x / 2)) - (posCollider.x - (sizeCollider.x / 2));

            original.setPosition(sf::Vector2f(posOriginal.x + (sizeOriginal.x - distance), posOriginal.y));
        }

        if (flagY)
        {
            float distance = 0.f;

            if (posOriginal.y > posCollider.y)
                distance = (posOriginal.y - (sizeOriginal.y / 2)) - (posCollider.y + (sizeCollider.y / 2));
            else if (posOriginal.y < posCollider.y)
                distance = (posOriginal.y + (sizeOriginal.y / 2)) - (posCollider.y - (sizeCollider.y / 2));

            original.setPosition(sf::Vector2f(posOriginal.x, posOriginal.y - distance));
        }
    }


}

void CheckForCollision(sf::RectangleShape& original, std::string nameOriginal, GameObjects listOfGameObjects, float& X, float& Y, sf::Sound& sound)
{
    for (int i = 0; i < listOfGameObjects.Size(); i++)
    {
        if (listOfGameObjects.GetName(i) != nameOriginal)
        {
            DoesCollide(original, nameOriginal, listOfGameObjects[i], X, Y, sound);
        }
    }

}

void DoesCollide(sf::RectangleShape& original, std::string name, sf::RectangleShape collider, float& X, float& Y, sf::Sound& sound)
{
    sf::Vector2f posOriginal = original.getPosition();
    sf::Vector2f posCollider = collider.getPosition();
    sf::Vector2f sizeOriginal = original.getSize();
    sf::Vector2f sizeCollider = collider.getSize();
    bool flagX = CollideX(posOriginal.x, sizeOriginal.x, posCollider.x, sizeCollider.x);
    bool flagY = CollideY(posOriginal.y, sizeOriginal.y, posCollider.y, sizeCollider.y);
    bool isX = false;

    if (flagX && flagY)
    {
        float PosX = posOriginal.x;
        float PosY = posOriginal.y;

        while (true)
        {
            float XTemp = X * 0.1;
            float YTemp = Y * 0.1;

            PosX -= XTemp;
            PosY -= YTemp;

            if (!CollideX(PosX, sizeOriginal.x, posCollider.x, sizeCollider.x))
            {
                isX = true;
                break;
            }
            else if (!CollideY(PosY, sizeOriginal.y, posCollider.y, sizeCollider.y))
            {
                break;
            }


        }

        if (isX)
        {
            

            float distance = 0.f;

            if (posOriginal.x > posCollider.x)
                distance = (posOriginal.x - (sizeOriginal.x / 2)) - (posCollider.x + (sizeCollider.x / 2));
            else if (posOriginal.x < posCollider.x)
                distance = (posOriginal.x + (sizeOriginal.x / 2)) - (posCollider.x - (sizeCollider.x / 2));

            original.setPosition(sf::Vector2f(posOriginal.x - distance, posOriginal.y));

            X *= -1;
        }
        else if (!isX)
        {
            float distance = 0.f;

            if (posOriginal.y > posCollider.y)
                distance = (posOriginal.y - (sizeOriginal.y / 2)) - (posCollider.y + (sizeCollider.y / 2));
            else if (posOriginal.y < posCollider.y)
                distance = (posOriginal.y + (sizeOriginal.y / 2)) - (posCollider.y - (sizeCollider.y / 2));

            original.setPosition(sf::Vector2f(posOriginal.x, posOriginal.y - distance));

            Y *= -1;
        }

        sound.play();
    }
    
}
// |O||   0    | or |   0   ||0| 
bool CollideX(float posOriginal, float sizeOriginal, float posCollider, float sizeCollider)
{
    return  CollisionX1(posOriginal, sizeOriginal, posCollider, sizeCollider) && CollisionX2(posOriginal, sizeOriginal, posCollider, sizeCollider);
}

bool CollideY(float posOriginal, float sizeOriginal, float posCollider, float sizeCollider)
{
    return CollisionY1(posOriginal, sizeOriginal, posCollider, sizeCollider) && CollisionY2(posOriginal, sizeOriginal, posCollider, sizeCollider);
}

bool CollisionX1(float posOriginal, float sizeOriginal, float posCollider, float sizeCollider)
{
    return posOriginal + (sizeOriginal / 2) > posCollider - (sizeCollider / 2);
}

bool CollisionX2(float posOriginal, float sizeOriginal, float posCollider, float sizeCollider)
{
    return posOriginal - (sizeOriginal / 2) < posCollider + (sizeCollider / 2);
}

bool CollisionY1(float posOriginal, float sizeOriginal, float posCollider, float sizeCollider)
{
    return posOriginal - (sizeOriginal / 2) < posCollider + (sizeCollider / 2);
}

bool CollisionY2(float posOriginal, float sizeOriginal, float posCollider, float sizeCollider)
{
    return posOriginal + (sizeOriginal / 2) > posCollider - (sizeCollider / 2);
}