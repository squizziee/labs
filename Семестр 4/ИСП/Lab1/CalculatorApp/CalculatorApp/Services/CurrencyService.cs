using CalculatorApp.Entities;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace CalculatorApp.Services
{
    public class CurrencyService : ICurrencyService
    {
        private string[]? currencyIdList;
        private readonly HttpClient _httpClient;

        public CurrencyService(HttpClient httpClient)
        {
            _httpClient = httpClient;
        }

        private void LoadCurrencyIdListFromJson()
        {
            var baseFolder = AppDomain.CurrentDomain.BaseDirectory;
            var json = File.ReadAllText(baseFolder + "\\currency_id_list.json");
            currencyIdList = JsonConvert.DeserializeObject<string[]>(json);
        }

        public async Task<Currency> GetCurrency(string currencyId)
        {
            var response = await _httpClient.GetAsync($"{_httpClient.BaseAddress}/{currencyId}");
            return JsonConvert.DeserializeObject<Currency>(await response.Content.ReadAsStringAsync())!;
        }

        public async Task<List<Currency>> GetCurrencies()
        {
            if (currencyIdList == null)
            {
                LoadCurrencyIdListFromJson();
            }
            List<Currency> currencies = [];
            foreach (var currencyId in currencyIdList!)
            {
                var response = await _httpClient.GetAsync($"{_httpClient.BaseAddress}/{currencyId}");
                var currency = JsonConvert.DeserializeObject<Currency>(await response.Content.ReadAsStringAsync());
                currencies.Add(currency!);
            }
            currencies.Add(new Currency() { Cur_Abbreviation = "BYN", Cur_Name_Eng = "Belarussian Ruble"});
            return currencies;
        }
    }
}
