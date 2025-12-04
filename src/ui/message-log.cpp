#include "../../header/ui/message-log.h"
#include <algorithm>
MessageLog::MessageLog(sf::Font& font, int max_logs) : _font(font), _max_logs(max_logs) {}
void MessageLog::addMessage(std::string msg) {
    sf::Text text(msg, _font, 18);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(10, 10 + _logs.size() * 20);
    _logs.push_back(text);
    sf::Clock clk;
    _clocks.push_back(clk);
    if (_logs.size() > _max_logs) {
        _logs.erase(_logs.begin());
        _clocks.erase(_clocks.begin());
    }
    for (size_t i = 0; i < _logs.size(); ++i) {
        _logs[i].setPosition(10, 10 + i * 20);
    }
}
void MessageLog::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < _logs.size(); ++i) {
        float time = _clocks[i].getElapsedTime().asSeconds();
        if (time > 3.f) {
            _logs.erase(_logs.begin() + i);
            _clocks.erase(_clocks.begin() + i);
            --i;
            continue;
        } else if (time > 2.f) {
            sf::Color col = _logs[i].getFillColor();
            col.a = static_cast<sf::Uint8>(255 * (3.f - time));
            _logs[i].setFillColor(col);
        }
        window.draw(_logs[i]);
    }
}
