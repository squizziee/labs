using _253504Lianha.UI.ViewModels;

namespace _253504Lianha.UI.Pages;

public partial class CarsList : ContentPage
{
	public CarsList(CarsListViewModel carsListViewModel)
	{
		InitializeComponent();

		BindingContext = carsListViewModel;
	}
}