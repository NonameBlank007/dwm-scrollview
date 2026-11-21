# dwm-scrollview

dwm-scrollview brings a continuous scrolling ribbon layout and an interactive workspace overview to dwm, heavily inspired by modern wayland compositor like Niri.

**Note: Multi-monitors arnt tested (Only have a laptop lol). So, take it with grain of salt and do report bugs. Bugs might be a sync issue with overview and scroller for diffrent monitors, It may act seprately on both.** 

## Contents
- [About](#about)
- [Recommended Patches](#recommended-patches)
- [Key Modes](#key-modes)
- [Centering Modes](#centering-modes)
- [Keybindings](#keybindings)


## About

Traditional tiling window managers force all windows into a single static frame. If you open four or five apps, text becomes unreadable.

dwm-scrollview changes that workflow:
* Windows open at a comfortable width (like 50% or 66% of the screen) along a horizontal ribbon.
* You can navigate between windows using your keyboard, mouse wheel, or smooth trackpad gestures.
* Windows can be stacked on top of each other in the same column (like an editor on top and a terminal below).
* Super + Shift + Up/Down stacks or swaps windows vertically, while Super + Shift + Left/Right pulls a window out into its own column.
* Super + Tab opens a overview of every tag client, letting you see running apps and jump straight to what you need.

## Recommended

To have better experiance it is recommended to patch `dwm-scrollview` after patch of `dwm-cfacts-vanitygaps-combo` patch:


## Key Modes

To keep shortcuts from clashing with regular apps, dwm-scrollview splits keys into three active modes:

* **Normal Mode**: Active when using standard dwm layouts (tile, monocle, floating). Your regular dwm keys work exactly as you expect.
* **Scroll Mode**: Active whenever you switch to the Scroller layout (`[|||]`). Unlocks horizontal ribbon navigation, column width adjustments, and vertical stacking.
* **Overview Mode**: Active when you press Super + Tab to enter the overview (`[⊞]`). Arrow keys or hjkl navigate workspace ribbons and window cards. Pressing Return zooms into the selected window, and Escape exits.
* **All (Universal)**: Global shortcuts that work anywhere, like volume, brightness and screenshots.


## Centering Modes

You can choose how the screen camera tracks your focused window along the ribbon:

| Mode | What it does |
| :--- | :--- |
| **`CenterOnFlow`** | The screen only scrolls when your focused window hits an edge. If two window in screen and one size is big to fit two, It triggers centering on big window when focused. Great for laptops and regular screens. |
| **`CenterAlways`** | Keeps your focused window centered on screen at all times. Great for ultrawide monitors. |
| **`CenterNever`** | The screen stays put unless a window is completely off screen, dosn't centre on flow. Ideal if you prefer manual panning. |

* **Single Window Centering Override**: If a workspace only has one window or stack, it automatically centers on screen on value `1`.

* **Switch Modes**: Press `Super + Shift + c` at any time to cycle between these three modes.


## Keybindings

### Scroll

| Shortcut | Function | Description |
| :--- | :--- | :--- |
| `Super + Left / Right` | `scrollwin` | Move focus to previous / next column |
| `Super + Up / Down` | `focuswinstack` | Move focus up / down inside a stacked column |
| `Super + w` | `togglestack` | Stack window into neighbor, or unstack if already stacked |
| `Super + r` | `cyclewinwidth` | Cycle column width preset (33% -> 50% -> 66% -> 100%) |
| `Super + c` | `centerfocused` | Center current column on screen |
| `Super + Shift + c` | `togglecentering`| Cycle centering mode (CenterOnFlow / Always / Never) |
| `Super + Shift + Left / Right` | `movewin` | Move column; if stacked, pulls window out into its own column |
| `Super + Shift + Up / Down` | `movewinstack` | Reorder window in stack; if single, stacks into neighbor |
| `Super + Ctrl + n` | `toggleloopnav` | Toggle wrapping around when reaching the ribbon edges |
| `Super + Left Drag` | `dragdrop` | Drag window to reorder columns or drop into a stack |
| `Super + Right Drag` | `resizemouse` | Drag window edge to resize column width |
| `Super + Mouse Wheel` | `scrollwin` | Scroll ribbon horizontally |
| `Super + Trackpad Pan` | `trackscroll` | Smooth two-finger horizontal panning |

### Overview

| Shortcut | Function | Description |
| :--- | :--- | :--- |
| `Super + Tab` or `Super + o` | `toggleov` | Open or close the overview |
| `Return` | `zoomov` | Jump to selected window and tag |
| `Escape` or `q` | `toggleov` | Close overview and return to where you were |
| `Left / Right` or `h / l` | `focusovwin` | Move selection horizontally across windows |
| `Up / Down` or `k / j` | `focusovwin` | Move selection vertically inside a stack |
| `1 .. 9` | `ovjumptag` | Jump directly to tag 1 through 9 |
| `Mouse Wheel` | `ovscrollvert` | Scroll vertically through workspace layers |
| `Shift + Mouse Wheel` | `ovscrollribbon`| Scroll the ribbon of the hovered workspace |
| `Trackpad Pan` | `ovscrollribbon`| Smooth trackpad pan on workspace ribbon |
| `Super + Left Drag` | `dragdrop` | Drag a window card to another workspace or column |

