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
  for (auto const& handler : _zoom_handlers) {
    handler->notify_zoom(delta);
  }
}

void Input::zoom_stop(float delta) {
  for (auto const& handler : _zoom_handlers) {
    handler->notify_zoom_stop(delta);
  }
}

void Input::touch(TouchState state, float x, float y) {
  for (auto const& handler : _touch_handlers) {
    handler->notify_touch(state, x, y);
  }
}

void Input::drag_start() {
  for (auto const& handler : _drag_handlers) {
    handler->notify_drag_start();
  }
}

void Input::drag(float x, float y) {
  for (auto const& handler : _drag_handlers) {
    handler->notify_drag(x, y);
  }
}

void Input::drag_stop(float x, float y) {
  for (auto const& handler : _drag_handlers) {
    handler->notify_drag_stop(x, y);
  }
}

void Input::register_handler(InputHandler* handler) {
  if (handler->listen_for_touch()) {
    _touch_handlers.push_back(handler);
  }

  if (handler->listen_for_zoom()) {
    _zoom_handlers.push_back(handler);
  }

  if (handler->listen_for_drag()) {
    _drag_handlers.push_back(handler);
  }
}

void Input::unregister_handler(InputHandler* handler) {
  if (handler->listen_for_zoom()) {
    for (auto it = _zoom_handlers.begin(); it != _zoom_handlers.end(); ++it) {
      if (*it == handler) {
        _zoom_handlers.erase(it);
        break;
      }
    }
  }

  if (handler->listen_for_touch()) {
    for (auto it = _touch_handlers.begin(); it != _touch_handlers.end(); ++it) {
      if (*it == handler) {
        _touch_handlers.erase(it);
        break;
      }
    }
  }

  if (handler->listen_for_drag()) {
    for (auto it = _drag_handlers.begin(); it != _drag_handlers.end(); ++it) {
      if (*it == handler) {
        _drag_handlers.erase(it);
        break;
      }
    }
  }
}

void InputHandler::handle_zoom() { _handle_zoom = true; }
void InputHandler::handle_touch() { _handle_touch = true; }
void InputHandler::handle_drag() { _handle_drag = true; }

bool InputHandler::listen_for_zoom() { return _handle_zoom; }
bool InputHandler::listen_for_touch() { return _handle_touch; }
bool InputHandler::listen_for_drag() { return _handle_drag; }

void InputHandler::notify_zoom_start() {
  _zoom_callback(ZoomState::ZOOM_START, 1.0f);
}
void InputHandler::notify_zoom(float delta) {
  _zoom_callback(ZoomState::ZOOM_MIDDLE, delta);
}
void InputHandler::notify_zoom_stop(float delta) {
  _zoom_callback(ZoomState::ZOOM_STOP, delta);
}

void InputHandler::notify_touch(TouchState state, float x, float y) {
  _touch_callback(state, x, y);
}

void InputHandler::notify_drag_start() {
  _drag_callback(DRAG_START, 0.0f, 0.0f);
}
void InputHandler::notify_drag(float x, float y) {
  _drag_callback(DRAG_MIDDLE, x, y);
}
void InputHandler::notify_drag_stop(float x, float y) {
  _drag_callback(DRAG_STOP, x, y);
}

void InputHandler::set_zoom_callback(
    std::function<void(ZoomState, float)> const& callback) {
  _zoom_callback = callback;
}

void InputHandler::set_touch_callback(
    std::function<void(TouchState, float, float)> const& callback) {
  _touch_callback = callback;
}

void InputHandler::set_drag_callback(
    std::function<void(DragState, float, float)> const& callback) {
  _drag_callback = callback;
}

}  // namespace GoumzAndStuff
