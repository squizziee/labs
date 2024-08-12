using _253504Lianha.UI.ViewModels;

namespace _253504Lianha.UI.Pages;

public partial class AddAdvertisement : ContentPage
{
	public AddAdvertisement(AddAdvertisementViewModel addAdvertisementViewModel)
	{
		InitializeComponent();

		BindingContext = addAdvertisementViewModel;
	}
}