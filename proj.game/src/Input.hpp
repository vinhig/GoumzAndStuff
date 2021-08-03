#include <functional>
#include <vector>

namespace GoumzAndStuff {
enum KeyState : char { PRESSED, RELEASED, JUST_PRESSED, JUST_RELEASED };

enum ZoomState : char {
  ZOOM_START,
  ZOOM_MIDDLE,
  ZOOM_STOP,
};

class InputHandler;

class Input {
 private:
  std::vector<InputHandler*> _touch_handlers;
  std::vector<InputHandler*> _zoom_handlers;

 public:
  Input();
  ~Input();

  void zoom_start();
  void zoom(float delta);
  void zoom_stop(float delta);

  void touch(float x, float y);

  void register_handler(InputHandler* handler);
  void unregister_handler(InputHandler* handler);
};

class InputHandler {
 private:
  std::function<void(ZoomState, float)> _zoom_callback;
  std::function<void(float, float)> _touch_callback;

  bool _handle_touch;
  bool _handle_zoom;

 public:
  InputHandler() = default;
  ~InputHandler() = default;

  void handle_zoom();
  void handle_touch();

  bool listen_for_zoom();
  bool listen_for_touch();

  void notify_zoom_start();
  void notify_zoom(float delta);
  void notify_zoom_stop(float delta);
  void notify_touch(float x, float y);

  void set_zoom_callback(std::function<void(ZoomState, float)> const& f);
  void set_touch_callback(std::function<void(float, float)> const& f);
};

}  // namespace GoumzAndStuff