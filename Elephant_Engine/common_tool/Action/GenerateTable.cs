using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

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
        bool GenerateCode(string sourcePath, string outputPath)
        {
            string filePath = string.Empty;
            foreach (string fileName in fileEn)
        }
    }
}
