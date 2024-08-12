using CalculatorApp.Services;
using Microsoft.Extensions.Logging;
using Microsoft.Maui.LifecycleEvents;
using Microsoft.Maui.Platform;

namespace CalculatorApp
{
    public static class MauiProgram
    {
        public static MauiApp CreateMauiApp()
        {
            var builder = MauiApp.CreateBuilder();
            builder
                .UseMauiApp<App>()
                .ConfigureFonts(fonts =>
                {
                    fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
                    fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
                });
            builder.Services.AddSingleton<IDBService, SQLiteService>();
            builder.Services.AddTransient<ListPage>();
            builder.Services.AddHttpClient<IRateService, RateService>(opt => 
                opt.BaseAddress = new Uri("https://www.nbrb.by/api/exrates/rates"));
            builder.Services.AddHttpClient<ICurrencyService, CurrencyService>(opt => 
            opt.BaseAddress = new Uri("https://api.nbrb.by/exrates/currencies"));
            builder.Services.AddTransient<RatePage>();
#if WINDOWS
            builder.ConfigureLifecycleEvents(events =>
            {
                events.AddWindows(lfcBuilder =>
                {
                    lfcBuilder.OnWindowCreated(window =>
                    {
                        IWindow window1 = new Window() { 
                            MaximumWidth = 400, 
                            MaximumHeight = 600, 
                            MinimumHeight = 600, 
                            MinimumWidth = 400 
                        };
                        window.UpdateMinimumSize(window1);
                        window.UpdateMaximumSize(window1);
                    });
                });
            });
#endif

#if DEBUG
            builder.Logging.AddDebug();
#endif

            return builder.Build();
        }
    }
}
