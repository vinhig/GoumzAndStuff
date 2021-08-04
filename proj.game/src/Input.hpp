#include <functional>
#include <vector>

namespace GoumzAndStuff {
enum TouchState : char {
  TOUCH_PRESSED = 0,
  TOUCH_JUST_PRESSED = 1,
  TOUCH_JUST_RELEASED = 2,
};

enum ZoomState : char {
  ZOOM_START,
  ZOOM_MIDDLE,
  ZOOM_STOP,
};

enum DragState : char {
  DRAG_START,
  DRAG_MIDDLE,
  DRAG_STOP,
};

class InputHandler;

class Input {
 private:
  std::vector<InputHandler*> _zoom_handlers;
  std::vector<InputHandler*> _touch_handlers;
  std::vector<InputHandler*> _drag_handlers;

 public:
  Input();
  ~Input();

  void zoom_start();
  void zoom(float delta);
  void zoom_stop(float delta);

  void touch(TouchState state, float x, float y);

  void drag_start();
  void drag(float delta_x, float delta_y);
  void drag_stop(float delta_x, float delta_y);

  void register_handler(InputHandler* handler);
  void unregister_handler(InputHandler* handler);
};

class InputHandler {
 private:
  std::function<void(ZoomState, float)> _zoom_callback;
  std::function<void(TouchState, float, float)> _touch_callback;
  std::function<void(DragState, float, float)> _drag_callback;

  bool _handle_zoom;
  bool _handle_touch;
  bool _handle_drag;

 public:
  InputHandler() = default;
  ~InputHandler() = default;

  void handle_zoom();
  void handle_touch();
  void handle_drag();

  bool listen_for_zoom();
  bool listen_for_touch();
  bool listen_for_drag();

  void notify_zoom_start();
  void notify_zoom(float delta);
  void notify_zoom_stop(float delta);

  void notify_touch(TouchState state, float x, float y);

  void notify_drag_start();
  void notify_drag(float delta_x, float delta_y);
  void notify_drag_stop(float delta_x, float delta_y);

  void set_zoom_callback(std::function<void(ZoomState, float)> const& f);
  void set_touch_callback(
      std::function<void(TouchState, float, float)> const& f);
  void set_drag_callback(std::function<void(DragState, float, float)> const& f);
};

}  // namespace GoumzAndStuff