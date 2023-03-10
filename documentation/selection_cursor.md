# Component

```yaml
properties:


  - name: cursor_pos
    type: int
    init_with: 0
    getter: true

  - name: selection_cursor_box
    type: AllegroFlare::Elements::SelectionCursorBox
    init_with: '{}'

  - name: box_gutter_y
    type: float
    init_with: 10.0f
    getter: true
    setter: true

  - name: scrollbar_position
    type: float
    init_with: 0.0f
    getter: true
    getter_ref: false
    setter: false

  - name: scrollbar_position_destination
    type: float
    init_with: 0.0f
    getter: true
    getter_ref: false
    setter: false

  - name: scrollbar_reposition_multiplier
    type: float
    init_with: DEFAULT_SCROLLBAR_REPOSITION_MULTIPLIER
    getter: true
    getter_ref: false
    setter: false

  - name: scrollbar_movement_mode
    type: uint32_t
    init_with: SCROLLBAR_MOVEMENT_FOLLOW_PROPORTIONAL

  - name: SCROLLBAR_MOVEMENT_NONE
    type: uint32_t
    init_with: 0
    const: true
    static: true
    constexpr: true

  - name: SCROLLBAR_MOVEMENT_FOLLOW_PROPORTIONAL
    type: uint32_t
    init_with: 1
    const: true
    static: true
    constexpr: true

  - name: DEFAULT_SCROLLBAR_REPOSITION_MULTIPLIER
    type: float
    init_with: 0.1f
    const: true
    static: true
    constexpr: true


functions:


  - name: initialize
    guards: [ (!initialized), al_is_system_installed(), al_is_font_addon_initialized() ]
    body: |
      selection_cursor_box.set_position(0, 0);
      selection_cursor_box.set_size(list_item_box_width, list_item_box_height);
      selection_cursor_box.set_padding(6.0f, 6.0f);
      initialized = true;
      return;


  - name: move_cursor_up
    type: bool
    body: |
      if (list_items.empty()) return false;
      if (state != STATE_MOVING_CURSOR) return false; // TODO: test this logic

      int previous_cursor_pos = cursor_pos;
      cursor_pos--;
      // TODO: add optional "wrap"
      while (cursor_pos < 0)
      {
         cursor_pos += joystick_configuration_mapping.size();
      }

      bool cursor_moved = (previous_cursor_pos != cursor_pos);
      if (cursor_moved) move_selection_cursor_box_to_current_cursor_location();

      return true;


  - name: move_cursor_down
    type: bool
    body: |
      if (list_items.empty()) return false;
      if (state != STATE_MOVING_CURSOR) return false; // TODO: test this logic

      int previous_cursor_pos = cursor_pos;
      cursor_pos++;
      // TODO: add optional "wrap"
      while (cursor_pos >= joystick_configuration_mapping.size())
      {
         cursor_pos -= joystick_configuration_mapping.size();
      }

      bool cursor_moved = (previous_cursor_pos != cursor_pos);
      if (cursor_moved) move_selection_cursor_box_to_current_cursor_location();

      return cursor_moved;


  - name: move_selection_cursor_box_to_current_cursor_location
    private: true
    body: |
      // TODO: this function
      AllegroFlare::Vec2D new_position = build_selection_cursor_box_position_of_current_cursor_pos();
      selection_cursor_box.reposition_to(new_position.x, new_position.y);

      if (scrollbar_movement_mode_is_follow_proportional())
      {
         float new_scrollbar_position = build_scrollbar_position_at_current_cursor_pos();
         scrollbar_position_destination = new_scrollbar_position;
         // TODO: replace this logic with a "scrollbar_position_destination" type logic
         //scrollbar_position = new_scrollbar_position;
      }

      return;


  - name: build_selection_cursor_box_position_of_current_cursor_pos
    private: true
    type: AllegroFlare::Vec2D
    body: |
      return AllegroFlare::Vec2D(0, cursor_pos * infer_list_item_spacing_y());


  - name: infer_list_item_spacing_y
    type: float
    body: |
      return list_item_box_height + box_gutter_y;


  - name: scrollbar_movement_mode_is_follow_proportional
    type: bool
    body: |
      return scrollbar_movement_mode == SCROLLBAR_MOVEMENT_FOLLOW_PROPORTIONAL;


  - name: build_scrollbar_position_at_current_cursor_pos
    private: true
    type: float
    body: |
      if (joystick_configuration_mapping.size() <= 1) return 0;
      float normalized_cursor_position = (float)cursor_pos / (joystick_configuration_mapping.size() - 1);
      float container_scroll_range = infer_container_scroll_range();
      return normalized_cursor_position * container_scroll_range;
```

# Test

```cpp
      // draw the scrollbar
      if (!scrollbar_is_autohidden_because_list_contents_is_smaller_than_the_container())
      {
         AllegroFlare::Elements::Scrollbar scrollbar(
            input_devices_list_width + scrollbar_x_padding,
            scrollbar_y_padding,
            container_height - scrollbar_y_padding * 2,
            normalized_scrollbar_position,
            scrollbar_bar_color,
            scrollbar_handle_color
         );
         scrollbar.render();
      }
```


# Inside the `render()` Function

```cpp

      if (list_item_elements_exist)
      {
         // TODO: Render an empty state
      }
      else // Render list items
      {
         AllegroFlare::Placement2D scrollarea_contents(
            0,
            -scrollbar_position,
            0,
            0
         );

         // Draw the scrollarea contents
         scrollarea_contents.start_transform();

         // TODO: Draw the contents of the scrollarea here


         scrollarea_contents.restore_transform();
      }
```
