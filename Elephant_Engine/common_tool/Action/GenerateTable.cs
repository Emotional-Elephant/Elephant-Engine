using System;
using System.Collections.Generic;
using System.IO;

namespace CommonTool.Action
{
    public class GenerateTable : ActionBase
    {
        public GenerateTable(Parameter param) : base(param)
        {
        }

        public override void Run()
        {
            if (_param.DicActionParam.ContainsKey("--target-path") == false)
            {
                throw new Exception($"not found parameter - \"--target-path\"");
            }

            // 테이블 클래스 코드 생성
            string outputPath = Directory.GetCurrentDirectory();
            string targetPath = _param.DicActionParam["--target-path"];
            if (_param.DicActionParam.ContainsKey("--output") == true)
            {
                outputPath = new DirectoryInfo(_param.DicActionParam["--output"]).FullName;
            }

            if (GenerateCode(targetPath, outputPath) == false)
            {
                throw new Exception($"failed to generate files. path: {outputPath}");
            }
            Console.WriteLine($"Generate table. target: {targetPath}, output: {outputPath}");
        }

        // 코드 생성
        private bool GenerateCode(string sourcePath, string outputPath)
        {
            string filePath = string.Empty;
            try
            {
                string[] fileEntries = Directory.GetFiles(sourcePath);
                foreach (string fileName in fileEntries)
                {
                    FileInfo fi = new FileInfo(fileName);
                    string title = fi.Name.Substring(0, fi.Name.IndexOf("."));
                    filePath = fileName;
                    if (fi.Extension != ".csv")
                    {
                        continue;
                    }

                    List<Column> cols = new List<Column>();
                    List<KeyValuePair<string, int>> enumKeys = new List<KeyValuePair<string, int>>();
                    using (var reader = new StreamReader(fi.FullName))
                    {
                        int row = 0;
                        while (!reader.EndOfStream)
                        {
                            var line = reader.ReadLine();
                            List<string> words = new List<string>(line.Split(','));
                            if (row == 0)
                            {
                                for (var i = 0; i < words.Count; i++)
                                {
                                    cols.Add(new Column { Name = words[i] });
                                }
                            }
                            else if (row == 1)
                            {
                                for (var i = 0; i < words.Count; i++)
                                {
                                    cols[i].Type = words[i];
                                }
                            }
                            row++;
                        }
                    }

                    if (Directory.Exists(outputPath) == false)
                    {
                        Directory.CreateDirectory(outputPath);
                    }

                    using (var streamWriter = new StreamWriter($"{outputPath}/{title}.h"))
                    {
                        streamWriter.WriteLine("#include <string>");
                        streamWriter.WriteLine("#include <unordered_map>");
                        streamWriter.WriteLine("#include <vector>");
                        streamWriter
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine($"Error GenerateCode. filePath: {filePath}");
                return false;
            }
            return true;
        }
    }
}