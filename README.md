# Mainframe Mayhem

## Requirements

1. [GDBK 2020](https://github.com/gbdk-2020/gbdk-2020) SDK. See the [Docs](https://gbdk-2020.github.io/gbdk-2020/docs/api/docs_releases.html).
2. [Make](https://gnuwin32.sourceforge.net/packages/make.htm) for Windows in the path.
3. [.NET 7](https://dotnet.microsoft.com/) to parse the level files.

## Parselevels

This .NET program takes levels in a simple TXT format and converts them
to C code to add into the `levels.h` file. The level files are in the `res\levels`
directory.

This program looks at each level and skips levels that are bigger than 18x20 squares.
If a level is taller than it is wide, it rotates the level to fit better on the
Gameboy screen. It then centers the level if it is smaller than 18x20.

Lastly, it compresses the levels using a simple run length encoding (RLE) format
inspired by the the Sokoban XSB format, but modified to take fewer bytes of memory
on the Gameboy.

Running the batch file `Generatelevels.cmd` will regenerate the levels.

## Credits

The game uses levels created by [David W. Skinner](http://www.abelmartin.com/rj/sokobanJS/Skinner/David%20W.%20Skinner%20-%20Sokoban.htm)
and Yoshio Murase. This game is under the [MIT License](LICENSE).
