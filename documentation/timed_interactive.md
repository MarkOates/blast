## Before the primary loop:
```
   float duration_until_abort_sec = 3.0f;
   float interactive_started_at = al_get_time();
   bool abort_timer_in_effect = true;
```

## Within the primary loop body:
```
  while(!abort)
      if (abort_timer_in_effect && (al_get_time() - interactive_started_at) > duration_until_abort_sec) break;

```

## On events that should halt the auto-abort feature:
```
            abort_timer_in_effect = false;
```

