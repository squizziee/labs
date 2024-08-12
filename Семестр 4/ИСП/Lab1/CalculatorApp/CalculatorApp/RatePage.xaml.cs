using CalculatorApp.Entities;
using CalculatorApp.Services;
using static SQLite.SQLite3;

namespace CalculatorApp;

public partial class RatePage : ContentPage
{
	private readonly IRateService _rateService;
    private readonly ICurrencyService _currencyService;
    private IEnumerable<Rate>? rates;
    private IEnumerable<Currency>? currencies;
    private bool isFirstTime = true;

	public RatePage(IRateService rateService, ICurrencyService currencyService)
	{
		InitializeComponent();
		_rateService = rateService;
		_currencyService = currencyService;
		SetupDatePicker();
	}

	private void SetupDatePicker()
	{
		this.selectedDate.MaximumDate = DateTime.Today;
        this.selectedDate.MinimumDate = new DateTime(1980, 1, 1);
    }

	private void SetupCurrencyPickers()
	{
        this.selectedCurrencySource.ItemsSource = currencies!
			.Select(curr => curr.Cur_Name_Eng)
			.ToList();
		this.selectedCurrencySource.SelectedIndex = 0;
        this.selectedCurrencyDestination.ItemsSource = currencies!
            .Select(curr => curr.Cur_Name_Eng)
            .ToList();
		this.selectedCurrencyDestination.SelectedIndex = 1;
    }

	private async Task LoadCurrencyData()
	{
		currencies = await _currencyService.GetCurrencies();
	}

	private async Task LoadRateData()
	{
        rates = await _rateService.GetRates(this.selectedDate.Date);
		if (rates.Count() == 1)
		{
			SwitchUI(1);
		}
		else
		{
			SwitchUI(0);
		}
    }

	private void SwitchUI(int code)
	{
        if (code == 0)
        {
            this.selectedCurrencySource.IsEnabled = true;
            this.selectedCurrencyDestination.IsEnabled = true;
            this.sourceEntry.IsEnabled = true;
            this.destinationEntry.IsEnabled = true;
			this.convertBtn.IsEnabled = true;
        }
        else if (code == 1)
		{
			this.selectedCurrencySource.IsEnabled = false;
			this.selectedCurrencyDestination.IsEnabled = false;
			this.sourceEntry.IsEnabled = false;
			this.destinationEntry.IsEnabled = false;
			this.convertBtn.IsEnabled = false;
		}
	}

	private async void OnDateSelected(object sender, EventArgs e)
	{
        await LoadRateData();
        if (isFirstTime)
		{
            await LoadCurrencyData();
            SetupCurrencyPickers();
			isFirstTime = false;
        }
	}

    private void OnConvertBtnClicked(object sender, EventArgs e)
    {
        decimal value = 0;
		if (decimal.TryParse(this.sourceEntry.Text, out value))
		{
			var currencySource = rates!
				.FirstOrDefault(rate => rate.Cur_Abbreviation == rates!
				.ElementAt(this.selectedCurrencySource.SelectedIndex).Cur_Abbreviation);
            var currencyDestination = rates!
                .FirstOrDefault(rate => rate.Cur_Abbreviation == rates!
                .ElementAt(this.selectedCurrencyDestination.SelectedIndex).Cur_Abbreviation);
            var result = _rateService.ConvertCurrency(currencySource!, currencyDestination!, value);
			this.destinationEntry.Text = result.ToString("#.##");
        }
        else
		{
            this.destinationEntry.Text = "Wrong input format";
        }
    }
}