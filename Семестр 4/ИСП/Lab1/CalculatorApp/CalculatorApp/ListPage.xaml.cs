using CalculatorApp.Entities;
using CalculatorApp.Services;

namespace CalculatorApp;

public partial class ListPage : ContentPage
{
    private readonly IDBService databaseService;    
    public ListPage(IDBService dbService)
	{
        InitializeComponent();
        databaseService = dbService;
        FillPicker();
    }

    private void FillPicker()
    {
        IEnumerable<Project> projects = databaseService.GetAllProjects();
        groupPicker.ItemsSource = projects.Select(p => p.Name).ToList();
    }

    private void OnPickerSelectedIndexChanged(object sender, EventArgs e)
    {
        IEnumerable<Project> projects = databaseService.GetAllProjects();
        var currentProject = projects.FirstOrDefault(p => p.Name == groupPicker.SelectedItem.ToString());
        if (currentProject != null)
        {
            collectionView.ItemsSource  = databaseService.GetProjectObjectives(currentProject.Id);
        }
    }
}