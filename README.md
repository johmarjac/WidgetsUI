# WidgetsUI
The simplest GUI library for internal cheats.

# Features
* Menu
* Button
* TabControl
* ToggleText (CheckBox but with configurable On Off Text)
* Slider (Like a Volume TrackBar e.g. for adjusting ESP Distance)

# Giphy
![](https://i.imgur.com/181YcAl.gif)

# How to use
* Add `WidgetsUI.lib` to your linker.
* Include `WidgetsUI.hpp` in your project.
* Create a class inheriting from the `ICanvas` interface and implement your drawing functions.
* Create your menu like so:

```cpp
Menu * menu = new Menu();
menu->Position = WVector2(5, 5);
menu->Size = WVector2(400, 200);
menu->Title = L"MyCheat";
```
// This would create a menu at position `X=5; Y=5;` with a size of `Width=400; Height=200;` and title `MyCheat`.
* Hook WndProc of the game and in the detour function call `menu->WndProc(...);` to make the menu interactive.
* In your cheats `Update()` loop call `menu->Update();` allthough I think the current code does not rely on the function.
* In your cheats `Render()` loop call `menu->Draw(..);` and pass your canvas class deriving from `ICanvas` as parameter.

# Adding Widgets
There is not much widgets yet, however if you want to add a widget to the menu, call `menu->AddWidget(...);` and pass the widget.
Creating a Button widget looks like that:
```cpp
Button * pSuicide = new Button(menu, OnSuicide_Click, L"Suicide");
pSuicide->Size = WVector2( 80, 25 );

menu->AddWidget(pSuicide);

...
void OnSuicide_Click()
{
  // Execute Suicide here.
}
```
Notice the Button's constructor gets the parent widget's pointer (the menu), a function pointer to a function returning `void` and accepting `void` as a parameter (that should get executed when pressing the button), and the text the Button should display.
And notice the Button being added to the menu using `menu->AddWidget(pSuicide);`.

Every single widget, the Button, the Slider, even the Menu are classes inheriting from the `Widget` class.
Therefore theoretically every Widget would be able to have Child Widgets. The Menu for example makes use of Child Widgets.

Every Widget gets the parent widget reference to be able to know where its relative Draw area takes place. For further information just look at the `Widget` class.
Its not that hard to understand.
