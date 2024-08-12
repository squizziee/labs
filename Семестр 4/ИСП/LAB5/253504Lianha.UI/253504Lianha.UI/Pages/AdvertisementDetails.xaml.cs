using _253504Lianha.UI.ViewModels;

namespace _253504Lianha.UI.Pages;

public partial class AdvertisementDetails : ContentPage
{
	public AdvertisementDetails(AdvertisementDetailsViewModel advertisementDetailsViewModel)
	{
		InitializeComponent();

		BindingContext = advertisementDetailsViewModel;
	}
}