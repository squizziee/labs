using _253504Lianha.UI.Pages;

namespace _253504Lianha.UI
{
    public partial class AppShell : Shell
    {
        public AppShell()
        {
            InitializeComponent();

            Routing.RegisterRoute(nameof(AdvertisementDetails), typeof(AdvertisementDetails));
            Routing.RegisterRoute(nameof(AddCar), typeof(AddCar));
            Routing.RegisterRoute(nameof(CarsList), typeof(CarsList));
            Routing.RegisterRoute(nameof(AddAdvertisement), typeof(AddAdvertisement));
            Routing.RegisterRoute(nameof(EditAdvertisement), typeof(EditAdvertisement));
        }
    }
}
