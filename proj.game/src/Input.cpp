#include "Input.hpp"

#include <string>

#include "Log.hpp"

namespace GoumzAndStuff {

Input::Input() {}

Input::~Input() {}

void Input::zoom_start() {
  for (auto const& handler : _zoom_handlers) {
    handler->notify_zoom_start();
  }
}

void Input::zoom(float delta) {
  Log::debug("Zooming " + std::to_string(delta) + "...");
  for (auto const& handler : _zoom_handlers) {
    Log::debug("notifyyyyy");
    handler->notify_zoom(delta);
  }
}

void Input::zoom_stop(float delta) {
  for (auto const& handler : _zoom_handlers) {
    handler->notify_zoom_stop(delta);
  }
}

void Input::touch(float x, float y) {
  for (auto const& handler : _touch_handlers) {
    handler->notify_touch(x, y);
  }
}

void Input::register_handler(InputHandler* handler) {
  if (handler->listen_for_touch()) {
    _touch_handlers.push_back(handler);
  }

  if (handler->listen_for_zoom()) {
    _zoom_handlers.push_back(handler);
  }
}

void Input::unregister_handler(InputHandler* handler) {
  if (handler->listen_for_touch()) {
    for (auto it = _touch_handlers.begin(); it != _touch_handlers.end(); ++it) {
      if (*it == handler) {
        _touch_handlers.erase(it);
        break;
      }
    }
  }

  if (handler->listen_for_zoom()) {
    for (auto it = _zoom_handlers.begin(); it != _zoom_handlers.end(); ++it) {
      if (*it == handler) {
        _zoom_handlers.erase(it);
        break;
      }
    }
  }
}

void InputHandler::handle_zoom() { _handle_zoom = true; }
void InputHandler::handle_touch() { _handle_touch = true; }

bool InputHandler::listen_for_zoom() { return _handle_zoom; }
bool InputHandler::listen_for_touch() { return _handle_touch; }

void InputHandler::notify_zoom_start() {
  _zoom_callback(ZoomState::ZOOM_START, 1.0f);
}
void InputHandler::notify_zoom(float delta) {
  _zoom_callback(ZoomState::ZOOM_MIDDLE, delta);
}
void InputHandler::notify_zoom_stop(float delta) {
  _zoom_callback(ZoomState::ZOOM_STOP, delta);
}

void InputHandler::notify_touch(float x, float y) { _touch_callback(x, y); }

void InputHandler::set_zoom_callback(
    std::function<void(ZoomState, float)> const& callback) {
  _zoom_callback = callback;
}
void InputHandler::set_touch_callback(
    std::function<void(float, float)> const& callback) {
  _touch_callback = callback;
}

}  // namespace GoumzAndStuff
