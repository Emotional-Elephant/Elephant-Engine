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
                        streamWriter.WriteLine("#include <ctime>");
                        streamWriter.WriteLine("#include <string>");
                        streamWriter.WriteLine("#include <unordered_map>");
                        streamWriter.WriteLine("#include <vector>");
                        streamWriter.WriteLine();
                        streamWriter.WriteLine("#include \"TableDataInterface.h\"");
                        streamWriter.WriteLine();
                        streamWriter.WriteLine($"class {title} : public TableDataInterface");
                        streamWriter.WriteLine("{");
                        streamWriter.WriteLine("public:");
                        for (int i = 0; i < cols.Count; ++i)
                        {
                            if (cols[i].Name.StartsWith("~") == true)
                            {
                                continue;
                            }

                            if (cols[i].Type.ToLower() == "array_bool")
                            {
                                streamWriter.WriteLine($"\tstd::vector<bool> {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "array_short")
                            {
                                streamWriter.WriteLine($"\tstd::vector<short> {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "array_ushort")
                            {
                                streamWriter.WriteLine($"\tstd::vector<unsigned short> {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "array_int")
                            {
                                streamWriter.WriteLine($"\tstd::vector<int> {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "array_uint")
                            {
                                streamWriter.WriteLine($"\tstd::vector<unsigned int> {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "array_float")
                            {
                                streamWriter.WriteLine($"\tstd::vector<float> {cols[i].Name};");
                            }
                            else if(cols[i].Type.ToLower() == "array_double")
                            {
                                streamWriter.WriteLine($"\tstd::vector<double> {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "array_time")
                            {
                                streamWriter.WriteLine($"\tstd::vector<std::tm> {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "array_sbyte")
                            {
                                streamWriter.WriteLine($"\tstd::vector<char> {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "array_byte")
                            {
                                streamWriter.WriteLine($"\tstd::vector<unsigned char> {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "array_string")
                            {
                                streamWriter.WriteLine($"\tstd::vector<std::string> {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "bool")
                            {
                                streamWriter.WriteLine($"\tbool {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "short")
                            {
                                streamWriter.WriteLine($"\tshort {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "ushort")
                            {
                                streamWriter.WriteLine($"\tunsigned short {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "int")
                            {
                                streamWriter.WriteLine($"\tint {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "uint")
                            {
                                streamWriter.WriteLine($"\tunsigned int {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "float")
                            {
                                streamWriter.WriteLine($"\tfloat {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "double")
                            {
                                streamWriter.WriteLine($"\tdouble {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "time")
                            {
                                streamWriter.WriteLine($"\tstd::tm {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "sbyte")
                            {
                                streamWriter.WriteLine($"\tchar {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "byte")
                            {
                                streamWriter.WriteLine($"\tunsigned char {cols[i].Name};");
                            }
                            else if (cols[i].Type.ToLower() == "string")
                            {
                                streamWriter.WriteLine($"\tstd::string {cols[i].Name};");
                            }
                        }
                        streamWriter.WriteLine();
                        streamWriter.WriteLine("public:");
                        streamWriter.WriteLine("\tvirtual void Serialize(std::unordered_map<std::string, std::string>& data);");
                        streamWriter.WriteLine("\tstatic class init_");
                        streamWriter.WriteLine("\t{");
                        streamWriter.WriteLine("\tpublic:");
                        streamWriter.WriteLine("\t\tinit_();");
                        streamWriter.WriteLine("\t} _initializer;");
                        streamWriter.WriteLine("};");
                    }
                    using (var streamWriter = new StreamWriter($"{outputPath}/{title}.cpp"))
                    {
                        streamWriter.WriteLine($"#include \"{title}.h\"");
                        streamWriter.WriteLine("#include \"TableManager.h\"");
                        streamWriter.WriteLine("#include \"DataTable.h\"");
                        streamWriter.WriteLine("#include \"Utils.h\"");
                        streamWriter.WriteLine();
                        streamWriter.WriteLine($"{title}::init_ {title}::_initializer;");
                        streamWriter.WriteLine();
                        streamWriter.WriteLine($"{title}::init_::init_()");
                        streamWriter.WriteLine("{");
                        streamWriter.WriteLine($"\tDataTable<int, {title}>::GetInstance().set_name(\"{title}\");");
                        streamWriter.WriteLine($"\tTableManager::GetInstance().Add(&DataTable<int, {title}>::GetInstance());");
                        streamWriter.WriteLine("}");
                        streamWriter.WriteLine();
                        streamWriter.WriteLine($"void {title}::Serialize(std::unordered_map<std::string, std::string>& data)");
                        streamWriter.WriteLine("{");
                        int row = 0;
                        for (int i = 0; i < cols.Count; ++i)
                        {
                            if (cols[i].Name.StartsWith("~") == true)
                            {
                                continue;
                            }

                            if (row == 0)
                            {
                                streamWriter.Write("\tauto iter = ");
                            }
                            else
                            {
                                streamWriter.Write("\titer = ");
                            }
                            ++row;

                            streamWriter.WriteLine($"data.find(\"{cols[i].Name}\");");
                            streamWriter.WriteLine("\tif (iter != data.end())");
                            streamWriter.WriteLine("\t{");
                            if (cols[i].Type.ToLower() == "array_bool")
                            {
                                streamWriter.WriteLine("\t\tstd::vector<std::string> result = Split(iter->second, '|');");
                                streamWriter.WriteLine("\t\tfor (auto& data : result)");
                                streamWriter.WriteLine("\t\t{");
                                streamWriter.WriteLine($"\t\t\t{cols[i].Name}.push_back(Lexical_cast_boolean(data));");
                                streamWriter.WriteLine("\t\t}");

                            }
                            else if (cols[i].Type.ToLower() == "array_short")
                            {
                                streamWriter.WriteLine("\t\tstd::vector<std::string> result = Split(iter->second, '|');");
                                streamWriter.WriteLine("\t\tfor (auto& data : result)");
                                streamWriter.WriteLine("\t\t{");
                                streamWriter.WriteLine($"\t\t\t{cols[i].Name}.push_back(Lexical_cast<short>(data));");
                                streamWriter.WriteLine("\t\t}");
                            }
                            else if (cols[i].Type.ToLower() == "array_ushort")
                            {
                                streamWriter.WriteLine("\t\tstd::vector<std::string> result = Split(iter->second, '|');");
                                streamWriter.WriteLine("\t\tfor (auto& data : result)");
                                streamWriter.WriteLine("\t\t{");
                                streamWriter.WriteLine($"\t\t\t{cols[i].Name}.push_back(Lexical_cast<unsigned short>(data));");
                                streamWriter.WriteLine("\t\t}");
                            }
                            else if (cols[i].Type.ToLower() == "array_int")
                            {
                                streamWriter.WriteLine("\t\tstd::vector<std::string> result = Split(iter->second, '|');");
                                streamWriter.WriteLine("\t\tfor (auto& data : result)");
                                streamWriter.WriteLine("\t\t{");
                                streamWriter.WriteLine($"\t\t\t{cols[i].Name}.push_back(Lexical_cast<int>(data));");
                                streamWriter.WriteLine("\t\t}");
                            }
                            else if (cols[i].Type.ToLower() == "array_uint")
                            {
                                streamWriter.WriteLine("\t\tstd::vector<std::string> result = Split(iter->second, '|');");
                                streamWriter.WriteLine("\t\tfor (auto& data : result)");
                                streamWriter.WriteLine("\t\t{");
                                streamWriter.WriteLine($"\t\t\t{cols[i].Name}.push_back(Lexical_cast<unsigned int>(data));");
                                streamWriter.WriteLine("\t\t}");
                            }
                            else if (cols[i].Type.ToLower() == "array_float")
                            {
                                streamWriter.WriteLine("\t\tstd::vector<std::string> result = Split(iter->second, '|');");
                                streamWriter.WriteLine("\t\tfor (auto& data : result)");
                                streamWriter.WriteLine("\t\t{");
                                streamWriter.WriteLine($"\t\t\t{cols[i].Name}.push_back(Lexical_cast<float>(data));");
                                streamWriter.WriteLine("\t\t}");
                            }
                            else if (cols[i].Type.ToLower() == "array_double")
                            {
                                streamWriter.WriteLine("\t\tstd::vector<std::string> result = Split(iter->second, '|');");
                                streamWriter.WriteLine("\t\tfor (auto& data : result)");
                                streamWriter.WriteLine("\t\t{");
                                streamWriter.WriteLine($"\t\t\t{cols[i].Name}.push_back(Lexical_cast<double>(data));");
                                streamWriter.WriteLine("\t\t}");
                            }
                            else if (cols[i].Type.ToLower() == "array_time")
                            {
                                streamWriter.WriteLine("\t\tstd::vector<std::string> result = Split(iter->second, '|');");
                                streamWriter.WriteLine("\t\tfor (auto& data : result)");
                                streamWriter.WriteLine("\t\t{");
                                streamWriter.WriteLine($"\t\t\t{cols[i].Name}.push_back(StringTotm(data));");
                                streamWriter.WriteLine("\t\t}");
                            }
                            else if (cols[i].Type.ToLower() == "array_sbyte")
                            {
                                streamWriter.WriteLine("\t\tstd::vector<std::string> result = Split(iter->second, '|');");
                                streamWriter.WriteLine("\t\tfor (auto& data : result)");
                                streamWriter.WriteLine("\t\t{");
                                streamWriter.WriteLine($"\t\t\t{cols[i].Name}.push_back(Lexical_cast<char>(data));");
                                streamWriter.WriteLine("\t\t}");
                            }
                            else if (cols[i].Type.ToLower() == "array_byte")
                            {
                                streamWriter.WriteLine("\t\tstd::vector<std::string> result = Split(iter->second, '|');");
                                streamWriter.WriteLine("\t\tfor (auto& data : result)");
                                streamWriter.WriteLine("\t\t{");
                                streamWriter.WriteLine($"\t\t\t{cols[i].Name}.push_back(Lexical_cast<unsigned char>(data));");
                                streamWriter.WriteLine("\t\t}");
                            }
                            else if (cols[i].Type.ToLower() == "array_string")
                            {
                                streamWriter.WriteLine("\t\tstd::vector<std::string> result = Split(iter->second, '|');");
                                streamWriter.WriteLine("\t\tfor (auto& data : result)");
                                streamWriter.WriteLine("\t\t{");
                                streamWriter.WriteLine($"\t\t\t{cols[i].Name}.push_back(data);");
                                streamWriter.WriteLine("\t\t}");
                            }
                            else if (cols[i].Type.ToLower() == "bool")
                            {
                                streamWriter.WriteLine($"\t\t{cols[i].Name} = Lexical_cast_boolean(iter->second);");
                            }
                            else if (cols[i].Type.ToLower() == "short")
                            {
                                streamWriter.WriteLine($"\t\t{cols[i].Name} = Lexical_cast<short>(iter->second);");
                            }
                            else if (cols[i].Type.ToLower() == "ushort")
                            {
                                streamWriter.WriteLine($"\t\t{cols[i].Name} = Lexical_cast<unsigned short>(iter->second);");
                            }
                            else if (cols[i].Type.ToLower() == "int")
                            {
                                streamWriter.WriteLine($"\t\t{cols[i].Name} = Lexical_cast<int>(iter->second);");
                            }
                            else if (cols[i].Type.ToLower() == "uint")
                            {
                                streamWriter.WriteLine($"\t\t{cols[i].Name} = Lexical_cast<unsigned int>(iter->second);");
                            }
                            else if (cols[i].Type.ToLower() == "float")
                            {
                                streamWriter.WriteLine($"\t\t{cols[i].Name} = Lexical_cast<float>(iter->second);");
                            }
                            else if (cols[i].Type.ToLower() == "double")
                            {
                                streamWriter.WriteLine($"\t\t{cols[i].Name} = Lexical_cast<double>(iter->second);");
                            }
                            else if (cols[i].Type.ToLower() == "time")
                            {
                                streamWriter.WriteLine($"\t\t{cols[i].Name} = StringTotm(iter->second);");
                            }
                            else if (cols[i].Type.ToLower() == "sbyte")
                            {
                                streamWriter.WriteLine($"\t\t{cols[i].Name} = Lexical_cast<char>(iter->second);");
                            }
                            else if (cols[i].Type.ToLower() == "byte")
                            {
                                streamWriter.WriteLine($"\t\t{cols[i].Name} = Lexical_cast<unsigned char>(iter->second);");
                            }
                            else if (cols[i].Type.ToLower() == "string")
                            {
                                streamWriter.WriteLine($"\t\t{cols[i].Name} = iter->second;");
                            }
                            streamWriter.WriteLine("\t}");
                        }
                        streamWriter.WriteLine("}");
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