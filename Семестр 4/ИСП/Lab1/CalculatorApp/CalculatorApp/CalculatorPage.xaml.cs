using static System.Net.Mime.MediaTypeNames;

namespace CalculatorApp;

public partial class CalculatorPage : ContentPage
{
	private double left, right;

	// 0 - left operand input
	// 1 - operator selected

	private int state = 0;
	private String operation = "";
	private bool erased = false;

	public CalculatorPage()
	{
		InitializeComponent();
		
	}

	public void OnClicked(object sender, EventArgs e)
	{
		Button btn = (Button)sender;
		String text = btn.Text;

		if (!double.TryParse(this.result.Text, out _))
		{
			this.result.Text = "0";
			return;
		}

		if (text == "sqr(x)")
		{
			left = double.Parse(this.result.Text);
			this.result.Text = (left * left).ToString();
            DisplayUnaryOperation("sqr");
            return;
		}

        if (text == "sqrt(x)")
        {
            left = double.Parse(this.result.Text);
			if (left < 0)
			{
				this.result.Text = "0";
				return;
			}
            this.result.Text = Math.Sqrt(left).ToString();
            DisplayUnaryOperation("sqrt");
            return;
        }

        if (text == "1/x")
        {
            left = double.Parse(this.result.Text);
            if (left == 0)
			{
				this.result.Text = "0";
			}
            this.result.Text = (1.0 / left).ToString();
            DisplayUnaryOperation("1/x");
            return;
        }

        if (text == "C" || text == "CE")
        {
			left = 0;
			right = 0;
            this.result.Text = "0";
			ClearOperations();
            return;
        }

		if (text == "sin(x)")
		{
			left = double.Parse(this.result.Text);
			double radians = left * Math.PI / 180;
			this.result.Text = Math.Sin(radians).ToString();
			DisplayUnaryOperation("sin");
			return;
		}

        if (state == 1 && !erased && !("+*/-".Contains(text)))
		{
            this.result.Text = "";
			erased = true;
        }

		if (this.result.Text == "0" && !("+*/=-".Contains(text)))
		{
			this.result.Text = "";
		}

        if (int.TryParse(text, out _))
        {
            HandleNumberSelection(text);
        }
        else if (text == ",")
        {
            HandleDot();
        }
        else if ("+/-*".Contains(text))
		{
			HandleOperation(text);
		}
		else if (text == "=")
		{
			HandleEquals(false);
		}
		else if (text == "%" && state == 1)
		{
			right = left * (double.Parse(this.result.Text) / 100.0);
			this.result.Text = right.ToString();
		}
		else if(text == "BSP")
		{
			HandleBackspace();
		}
    }

	private void HandleBackspace()
	{
		if (result.Text.Length <= 1 || 
			result.Text == "0" || 
			(result.Text.Length == 2 && result.Text[0] == '-')) {
			result.Text = "0";
			return;
		}
        this.result.Text = this.result.Text.Remove(this.result.Text.Length - 1);
    }

	private void HandleDot()
	{
		if (this.result.Text.Contains(','))
		{
			return;
		}
        this.result.Text += ",";
    }

	private void HandleNumberSelection(String text)
	{
		this.result.Text += text;
    }

	private void HandleOperation(String operation)
	{
        if (state == 1)
		{
			HandleEquals(true);
            this.operation = operation;
            return;
		}
        this.operation = operation;
        state = 1;
		left = double.Parse(this.result.Text);
	}

	private void HandleEquals(bool activatedByOperation)
	{
		if (state != 1) return;

		right = double.Parse(this.result.Text);

		double result = 0;
        switch (operation)
		{
			case "+": result = right + left; break;
			case "-": result = left - right; break;
			case "*": result = left * right; break;
			case "/": result = left / right; break;
		}
		if (!activatedByOperation) {
			DisplayEquals(operation);
            left = result;
        }
		else {
            left = result;
            DisplayOperation(operation); 
		}
		right = 0;
		state = activatedByOperation ? 1 : 0;
		erased = false;
		operation = "";
		this.result.Text = left.ToString();
	}

	private void ClearOperations()
	{
		this.operations.Text = "";
	}

    private void DisplayEquals(String operation)
    {
        this.operations.Text = $"{left} {operation} {right} = ";
    }
	
	private void DisplayUnaryOperation(String operation)
	{
		this.operations.Text = $"{operation}({left})";
	}

    private void DisplayOperation(String operation) {
		this.operations.Text = $"{left} {operation} ";
	}
}