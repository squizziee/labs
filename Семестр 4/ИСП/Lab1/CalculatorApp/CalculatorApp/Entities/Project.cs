using SQLite;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalculatorApp.Entities
{
    [Table("Projects")]
    public class Project
    {
        [PrimaryKey, AutoIncrement, Indexed]
        public int Id { get; set; }
        public string? Name { get; set; }
        public string? Description { get; set; }
        public string? Version { get; set; }
    }

    [Table("Objectives")]
    public class Objective
    {
        [PrimaryKey, AutoIncrement, Indexed]
        public int Id { get; set; }
        public string? Name { get; set; }
        public string? Description { get; set; }
        [Indexed]
        public int ProjectId { get; set; }
    }
}
