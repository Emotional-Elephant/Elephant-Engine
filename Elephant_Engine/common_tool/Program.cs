using System;
using System.Collections.Generic;
using CommonTool.Action;

namespace CommonTool
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Parameter param = new Parameter(args);
                Console.WriteLine($"[gamebase] startup gamebase tool");
                Console.WriteLine($"[gamebase] version : v1.0.8");
                Console.WriteLine($"[gamebase] args : {string.Join(" ", args)}");

                Dictionary<string, ActionBase> dicAction = new Dictionary<string, ActionBase>
                {
                    {"gen:table", new GenerateTable(param)}
                };
            }
            catch (Exception ex)
            {
                throw;
            }
        }
    }
}
