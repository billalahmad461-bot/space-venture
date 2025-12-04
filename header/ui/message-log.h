#ifndef MESSAGE_LOG_H
#define MESSAGE_LOG_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
class MessageLog {
private:
    std::vector<sf::Text> _logs;
    std::vector<sf::Clock> _clocks;
    sf::Font& _font;
    int _max_logs;
public:
    MessageLog(sf::Font& font, int max_logs = 5);
    void addMessage(std::string msg);
    void draw(sf::RenderWindow& window);
};
#endif
