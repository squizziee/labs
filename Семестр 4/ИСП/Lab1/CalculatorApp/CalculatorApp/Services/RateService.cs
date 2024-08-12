using CalculatorApp.Entities;
using Newtonsoft.Json;
using System.Runtime.Versioning;
using System.Text.Json.Serialization;

namespace CalculatorApp.Services
{
    class RateService : IRateService {

        private string[]? currencyIdList;

        private HttpClient _httpClient;
        public RateService(HttpClient httpClient) {
            _httpClient = httpClient;   
        }

        private void LoadCurrencyIdListFromJson()
        {
            var baseFolder = AppDomain.CurrentDomain.BaseDirectory;           
            var json = File.ReadAllText(baseFolder + "\\currency_id_list.json");
            currencyIdList = JsonConvert.DeserializeObject<string[]>(json);
        }

        public async Task<IEnumerable<Rate>> GetRates(DateTime date)
        {
            if (currencyIdList == null)
            {
                LoadCurrencyIdListFromJson();
            }
            List<Rate> rates = [];
            foreach (var currencyId in currencyIdList!)
            {
                var response = await _httpClient.GetAsync($"{_httpClient.BaseAddress}/{currencyId}?ondate={date:yyyy-MM-dd}");
                var rate = await System.Text.Json.JsonSerializer.DeserializeAsync<Rate>(await response.Content.ReadAsStreamAsync());// .ReadAsStringAsync());
                if (rate!.Cur_Name != null) 
                {
                    rates.Add(rate!);
                }              
            }
            rates.Add(new Rate() { Cur_Abbreviation = "BYN", Cur_OfficialRate = 1, Cur_Scale = 1 });
            return rates;
        }

        public decimal ConvertCurrency(Rate source, Rate destination, decimal sum)
        {
            decimal temp = (decimal)(sum * source.Cur_OfficialRate / source.Cur_Scale)!;
            return temp * destination.Cur_Scale / (decimal)((destination.Cur_OfficialRate))!;
        }
    }
}
