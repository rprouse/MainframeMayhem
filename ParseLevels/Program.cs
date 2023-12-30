using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace ParseLevels;

class Program
{
    const int WIDTH  = 20;
    const int HEIGHT = 18;
    const int LEVELS = 255;

    static Dictionary<char, byte> TileMap { get; } = CreateTileMap();
    static int Count { get; set; } = 0;

    static void Main(string[] args)
    {
        if (args.Length != 1 || !Directory.Exists(args[0]))
        {
            Console.WriteLine("Usage: ParseLevels <directory>");
            return;
        }

        WriteSource(args[0], LEVELS);
        WriteHeader();
    }

    private static void WriteSource(string dir, int levels)
    {
        using var source = new StreamWriter(@".\src\Levels.c");

        source.WriteLine("#pragma bank 2");
        source.WriteLine();
        source.WriteLine("#include \"levels.h\"");
        source.WriteLine();
        source.WriteLine("const uint8_t Levels[] = {");

        var files = Directory.GetFiles(dir, "*.txt");
        foreach (string filename in files)
        {
            if (!File.Exists(filename))
            {
                source.WriteLine($"// Level file {filename} not found");
                continue;
            }

            var pack = Path.GetFileNameWithoutExtension(filename);
            string name = null;
            List<string> puzzle = new List<string>();

            using TextReader input = new StreamReader(filename);

            try
            {
                string line = input.ReadLine();
                while (line != null && Count < levels)
                {
                    if (line.StartsWith(";"))
                    {
                        name = line.Substring(2);
                        puzzle.Clear();
                    }
                    else if (string.IsNullOrWhiteSpace(line))
                    {
                        if (puzzle.Count > 0)
                        {
                            ParsePuzzle(source, pack, name, puzzle);
                            puzzle.Clear();
                        }
                    }
                    else
                    {
                        puzzle.Add(line);
                    }
                    line = input.ReadLine();
                }

                if (puzzle.Count > 0 && Count < levels)
                {
                    ParsePuzzle(source, pack, name, puzzle);
                }
            }
            catch (Exception ex)
            {
                Console.Error.WriteLine($"Error processing file {filename}");
                Console.Error.WriteLine(ex);
            }
        }
        source.WriteLine("};");
    }

    private static void WriteHeader()
    {
        using var header = new StreamWriter(@".\include\Levels.h");
        header.WriteLine("#ifndef LEVELS_H");
        header.WriteLine("#define LEVELS_H");
        header.WriteLine();
        header.WriteLine("#include <stdint.h>");
        header.WriteLine();
        header.WriteLine($"#define NUM_LEVELS {Count}");
        header.WriteLine();
        header.WriteLine("extern const uint8_t Levels[];");
        header.WriteLine();
        header.WriteLine("#endif");
    }

    static void ParsePuzzle(TextWriter source, string pack, string name, List<string> puzzle)
    {
        byte[,] level = GetLevel(puzzle);
        if(level != null)
        {
            List<List<byte>> rle = RunLengthEncodeLevel(level);
            OutputLevel(source, pack, name, rle);
        }
    }

    /// <summary>Outputs one level to the console</summary
    static void OutputLevel(TextWriter source, string pack, string name, List<List<byte>> rle)
    {
        Console.WriteLine($"Level {++Count} from {pack} level {name}");
        source.WriteLine($"    // Level {Count} from {pack} level {name}");
        foreach(List<byte> row in rle)
        {
            source.Write("    ");
            foreach(byte b in row)
            {
                source.Write($"0x{b:X2},");
            }
            source.WriteLine();
        }
    }

    static byte[,] GetLevel(List<string> puzzle)
    {
        int width = longestLine(puzzle);
        int height = puzzle.Count;

        if(width > WIDTH || height > WIDTH)
            return null;

        if(width > HEIGHT && height > HEIGHT)
            return null;

        // Switch to landscape mode for the wide screen
        bool rotate = height > width;

        byte[,] level = new byte[HEIGHT,WIDTH];
        for(int row = 0; row < HEIGHT; row++)
        {
            for(int col = 0; col < WIDTH; col++)
            {
                level[row,col] = 0x00;  // FLOOR
            }
        }

        // Center the puzzles
        int r_off = rotate ? (HEIGHT - width) / 2 : (HEIGHT - height) / 2;
        int c_off = rotate ? (WIDTH - height) / 2 : (WIDTH - width) / 2;

        int r = 0;
        foreach(string row in puzzle)
        {
            for(int c = 0; c < row.Length; c++)
            {
                if(rotate)
                    level[c + r_off, r + c_off] = TileMap[row[c]];
                else
                    level[r + r_off, c + c_off] = TileMap[row[c]];
            }
            r++;
        }
        return level;
    }

    static List<List<byte>> RunLengthEncodeLevel(byte[,] level)
    {
        List<List<byte>> rle = new List<List<byte>>(8);

        for(int row = 0; row < HEIGHT; row++)
        {
            var list = new List<byte>();
            rle.Add(list);
            byte last = level[row, 0];
            byte count = 0; // Count is zero based
            for(int col = 1; col < WIDTH; col++)
            {
                if(level[row, col] != last)
                {
                    list.Add((byte)(((int)count << 3) | (int)last));
                    last = level[row, col];
                    count = 0;
                }
                else
                {
                    count++;
                }
            }
            list.Add((byte)(((int)count << 3) | (int)last));
        }
        byte byteCount = (byte)rle.Sum(row => row.Count());
        rle.Insert(0, new List<byte> { byteCount });
        return rle;
    }

    static int longestLine(IEnumerable<string> puzzle) =>
        puzzle.Max(s => s.Length);

    static Dictionary<char, byte> CreateTileMap() =>
        new Dictionary<char, byte>
        {
            {' ', 0x00},    // FLOOR
            {'#', 0x01},    // WALL
            {'.', 0x02},    // GOAL
            {'$', 0x03},    // BOX
            {'*', 0x04},    // BOX_ON_GOAL
            {'@', 0x05},    // PLAYER
            {'+', 0x06},    // PLAYER_ON_GOAL
        };
}
