using CalculatorApp.Entities;

namespace CalculatorApp.Services
{
    public interface IDBService
    {
        void Init();
        IEnumerable<Project> GetAllProjects();
        IEnumerable<Objective> GetProjectObjectives(int id);
    }
}
