#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <bitset>

namespace Cx::KeyState
{
    // Keyboard state tracked from window events. Unlike sf::Keyboard::isKeyPressed,
    // this does not need the Input Monitoring permission on macOS.
    inline std::bitset<sf::Keyboard::KeyCount> Pressed;

    inline void Update(const sf::Event& ev)
    {
        if (const auto pressed = ev.getIf<sf::Event::KeyPressed>(); pressed && pressed->code != sf::Keyboard::Key::Unknown)
            Pressed.set(static_cast<std::size_t>(pressed->code));
        else if (const auto released = ev.getIf<sf::Event::KeyReleased>(); released && released->code != sf::Keyboard::Key::Unknown)
            Pressed.reset(static_cast<std::size_t>(released->code));
    }

    inline bool IsPressed(const sf::Keyboard::Key key)
    {
        return key != sf::Keyboard::Key::Unknown && Pressed.test(static_cast<std::size_t>(key));
    }
}
