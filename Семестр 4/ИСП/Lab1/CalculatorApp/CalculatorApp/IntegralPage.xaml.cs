namespace CalculatorApp;

public partial class IntegralPage : ContentPage
{
	private CancellationTokenSource cts = new CancellationTokenSource();

	public IntegralPage()
	{
		InitializeComponent();
	}

	public async void OnClicked(object sender, EventArgs e)
	{
		var token = cts.Token;
		var text = ((Button)sender).Text;
		if (text == "Start")
		{
			this.progressBar.Progress = 0;
            this.infoText.Text = "Press 'Start' to proceed";
			this.CancelButton.IsEnabled = true;
			this.StartButton.IsEnabled = false;
			
			await StartCalculation(token);
			//this.infoText.Text = result.ToString();
        }
		else if(text == "Cancel")
		{
			StopCalculation();
            this.CancelButton.IsEnabled = false;
            this.StartButton.IsEnabled = true;
            cts.Dispose();
			cts = new CancellationTokenSource();
        }
    }

	private void StopCalculation()
	{
		cts.Cancel();
	}

	private async Task StartCalculation(CancellationToken token)
	{
        this.infoText.Text = "Calculating...";
        double result = 0;
		double step = 0.00000001;
        double progress = 0;
		int counter = 0;
		for (double i = 0; i <= 1; i += step)
		{
			if (token.IsCancellationRequested)
			{
                this.infoText.Text = "Canceled";
                return;
			}
			if (counter == 100000)
			{
				progress += step * 100000;
				await this.progressBar.ProgressTo(progress, 1, Easing.Linear);
				this.progressText.Text = (progress * 100).ToString("#.###") + "%";
				counter = 0;
			}
			counter++;
			result += step * Math.Sin(i);
		}
		this.progressText.Text = "100%";
		this.infoText.Text = result.ToString();
        this.CancelButton.IsEnabled = false;
        this.StartButton.IsEnabled = true;
        //return result;
    }
}