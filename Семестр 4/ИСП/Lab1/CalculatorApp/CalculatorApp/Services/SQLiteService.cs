using CalculatorApp.Entities;
using SQLite;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalculatorApp.Services
{
	public class SQLiteService : IDBService
	{
		private static readonly string databasePath = "C:\\Users\\USER\\Desktop\\cstemp\\sqlite-orm\\ormfile.db ";
        SQLiteConnection? database;

        public SQLiteService()
        {
            Init();
        }

		private static Dictionary<Project, Objective[]> databaseContent = new() {
			{ new Project() {
				Name = "Project 1", 
				Description = "Description for Project 1",
				Version = "1.0.0",
				}, [
					new Objective() { Name = "Objective 1",  Description = "habitant morbi tristique senectus et", ProjectId = 1},
                    new Objective() { Name = "Objective 2",  Description = "accumsan tortor posuere ac ut ", ProjectId = 1},
                    new Objective() { Name = "Objective 3",  Description = "ipsum nunc", ProjectId = 1},
                    new Objective() { Name = "Objective 4",  Description = "scelerisque varius morbi ", ProjectId = 1},
                    new Objective() { Name = "Objective 5",  Description = "phasellus faucibus scelerisque", ProjectId = 1},
                    new Objective() { Name = "Objective 6",  Description = "sit amet cursus sit ", ProjectId = 1},
                    new Objective() { Name = "Objective 7",  Description = "amet dictum sit ", ProjectId = 1},
                    new Objective() { Name = "Objective 8",  Description = "amet justo donec e", ProjectId = 1}
               ]
			},
            { new Project() {
                Name = "Project 2",
                Description = "Description for Project 2",
                Version = "1.2.3",
                }, [
                    new Objective() { Name = "Objective 1",  Description = "consequat semper viverra nam ", ProjectId = 2},
                    new Objective() { Name = "Objective 2",  Description = "libero justo laoreet ", ProjectId = 2},
                    
               ]
            },
            { new Project() {
                Name = "Project 3",
                Description = "Description for Project 3",
                Version = "0.0.1 alpha",
                }, [
                    new Objective() { Name = "Objective 1",  Description = "enim diam vulputat", ProjectId = 3},
                    new Objective() { Name = "Objective 2",  Description = "enim nunc faucibus r", ProjectId = 3},
                    new Objective() { Name = "Objective 3",  Description = "a pellentesque sit amet porttito", ProjectId = 3},
                    new Objective() { Name = "Objective 4",  Description = "nulla pharetra diam", ProjectId = 3},
               ]
            },
             { new Project() {
                Name = "Project 4",
                Description = "Description for Project 4",
                Version = "9.9.9 amogus",
                }, [
                    new Objective() { Name = "Objective 1",  Description = "luctus accumsan tortor", ProjectId = 4},
                    new Objective() { Name = "Objective 2",  Description = "vel fringilla est", ProjectId = 4},
                    new Objective() { Name = "Objective 3",  Description = "neque convallis a", ProjectId = 4},
                    new Objective() { Name = "Objective 4",  Description = "mi eget mauris", ProjectId = 4},
                    new Objective() { Name = "Objective 5",  Description = "morbi leo urna", ProjectId = 4},
                    new Objective() { Name = "Objective 6",  Description = "sed risus pretium", ProjectId = 4}
               ]
            }
        };

		public void Init()
		{            
			database = new SQLiteConnection(databasePath);

			database.CreateTable<Project>();
            database.CreateTable<Objective>();

			if (database.Table<Project>().Count() == 0) { 
                foreach (var project in databaseContent.Keys)
                {
                    database.Insert(project);
                }
                foreach (var objectiveArr in databaseContent.Values)
                {
                    foreach (var objective in objectiveArr)
                    {
                        database.Insert(objective);
                    }
                }
            }          
		}
		public IEnumerable<Project> GetAllProjects()
		{
			return database!.Table<Project>().ToList();
		}

		public IEnumerable<Objective> GetProjectObjectives(int id)
		{
            return database!.Table<Objective>().Where(obj => obj.ProjectId == id).ToList();
        }
	}
}
