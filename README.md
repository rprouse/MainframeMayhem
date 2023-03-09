# Mainframe Mayhem

## Requirements

1. [GDBK 2020](https://github.com/gbdk-2020/gbdk-2020) SDK. See the [Docs](https://gbdk-2020.github.io/gbdk-2020/docs/api/docs_releases.html).
2. [Make](https://gnuwin32.sourceforge.net/packages/make.htm) for Windows in the path.

## Parselevels

This .NET Core program takes levels in a simple TXT format and converts them
to C code to add into the `levels.h` file. The level files are in the `assets\levels`
directory.

This program looks at each level and skips levels that are bigger than 18x20 squares.
If a level is taller than it is wide, it rotates the level to fit better on the
Gameboy screen. It then centers the level if it is smaller than 18x20.

Lastly, it compresses the levels using a simple run length encoding (RLE) format
inspired by the the Sokoban XSB format, but modified to take fewer bytes of memory
on the Gameboy.

You must have .NET 7 installed. The utility is run using the batch file;

```cmd
GenerateLevels.cmd
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
