#include "../../header/ui/message-log.h"
MessageLog::MessageLog(sf::Font& font, int max_logs) : _font(font), _max_logs(max_logs) {}
void MessageLog::addMessage(std::string msg) {
    sf::Text text(msg, _font, 18);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(10, 10 + _logs.size() * 20);
    _logs.push_back(text);
    if (_logs.size() > _max_logs) _logs.erase(_logs.begin());
    for (size_t i = 0; i < _logs.size(); ++i) {
        _logs[i].setPosition(10, 10 + i * 20);
    }
}
void MessageLog::draw(sf::RenderWindow& window) {
    for (auto& text : _logs) {
        window.draw(text);
    }
}
