using _253504Lianha.UI.ViewModels;

namespace _253504Lianha.UI.Pages;

public partial class EditAdvertisement : ContentPage
{
	public EditAdvertisement(EditAdvertisementViewModel editAdvertisementViewModel)
	{
		InitializeComponent();

		BindingContext = editAdvertisementViewModel;
	}
}