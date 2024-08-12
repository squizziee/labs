using _253504Lianha.UI.ViewModels;

namespace _253504Lianha.UI.Pages;

public partial class AddCar : ContentPage
{
	public AddCar(AddCarViewModel addCarViewModel)
	{
		InitializeComponent();

		BindingContext = addCarViewModel;
	}
}