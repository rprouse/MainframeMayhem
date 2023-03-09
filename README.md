# Mainframe Mayhem

## Requirements

1. [GDBK 2020](https://github.com/gbdk-2020/gbdk-2020) SDK. See the [Docs](https://gbdk-2020.github.io/gbdk-2020/docs/api/docs_releases.html).
2. [Make](https://gnuwin32.sourceforge.net/packages/make.htm) for Windows in the path.

## Parselevels

This .NET Core program takes levels in a simple TXT format and converts them
to C code to add into the `levels.h` file. The level files are in the `assets\levels`
directory.

This program looks at each level and skips levels that are bigger than 16x8 squares.
If a level is taller than it is wide, it rotates the level to fit better on the
Arduboy screen. It then centers the level if it is smaller than 16x8.

Lastly, it compresses the levels using a simple run length encoding (RLE) format
inspired by the the Sokoban XSB format, but modified to take fewer bytes of memory
on the Arduboy. As of this writing, I've managed to load 295 levels and use 89%
of memory. I will probably want to reduce that to around 255 levels to make room
for more bitmaps.

You must have .NET Core 2.1 installed. The utility is run with a command like the following;

```
dotnet run -- 'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Microban.txt' 'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Microban II.txt'  'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Microban III.txt' 'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Microban IV.txt' 'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Sasquatch.txt'  'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Sasquatch II.txt'  'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Sasquatch III.txt'  'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Sasquatch IV.txt'  'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Sasquatch V.txt'  'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Sasquatch VI.txt'  'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Sasquatch VII.txt'  'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Sasquatch VIII.txt'  'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Sasquatch IX.txt'  'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Sasquatch X.txt'  'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\Sasquatch XI.txt'  'C:\Src\Retro\GameBoy\MainframeMayhem\res\levels\YoshioMurase.txt' > C:\src\Arduino\Arduboy\Arduban\Arduban\levels.h
```

To make this easier, running the batch file `Generatelevels.cmd` will regenerate
the levels.

## Credits

The game uses levels created by [David W. Skinner](http://www.abelmartin.com/rj/sokobanJS/Skinner/David%20W.%20Skinner%20-%20Sokoban.htm)
and Yoshio Murase. This game makes use of the [4x6 Font by Filmote](https://github.com/filmote/Font4x6) which is under the
BSD-3 license. This game is under the [MIT License](LICENSE).

Thanks to [@Pharap](https://community.arduboy.com/u/Pharap) and
[@Mr.Blinky](https://community.arduboy.com/u/Mr.Blinky) from the
[Arduboy Community](https://community.arduboy.com/) for memory reduction ideas
and help.
